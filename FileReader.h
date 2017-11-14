/**
	k_amber-reader
    FileReader.h
	FileReader (freader) inherits from FileManipulator. Its main use
		is to read output from AMBER.
		FileReader will not generate any files. 
		In the case that FileReader's work should be saved, the FileWriter class can be used.

	Notable Bugs:
		10/18/2017: Maybe remove a lot of miscellaneous work from reader into writer, or
		provide better names. As it is now, the only difference between the reader and writer
		is that the reader creates a string and the writer puts it into a file. It adds a lot
		of extra work that is not necessary. This isn't so bad because all the code necessary
		to read and write exists; the problem lies in deciding where that code should go.

    Author(s): Kevin B. Krause
    Version:   unreleased
*/

#pragma once
#include "FileManipulator.h"
#include <vector>
#include <unordered_map>

class FileReader : public FileManipulator
{
public:

	/**
		Constructor for FileReader objects. Because freader does not
		   have any private data members, it is an empty constructor
		   that also calls the constructor for FileManipulator.
   		Parameters:
      		string filePath - Path to the file being used
   		Returns:
      		An freader object
	*/
	FileReader(string filePath);
	/**
   		Asks the user for n strings and searches for those n strings in a file
   		Parameters:
      		none
   		Returns:
			none
		Bugs:
			This function matches punctuation and case when searching. It should not.
		It should remove all puncutation and change all case to lower case.
			11/13/2017: Static method? Only 1 implementation of count_string() ever needed at once.
	*/
	void count_string();
	/**
		Determines the distances between two atoms. 
		Typically, it used in conjunction with hbond_intra_avg to determine which frames from the simulation can best represent a
			hydrogen bond. The corresponding AMBER input file is a distance.dat between two atoms.
		Parameters:
			double threshold_persistence - the percent at which to stop reading the configured file
				A 5% threshold should be passed as 0.05.
		Returns:
			none
		Bugs:
			10/23/2017: Returns an empty string with threshold 0 and 100. Fix.
			11/13/2017: Does this count as its own "simulation," or should it remain in FileReader?
	*/
	void distance_atoms(double threshold_distance);
	/**
		Configure this object to use a new file for reading. The old one (associated file)
			will be discarded.
		Parameters:
			string newPath - Path to the new file being read
		Returns:
			true - Old file closed and newPath set
			false - Either: newPath does not exist, OR old file is still open/cannot be closed
		Other:
			Can we report how it failed (stderr) and why it returns false?
	*/
	bool set_file_path(string newPath) override;

	/*
	10/27/2017
		These are the overrideable methods provided by FileReader to its derived classes.
		They are all called "analyze" with several different parameter lists.
		Each derived class may override one/some of these functions, but not all.
		Because not all classes will use each of them, I decided not to make these pure virtual functions.
		If a derived FileReader object's analyze method is called without implementation, the base class
			function will be called, which will throw an exception.
	*/
	virtual string analyze(double threshold);
	virtual string analyze(string s);
	virtual string analyze();

protected:

	inline void pre_read_greeting(string title, string msg);

	// override for FileManipulator::open_file
	void open_file() override;
	// override for FileManipulator::close_file
	void close_file() override;
};