#include "HydrogenBondReader.h"

HydrogenBondReader::HydrogenBondReader(string filePath) : FileReader(filePath)
{

}
//--
string HydrogenBondReader::analyze(double threshold)
{
	// The threshold cannot be below or at 0.
	if (threshold <= 0)
	{
		PRN_WARNING(AT);
		return "";
	}

	pre_read_greeting(__FUNCTION__, "Calculating intramolec. hbonds with persistence = " + to_string(threshold));

	string output = "";

	open_file();

	vector <string> ACCEPTORS;
	unordered_map < string, vector < hbond_child > > DONORS;

	string in_string = "";
	double in_frac;

	output += "*-*-*-*-*-*-*-*-*-*-* HBOND-INTRA-AVG.DAT *-*-*-*-*-*-*-*-*-*-* \n";
	output += "INPUT = " + this->getFilePath() + "\n";
	//output += "OUTPUT .dat = " << output_file << endl;
	output += "HYDROGEN BONDS ACCEPTED AT THRESHOLD MINIMUM = " + to_string(threshold) + "\n";

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
		if (in_frac < threshold)
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

	close_file();

	return output;
}
bool HydrogenBondReader::found_acceptor(vector < string > in_ACCEPTORS, string search_atom)
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
bool HydrogenBondReader::found_donor(unordered_map<string, vector<hbond_child>>& in_DONORS, string acceptor_search_atom, string donor_search_atom)
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