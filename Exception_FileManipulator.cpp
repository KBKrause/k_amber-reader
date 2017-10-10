/**
	k_amber-reader
	Exception_FileManipulator.cpp
	Implementation of Exception_FileManipulator.h
		It will eventually be renamed ExceptionFileManipulator (to be more
		stylistically pleasing).

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#include "Exception_FileManipulator.h"
#include <iostream>

Exception_FileManipulator::Exception_FileManipulator()
{
	exceptionFile = "";
	exceptionFileLine = "";
}

Exception_FileManipulator::Exception_FileManipulator(string file, string line)
{
	exceptionFile = file;
	exceptionFileLine = line;
}
