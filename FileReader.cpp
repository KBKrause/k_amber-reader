#include "FileReader.h"
#include <string>
#include <unordered_map>

FileReader::FileReader(string filePath_read)
	:FileManipulator(filePath_read)
{
	
}
//--
void FileReader::count_string()
{
	string in_string = " ";
	vector <string> vec;
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

		vec.push_back(in_string);
		freq_vec.push_back(0);
	}

	ifstream inFile = open_file();
	string phr;

	cout << "Searching for occurences ..." << endl;

	while (inFile.good())
	{
		inFile >> phr;

		for (unsigned int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == phr)
			{
				freq_vec[i]++;
			}
		}
	}

	cout << "Occurences found: " << endl;
	
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " found " << freq_vec[i] << " times" << endl;
	}

	if (close_file() == true)
	{
		cout << "File closed successfully" << endl;
	}
	else
	{
		cout << "File unable to be closed" << endl;
	}
}
//--
void FileReader::hydrogen_bond_intra_average(string output_file, double threshold_persistence)
{
	ifstream inFile = open_file();

	vector <string> ACCEPTORS;
	unordered_map < string, vector < hbond_child > > DONORS;

	string in_string = "";
	double in_frac;

	cout << "*-*-*-*-*-*-*-*-*-*-* HBOND-INTRA-AVG.DAT *-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "INPUT = " << filePath_read << endl;
	cout << "OUTPUT .dat = " << output_file << endl;
	cout << "HYDROGEN BONDS ACCEPTED AT THRESHOLD MINIMUM = " << threshold_persistence << endl;

	// first 6 words aren't needed
	for (int i = 0; i < 7; i++)
	{
		inFile >> in_string;
	}

	while (inFile.good())
	{
		inFile >> in_string;
		string atom_copy = in_string;
		string chain_copy = in_string;
		
		//  -- #Acceptor Work -- //
		string acceptorAtom = atom_copy.erase(0, in_string.find('@') + 1);
		string acceptorChain = chain_copy.erase(0, in_string.find('_') + 1);

		acceptorChain = acceptorChain.erase(acceptorChain.find('@'), acceptorChain.size());

		//cout << "Acceptor atom is " << acceptorAtom << endl;
		//cout << "Acceptor chain is " << acceptorChain << endl;
		// --

		inFile >> in_string;
		inFile >> in_string;

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

		inFile >> in_string;
		inFile >> in_frac;

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
			inFile >> in_string;
		}
	}

	cout << endl << "Done" << endl << endl;

	// had to hard code in the second for loop and onwards
	// not sure how to account for an N, then an N1, and so on
	// or if a certain acceptor has already encountered a certain donor
	for (unsigned int i = 0; i < ACCEPTORS.size(); i++)
	{
		cout << "BONDS AT ACCEPTOR: " << ACCEPTORS[i] << endl;
		cout << "ACCEPTOR CHAIN";
		cout << "		";
		cout << "DONOR CHAIN";
		cout << "		";
		cout << "PERSISTENCE" << endl;

		cout << endl;
		
		cout << "DONOR: N" << endl;
		for (unsigned int j = 0; j < DONORS[ACCEPTORS[i] + "_" + "N"].size(); j++)
		{
			cout << DONORS[ACCEPTORS[i] + "_" + "N"][j].acceptor_chain;
			cout << "			";
			cout << DONORS[ACCEPTORS[i] + "_" + "N"][j].donor_chain;
			cout << "			";
			cout << DONORS[ACCEPTORS[i] + "_" + "N"][j].persistence;

			cout << endl;
		}

		cout << "DONOR: N1" << endl;
		for (unsigned int j = 0; j < DONORS[ACCEPTORS[i] + "_" + "N1"].size(); j++)
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

			for (unsigned int i = 0; i < iter->second.size(); i++)
			{
				cout << iter->second[i].acceptor_chain << ", " << iter->second[i].donor_chain << ", " << iter->second[i].persistence << endl;
			}

			cout << endl;
		}
	}
}
//--
void FileReader::distance_atoms(string output_file, double threshold_distance)
{
	cout << "*-*-*-*-*-*-*-*-*-*-* DISTANCE.IN *-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "INPUT = " << filePath_read << endl;
	cout << "OUTPUT .dat = " << output_file << endl;
	cout << "MAXIMUM ANGSTROM DISTANCE = " << threshold_distance << endl;

	ifstream inFile = open_file();
	string garbage;

	struct frame_pair
	{
		int start_frame;
		int end_frame;
	};

	inFile >> garbage >> garbage;

	vector < frame_pair > DISTANCES;

	frame_pair val;
	val.start_frame = -1;
	val.end_frame = -1;

	int best_frame;
	double best_distance = INT_MAX;

	int iterator;

	while (inFile.good())
	{
		double angstroms;
		
		inFile >> iterator;
		inFile >> angstroms;

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

	if (close_file())
	{
		cout << "Done" << endl;
	}
}
//--
void FileReader::filter_pdb_by_hbond(string output_file, string in_acceptor, string in_donor)
{
	cout << "*-*-*-*-*-*-*-*-*-*-* HBOND-INTRA-AVG.IN *-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "INPUT = " << filePath_read << endl;
	cout << "OUTPUT .dat = " << output_file << endl;
	cout << "FILTER ALL BUT ACCEPTOR/DONOR = " << in_acceptor << " / " << in_donor << endl;
}
//--
bool FileReader::found_acceptor(vector < string > in_ACCEPTORS, string search_atom)
{
	for (unsigned int i = 0; i < in_ACCEPTORS.size(); i++)
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