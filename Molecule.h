/**
	k_amber-reader
	Molecule.h
	A molecule can represent a single molecule in space or water, or a molecular micelle (MM).
		Each molecule has a name, such as poly(SULL). It can also have files associated with it,
		such as a .pdb. These possible file associations are contained in a static set called
		validAnalysisNames.
	One problem we encountered over the summer was keeping everything atomic and consistent. To remedy this,
		a single Molecule object can be created per molecule being studied. This will organize all of the
		molecule's files under a single directory.

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

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

enum AnalysisTitle
{
	HBOND, SASA, PDB_ORIG, PDB_FIXED
};

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
	
	// This method does not require a FileReader object's getFilePath() method to return the path of the file.
	// Instead, filePath is the string itself. However, this method needs to verify that:
	// -it's a valid file
	// -it belongs to this micelle
	// -the analysis type analy, specified by the second string parameter, matches the file
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