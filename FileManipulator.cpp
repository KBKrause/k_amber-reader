/**
	k_amber-reader
    FileManipulator.cpp
	Implementation of FileManipulator.h

    Author(s): Kevin B. Krause
    Version:   unreleased
*/

#include "FileManipulator.h"

using namespace std;

FileManipulator::FileManipulator(string f)
{
	filePath = f;
}
//--
bool FileManipulator::open_file(ifstream& inFile)
{
	inFile.open(filePath.c_str());

	if (inFile.good())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--
bool FileManipulator::close_file(ifstream& inFile)
{
	inFile.close();

	if (inFile.is_open() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--