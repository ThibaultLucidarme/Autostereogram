#include "CommandLineParser.hpp"
#include "ProgressBar.hpp"

using namespace std;


int main( int argc, char** argv)
{
	// Parse commandline for parameters
	p::CommandLineParser parser(argc, argv);
	int size = parser.addOption<int>("-n", 250, "Size of simulation domain");
	string initialDensity = parser.addOption<string>("-i","", "input height map");
	string initialDensity = parser.addOption<string>("-o","", "output stereogram file");
	parser.addHelpOption();

}
	

