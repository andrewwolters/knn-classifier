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

Dataset::~Dataset()
{
	// Free stimuli
	for (size_t i = 0; i < stimulusCount; ++i)
	{
		delete stimuli[i];
	}
	free(stimuli);
}

std::ostream& Dataset::Stimulus::writeToStream(std::ostream& stream, const Dataset *dataset)
{
	for (size_t i = 0; i < dataset->getFeatureCount(); ++i)
	{
		stream << features[i] << " ";
	}
	if (!classLabel.empty())
	{
		stream << classLabel;
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Dataset *dataset)
{
	for (size_t i = 0; i < dataset->getCount(); ++i)
	{
		dataset->getStimulus(i)->writeToStream(stream, dataset) << std::endl;
	}
}

std::ostream& operator<<(std::ostream& stream, const Dataset& dataset)
{
	return operator<<(stream, &dataset);
}
