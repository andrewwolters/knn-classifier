#ifndef HMN__
#define HMN__

#include <kNN/Dataset.hpp>

/**
 * Class to optimize a dataset using Hit Miss Networks
 * 
 * @author Hans Harmannij
 */
class HMN
{
	private:
		/**
		 * Struct to represent a stimulus and it's properties needed for HMN
		 */
		struct StimulusRef
		{
			size_t index;
			int label;
			int hits;
			int misses;
			bool remove;
			
			/**
			 * Constructor
			 */
			StimulusRef() :
				index(0),
				label(0),
				hits(0),
				misses(0),
				remove(false)
			{}
			
			/**
			 * Constructor
			 *
			 * @param Index
			 * @param Label
			 */
			StimulusRef(size_t index_, int label_) :
				index(index_),
				label(label_),
				hits(0),
				misses(0),
				remove(false)
			{}
			
			Dataset::Stimulus* stimulus(Dataset *dataset) { return dataset->getStimulus(index); }
			int inDegree() { return hits + misses; }
		};

		Dataset *dataset;
		StimulusRef* stimuli;

		double e;
		int l;
		int cc;
		double cf;
		double f;
		
		/**
		 * Fill the stimuli-array
		 */
		void fillRefs();

		/**
		 * Compute the HMN-graph. Complexity: O(dn^2)
		 */
		void computeHMN();
		
	public:
		/**
		 * Construct a new HMN with a given dataset
		 * @param dataset
		 */
		HMN(Dataset *dataset);

		/**
		 * Perform the optimization using HMN. Complexity O(dn)
		 * @return The optimized dataset
		 */
		Dataset* optimize();

		/**
		 * Set the parameters needed for the optimization. No need to recompute the HMN..
		 */
		void setParams(double e, int l, int cc, double cf, double f) { this->e = e; this->l = l; this->cc = cc; this->cf = cf; this->f = f; }
		void setE(double e) { this->e = e; }
		void setL(int l) { this->l = l; }
		void setCc(int cc) { this->cc = cc; }
		void setCf(double cf) { this->cf = cf; }
		void setF(double f) { this->f = f; }
		
		double getE() { return e; }
		int getL() { return l; }
		int getCc() { return cc; }
		double getCf() { return cf; }
		double getF() { return f; }
};

#endif