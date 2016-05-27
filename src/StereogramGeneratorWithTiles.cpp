#include "StereogramGenerator.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


StereogramGeneratorWithTiles::StereogramGeneratorWithTiles( cv::Mat heightmap, cv::Mat tile, cv::Size outputSize, int repeat): StereogramGeneratorWithOcclusion( heightmap, outputSize) 
{

	int maxdepth = _xppcm * 12,
		_maxSep = static_cast<int>( ((long)_eyeSeparation*maxdepth) / (maxdepth+_eye2screenDist) ),
		width = (float)_output.size().width/repeat;

	cv::Size size = ( width < _maxSep ) ? cv::Size(_maxSep,_maxSep) : cv::Size(width,width);
	cv::resize( tile, _tile, size, 0, 0, cv::INTER_LINEAR);

}

cv::Vec3b StereogramGeneratorWithTiles::ColorLink ( int x, cv::RNG* rng )
{
	static int lastLinked = -10;
	static int call = 0;
	int w = _output.size().width,
		h = _output.size().height;

	int y = call / w; //y = number of pixel processed row by row / row width
	int yShift = _yppcm/16;

	cv::Vec3b color;

	if ( _linksR2L[ x ] == x )
	{
		if (lastLinked==(x-1))
			color = _colorRow[ x-1 ];
		else
			color = _tile.at<cv::Vec3b>( x%w, (y+(x/w)*yShift) % h );
	}
	else 
	{
		_colorRow[ x ] = _colorRow[ _linksR2L[x] ];
		lastLinked = x; // keep track of the last pixel to be constrained
	}

	call++;
	return color;
}
