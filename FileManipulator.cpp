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
FileManipulator::FileManipulator()
{
	// This constructor exists for the FileWriter's empty constructor.
	PRN_WARNING(AT);
	filePath = "";
}
//--
string FileManipulator::getFilePath()
{
	return filePath;
}
//--
bool FileManipulator::isValidFile(string newPath)
{
	ifstream exists(newPath);

	if (!exists)
	{
		return false;
	}
	else
	{
		return true;
	}
}
