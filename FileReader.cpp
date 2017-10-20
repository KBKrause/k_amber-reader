/**
	k_amber-reader
	FileReader.cpp
	Implementation of FileReader.h.

	Notable Bugs:
		-Reduce opening of files to a function.
		-Automatically close files at the end of file reading, writing, etc.
			functions. Destructor?
		-Add safety checks to read, write, open, close, etc.

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
	cout << "FileReader created with file: " << filePath << endl;
}
//--
void FileReader::count_string()
{
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
string FileReader::hydrogen_bond_intra_average(double threshold_persistence)
{
	string output = "";

	this->ioFile.open(this->filePath);

	vector <string> ACCEPTORS;
	unordered_map < string, vector < hbond_child > > DONORS;

	string in_string = "";
	double in_frac;

	output += "*-*-*-*-*-*-*-*-*-*-* HBOND-INTRA-AVG.DAT *-*-*-*-*-*-*-*-*-*-* \n";
	output += "INPUT = " + this->getFilePath() + "\n";
	//output += "OUTPUT .dat = " << output_file << endl;
	output += "HYDROGEN BONDS ACCEPTED AT THRESHOLD MINIMUM = " + to_string(threshold_persistence) + "\n";

	// first 6 words aren't needed
	for (int i = 0; i < 7; i++)
	{
		this->ioFile >> in_string;
	}

	while (this->ioFile.good())
	{
		this->ioFile >> in_string;
		string atom_copy = in_string;
		string chain_copy = in_string;
		
		//  -- #Acceptor Work -- //
		string acceptorAtom = atom_copy.erase(0, in_string.find('@') + 1);
		string acceptorChain = chain_copy.erase(0, in_string.find('_') + 1);

		acceptorChain = acceptorChain.erase(acceptorChain.find('@'), acceptorChain.size());

		//cout << "Acceptor atom is " << acceptorAtom << endl;
		//cout << "Acceptor chain is " << acceptorChain << endl;
		// --

		this->ioFile >> in_string;
		this->ioFile >> in_string;

		// -- #Donor Work -- //
		string donorAtom;
		string donorChain;

		atom_copy = in_string;
		chain_copy = in_string;

		donorAtom = atom_copy.erase(0, in_string.find('@') + 1);
		donorChain = chain_copy.erase(0, in_string.find('_') + 1);
		donorChain = donorChain.erase(donorChain.find('@'), donorChain.size());

		//cout << "Donor atom: " << donorAtom << endl;
		//cout << "Donor chain is " << donorChain << endl;
		// --

		this->ioFile >> in_string;
		this->ioFile >> in_frac;

		// -- #Frac Work -- //
		//cout << "Persistence: " << in_frac << endl;
		// --

		// arbitrary 
		if (in_frac < threshold_persistence)
		{
			break;
		}
		
		// Update Lists //
		// if the acceptor is new, add it
		if (found_acceptor(ACCEPTORS, acceptorAtom) == false)
		{
			ACCEPTORS.push_back(acceptorAtom);
			
			vector <hbond_child> DONOR;

			hbond_child sct;
			sct.acceptor_chain = acceptorChain;
			sct.donor_chain = donorChain;
			sct.persistence = in_frac;

			DONOR.push_back(sct);

			DONORS.insert({ acceptorAtom + "_" + donorAtom, DONOR });

			//cout << "New acceptor atom: " << acceptorAtom << endl;
		}
		// else, if the donor is new, but the acceptor is not new, add the new donor to the acceptor
		else if (found_donor(DONORS, acceptorAtom, donorAtom) == false)
		{
			hbond_child sct;
			sct.acceptor_chain = acceptorChain;
			sct.donor_chain = donorChain;
			sct.persistence = in_frac;

			vector <hbond_child> DONOR;

			DONOR.push_back(sct);

			DONORS.insert({ acceptorAtom + "_" + donorAtom, DONOR });

			//cout << "New donor for: " << acceptorAtom << " found: " << donorAtom << endl;
		}
		// otherwise, add the hbond to the donor that already exists
		else
		{
			hbond_child sct;
			sct.acceptor_chain = acceptorChain;

			sct.donor_chain = donorChain;
			sct.persistence = in_frac;

			DONORS[acceptorAtom + "_" + donorAtom].push_back(sct);

			//cout << "Bond added for acceptor: " << acceptorAtom << " at donor: " << donorAtom << endl;
		}

		//cout << endl;

		// could cause issues later if it reaches the end of the file...
		for (int i = 0; i < 2; i++)
		{
			this->ioFile >> in_string;
		}
	}

	// had to hard code in the second for loop and onwards
	// not sure how to account for an N, then an N1, and so on
	// or if a certain acceptor has already encountered a certain donor

	for (size_t i = 0; i < ACCEPTORS.size(); i++)
	{
		output += "BONDS AT ACCEPTOR: " + ACCEPTORS[i] + "\n";
		output += "ACCEPTOR CHAIN";
		output += "		";
		output += "DONOR CHAIN";
		output += "		";
		output += "PERSISTENCE \n";

		output += "\n";
		
		output += "DONOR: N \n";
		for (size_t j = 0; j < DONORS[ACCEPTORS[i] + "_" + "N"].size(); j++)
		{
			output += DONORS[ACCEPTORS[i] + "_" + "N"][j].acceptor_chain;
			output += "			";
			output += DONORS[ACCEPTORS[i] + "_" + "N"][j].donor_chain;
			output += "			";
			output += to_string(DONORS[ACCEPTORS[i] + "_" + "N"][j].persistence);

			output += "\n";
		}

		output += "DONOR: N1 \n";
		for (size_t j = 0; j < DONORS[ACCEPTORS[i] + "_" + "N1"].size(); j++)
		{
			output += DONORS[ACCEPTORS[i] + "_" + "N1"][j].acceptor_chain;
			output += "			";
			output += DONORS[ACCEPTORS[i] + "_" + "N1"][j].donor_chain;
			output += "			";
			output += to_string(DONORS[ACCEPTORS[i] + "_" + "N1"][j].persistence);

			output += "\n";
		}
	}

	cout << "View debugging info? (Y / N): ";
	char choice;
	cin >> choice;

	if (choice == 'Y')
	{
		cout << "Debugging info: " << endl;
		cout << "Hydrogen cannot accept or donate electron pairs" << endl << endl;
		cout << "Contents of DONORS:" << endl << endl;
		for (auto iter = DONORS.begin(); iter != DONORS.end(); ++iter)
		{
			cout << iter->first << endl;

			for (size_t i = 0; i < iter->second.size(); i++)
			{
				cout << iter->second[i].acceptor_chain << ", " << iter->second[i].donor_chain << ", " << iter->second[i].persistence << endl;
			}

			cout << endl;
		}
	}

	this->ioFile.close();

	return output;
}
//--
void FileReader::distance_atoms(double threshold_distance)
{
	cout << "*-*-*-*-*-*-*-*-*-*-* DISTANCE.IN *-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "INPUT = " << this->getFilePath() << endl;
	//cout << "OUTPUT .dat = " << output_file << endl;
	cout << "MAXIMUM ANGSTROM DISTANCE = " << threshold_distance << endl;

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
string FileReader::surface_average()
{
	string retVal = "";

	retVal += "*-*-*-*-*-*-*-*-*-*-* SURFACE.DAT ANALYSIS *-*-*-*-*-*-*-*-*-*-*\n";
	retVal += "INPUT = " + this->getFilePath() + "\n";

	this->ioFile.open(this->filePath);

	double lowestSurface = DBL_MAX;
	double highestSurface = DBL_MIN;

	int lowestFrame = INT_MAX;
	int highestFrame = INT_MIN;

	int currentFrame;
	double currentSurface;

	vector <double> surfaces;

	// seekg - seek "get" pointer, move it past the initial strings
	this->ioFile.seekg(sizeof("#Frame") + sizeof("SA_00000"));

	if (this->ioFile.good())
	{
		this->ioFile >> currentFrame;
		this->ioFile >> currentSurface;

		while (this->ioFile.good())
		{
			surfaces.push_back(currentSurface);

			if (currentSurface < lowestSurface)
			{
				lowestSurface = currentSurface;
				lowestFrame = currentFrame;
			}
			else if (currentSurface > highestSurface)
			{
				highestSurface = currentSurface;
				highestFrame = currentFrame;
			}

			ioFile >> currentFrame >> currentSurface;
		}
	}

	retVal += "The highest frame was " + to_string(highestFrame) + " with a surface area of " + to_string(highestSurface)
		+ " squared angstroms" + "\n";
	retVal += "The lowest frame was " + to_string(lowestFrame) + " with a surface area of " + to_string(lowestSurface)
		+ " squared angstroms" + "\n";
	retVal += "The average exposed surface area was " + to_string(Compute::average(surfaces)) + " angstroms" + "\n";
	retVal += "The standard deviation is +/- " + to_string(Compute::standard_deviation(surfaces)) + " angstroms\n";

	this->ioFile.close();

	return retVal;
}
//--
bool FileReader::found_acceptor(vector < string > in_ACCEPTORS, string search_atom)
{
	for (size_t i = 0; i < in_ACCEPTORS.size(); i++)
	{
		if (in_ACCEPTORS[i] == search_atom)
		{
			return true;
		}
	}

	return false;
}
//--
bool FileReader::found_donor(unordered_map<string, vector<hbond_child>>& in_DONORS, string acceptor_search_atom, string donor_search_atom)
{
	if (in_DONORS.find(acceptor_search_atom + "_" + donor_search_atom) == in_DONORS.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}
//--
void FileReader::open_file()
{
	this->ioFile.open(this->filePath);
}
//--
void FileReader::close_file()
{
	this->ioFile.close();
}
//--
bool FileReader::set_file_path(string newPath)
{
	if (FileManipulator::isValidFile(newPath))
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
void FileReader::autofix_pdb(string monomer)
{
	if (monomer.length() != 3)
	{
		return;
	}

	cout << "Fixing pdb ..." << endl;

	//ofstream fixedPDB;
	//fixedPDB.open("C:/Users/Kevin/Documents/Github/k_amber-reader/data/fixedPDB.dat");

	open_file();

	char thisChar;

	string thisString;
	vector < string > thisLine;

	while (this->ioFile.good())
	{
		ioFile.get(thisChar);

		if ((thisChar == ' ') || (thisChar == '\n'))
		{
			if (thisString == "INT")
			{
				thisString = monomer;
			}

			thisString.push_back(thisChar);
			thisLine.push_back(thisString);
			thisString.clear();

			if (thisChar == '\n')
			{
				if ((thisLine[0] != "LINK ") && (thisLine[0] != "CONECT "))
				{
					for (size_t i = 0; i < thisLine.size(); i++)
					{
						//fixedPDB << thisLine[i];
					}
				}

				thisLine.clear();
			}
		}
		else
		{
			thisString.push_back(thisChar);
		}
	}

	//fixedPDB.close();

	close_file();
}
//--