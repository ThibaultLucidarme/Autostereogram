#include "CommandLineParser.hpp"
// #include "ProgressBar.hpp"

#include "StereogramGenerator.hpp"
// #include "StereogramGeneratorWithTiles.hpp"
// #include "StereogramGeneratorWithOcclusion.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace std;


int main( int argc, char** argv)
{
	// Parse commandline for parameters
	p::CommandLineParser parser(argc, argv);
	int sizeFactor = parser.addOption<int>("-s", 1, "Size of the stereogram");
	string heightmapName = parser.addOption<string>("-i","../data/shark.png", "input height map");
	string outputFilename = parser.addOption<string>("-o","", "output stereogram file");
	string tileName = parser.addOption<string>("-t","../data/tile1.jpg", "tile name");
	parser.CompileHelpFromOptions();

	cv::Mat output;
	cv::Mat heightMap = cv::imread( heightmapName, cv::IMREAD_GRAYSCALE  );

	if ( tileName == "")
	{
		StereogramGenerator sg(heightMap, heightMap.size()*sizeFactor );
		output = sg.Generate();
	}
	else
	{
		cv::Mat tile = cv::imread( tileName );
		StereogramGeneratorWithTiles sg(heightMap, tile, heightMap.size()*sizeFactor);
		output = sg.Generate();
	}

	cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE |cv::WINDOW_KEEPRATIO );// Create a window for display.
    cv::imshow( "Display window", output );

    if (outputFilename!="")
 	   cv::imwrite(outputFilename, output);
	
	cv::waitKey(0);
    return EXIT_SUCCESS;

}
	

