#include <datasets/FileDataset.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

/**
 * Optimize
 *
 * @param Input dataset file
 * @param Output dataset file
 * @return Exit code
 */
int optimize(const char *inputDatasetFile, const char *outputDatasetFile)
{
	try
	{
		// Open input dataset
		FileDataset inputDataset(inputDatasetFile, FileDataset::NORMAL);
		
		// Optimize
		// TODO
		Dataset resultDataset; // or so
		int k = 3; // or so
		
		// Store in file
		std::ofstream outputStream(outputDatasetFile);
		outputStream << resultDataset;
		int result = ((bool)outputStream ? 0 : 1);
		outputStream.close();
		
		// Display result
		std::cout << "Optimized from dataset (file = '" << inputDatasetFile << "', size = " << inputDataset.getCount() << ")";
		std::cout << " to dataset (file = '" << outputDatasetFile << "', size = " << resultDataset.getCount() << ")" << std::endl;
		std::cout << "Found k for kNN: " << k << std::endl;
		
		return result;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1; // exit with error
	}
}

/**
 * Classify
 *
 * @param Dataset file
 * @param K (for kNN)
 * @param Features file
 * @param Result labels file
 * @return Exit code
 */
int classify(const char *datasetFile, int k, const char *featuresFile, const char *labelsFile)
{
	try
	{
		// Open dataset
		FileDataset dataset(datasetFile, FileDataset::NORMAL);
		
		// Open features file
		FileDataset featuresDataset(datasetFile, FileDataset::FEATURES);
		
		// Classify
		// TODO (do something with k)
		Dataset labelsDataset(featuresDataset.getCount());
		// labelsDataset.setStimulus(index, new Dataset::Stimulus(); // or so
		
		// Store in file
		std::ofstream outputStream(labelsFile);
		labelsDataset.writeToStream(outputStream, true);
		int result = ((bool)outputStream ? 0 : 1);
		outputStream.close();
		
		return result;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1; // exit with error
	}
}

/**
 * Help
 *
 * @param Argc
 * @param Argv
 * @return Exit code
 */
int help(int argc, char* argv[])
{
	std::cout << "Usage:" << std::endl;
	std::cout << "\tkNN optimize <dataset file> <result dataset file>" << std::endl;
	std::cout << "\tkNN classify <dataset file> <k> <features file> <result labels file>" << std::endl;
	return 1;
}

/**
 * Main
 *
 * @param Argument count
 * @param Arguments
 */
int main(int argc, char* argv[])
{
	// Mode
	if (argc > 3 && strcmp(argv[1], "optimize") == 0) // optimize
	{
		return optimize(argv[2], argv[3]);
	}
	else if (argc > 5 && strcmp(argv[1], "classify") == 0) // classify
	{
		return classify(argv[2], atoi(argv[3]), argv[4], argv[5]);
	}
	else
	{
		return help(argc, argv);
	}
}
