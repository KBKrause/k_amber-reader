/**
	k_amber-reader
	PDBReader.h
	This class "fixes" protein data bank (.pdb) files to be compatible with AMBER.
		Historically, .pdb files created by Molecular Operating Environment (MOE) have
		some additional comments and MOE-only content that are unnecessary for our purposes.

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#pragma once
#include "FileReader.h"

class PDBReader : public FileReader
{
public:

	/**
		Constructor for PDBReader objects.
		Parameters:
			string filePath - Path to the file being used
	*/
	PDBReader(string filePath);

	/**
		"Fix" a PDB file by changing the following:
			-change all instances of "INT" to the monomer's 3 letter acronym
			-remove all lines starting with "CONECT"
			-remove all lines starting with "LINK"
			-add a "TER" and "END" to the end of the file
		Parameters:
		string monomer - the 3 letter acronyom of the monomer on the micelle, such as
			poly(SULL) being ULL, poly(SULV) being ULV, and so on
		Returns:
			String aggregate
	*/
	string analyze(string s) override;

};