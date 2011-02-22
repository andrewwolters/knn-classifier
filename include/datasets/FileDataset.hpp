#ifndef FileDataset__
#define FileDataset__

#include <kNN/Dataset.hpp>
#include <string>
#include <datasets/FileDatasetException.hpp>

/**
 * File dataset class
 *
 * @author Leon van der Veen
 */
class FileDataset : public Dataset
{
	public:
		/**
		 * Mode
		 */
		enum Mode
		{
			FEATURES		= 1, // only features
			CLASS_LABELS	= 2, // only class labels
			NORMAL			= 3  // features and class labels
		};
	
	protected:
		Mode mode;
	
	public:
		/**
		 * Constructor
		 *
		 * @param File
		 */
		FileDataset(const char *file, Mode mode = NORMAL) throw(FileDatasetException);
	
	protected:
		/**
		 * Parse line
		 *
		 * @param Line
		 * @return Stimulus pointer
		 */
		Stimulus* parseLine(const std::string& line);
		
		/**
		 * Parse first line
		 *
		 * @param Line
		 * @return Stimulus pointer
		 */
		Stimulus* parseFirstLine(const std::string& line, const char *file) throw(FileDatasetException);
};

#endif
