#pragma once
#include "FileReader.h"

class PDBReader : public FileReader
{
public:

	PDBReader(string filePath);
	string analyze(string s) override;

};