#include <kNN/Dataset.hpp>
#include <cassert>
#include <cstdlib>

Dataset::Stimulus::Stimulus(const double *features, size_t featureCount, const std::string& classLabel)
{
	// Set features
	this->features = (double*)calloc(featureCount, sizeof(double));
	assert(this->features);
	memcpy(this->features, features, featureCount * sizeof(double));
	
	// Set class label
	this->classLabel = classLabel;
}

Dataset::Dataset(size_t count, size_t featureCount_) :
	stimuli(NULL), stimulusCount(count), featureCount(featureCount_)
{
	// Allocate stimuli
	stimuli = (Stimulus**)calloc(stimulusCount, sizeof(Stimulus*));
	assert(stimuli);
}

void Dataset::reset(size_t count, size_t featureCount_)
{
	// Free current
	free();
	
	// Reset
	stimuli = NULL;
	stimulusCount = count;
	featureCount = featureCount_;
	
	// Allocate stimuli
	stimuli = (Stimulus**)calloc(stimulusCount, sizeof(Stimulus*));
	assert(stimuli);
}

Dataset::~Dataset()
{
	free();
}

void Dataset::free()
{
	if (stimuli != NULL)
	{
		// Free stimuli
		for (size_t i = 0; i < stimulusCount; ++i)
		{
			delete stimuli[i];
		}
		::free(stimuli);
		stimuli = NULL;
	}
	stimulusCount = 0;
}

std::ostream& Dataset::Stimulus::writeToStream(std::ostream& stream, const Dataset *dataset, bool onlyLabels)
{
	if (!onlyLabels)
	{
		for (size_t i = 0; i < dataset->getFeatureCount(); ++i)
		{
			stream << features[i] << " ";
		}
		stream << classLabel;
	}
	else
	{
		stream << classLabel;
	}
	return stream;
}

std::ostream& Dataset::writeToStream(std::ostream& stream, bool onlyLabels) const
{
	for (size_t i = 0; i < getCount(); ++i)
	{
		getStimulus(i)->writeToStream(stream, this, onlyLabels) << std::endl;
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Dataset *dataset)
{
	return dataset->writeToStream(stream);
}

std::ostream& operator<<(std::ostream& stream, const Dataset& dataset)
{
	return operator<<(stream, &dataset);
}
