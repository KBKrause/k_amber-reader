/**
	k_amber-reader
	Source.cpp
	Driver file. This is launched in the console window. See below for
		specific instructions.

    Author(s): Kevin B. Krause
    Version:   unreleased
*/

#include <iostream>
#include <string>
#include <unordered_map>

#include "FileManipulator.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Test.h"

#include "HydrogenBondReader.h"
#include "SASAReader.h"
#include "PDBReader.h"

#include "Molecule.h"

using namespace std;

void testAll();

int main(int argc, char* argv[])
{
	try
	{	
		unordered_map <string, Molecule> allMolecules = Molecule::loadMolecules();

		cout << "Number of molecules loaded: " << allMolecules.size() << endl;

		/*
		HydrogenBondReader hbr(FILE_HBOND);
		PDBReader pdbr(FILE_PDB);

		Molecule realmolecule("SULL-ALP-R4");
		realmolecule.add_analysis(hbr, "HBOND");
		realmolecule.add_analysis(pdbr, "PDB_ORIG");
		realmolecule.print_all_analysis_paths();
		*/
	}
	catch (exception& e)
	{
		cout << e.what();
	}

	return 0;
}

void testAll()
{
	Test::test_HydrogenBondReader();
	Test::test_SASAReader();
	Test::test_FileReader();
	Test::test_PDBReader();
	Test::test_Molecule();
}

// Key Tags:
// [ELABORATE]
// TODO