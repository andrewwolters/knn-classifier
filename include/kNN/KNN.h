/*
 *  Created by Tom de Ruijter on 2/21/11.
 */

#include <kNN/Dataset.hpp>

class KNN
{
		
public:
	/**
	 * Constructor
	 * 
	 */
	KNN(Dataset *dataset);
	
	/**
	 * Destructor
	 */
	~KNN();
	
	std::string classify(Dataset::Stimulus stimulus);
	
protected:

	Dataset *dataset;
}
