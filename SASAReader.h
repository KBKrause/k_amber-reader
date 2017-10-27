#pragma once
#include "FileReader.h"

class SASAReader : public FileReader
{
public:

	SASAReader(string filePath);
	// threshold parameter not even used.
	// go to base class and add virtual functions for analysis that does not take this parameter.
	// then test with HydrogenBondReader to make sure it will only call the correct analysis methods (not the ones
	//	meant for SASAReader or anything else).
	string analyze() override;
};