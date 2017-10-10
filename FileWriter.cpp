/**
	k_amber-reader
	FileWriter.cpp
	Implementation of FileWriter.h.

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#include "FileWriter.h"

FileWriter::FileWriter(string path) : FileManipulator(path)
{
	
}

FileWriter::FileWriter()
{
	PRN_WARNING();
}
