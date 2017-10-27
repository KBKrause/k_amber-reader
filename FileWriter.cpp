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
bool FileWriter::set_file_path(string newPath)
{
	PRN_WARNING(AT);

	this->filePath = newPath;
	return true;
}
//--
void FileWriter::write_analysis(FileReader& input, double threshold)
{
	open_file();

	this->ioFile << input.analyze(threshold);

	close_file();
}
//--
void FileWriter::write_analysis(FileReader& input, string s)
{
	open_file();

	this->ioFile << input.analyze(s);

	close_file();
}
//
void FileWriter::write_analysis(FileReader& input)
{
	open_file();

	this->ioFile << input.analyze();

	close_file();
}
//--
void FileWriter::open_file()
{
	PRN_WARNING(AT);

	this->ioFile.open(this->filePath, fstream::out);
}

void FileWriter::close_file()
{
	PRN_WARNING(AT);

	this->ioFile.close();
}