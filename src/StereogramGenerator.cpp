#include "StereogramGenerator.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

StereogramGenerator::StereogramGenerator( cv::Mat heightmap, cv::Size outputSize )
{

    _output = cv::Mat( outputSize, CV_8UC3 );
    CV_Assert( heightmap.depth() == CV_8UC1 );
	cv::resize( heightmap, _heightmap, outputSize, 0, 0, cv::INTER_LINEAR);
	NormalizeDepth();

	_xppcm = 28;
	_yppcm = 28;
	_eyeSeparation = _xppcm*6; //6cm = 28*6 dots
	_eye2screenDist = _xppcm*30; //30cm = 28*30 dots

	_linksR2L = new int[ outputSize.width ];
	_colorRow = new cv::Vec3b[ outputSize.width ];
}

StereogramGenerator::~StereogramGenerator()
{
	delete[] _linksR2L;
	delete[] _colorRow;
}

double StereogramGenerator::NormalizeDepth( void )
{
	cv::Mat __heightmap;
	double mindepth=0,maxdepth=5; // maxdepth=5 ; >5 is visible to naked eye
	double min, max;
	cv::minMaxLoc(_heightmap, &min, &max);
	_heightmap = (_heightmap-min)/(max-min)*(maxdepth-mindepth)+mindepth;

	return maxdepth;
}

int StereogramGenerator::getStereoSeparation ( unsigned char objectDepth )
{ 
	// eyeSeparation : separation between the eyes
	// stereoSeparation : projection of the eye separation on the screen when looking at an object
	// eye2screenDist : distance from observer to the screen
	// objectDepth : depths of the object heightmap

	// the multiplication below is 'long' to prevent overflow errors
	return static_cast<int>( (long)(_eyeSeparation*objectDepth) / ( objectDepth + _eye2screenDist ) );
}

void StereogramGenerator::Link ( int x, int stereoSeparation ) 
{
	//get corresponding pixels from stereoSeparation
	int left = x - stereoSeparation/2;
	int right = left + stereoSeparation;
	int width = _heightmap.size().width;

   //link the two pixels
   if ( left>=0 && right<width ) 
   		_linksR2L[right]=left;

}

cv::Vec3b StereogramGenerator::ColorLink ( int x, cv::RNG* rng )
{
	cv::Vec3b color;
	// give random color to left links and unlinked and matching color to right link
	if ( _linksR2L[ x ] == x )
		color = cv::Vec3b( rng->uniform(0, 255), rng->uniform(0, 255), rng->uniform(0, 255) );
	
	else // _linksR2L[ x ] < x; _linksL2R[ x ] > x
		color = _colorRow[ _linksR2L[x] ];
	
	return color;
}

void StereogramGenerator::Init( int x )
{
	_linksR2L[x]=x;
}


cv::Mat StereogramGenerator::ProcessRow ( cv::Mat iRow, cv::RNG* colormap )
{
	int x;
	int width = _output.size().width;

	// std::cout << iRow.size() << std::endl;
	cv::Mat row = cv::Mat(iRow.size(), CV_8UC3, cv::Scalar(0,0,0) );

	// init links;
	for ( x=0; x<width; x++ )
		Init(x);

	// evaluate links
	for ( x=0; x<width; x++ )
	{
		unsigned char objectDepth = iRow.at<char>( x );
		int separation = getStereoSeparation(objectDepth);
		Link( x, separation);
	}

	// Assign color to row
	for ( x=0; x<width; x++ )
		_colorRow[x] = ColorLink( x, colormap );
	
	for ( x=0; x<width; x++ )
	{	
		row.data[row.channels()*(row.cols*0 + x) + 0] = _colorRow[ x ][0]; 
		row.data[row.channels()*(row.cols*0 + x) + 1] = _colorRow[ x ][1]; 
		row.data[row.channels()*(row.cols*0 + x) + 2] = _colorRow[ x ][2]; 
	}

	return row;
}


cv::Mat StereogramGenerator::GetStereogram ( void )
{
	return _output;
}

cv::Mat StereogramGenerator::Generate ( void )
{
	// _heightmap = NormalizeDepth( _heightmap );
	cv::RNG* colormap = new cv::RNG();

	CV_Assert( _output.size() == _heightmap.size() );

	for( int y = 0; y < _heightmap.rows; y++ )
		ProcessRow( _heightmap.row(y), colormap ).copyTo(_output.row(y));

    delete colormap;

    return _output;

}
