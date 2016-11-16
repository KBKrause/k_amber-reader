#pragma once
#include <string>
#include <fstream>
#include <iostream>

#include "Exception_FileManipulator.h"

using namespace std;

class FileManipulator
{
public:
	
	// What is filePath_read_write currently used for?

	FileManipulator(string f);

	/* configure the reading filePath_read, writing filePath_read,
	and future options. Returns true if all changes succesfully made.*/
	bool configure(string in_read_path, string in_write_path);

protected:

	ifstream open_file();

	// returns true if the file's state is closed (or NOT is_open())
	bool close_file();

	ofstream open_for_writing(string path);

	//----- DATA MEMBERS -----//

	string filePath_read;
	string filePath_read_write;
	
};