/**
	k_amber-reader
	FileReader.cpp
	Implementation of FileReader.h.

	Notable Bugs:
		-Reduce opening of files to a function.
		-Automatically close files at the end of file reading, writing, etc.
			functions. Destructor?

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#include "FileReader.h"
#include <string>
#include <unordered_map>

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
	if (this->close_file() == true)
	{
		cout << "File closed successfully" << endl;
	}
	else
	{
		Exception_FileManipulator ex;
		throw ex;
	}
}
//--
void FileReader::hydrogen_bond_intra_average(double threshold_persistence)
{
	if (this->open_file() == false)
	{
		Exception_FileManipulator ex;
		throw ex;
	}

	vector <string> ACCEPTORS;
	unordered_map < string, vector < hbond_child > > DONORS;

	string in_string = "";
	double in_frac;

	cout << "*-*-*-*-*-*-*-*-*-*-* HBOND-INTRA-AVG.DAT *-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "INPUT = " << this->getFilePath() << endl;
	//cout << "OUTPUT .dat = " << output_file << endl;
	cout << "HYDROGEN BONDS ACCEPTED AT THRESHOLD MINIMUM = " << threshold_persistence << endl;

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

	cout << endl << "Done" << endl << endl;

	// had to hard code in the second for loop and onwards
	// not sure how to account for an N, then an N1, and so on
	// or if a certain acceptor has already encountered a certain donor

	for (size_t i = 0; i < ACCEPTORS.size(); i++)
	{
		cout << "BONDS AT ACCEPTOR: " << ACCEPTORS[i] << endl;
		cout << "ACCEPTOR CHAIN";
		cout << "		";
		cout << "DONOR CHAIN";
		cout << "		";
		cout << "PERSISTENCE" << endl;

		cout << endl;
		
		cout << "DONOR: N" << endl;
		for (size_t j = 0; j < DONORS[ACCEPTORS[i] + "_" + "N"].size(); j++)
		{
			cout << DONORS[ACCEPTORS[i] + "_" + "N"][j].acceptor_chain;
			cout << "			";
			cout << DONORS[ACCEPTORS[i] + "_" + "N"][j].donor_chain;
			cout << "			";
			cout << DONORS[ACCEPTORS[i] + "_" + "N"][j].persistence;

			cout << endl;
		}

		cout << "DONOR: N1" << endl;
		for (size_t j = 0; j < DONORS[ACCEPTORS[i] + "_" + "N1"].size(); j++)
		{
			cout << DONORS[ACCEPTORS[i] + "_" + "N1"][j].acceptor_chain;
			cout << "			";
			cout << DONORS[ACCEPTORS[i] + "_" + "N1"][j].donor_chain;
			cout << "			";
			cout << DONORS[ACCEPTORS[i] + "_" + "N1"][j].persistence;

			cout << endl;
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

	if (this->close_file() == false)
	{
		Exception_FileManipulator ex;
		throw ex;
	}
}
//--
void FileReader::distance_atoms(double threshold_distance)
{
	cout << "*-*-*-*-*-*-*-*-*-*-* DISTANCE.IN *-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "INPUT = " << this->getFilePath() << endl;
	//cout << "OUTPUT .dat = " << output_file << endl;
	cout << "MAXIMUM ANGSTROM DISTANCE = " << threshold_distance << endl;

	if (this->open_file() == false)
	{
		Exception_FileManipulator ex;
		throw ex;
	}

	// Is this string really necessary?
	string garbage;

	struct frame_pair
	{
		int start_frame;
		int end_frame;
	};

	this->ioFile >> garbage >> garbage;

	vector < frame_pair > DISTANCES;

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
			DISTANCES.push_back(val);
			val.start_frame = -1;
			val.end_frame = -1;
		}
	}

	cout << endl << "RANGES WITH MAXIMUM DISTANCE THRESHOLD = " << threshold_distance << ", FOUND: " << DISTANCES.size() << endl;
	cout << "Lowest distance located at frame: " << best_frame << ", with distance: " << best_distance << " angstroms." << endl;
	cout << "FRAME START	FRAME END" << endl;

	/*
	for (unsigned int i = 0; i < DISTANCES.size(); i++)
	{
		cout << DISTANCES[i].start_frame << "		" << DISTANCES[i].end_frame << endl;
	}
	*/

	if (this->close_file() == false)
	{
		Exception_FileManipulator ex;
		throw ex;
	}
}
//--
void FileReader::surface_average()
{
	cout << "*-*-*-*-*-*-*-*-*-*-* SURFACE.DAT ANALYSIS *-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "INPUT = " << this->getFilePath() << endl;

	if (this->open_file() == false)
	{
		Exception_FileManipulator ex;
		throw ex;
	}

	double average = 0.0;

	double lowestSurface = DBL_MAX;
	double highestSurface = DBL_MIN;

	int lowestFrame = INT_MAX;
	int highestFrame = INT_MIN;

	int currentFrame;
	double currentSurface;

	// seekg - seek "get" pointer, move it past the initial strings
	this->ioFile.seekg(sizeof("#Frame") + sizeof("SA_00000"));

	if (this->ioFile.good())
	{
		this->ioFile >> currentFrame;
		this->ioFile >> currentSurface;

		while (this->ioFile.good())
		{
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

			average += currentSurface;

			ioFile >> currentFrame >> currentSurface;
		}
	}

	average /= currentFrame;

	cout << "The highest frame was " << highestFrame << " with a surface area of " << highestSurface
		<< " squared angstroms" << endl;
	cout << "The lowest frame was " << lowestFrame << " with a surface area of " << lowestSurface
		<< " squared angstroms" << endl;
	cout << "The average exposed surface area was " << average << " angstroms" << endl;

	if (this->close_file() == false)
	{
		Exception_FileManipulator ex;
		throw ex;
	}
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