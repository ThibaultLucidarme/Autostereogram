#include "StereogramGenerator.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


StereogramGeneratorWithOcclusion::StereogramGeneratorWithOcclusion( cv::Mat heightmap, cv::Size outputSize): StereogramGenerator( heightmap, outputSize)
{
	_linksL2R = new int[ outputSize.width ];
}

StereogramGeneratorWithOcclusion::~StereogramGeneratorWithOcclusion( void)
{
	delete[] _linksL2R;
}

void StereogramGeneratorWithOcclusion::Init( int x )
{
	_linksR2L[x]=x;
	_linksL2R[x]=x;
}

void StereogramGeneratorWithOcclusion::Link ( int x, int stereoSeparation ) 
{
	//get corresponding pixels from stereoSeparation
	int left = x - stereoSeparation/2;
	int right = left + stereoSeparation;
	int width = _heightmap.size().width;

	bool visible = true; // default to visible to both eyes
	
	if ( left>=0 && right<width )
	{
   		if( _linksR2L[right]!=right ) // right pt already linked
   		{
   			if ( _linksR2L[right]<left ) // deeper than current
   			{
   				_linksL2R[ _linksR2L[right]] = _linksR2L[right];// break old links
   				_linksR2L[right] = right;// create new one
   			}
   			else visible = false;
   		}

   		if( _linksL2R[left]!=left ) // left pt already linked
   		{
   			if ( _linksL2R[left]>right ) // deeper than current
   			{
   				_linksR2L[ _linksL2R[left]] = _linksL2R[left]; // break old links
   				_linksL2R[left] = left;// create new one
   			}
   			else visible = false;
   		}

   		if( visible )
   		{
   			_linksL2R[left] = right;
   			_linksR2L[right] = left;
   		}
   	}

}
