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
	PRN_WARNING(AT);
	filePath = "";
}
//--
string FileManipulator::getFilePath()
{
	return filePath;
}