#ifndef __MAIN_HPP__
#define __MAIN_HPP__


#include <opencv2/cv>


class StereogramGenerator
{
private:

	cv::Mat _heightmap;
	cv::Mat _output;


	int* _linksR2L;	// list of links

	int _eyeSeparation; // separation between the eyes (cm)
	int _eye2screenDist; // distance from observer to the screen (cm)
	int _xppcm, _yppcm; // point per cm (resolution)



	cv::Mat NormalizeDepth( cv::Mat& heightmap, float mindepth, float maxdepth )
	{
		return heightmap;
	}

	inline int getStereoSeparation ( float objectDepth )
	{ 
		// eyeSeparation : separation between the eyes
		// stereoSeparation : projection of the eye separation on the screen when looking at an object
		// eye2screenDist : distance from observer to the screen
		// objectDepth : depths of the object heightmap

		// the multiplication below is 'long' to prevent overflow errors
		return static_cast<int>( (long)(_eyeSeparation*objectDepth) / ( objectDepth + _eye2screenDist ) );
	}

	inline virtual void Link ( int x, int stereoSeparation ) 
	{
		//get corresponding pixels from stereoSeparation
		int left = x - stereoSeparation/2;
		int right = left + stereoSeparation;
		int width = _heightmap.size()[0];

	   //link the two pixels
	   if ( left>=0 && right<width ) 
	   		_linksR2L[right]=left;
	
	}

	inline virtual Scalar ColorLink ( int x )
	{
		Scalar color;
		// give random color to left links and unlinked and matching color to right link
   		if ( _linksR2L[ x ] == x )
   			_colorRow[ x ] = Scalar( rng->uniform(0, 255),rng->uniform(0, 255),rng->uniform(0, 255) )
 		else // _linksR2L[ x ] < x; _linksL2R[ x ] > x
 			_colorRow[ x ] = _colorRow[ _linksR2L[x] ];
 		
	}




	inline virtual cv::Mat ProcessRow ( cv::Mat row )
	{
		int x;
		int width = _output.size()[0];

		// init links;
		for ( x=0; x<width; x++ )
			_linksR2L[x]=x;

		// evaluate links
		for ( x=0; x<width; x++ )
		{
			int stereoSeparation = getStereoSeparation( x );
			Link( x, stereoSeparation );
		}

		// Assign color to each channel
		for ( x=0; x<3*width; x+=3 )
			row.at( x ) = ColorLink( x );

		for ( x=0; x<width; x++ )
		{
			row.at( x ) = _colorRow[ x ];
		}
	}


	
public:


	StereogramGenerator( cv:Mat heightmap, int outputWidth, int outputHeight )
	{

	    _output = cv::Mat( outputWidth, outputHeight, CV_8UC3 );
	    CV_Assert( heightmap.depth() == CV_8UC1 );
		cv::resize( heightmap, _heightmap, _output.size(), 0, 0, INTER_LINEAR);

		_eyeSeparation = 6;
		_eye2screenDist = 30;
		_xppcm = 28;
		_yppcm = 28;

		_linksR2L = new int[ outputWidth ];
		_colorRow = new Scalar[ outputWidth ];
	}

	~StereogramGenerator()
	{
		delete[] _linksR2L;
		delete[] _colorRow;
	}

	cv::Mat GetStereogram ( void )
	{
		return _output;
	}

	cv::Mat Generate ( void )
	{
		_heightmap = NormalizeDepth( _heightmap );

		cv::CV_Assert( _output.size() == _heightmap.size() );

		for( y = 0; y < _heightMap.rows; y++ )
			ProcessRow( _heightMap.row(y) ).copyTo( _output.row(y) );

	}

	void UseTile ( cv::Mat tile, int repeatX, int repeatY )
	{
		cv::repeat( tile, repeatX, repeatY, _output );
		cv::resize( _heightmap, _heightmap, _output.size(), 1, 1, INTER_LINEAR);

		_linksR2L = new int[ _output.size().width ];
		_colorRow = new Scalar[ _output.size().height ];
	}



};


class StereogramGeneratorWithHiddenLinks : public StereogramGenerator
{

private:

	void RemoveHiddenLinks ( void )
	{

	}

};



#endif
