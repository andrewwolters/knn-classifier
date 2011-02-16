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
