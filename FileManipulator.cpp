#include "FileManipulator.h"

using namespace std;

FileManipulator::FileManipulator(string f)
{
	filePath_read = f;
}
//--
ifstream FileManipulator::open_file()
{
	ifstream inFile;

	inFile.open(filePath_read);

	if (inFile.good())
	{
		return inFile;
	}
	else
	{
		Exception_FileManipulator ex("open_file(): unable to use filePath_read!");
		throw ex;
	}
}
//--
bool FileManipulator::close_file()
{
	ifstream inFile;

	inFile.close();

	if (inFile.is_open() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--
ofstream FileManipulator::open_for_writing(string path)
{
	ofstream outFile;

	outFile.open(path);

	if (outFile.good())
	{
		return outFile;
	}
	else
	{
		Exception_FileManipulator ex("open_for_writing(): unable to open filePath for writing!");
		throw ex;
	}
}
//--
bool FileManipulator::configure(string in_read_path, string in_write_path)
{
	// numChanges will be the number of things to change/add
	int numChanges = 0;

	ifstream verify_read;
	ofstream verify_write;

	verify_read.open(in_read_path);
	verify_write.open(in_write_path);

	if (verify_read.good())
	{
		filePath_read = in_read_path;
		numChanges++;
	}
	else
	{
		cout << "Unable to configure new reading filePath_read: " << in_read_path << endl;
	}
	verify_read.close();

	
	if (verify_write.good())
	{
		filePath_read_write = in_write_path;
		numChanges++;
	}
	else
	{
		cout << "Unable to configure new writing filePath_read: " << in_write_path << endl;
	}
	verify_write.close();

	if (numChanges == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}