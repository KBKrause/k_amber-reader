#pragma once
#include "FileManipulator.h"
#include <vector>
#include <unordered_map>

class FileReader : FileManipulator
{
public:

	// add file_write path and ofstream to each method.

	//count_string:
	// - IS NOT A siMULATION
	// - check to make sure no duplicate words are added
	// - clean words for things like "cat" and "cat." since cat is one word, not two

	FileReader(string filePath_read);

	void count_string();

	// BUGS vvv
	// - one of the bonds is being created, but nothing is being pushed back (think it's O1 to N or N1)
	//	- use system pause for each read to determine what's being added - system("pause") after ea. read of all.
	//	- H21_N and O1_N1
	// - hard coded the N and N1 for second part of hash key, how do I figure out the donors for that acceptor?

	// PARAMETERS: output_file is the name of the .dat to generate, threshold_persistence is the fraction that it stops recording bonds
		// Say, for a 5% persistence, the parameter would be 0.05
		// still not working
	void hydrogen_bond_intra_average(string output_file, double threshold_persistence);

	// PARSE: find the distances that meet threshold_distance requirement
			// also prints the lowest distance found and at the frame
	void distance_atoms(string output_file, double threshold_distance);

	// UNFINISHED
	void filter_pdb_by_hbond(string output_file, string in_acceptor, string in_donor);

private:

	struct hbond_child
	{
		string acceptor_chain;
		string donor_chain;
		double persistence;
	};

	bool found_acceptor(vector < string > in_ACCEPTORS, string search_atom);
	bool found_donor(unordered_map < string, vector < hbond_child > >& in_DONORS, string acceptor_search_atom, string donor_search_atom);


	// -- //
};