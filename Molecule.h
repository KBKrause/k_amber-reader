/*
	No 2 molecules can have the same name (no copies).
	If a molecule needs to be saved - figure it out.
*/

#pragma once

#include <unordered_set>
#include <filesystem>

#include "HydrogenBondReader.h"
#include "PDBReader.h"
#include "SASAReader.h"

// https://stackoverflow.com/questions/7531981/how-to-instantiate-a-static-vector-of-object
static unordered_set <string> validAnalysisNames;

class Molecule
{
public:

	Molecule(string name);

	string getMoleculeName();

	// http://en.cppreference.com/w/cpp/filesystem/path
	static unordered_map <string, Molecule> loadMolecules();

	bool add_analysis(FileReader& input, string analy);
	bool add_analysis(string filePath, string analy);
	void print_all_analysis_paths();

	// "Save" all file paths associated with this molecule.
	// Disable/prevent overwriting.
	~Molecule();

private:

	string name;
	
	// This table holds a string as the name for the analysis and another string which contains the path to the file written
	// Prevent duplicates of filereader inputs also ... each FileReader really only holds 1 analysis and consequently 1 output file.
	unordered_map <string, string> analyses;

};