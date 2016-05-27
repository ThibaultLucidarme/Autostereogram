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
	 virtual void Init( int x );
	 virtual void Link ( int x, int stereoSeparation );
	 virtual cv::Vec3b ColorLink ( int x, cv::RNG* rng );
	 virtual cv::Mat ProcessRow ( cv::Mat iRow, cv::RNG* colormap );

public:

	StereogramGenerator( cv::Mat heightmap, cv::Size outputSize );
	virtual ~StereogramGenerator();
	
	cv::Mat GetStereogram ( void );
	virtual cv::Mat Generate ( void );

};



class StereogramGeneratorWithOcclusion : public StereogramGenerator
{

protected:

	int* _linksL2R;

	void Init( int x );
	void Link ( int x, int stereoSeparation );

public:

	StereogramGeneratorWithOcclusion( cv::Mat heightmap, cv::Size outputSize);
	~StereogramGeneratorWithOcclusion( void);

};


class StereogramGeneratorWithTiles : public StereogramGeneratorWithOcclusion
{

protected:

	cv::Mat _tile;
	int _maxSep;

	cv::Vec3b ColorLink ( int x, cv::RNG* rng );

public:

	StereogramGeneratorWithTiles( cv::Mat heightmap, cv::Mat tile, cv::Size outputSize, int repeat=1);

};

#endif
