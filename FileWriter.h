/**
	k_amber-reader
	FileWriter.h
	FileWriter (fwriter) inherits from FileManipulator. It can work with
		FileReader.h to create readable output for the user. The associated 
		FileReader generates the data, while the FileWriter "decrypts" the 
		data and makes it user friendly.

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#pragma once
#include "FileManipulator.h"
#include "FileReader.h"

class FileWriter : FileManipulator
{
public:

	/**
		Constructor for fwriter objects. This constructor takes
			an explicit path for its output.
		Parameters:
			string path - Associated path to the output
		Returns:
			An fwriter object
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
	*/
	FileWriter();

	void write_surface_average(FileReader& input, double threshold);
	void write_hydrogen_bond_intra_avg(FileReader& input, double threshold);

};