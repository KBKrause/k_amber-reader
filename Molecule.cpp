#include "Molecule.h"
#include "FileWriter.h"
#include <unordered_map>
#include <filesystem>
#include "Test.h"

Molecule::Molecule(string n)
{
	if (validAnalysisNames.size() == 0)
	{
		validAnalysisNames.insert("HBOND");
		validAnalysisNames.insert("SASA");
		validAnalysisNames.insert("PDB_ORIG");
		validAnalysisNames.insert("PDB_FIXED");
	}

	name = n;
}
string Molecule::getMoleculeName()
{
	return name;
}
//--
bool Molecule::add_analysis(FileReader& input, string analy)
{
	// If the analysis is not already in the list, and it's a valid analysis name, add it to this molecule.
	if (analyses.find(analy) == analyses.end() && (validAnalysisNames.find(analy) != validAnalysisNames.end()))
	{
		analyses.insert({analy, input.getFilePath()});
		return true;
	}
	else
	{
		PRN_ERROR(AT);
		return false;
	}
}
bool Molecule::add_analysis(string filePath, string analy)
{
	return false;
}
//--
void Molecule::print_all_analysis_paths()
{
	for (auto i = analyses.begin(); i != analyses.end(); i++)
	{
		cout << i->first << " : " << i->second << endl;
	}
}
//--
Molecule::~Molecule()
{
	ofstream fout;
	fout.open("C:/Users/Kevin/Documents/Github/k_amber-reader/lib/kamber_" + this->getMoleculeName() + ".dat");

	fout << getMoleculeName() << endl;
	
	for (auto i = analyses.begin(); i != analyses.end(); i++)
	{
		fout << i->first << ":" << i->second << endl;
	}

	fout.close();
}
//--
unordered_map <string, Molecule> Molecule::loadMolecules()
{
	string path = "C:/Users/Kevin/Documents/Github/k_amber-reader/lib/";
	unordered_map <string, Molecule> molecules;

	namespace fs = std::experimental::filesystem;

	// Make sure all the "pieces" of this loop are error checked.
	// What is the structure of this for loop? (initializer : iterator)
	for (auto& p : fs::directory_iterator(path))
	{
		ifstream fin;

		fin.open(path);

		string mcname;

		fin >> mcname;

		Molecule newMolecule(mcname);

		while (fin.good())
		{
			string line, analysis, analysisPath;
			fin >> line;
			analysis = line.substr(0, line.find(':'));
			analysisPath = line.substr(line.find(':'), line.size());

			newMolecule.add_analysis(FileReader(analysisPath), analysis);
		}

		molecules.insert({ mcname, newMolecule });
	}
		
	return molecules;
}
