/**
	k_amber-reader
	SASAReader.cpp
	Implementation of SASAReader.h

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#include "SASAReader.h"
#include "Compute.h"

SASAReader::SASAReader(string filePath) : FileReader(filePath)
{

}
//--
string SASAReader::analyze()
{
	pre_read_greeting(__FUNCTION__, "Finds the average SASA of the molecule and its highest/lowest points");

	string retVal = "";

	retVal += "*-*-*-*-*-*-*-*-*-*-* SURFACE.DAT ANALYSIS *-*-*-*-*-*-*-*-*-*-*\n";
	retVal += "INPUT = " + this->getFilePath() + "\n";

	this->ioFile.open(this->filePath);

	double lowestSurface = DBL_MAX;
	double highestSurface = DBL_MIN;

	int lowestFrame = INT_MAX;
	int highestFrame = INT_MIN;

	int currentFrame;
	double currentSurface;

	vector <double> surfaces;

	// seekg - seek "get" pointer, move it past the initial strings
	this->ioFile.seekg(sizeof("#Frame") + sizeof("SA_00000"));

	if (this->ioFile.good())
	{
		this->ioFile >> currentFrame;
		this->ioFile >> currentSurface;

		while (this->ioFile.good())
		{
			surfaces.push_back(currentSurface);

			if (currentSurface < lowestSurface)
			{
				lowestSurface = currentSurface;
				lowestFrame = currentFrame;
			}
			else if (currentSurface > highestSurface)
			{
				highestSurface = currentSurface;
				highestFrame = currentFrame;
			}

			ioFile >> currentFrame >> currentSurface;
		}
	}

	retVal += "The highest frame was " + to_string(highestFrame) + " with a surface area of " + to_string(highestSurface)
		+ " squared angstroms" + "\n";
	retVal += "The lowest frame was " + to_string(lowestFrame) + " with a surface area of " + to_string(lowestSurface)
		+ " squared angstroms" + "\n";
	retVal += "The average exposed surface area was " + to_string(Compute::average(surfaces)) + " angstroms" + "\n";
	retVal += "The standard deviation is +/- " + to_string(Compute::standard_deviation(surfaces)) + " angstroms\n";

	this->ioFile.close();

	return retVal;
}
//--