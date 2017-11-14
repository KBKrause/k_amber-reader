/**
	k_amber-reader
	Compute.cpp
	Implementation of Compute.h

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#include "Compute.h"

double Compute::standard_deviation(vector<double>& values)
{
	double retVal = 0;

	// No vectors of size 0
	if (values.size() != 0)
	{
		return 0;
	}

	double differences = 0;

	double avg = average(values);

	for (size_t i = 0; i < values.size(); i++)
	{
		// Each measurement minus the mean, squared
		differences += (pow((values[i] - avg), 2.0));
	}

	retVal = sqrt(differences / (values.size() - 1));

	return retVal;
}
//--
double Compute::average(vector<double>& values)
{
	double retVal = 0;

	// No vectors of size 0
	if (values.size() == 0)
	{
		return 0;
	}

	for (size_t i = 0; i < values.size(); i++)
	{
		retVal += values[i];
	}

	retVal /= values.size();

	return retVal;
}
