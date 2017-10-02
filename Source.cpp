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
//#include <assert.h>

// FILE MANIPULATOR(S)
#include "FileManipulator.h"
//--
#include "FileReader.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Init ..." << endl << endl;
	FileReader f("./data/SULL_ALP-R4_Hbond.dat");
	f.hydrogen_bond_intra_average(0.05);

	// add output file to this method and it's done
	//FileReader test_hbond("C:/Users/Kevin/Desktop/H-bond-Intra-avg.dat");
	//test_hbond.hydrogen_bond_intra_average("nil", 0.05);

	// Test the exception thing in this.
	// Make connection to the open_for_write() function in fileManipulator.

	/*
	try
	{
	g.thrower();
	}
	catch(Exception_FileManipulator e)
	{
	cout << "Caught exception" << endl;
	}
	*/

	return 0;
}

/* TODO
FIXES:

SUGGESTIONS:
	-MAke FileManipulator an abstract class. Fmanip is useless on its own. Doesn't need to be
	instantiated every time.
	-Give it static methods.

*/