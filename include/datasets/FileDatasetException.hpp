#ifndef FileDatasetException__
#define FileDatasetException__

#include <exception>
#include <string>

/**
 * File dataset exception class
 *
 * @author Leon van der Veen
 */
class FileDatasetException : public std::exception
{
	protected:
		const char *message;

	public:
		/**
		 * Constructor
		 *
		 * @param File
		 */
		FileDatasetException(const char *file) throw() :
			std::exception(),
			message((std::string("Dataset file '") + std::string(file) + std::string("' could not been found")).c_str())
		{}
		
		/**
		 * Constructor
		 *
		 * @param File
		 */
		explicit FileDatasetException(const std::string& message_) throw() : std::exception(), message(message_.c_str())
		{}
		
		/**
		 * Constructor
		 *
		 * @param Other exception
		 */
		FileDatasetException(const FileDatasetException& other) : std::exception(other), message(other.message)
		{}
		
		/**
		 * What
		 *
		 * @return Message
		 */
		const char* what() const throw()
		{
			return message;
		}
};

#endif
