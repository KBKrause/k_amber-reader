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

using namespace std;

void test_constructors();
void test_reader_methods();

int main(int argc, char* argv[])
{
	try
	{	
		FileReader f("C:/Users/Kevin/Documents/Github/k_amber-reader/data/sull_oxp-r-1.pdb");
		//FileWriter f_pdbFix("C:/Users/Kevin/Documents/Github/k_amber-reader/data/sull_oxp-r-1.pdb");

		f.autofix_pdb("ULV");

		//f_pdbFix.autofix_pdb();

		//test_constructors();
	}
	catch (exception& e)
	{
		e.what();
	}

	return 0;
}

void test_constructors()
{
	// Add good constructor cases
	try
	{
		FileReader r_badString("a/bad/string");
		FileWriter w_noString;
		FileWriter w_badString("a/bad/string");
	}
	catch (Exception_FileManipulator& e)
	{
		e.what();
	}
}

void test_reader_methods()
{

}

// Key Tags:
// [ELABORATE]
// TODO