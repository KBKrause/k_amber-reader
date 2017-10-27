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

#include "FileManipulator.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Test.h"

#include "HydrogenBondReader.h"
#include "SASAReader.h"
#include "PDBReader.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{	
		HydrogenBondReader hbr("C:/Users/Kevin/Documents/Github/k_amber-reader/data/SULL_ALP-R4_Hbond.dat");
		SASAReader sasar("C:/Users/Kevin/Documents/Github/k_amber-reader/data/SULL_surface_ALP-R4_ligand.dat");
		PDBReader pdbr("C:/Users/Kevin/Documents/Github/k_amber-reader/data/sull_oxp-r-1.pdb");

		FileWriter fw("C:/Users/Kevin/Documents/Github/k_amber-reader/out/newbranch_sasa.txt");
		//fw.write_analysis(sasar);
		fw.set_file_path("C:/Users/Kevin/Documents/Github/k_amber-reader/out/newbranch_hbond.txt");
		fw.write_analysis(hbr, 0.05);
		fw.set_file_path("C:/Users/Kevin/Documents/Github/k_amber-reader/out/newbranch_pdb.txt");
		fw.write_analysis(pdbr, "ULL");
		
	}
	catch (Exception_FileManipulator& e)
	{
		cout << e.what();
	}

	return 0;
}

// Key Tags:
// [ELABORATE]
// TODO