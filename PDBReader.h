#pragma once
#include "FileReader.h"

class PDBReader : public FileReader
{
public:

	PDBReader(string filePath);

	/**
	10/27/2017
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