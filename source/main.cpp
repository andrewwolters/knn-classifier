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
		FileDataset::Mode mode = FileDataset::NORMAL;
		if (argc > 2)
		{
			if (strcmp(argv[2], "features") == 0)
			{
				mode = FileDataset::FEATURES;
			}
			else if (strcmp(argv[2], "labels") == 0)
			{
				mode = FileDataset::CLASS_LABELS;
			}
		}
		FileDataset dataset(argc > 1 ? argv[1] : "dataset.db", mode);
		std::cout << "Loaded " << dataset.getCount() << " items." << std::endl;
		std::cout << "Loaded labels: ";
		std::list<std::string>::const_iterator it = dataset.getClassLabels().begin();
		std::list<std::string>::const_iterator end = dataset.getClassLabels().end();
		if (it == end)
		{
			std::cout << "no labels loaded" << std::endl;
		}
		else
		{
			bool first = true;
			for (; it != end; ++it)
			{
				if (first)
				{
					first = false;
				}
				else
				{
					std::cout << ", ";
				}
				std::cout << *it;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		
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
