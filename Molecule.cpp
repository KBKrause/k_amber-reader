#include "Molecule.h"
#include <unordered_map>
#include "Test.h"

Molecule::Molecule(string n)
{
	name = n;
}
string Molecule::getMoleculeName()
{
	return name;
}
//--
void Molecule::addAnalysis(FileReader& input, string analy)
{
	if (analyses.find(analy) == analyses.end())
	{
		analyses.insert({analy, input.getFilePath()});
	}
	else
	{
		PRN_ERROR(AT);
	}
}
