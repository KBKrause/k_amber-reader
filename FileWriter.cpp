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

FileWriter::FileWriter() : FileManipulator()
{
	// This FileWriter has no string associated with it. This is bad.
	// Without a path to write to, it will not produce any output.
	// It will need to be initialized before any methods are called.
	PRN_WARNING(AT);
}

void FileWriter::write_surface_average(FileReader& input)
{
	open_file();

	this->ioFile << input.surface_average();

	close_file();
}

void FileWriter::write_hydrogen_bond_intra_avg(FileReader& input, double threshold)
{
	open_file();

	this->ioFile << input.hydrogen_bond_intra_average(threshold);

	close_file();
}

void FileWriter::write_autofix_pdb(FileReader& input, string monomer)
{
	open_file();

	this->ioFile << input.autofix_pdb(monomer);

	close_file();
}

bool FileWriter::set_file_path(string newPath)
{
	if (FileManipulator::isValidFile(newPath))
	{
		this->filePath = newPath;
		return true;
	}
	else
	{
		return false;
	}
}

void FileWriter::open_file()
{
	PRN_WARNING(AT);

	// If the file being written to is one that already exists, overwriting is not allowed.
	if (FileManipulator::isValidFile(this->filePath))
	{
		Exception_FileManipulator ex;
		throw ex;
	}
	else
	{
		this->ioFile.open(this->filePath, fstream::out);
	}
}

void FileWriter::close_file()
{
	PRN_WARNING(AT);

	this->ioFile.close();
}

/*
void FileWriter::write_any(FileReader& input, void(*write_func)(FileReader&))
{
open_file();

write_func(input);

close_file();
}
*/