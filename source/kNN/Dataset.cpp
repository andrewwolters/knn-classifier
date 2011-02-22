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
