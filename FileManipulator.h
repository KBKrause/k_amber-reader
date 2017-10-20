/**
	k_amber-reader
    FileManipulator.h
	FileManipulator (fmanip) is an easy way for non-programmers
		to navigate and use the unix or windows file system. It also takes
		care of reading, writing, etc.

	Notable Bugs:
		-Change the stream handle to private data member in inherited objects.
		They are class specific.

    Author(s): Kevin B. Krause
    Version:   unreleased
*/

#pragma once
#include <string>
#include <fstream>
#include <iostream>

#include "Exception_FileManipulator.h"

using namespace std;

class FileManipulator
{
public:

	/**
		Getter methods for private data:
		string filePath
	*/
	string getFilePath();
	/**
		Pure virtual function to configure this fmanip to use a new file. The old one will be discarded.
			Depending on the object, the definition will vary.
		Parameters:
			string newPath - Path to the new file being read
		Returns:
			True and false return values dependent on class.
		Bugs:
			none
		Other:
			Can we report how it failed (stderr) and why it returns false?
	*/
	virtual bool set_file_path(string newPath) = 0;
	/**
		Static function that determines if a path exists and can be opened for reading.
		Parameters:
			string newPath - Path to the file being read
		Returns:
			true - if the file can be opened and read
			false - if the file does not exist, or it cannot be opened
		Bugs:
			none
		Other:
			Can we report how it failed (stderr) and why it returns false?
	*/
	static bool isValidFile(string newPath);

	// Proposed Functions
	/*
	static bool make_directory();
	static bool remove_directory();
	static bool make_file();
	static bool del_file();
	static bool change_perms(); // file or "directory"
	*/

protected:

	/**
		Constructor for fmanip objects. It needs to be protected so that it can
			only be called by inheriting classes.
		Parameters:
			string f - Path to the file being used
		Returns:
			An fmanip object
		Bugs:
			none
	*/
	FileManipulator(string f);
	/**
		Constructor for fmanip objects. The default constructor will have its
			path set in the future (hopefully) and reset as needed.
		Parameters:
			none
		Returns:
			An fmanip object
		Bugs:
			Safety
	*/
	FileManipulator();
	/**
   		Pure virtual function for file opening
   		Parameters:
			none
   		Returns:
			  none
		Bugs:
			none
		Other:
			Should throw exceptions.
	*/
	virtual void open_file() = 0;
	/**
   		Pure virtual function for file closing
   		Parameters:
			none
   		Returns:
			none
		Bugs:
			none
		Other:
			Should throw exceptions.
	*/
	virtual void close_file() = 0;

	fstream ioFile;

	// The path to the file being used.
	string filePath;
};