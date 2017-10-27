/**
	k_amber-reader
	FileReader.cpp
	Implementation of FileReader.h.

	Notable Bugs:
		-Reduce opening of files to a function.
		-Automatically close files at the end of file reading, writing, etc.
			functions. Destructor?
		-Add safety checks to read, write, open, close, etc.
		-Add function for screen printouts.

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#include "FileReader.h"
#include "Compute.h"
#include <string.h>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iterator>

FileReader::FileReader(string filePath) : FileManipulator(filePath)
{
	//cout << "FileReader created with file: " << filePath << endl;
}
//--
void FileReader::count_string()
{
	pre_read_greeting(__FUNCTION__, "Count the instances of strings in a file");

	string in_string = " ";
	vector <string> searchWords;
	// The freq_vec is a "mirrored" vector that matches the string at index n of searchWords
	// at index n. This is not a good use of memory and can be improved.
	vector <int> freq_vec;

	cout << "Enter all the strings to search for, separated with spaces." << endl;
	cout << "End the list of strings with ;; :" << endl;

	while (in_string != ";;")
	{
		cin >> in_string;

		if (in_string == ";;")
		{
			break;
		}

		searchWords.push_back(in_string);
		freq_vec.push_back(0);
	}

	string phr;

	cout << "Searching for occurences ..." << endl;

	while (this->ioFile.good())
	{
		this->ioFile >> phr;

		// TODO:
		// There is likely a better way than to perform a linear search.
		for (size_t i = 0; i < searchWords.size(); i++)
		{
			if (searchWords[i] == phr)
			{
				freq_vec[i]++;
			}
		}
	}

	cout << "Occurences found: " << endl;
	
	for (size_t i = 0; i < searchWords.size(); i++)
	{
		cout << searchWords[i] << " found " << freq_vec[i] << " times" << endl;
	}

	// TODO
	// Create a way to automatically close files at the end of each function.
	// Throw exceptions.
	this->ioFile.close();
}
//--
void FileReader::distance_atoms(double threshold_distance)
{
	/*
	cout << "*-*-*-*-*-*-*-*-*-*-* DISTANCE.IN *-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "INPUT = " << this->getFilePath() << endl;
	//cout << "OUTPUT .dat = " << output_file << endl;
	cout << "MAXIMUM ANGSTROM DISTANCE = " << threshold_distance << endl;
	*/

	this->ioFile.open(this->filePath);

	// Is this string really necessary?
	string garbage;

	struct frame_pair
	{
		int start_frame;
		int end_frame;
	};

	this->ioFile >> garbage >> garbage;

	vector < frame_pair > distances;

	frame_pair val;
	val.start_frame = -1;
	val.end_frame = -1;

	int best_frame;
	double best_distance = INT_MAX;

	int iterator;

	while (this->ioFile.good())
	{
		double angstroms;
		
		this->ioFile >> iterator;
		this->ioFile >> angstroms;

		if (angstroms < best_distance)
		{
			best_distance = angstroms;
			best_frame = iterator;
		}

		if (angstroms <= threshold_distance)
		{
			if (val.start_frame == -1)
			{
				val.start_frame = iterator;
			}
		}
		else if ((angstroms > threshold_distance) && (val.start_frame != -1))
		{
			val.end_frame = iterator;
			distances.push_back(val);
			val.start_frame = -1;
			val.end_frame = -1;
		}
	}

	cout << endl << "RANGES WITH MAXIMUM DISTANCE THRESHOLD = " << threshold_distance << ", FOUND: " << distances.size() << endl;
	cout << "Lowest distance located at frame: " << best_frame << ", with distance: " << best_distance << " angstroms." << endl;
	cout << "FRAME START	FRAME END" << endl;

	/*
	for (unsigned int i = 0; i < DISTANCES.size(); i++)
	{
		cout << DISTANCES[i].start_frame << "		" << DISTANCES[i].end_frame << endl;
	}
	*/

	this->ioFile.close();
}
//--
void FileReader::open_file()
{
	// What is this even good for?
	this->ioFile.open(this->filePath);
}
//--
void FileReader::close_file()
{
	this->ioFile.close();
}
inline void FileReader::invalid_analysis()
{
	Exception_FileManipulator e;
	throw e;
}
//--
bool FileReader::set_file_path(string newPath)
{
	if (isValidFile(newPath))
	{
		this->filePath = newPath;
		return true;
	}
	else
	{
		return false;
	}
}
//--
string FileReader::analyze(double threshold)
{
	invalid_analysis();
	return "";
}
string FileReader::analyze(string s)
{
	invalid_analysis();
	return "";
}
string FileReader::analyze()
{
	invalid_analysis();
	return "";
}
//--
void FileReader::pre_read_greeting(string title, string msg)
{
	cout << "*-*-*-*-*-*-*-*-*-*-* " << title << " *-*-*-*-*-*-*-*-*-*-* \n";
	cout << "INPUT = " + this->getFilePath() + "\n";
	cout << msg << endl;
}
//--