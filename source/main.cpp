#include <datasets/FileDataset.hpp>
#include <iostream>

/**
 * Main
 *
 * @param Argument count
 * @param Arguments
 */
int main(int argc, char* argv[])
{
	// Load dataset
	try
	{
		// Load data set
		std::cout << "Loading dataset..." << std::endl;
		FileDataset dataset(argc > 1 ? argv[1] : "dataset.db");
		std::cout << "Loaded " << dataset.getCount() << " items." << std::endl;
		
		// Show dataset
		std::cout << "Dataset:" << std::endl;
		for (size_t i = 0; i < dataset.getCount(); ++i)
		{
			std::cout << (i + 1) << ": ";
			Dataset::Stimulus *stimulus = dataset.getStimulus(i);
			for (size_t j = 0; j < dataset.getFeatureCount(); ++j)
			{
				std::cout << stimulus->getFeature(j) << " ";
			}
			std::cout << stimulus->getClassLabel() << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1; // exit with error
	}
	
	return 0; // exit ok
}
