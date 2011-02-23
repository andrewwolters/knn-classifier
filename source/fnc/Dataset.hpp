#ifndef Dataset__
#define Dataset__

#include <cstring>
#include <string>
#include <list>
#include <ostream>

/**
 * Dataset (base) class
 *
 * @author Leon van der Veen
 */
class Dataset
{
	public:
		/**
		 * Stimulus class
		 *
		 * @author Leon van der Veen
		 */
		class Stimulus
		{
			protected:
				double *features;
				std::string classLabel;
				
			public:
				/**
				 * Constructor
				 *
				 * @param Features pointer
				 * @param Feature count
				 */
				Stimulus(const double *features, size_t featureCount, const std::string& classLabel);
				
				/**
				 * Get class label
				 *
				 * @return Label
				 */
				const std::string& getClassLabel() const
				{
					return classLabel;
				}
				
				/**
				 * Get features
				 *
				 * @return Features
				 */
				const double* getFeatures() const
				{
					return features;
				}
				
				/**
				 * Get feature
				 *
				 * @param Index
				 * @return Features
				 */
				const double getFeature(size_t index) const
				{
					return features[index];
				}
				
				/**
				 * Write to stream
				 *
				 * @param Stream reference
				 * @param Dataset
				 * @return Stream reference
				 */
				std::ostream& writeToStream(std::ostream& stream, const Dataset *dataset);
		};
	
	protected:
		Stimulus **stimuli;
		size_t stimulusCount;
		size_t featureCount;
		std::list<std::string> classLabels;
	
	public:
		/**
		 * Constructor
		 */
		Dataset() :
			stimuli(NULL), stimulusCount(0), featureCount(0)
		{}
		
		/**
		 * Constructor
		 *
		 * Create a dataset with a given stimulus count and feature count.
		 *
		 * @param Stimulus count
		 * @param Feature count
		 */
		Dataset(size_t count, size_t featureCount_);
		
		/**
		 * Destructor
		 */
		~Dataset();
		
		/**
		 * Get class labels
		 *
		 * @return Class labels
		 */
		const std::list<std::string>& getClassLabels() const
		{
			return classLabels;
		}
		
		/**
		 * Get feature count
		 *
		 * @return Feature count
		 */
		size_t getFeatureCount() const
		{
			return featureCount;
		}
		
		/**
		 * Get stimulus
		 *
		 * @param Index
		 * @return Stimuli pointer or NULL on invalid index
		 */
		Stimulus* getStimulus(size_t index) const
		{
			if (index >= stimulusCount)
			{
				return NULL;
			}
			return stimuli[index];
		}
		
		/**
		 * Get stimulus
		 *
		 * @param Index
		 * @return Stimuli pointer or NULL on invalid index
		 */
		Stimulus* getStimulus(size_t index)
		{
			if (index >= stimulusCount)
			{
				return NULL;
			}
			return stimuli[index];
		}
		
		/**
		 * Get stimuli
		 *
		 * @return Stimuli pointer array
		 */
		Stimulus** getStimuli() const
		{
			return stimuli;
		}
		
		/**
		 * Get stimuli
		 *
		 * @return Stimuli pointer array
		 */
		Stimulus** getStimuli()
		{
			return stimuli;
		}
		
		/**
		 * Get stimuli count
		 *
		 * @return Stimuli count
		 */
		size_t getCount() const
		{
			return stimulusCount;
		}
		
		/**
		 * Set stimulus (at)
		 *
		 * @param Index
		 * @param Stimulus
		 * @return Success or not
		 */
		bool setStimulus(size_t index, Stimulus *stimulus)
		{
			if (index >= stimulusCount)
			{
				return false;
			}
			stimuli[index] = stimulus;
			return true;
		}
};

/**
 * Stream operator for dataset
 *
 * @param Stream reference
 * @param Dataset pointer
 * @return Stream reference
 */
std::ostream& operator<<(std::ostream& stream, const Dataset *dataset);

/**
 * Stream operator for dataset
 *
 * @param Stream reference
 * @param Dataset
 * @return Stream reference
 */
std::ostream& operator<<(std::ostream& stream, const Dataset& dataset);

#endif
