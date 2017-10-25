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

using namespace std;

int main(int argc, char* argv[])
{
	try
	{	
		/*
		FileReader f("C:/Users/Kevin/Documents/Github/k_amber-reader/data/sull_oxp-r-1.pdb");
		FileWriter f_pdbFix("C:/Users/Kevin/Documents/Github/k_amber-reader/out/sull_oxp-r-1_fixed.pdb");

		f.autofix_pdb("ULV");
		f_pdbFix.write_autofix_pdb(f, "ULV");
		*/

		//f_pdbFix.autofix_pdb();

		Test::test_reader_methods();
		
	}
	catch (Exception_FileManipulator& e)
	{
		e.what();
	}

	return 0;
}

// Key Tags:
// [ELABORATE]
// TODO