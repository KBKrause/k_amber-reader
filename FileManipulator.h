/**
	k_amber-reader
    FileManipulator.h
	FileManipulator encapsulates the responsibilities of file reading
		and file writing. It is the base class for FileReader and FileWriter.
		As a base class, it cannot be instantiated.

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
	 Proposed functions as static methods.
	 If not here, then in another class. This class can be used in input files/instructions
		like the ones given to cpptraj. The program can direct output from each "run" to a new
		directory.

	static bool make_directory();
	static bool remove_directory();
	static bool make_file();
	static bool del_file();
	static bool change_perms(); // file or "directory"
	*/

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
   		Pure virtual function for file opening. Its behavior is dependent on the inheriting class.
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
   		Pure virtual function for file closing. Its behavior is dependent on the inheriting class.
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

	// Stream handle.
	fstream ioFile;

	// The path to the file being used.
	string filePath;
};