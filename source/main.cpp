#include <kNN/FileDataset.hpp>
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
	std::cout << "Loading dataset..." << std::endl;
	FileDataset dataset("dataset.db");
	std::cout << "Loaded " << dataset.getSize() << " items." << std::endl;
	
	return 0; // exit ok
}
