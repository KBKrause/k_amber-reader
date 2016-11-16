#include <iostream>
#include <string>
#include <assert.h>

// FILE MANIPULATOR(S)
#include "FileManipulator.h"
//--
#include "FileReader.h"

using namespace std;

struct hbond_child
{
	string acceptor_chain;
	string donor_chain;
	double persistence;
};

int main()
{
	system("pause");

	// add output file to this method and it's done
	FileReader test_hbond("C:/Users/Kevin/Desktop/H-bond-Intra-avg.dat");
	test_hbond.hydrogen_bond_intra_average("nil", 0.05);

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