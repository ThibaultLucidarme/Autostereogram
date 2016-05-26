#ifndef __STEREOGRAMGENERATORWITHTILES_HPP__
#define __STEREOGRAMGENERATORWITHTILES_HPP__

#include "StereogramGenerator.hpp"

// #include <opencv2/opencv.hpp>
// #include <opencv2/core.hpp>
// #include <opencv2/imgproc.hpp>

class StereogramGeneratorWithTiles : public StereogramGenerator
{

protected:

	cv::Mat _tile;
	int _maxSep;


public:

	StereogramGeneratorWithTiles( cv::Mat heightmap, cv::Mat tile, cv::Size outputSize, int repeat=1): StereogramGenerator( heightmap, outputSize) {

		// double maxdepth = NormalizeDepth();
		int maxdepth = _xppcm * 12;
		_maxSep=(int)(((long)_eyeSeparation*maxdepth)/(maxdepth+_eye2screenDist));

		cv::Size size = ( (float)_output.size().width/repeat < _maxSep ) ? cv::Size(_maxSep,_maxSep) : cv::Size(_output.size().width/repeat,_output.size().width/repeat);

		cv::resize( tile, _tile, size, 0, 0, cv::INTER_LINEAR);

		std::cout<<"maxsep : "<<_maxSep<< "    "<<size<<std::endl;

	}

	cv::Vec3b ColorLink ( int x, cv::RNG* rng )
	{
		static int lastLinked = -10;
		static int call = 0;
		int y = call / _output.size().width; //y = number of pixel processed row by row / row width
		int yShift = _yppcm/16;

		cv::Vec3b color;
		// give random color to left links and unlinked and matching color to right link
		if ( _linksR2L[ x ] == x )
		{
			if (lastLinked==(x-1))
				_colorRow[ x ] = _colorRow[ x-1 ];
			else
				_colorRow[ x ] = _tile.at<cv::Vec3b>( x%_maxSep, (y+(x/_maxSep)*yShift)%_tile.size().height );
		}
		else  // _linksR2L[ x ] < x; _linksL2R[ x ] > x
		{
			color = _colorRow[ _linksR2L[x] ];
			lastLinked = x; // keep track of the last pixel to be constrained
		}
		
		color = _colorRow[ x ];
		call++;

		return color;
	}

};





#endif
