// #ifndef __MAIN_HPP__
// #define __MAIN_HPP__

// #include <exception>
// #include <opencv2/opencv.hpp>
// #include <opencv2/core.hpp>
// #include <opencv2/imgproc.hpp>


// class StereogramGenerator
// {
// private:

// 	cv::Mat _heightmap;
// 	cv::Mat _output;


// 	int* _linksR2L;	// list of links
// 	cv::Vec3b* _colorRow; // associated color

// 	int _eyeSeparation; // separation between the eyes (cm)
// 	int _eye2screenDist; // distance from observer to the screen (cm)
// 	int _xppcm, _yppcm; // point per cm (resolution)


// 	cv::Mat NormalizeDepth( cv::Mat& heightmap, float mindepth=0, float maxdepth=10 )
// 	{
// 		return heightmap;
// 	}

// 	inline int getStereoSeparation ( unsigned char objectDepth )
// 	{ 
// 		// eyeSeparation : separation between the eyes
// 		// stereoSeparation : projection of the eye separation on the screen when looking at an object
// 		// eye2screenDist : distance from observer to the screen
// 		// objectDepth : depths of the object heightmap

// 		// the multiplication below is 'long' to prevent overflow errors
// 		return static_cast<int>( (long)(_eyeSeparation*objectDepth) / ( objectDepth + _eye2screenDist ) );
// 	}

// 	inline virtual void Link ( int x, int stereoSeparation ) 
// 	{
// 		//get corresponding pixels from stereoSeparation
// 		int left = x - stereoSeparation/2;
// 		int right = left + stereoSeparation;
// 		int width = _heightmap.size().width;

// 	   //link the two pixels
// 	   if ( left>=0 && right<width ) 
// 	   		_linksR2L[right]=left;
	
// 	}

// 	inline virtual cv::Vec3b ColorLink ( int x, cv::RNG* rng )
// 	{
// 		cv::Vec3b color;
// 		// give random color to left links and unlinked and matching color to right link
//    		if ( _linksR2L[ x ] == x )
//    		{
//    			color = cv::Vec3b( rng->uniform(0, 255), rng->uniform(0, 255), rng->uniform(0, 255) );
//    			_colorRow[ x ] = color;
//    		}
//  		else // _linksR2L[ x ] < x; _linksL2R[ x ] > x
//  			color = _colorRow[ _linksR2L[x] ];
 		
//  		return color;
// 	}




// 	inline virtual cv::Mat ProcessRow ( cv::Mat iRow, cv::RNG* colormap )
// 	{
// 		int x;
// 		int width = _output.size().width;

// 		// std::cout << iRow.size() << std::endl;
// 		cv::Mat row = cv::Mat(iRow.size(), CV_8UC3, cv::Scalar(0,0,0) );

// 		// init links;
// 		for ( x=0; x<width; x++ )
// 			_linksR2L[x]=x;

// 		// evaluate links
// 		for ( x=0; x<width; x++ )
// 		{
// 			unsigned char objectDepth = iRow.at<char>( x );
// 			Link( x, getStereoSeparation(objectDepth) );
// 		}

// 		// Assign color to row
// 		for ( x=0; x<width; x++ )
// 		{
// 			cv::Vec3b color = ColorLink( x, colormap );
// 			row.data[row.channels()*(row.cols*0 + x) + 0] = color[0]; 
// 			row.data[row.channels()*(row.cols*0 + x) + 1] = color[1]; 
// 			row.data[row.channels()*(row.cols*0 + x) + 2] = color[2]; 
// 		}

// 		return row;
// 	}


	
// public:


// 	StereogramGenerator( cv::Mat heightmap, cv::Size outputSize )
// 	{

// 	    _output = cv::Mat( outputSize, CV_8UC3 );
// 	    CV_Assert( heightmap.depth() == CV_8UC1 );
// 		cv::resize( heightmap, _heightmap, outputSize, 0, 0, cv::INTER_LINEAR);

// 		_eyeSeparation = 6;
// 		_eye2screenDist = 30;
// 		_xppcm = 28;
// 		_yppcm = 28;

// 		_linksR2L = new int[ outputSize.width ];
// 		_colorRow = new cv::Vec3b[ outputSize.width ];
// 	}

// 	~StereogramGenerator()
// 	{
// 		delete[] _linksR2L;
// 		delete[] _colorRow;
// 	}

// 	cv::Mat GetStereogram ( void )
// 	{
// 		return _output;
// 	}

// 	cv::Mat Generate ( void )
// 	{
// 		_heightmap = NormalizeDepth( _heightmap );
// 		cv::RNG* colormap = new cv::RNG();
// 		double min, max;

// 		CV_Assert( _output.size() == _heightmap.size() );

// 		for( int y = 0; y < _heightmap.rows; y++ )
// 			ProcessRow( _heightmap.row(y), colormap ).copyTo(_output.row(y));

// 	    delete colormap;

// 	    return _output;

// 	}

// 	void UseTile ( cv::Mat tile, int repeatX, int repeatY )
// 	{
// 		cv::repeat( tile, repeatX, repeatY, _output );
// 		cv::resize( _heightmap, _heightmap, _output.size(), 1, 1);

// 		_linksR2L = new int[ _output.size().width ];
// 		_colorRow = new cv::Vec3b[ _output.size().height ];
// 	}



// };



// #endif
