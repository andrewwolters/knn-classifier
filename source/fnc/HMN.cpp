#include <cmath>

#include "HMN.hpp"

using namespace std;

HMN::HMN(Dataset *dataset)
{
	this->dataset = dataset;
	computeHMN();
	setParams(.1, 4, 3, .5, .25);
}

void HMN::fillRefs()
{
	stimuli = new stimulusRef[dataset->getCount()];
	for (size_t i = 0; i < dataset->getCount(); ++i)
	{
		int l=0;
		list<string> classLabels = dataset->getClassLabels();
		for(list<string>::iterator it = classLabels.begin(); it != classLabels.end() && it->compare(dataset->getStimulus(i)->getClassLabel()) != 0; it++)
			l++;
		stimuli[i] = stimulusRef(i,l);
	}
}

double dist(Dataset::Stimulus *x, Dataset::Stimulus *y, size_t featurecount)
{
	double sqrSum = 0;
	for (size_t i = 0; i < featurecount; ++i)
	{
		double diff = abs(x->getFeature(i) - y->getFeature(i));
		sqrSum += diff*diff;
	}
	return sqrt(sqrSum);
}

void HMN::computeHMN()
{
	fillRefs();

	int c = dataset->getClassLabels().size();
	for (int i = 0; i < dataset->getCount(); i++)
	{
		stimulusRef x = stimuli[i];
		double* minDistPerLabel = new double[c];
		stimulusRef** nearestPerLabel = new stimulusRef*[c];
		for (int j = 0; j < dataset->getCount(); ++j)
		{
			if (i != j)
			{
				double d = dist(x.stimulus(dataset), y.stimulus(dataset), dataset->getFeatureCount());
				if (d < minDistPerLabel[y.label])
				{
					minDistPerLabel[y.label] = d;
					if(x.label == y.label)
					{
						if(nearestPerLabel[c]->hits > 0)
							nearestPerLabel[c]->hits--;
						y.hits++;
					}
					else
					{
						if(nearestPerLabel[c]->misses > 0)
						{
							nearestPerLabel[c]->misses--;
						}
						y.misses++;
					}
					nearestPerLabel[c] = y;
					//No real graph represenation is needed, so only the hits and misses are calculated.
				}
			}
		}
	}
}

Dataset* HMN::optimize()
{
	int c = dataset->getClassLabels().size();
	int *left = new int[c];
	int *Xl = new int[c];
	int X = dataset->getCount();
	int countLeft = X;

	//Rule 1
	for (int i = 0; i < X; ++i)
	{
		stimulusRef *x = &stimuli[i];
		double w = c / (double)X;

		if (w*x->misses + e > (1 - w)*x->hits)
		{
			x->remove = true;
			countLeft--;
		}
		else
		{
			left[x->label]++;
		}
		Xl[x->label]++;
	}

	//Rule 2
	for(int lb = 0; lb < c; lb++)
	{
		if (left[lb] < l)
		{
			for(int i = 0; i < X; i++)
			{
				stimulusRef *x = &stimuli[i];
				if(x->label == lb && x->inDegree() > 0)
				{
					x->remove = false;
					countLeft++;
				}
			}
		}
	}

	for(int i = 0; i < X; i++)
	{
		stimulusRef *x = &stimuli[i];

		//Rule 3
		if (c > cc && x->misses < cf*c && x->inDegree() > 0)
		{
			x->remove = false;
			countLeft++;
		}

		//Rule 4
		if (x->hits >= f*Xl[x->label])
		{
			x->remove = false;
			countLeft++;
		}
	}

	//Make the changes in a new dataset (needs an extended Dataset, still to be developed)
	int p = 0;
	Dataset* returnSet = new Dataset(countLeft);
	for (int i = 0; i < X; ++i)
	{
		stimulusRef x = stimuli[i];
		returnSet->setStimulus(p++, x.stimulus(dataset));
	}
	
	return returnSet;
}