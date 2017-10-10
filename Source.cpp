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

int main(int argc, char* argv[])
{
	try
	{	
		FileReader f("C:/Users/Kevin/Documents/Github/k_amber-reader/data/SULL_surface_ALP-R4_ligand.dat");
		f.surface_average();
	}
	catch (Exception_FileManipulator ex)
	{
		
	}

	return 0;
}