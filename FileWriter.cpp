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

void FileWriter::write_autofix_pdb(FileReader & input, string monomer)
{
	open_file();

	// this->ioFile << input.autofix_pdb(monomer);

	close_file();
}

bool FileWriter::set_file_path(string newPath)
{
	PRN_WARNING(AT);
	this->filePath = newPath;
	return true;
}

void FileWriter::open_file()
{
	PRN_WARNING(AT);

	if (this->filePath != "")
	{
		this->ioFile.open(this->filePath, fstream::out);
	}
	else
	{
		// This string is full of shit
		string newPath = __DATE__;
		this->ioFile.open(newPath, fstream::out);
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