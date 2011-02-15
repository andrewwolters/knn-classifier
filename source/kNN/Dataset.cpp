#include <kNN/Dataset.hpp>
#include <cassert>
#include <cstdlib>

void Dataset::addItems(Item *items, size_t count)
{
	// Allocate enough memory
	size_t oldSize = dataSize;
	if (data == NULL)
	{
		data = (Item*)calloc(count, sizeof(Item));
		dataSize = count;
	}
	else
	{
		dataSize += count;
		data = (Item*)realloc(data, dataSize * sizeof(Item));
	}
	assert(data != NULL);
	
	// Add items
	memcpy(data + oldSize, items, count);
}
