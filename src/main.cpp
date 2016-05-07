#include "CommandLineParser.hpp"
// #include "ProgressBar.hpp"

#include "main.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace std;


int main( int argc, char** argv)
{
	// Parse commandline for parameters
	p::CommandLineParser parser(argc, argv);
	int size = parser.addOption<int>("-n", 250, "Size of simulation domain");
	string heightmapName = parser.addOption<string>("-i","", "input height map");
	string outputFilename = parser.addOption<string>("-o","", "output stereogram file");
	parser.CompileHelpFromOptions();

	cv::Mat heightMap = cv::imread( heightmapName, cv::IMREAD_GRAYSCALE  );
	// cv::Mat output = cv::create( outputFilename.size(), CV_8UC3 );

	StereogramGenerator sg(heightMap, cv::Size(size,size));


    return EXIT_SUCCESS;

}
	

