#ifndef FileDataset__
#define FileDataset__

#include <kNN/Dataset.hpp>

/**
 * File dataset class
 *
 * @author Leon van der Veen
 */
class FileDataset : public Dataset
{
	public:
		/**
		 * Constructor
		 *
		 * @param File
		 */
		FileDataset(const char *file);
};

#endif
