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
   		Constructor for fmanip objects
   		Parameters:
      		string f - Path to the file being used
   		Returns:
      		An fmanip object
		Bugs:
			none
	*/
	FileManipulator(string f);

protected:

	/**
   		Helper function to open a file
   		Parameters:
      		ifstream& inFile - Handle used by child class
   		Returns:
			  true - File found and opened without error
			  false - File not opened successfully
		Bugs:
			none
	*/
	bool open_file(ifstream& inFile);
	/**
   		Helper function to close a file
   		Parameters:
      		ifstream& inFile - Handle used by child class
   		Returns:
			true - File closed successfully
			false - File is still open
		Bugs:
			none
	*/
	bool close_file(ifstream& inFile);

	//----- DATA MEMBERS -----//

	string filePath;
	
};