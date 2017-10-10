/**
	k_amber-reader
    FileManipulator.h
	FileManipulator (fmanip) is an easy way for non-programmers
		to navigate and use the unix or windows file system. It also takes
		care of reading, writing, etc.

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
   		Helper function to open a file
   		Parameters:
			none
   		Returns:
			  true - File found and opened without error
			  false - File not opened successfully
		Bugs:
			none
	*/
	bool open_file();
	/**
   		Helper function to close a file
   		Parameters:
			none
   		Returns:
			true - File closed successfully
			false - File is still open
		Bugs:
			none
	*/
	bool close_file();
	/**
		Configure this fmanip to use a new file for reading. The old one will be discarded.
		Parameters:
			string newPath - Path to the new file being read
		Returns:
			true - Old file closed and newPath set
			false - Either: newPath does not exist, OR old file is still open/cannot be closed
		Bugs:
			none
		Other:
			Can we report how it failed (stderr) and why it returns false?
	*/
	bool set_file_path_read(string newPath);
	/**
		Configure this fmanip to use a new file for writing. The old one (associated file)
			will be discarded.
		Parameters:
			string newPath - Path to the new file being read
		Returns:
			true - Old file closed and newPath set
			false - Either: newPath does not exist, OR old file is still open/cannot be closed
		Bugs:
			none
		Other:
			Can we report how it failed (stderr) and why it returns false?
	*/
	bool set_file_path_write(string newPath);

	// The handle for interacting with the current file being used.
	fstream ioFile;

private:

	// The path to the file being used.
	string filePath;

};