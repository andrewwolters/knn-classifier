#include <datasets/FileDataset.hpp>
#include <fstream>
#include <cassert>
#include <cstdlib>

/*
void FileDataset::addStimuluss(Stimulus *items, size_t count)
{
	// Allocate enough memory
	size_t oldSize = dataSize;
	if (data == NULL)
	{
		data = (Stimulus*)calloc(count, sizeof(Stimulus));
		dataSize = count;
	}
	else
	{
		dataSize += count;
		data = (Stimulus*)realloc(data, dataSize * sizeof(Stimulus));
	}
	assert(data != NULL);
	
	// Add items
	memcpy(data + oldSize, items, count);
}
*/

FileDataset::FileDataset(const char *file) : Dataset()
{
	// TODO
	// load dataset from file
}
