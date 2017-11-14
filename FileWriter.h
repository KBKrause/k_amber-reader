/**
	k_amber-reader
	FileWriter.h
	FileWriter (fwriter) inherits from FileManipulator. It can work with
		FileReader.h to create readable output for the user.
		This class is, essentially, a "wrapper" for std::ofstream.

	Notable Bugs:
		-Use mem_fn or std::bind to simplify write_any and other write functions.
			**Lambda functions

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#pragma once
#include "FileManipulator.h"
#include "FileReader.h"

class FileWriter : public FileManipulator
{
public:

	/**
		Constructor for fwriter objects. This constructor takes
			an explicit path for its output.
		Parameters:
			string path - Associated path to the output
		Returns:
			An fwriter object
		Bugs:
			The ONLY thing this will do is overwrite a file.
			Does not check permissions, if it exists, etc.
	*/
	FileWriter(string path);
	/**
		Constructor for fwriter objects. This constructor is empty
			and will use automatically generate names depending on the method
			being used to write.
		Parameters:
			none
		Returns:
			An fwriter object
		Bugs:
			11/13/2017: Does it actually automatically generate names, as it indicates?
	*/
	FileWriter();
	/**
		TODO
	*/
	bool set_file_path(string newPath) override;

	/**
	10/27/2017
		These are the methods that actually create and write to files the output of FileReader's
			derived classes.
		They all require a FileReader object as its input and possible additional parameters
			depending on the specific analysis.
		Each method reads as 1) open, 2) ofstream << input.analyze(), 3) close
	11/13/2017: This doesn't really fix the problem of the FileReader and parameters being independent of each other.
				Can function pointers be used to help tie together the parameters of analyze() with the type of FileReader?
	*/
	void write_analysis(FileReader& input, double threshold);
	void write_analysis(FileReader& input, string s);
	void write_analysis(FileReader& input);

private:

	/**
		Overrides FileManipulator::open_file()
		Attempts to open the file associated with this object, using the ioFile handle.
		If no path is specified, a new file is created.
		Parameters:
			none
		Returns:
			none
		Bugs:
			Creates a garbage file name if the default ctor was used to create this object.
	*/
	void open_file() override;
	/**
		Overrides FileManipulator::close_file()
		Attempts to close the file associated with this object, using the ioFile handle.
		Parameters:
			none
		Returns:
			none
	*/
	void close_file() override;
};