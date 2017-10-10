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
	PRN_WARNING();
	filePath = "";
}
//--
bool FileManipulator::open_file()
{
	ioFile.open(filePath);

	if (ioFile.good())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--
bool FileManipulator::close_file()
{
	// Should there be protection here, so that close cannot be called if
		// it has never opened something?
	ioFile.close();

	if (ioFile.is_open() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FileManipulator::set_file_path_read(string newPath)
{
	ifstream exists(newPath);

	if (!exists)
	{
		return false;
	}
	else
	{
		if (close_file())
		{
			filePath = newPath;
			return true;
		}
		else
		{
			return false;
		}
	}
}

string FileManipulator::getFilePath()
{
	return filePath;
}