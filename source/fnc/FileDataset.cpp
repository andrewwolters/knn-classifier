#include <fstream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <sstream>

#include "FileDataset.hpp"

#define STIMULUS_BUFFER_SIZE 100

FileDataset::FileDataset(const char *file, Mode mode_) throw(FileDatasetException) :
	Dataset(),
	mode(mode_)
{
	// Open file
	std::ifstream ifs(file);
	
	// First line
	std::string line;
	std::getline(ifs, line);
	Stimulus *stimulus = parseFirstLine(line, file);
	
	// Create dataset in blocks
	stimuli = (Stimulus**)calloc(STIMULUS_BUFFER_SIZE, sizeof(Stimulus*));
	assert(stimuli);
	Stimulus **stimuliIt = stimuli;
	*stimuliIt = stimulus;
	++stimuliIt;
	size_t blockSize = 1;
	stimulusCount = 1;
	
	// Read rest lines
	while (std::getline(ifs, line) && !line.empty())
	{
		// Buffer full?
		if (blockSize >= STIMULUS_BUFFER_SIZE)
		{
			// Resize
			stimuli = (Stimulus**)realloc(stimuli, (stimulusCount + STIMULUS_BUFFER_SIZE) * sizeof(Stimulus*));
			assert(stimuli);
			stimuliIt = stimuli + stimulusCount;
			
			// Reset
			blockSize = 0;
		}
	
		// Parse line
		*stimuliIt = parseLine(line);
		++stimuliIt;
		
		// Higher counters
		++stimulusCount;
		++blockSize;
	}
	
	// Close file
	ifs.close();
}

Dataset::Stimulus* FileDataset::parseLine(const std::string& line)
{
	// Alloc features list
	double *features = (double*)calloc(featureCount, sizeof(double));
	double *featuresIt = features;
	
	// Parse parts
	std::stringstream ss(line);
	double last;
	size_t i = 0;
	std::string classLabel;
	if (FEATURES & mode)
	{
		bool first = true;
		while (ss >> classLabel)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				// Too many features?
				++i;
				if (i > featureCount)
				{
					std::stringstream message;
					message << "Invalid feature count on line " << (stimulusCount + 1) << ": " << line;
					throw FileDatasetException(message.str());
				}
				
				// Append feature
				*featuresIt = last;
				++featuresIt;
			}
			last = strtod(classLabel.c_str(), NULL);
		}
	}
	else
	{
		ss >> classLabel;
	}
	
	// No label?
	if (!(CLASS_LABELS & mode))
	{
		classLabel = "";
		
		// Too many features?
		++i;
		if (i > featureCount)
		{
			std::stringstream message;
			message << "Invalid feature count on line " << (stimulusCount + 1) << ": " << line;
			throw FileDatasetException(message.str());
		}
		
		// Append feature
		*featuresIt = last;
		++featuresIt;
	}
	
	// Too less features?
	if (i < featureCount)
	{
		std::stringstream message;
		message << "Invalid feature count on line " << (stimulusCount + 1) << ": " << line;
		throw FileDatasetException(message.str());
	}
	
	// Add to class labels?
	if (CLASS_LABELS & mode)
	{
		classLabels.push_back(classLabel);
		classLabels.unique();
		// TODO ^ optimize
	}
	
	// Make stimulus
	Stimulus *stimulus = new Stimulus(features, featureCount, classLabel);
	assert(stimulus);
	
	// Free features
	free(features);
	
	return stimulus;
}

Dataset::Stimulus* FileDataset::parseFirstLine(const std::string& line, const char *file) throw(FileDatasetException)
{
	std::vector<double> features;
	std::string classLabel;
	
	// Parse parts
	std::stringstream ss(line);
	double last;
	if (FEATURES & mode)
	{
		bool first = true;
		while (ss >> classLabel)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				features.push_back(last);
			}
			last = strtod(classLabel.c_str(), NULL);
		}
	}
	else
	{
		ss >> classLabel;
	}
	
	// No label?
	if (!(CLASS_LABELS & mode))
	{
		classLabel = "";
		features.push_back(last);
	}
	
	// Set feature count
	featureCount = features.size();
	if ((FEATURES & mode) && featureCount < 1)
	{
		throw FileDatasetException(file);
	}
	
	// Add to class labels
	if (CLASS_LABELS & mode)
	{
		classLabels.push_back(classLabel);
	}
	
	// Make stimulus
	Stimulus *stimulus = new Stimulus(&features.front(), featureCount, classLabel);
	assert(stimulus);
	
	return stimulus;
}
