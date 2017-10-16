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
	*/
	FileWriter();
	/**
		Writes the resulting output of FileReader::surface_average() to the file being used
			by this object.
		Parameters:
			FileReader& input - Reference to a specific file being used by FileReader
		Returns:
			none
	*/
	void write_surface_average(FileReader& input);
	/**
		Writes the resulting output of FileReader::hydrogen_bond_intra_avg() to the file being
			used by this object.
		Parameters:
			FileReader& input - reference to a specific file being used by FileReader
			double threshold - The percent at which to stop reading the configured file.
				A 5% threshold should be passed as 0.05.
		Returns:
			none
		Bugs:
			Will just write without any conditions.
	*/
	void write_hydrogen_bond_intra_avg(FileReader& input, double threshold);
	/**
		Configure this object to use a new file for writing. The old one (associated file)
			will be discarded.
		Parameters:
			string newPath - Path to the new file being read
		Returns:
			true - Old file closed and newPath set
			false - Either: newPath does not exist, OR old file is still open/cannot be closed
		Bugs:
			Does not check validity of new path.
		Other:
			Can we report how it failed (stderr) and why it returns false?
	*/
	bool set_file_path(string newPath) override;

	//void write_any(FileReader& input, void(*write_func)(FileReader&));

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