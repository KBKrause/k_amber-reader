/*
	No 2 molecules can have the same name (no copies).
	If a molecule needs to be saved - figure it out.
*/

#pragma once

#include <unordered_set>
#include "HydrogenBondReader.h"
#include "PDBReader.h"
#include "SASAReader.h"

class Molecule
{
public:

	Molecule(string name);

	string getMoleculeName();

	void addAnalysis(FileReader& input, string analy);

private:

	string name;
	
	// This table holds a string as the name for the analysis and another string which contains the path to the file written
	unordered_map <string, string> analyses;

	//static unordered_set <string> validAnalysisNames;
};