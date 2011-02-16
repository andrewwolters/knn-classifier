#ifndef Dataset__
#define Dataset__

#include <cstring>
#include <string>
#include <list>

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
		{
		}
	
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
};

#endif
