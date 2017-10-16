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

int main(int argc, char* argv[])
{
	try
	{	
		FileReader f("C:/Users/Kevin/Documents/Github/k_amber-reader/data/SULL_ALP-R4_surface.dat");
		FileWriter f2("C:/Users/Kevin/Documents/Github/k_amber-reader/data/some_output.dat");

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
	try
	{
		FileWriter test_defaultCtor;
	}
	catch (Exception_FileManipulator ex)
	{

	}
}

/*
separate printing to a public method
calculation to a private method

printFoo couts foo() foo() returns a string
writeFooToFile ... etc
*/

// Key Tags:
// [ELABORATE]
// TODO