#ifndef __STEREOGRAMGENERATOR_HPP__
#define __STEREOGRAMGENERATOR_HPP__

#include <opencv2/opencv.hpp>


class StereogramGenerator
{
protected:

	cv::Mat _heightmap;
	cv::Mat _output;


	int* _linksR2L;	// list of links
	cv::Vec3b* _colorRow; // associated color

	int _eyeSeparation; // separation between the eyes (cm)
	int _eye2screenDist; // distance from observer to the screen (cm)
	int _xppcm, _yppcm; // point per cm (resolution)


	double NormalizeDepth( void );
	 int getStereoSeparation ( unsigned char objectDepth );
	 virtual void Link ( int x, int stereoSeparation );
	 virtual cv::Vec3b ColorLink ( int x, cv::RNG* rng );
	 virtual cv::Mat ProcessRow ( cv::Mat iRow, cv::RNG* colormap );

public:

	StereogramGenerator( cv::Mat heightmap, cv::Size outputSize );
	~StereogramGenerator();
	
	cv::Mat GetStereogram ( void );
	virtual cv::Mat Generate ( void );
	void UseTile ( cv::Mat tile, int repeatX, int repeatY );



};

#endif
