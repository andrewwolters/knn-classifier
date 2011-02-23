/*
 *  kNN.cpp
 *  
 *
 *  Created by Tom de Ruijter on 2/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <kNN/kNN.hpp>

KNN::KNN(Dataset *dataset)
{
}

KNN::~KNN()
{
}

std::string KNN::classify(Dataset::Stimulus *target)
{
	int *nearestK = new int[k];		//Sorted list with k Nearest points from target.
	double *distK = new double[k];	//Distances to k Nearest points from target.
	
	Dataset::Stimulus *stimuli = dataset.getStimuli();
	
	for(int i = 0; i < dataset->getFeatureCount(); i++)
	{
		double distance = stimuli[i]->dist(target);
	}
}
