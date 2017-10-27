#pragma once
#include "FileReader.h"

class HydrogenBondReader : public FileReader
{
public:

	HydrogenBondReader(string filePath);
	string analyze(double threshold) override;

private:

	/*
	This is the helper struct used to create hydrogen bonds in hydrogen_bond_intra_average. Each "child"
	consists of two interacting monomers of the micelle and how long they were interacting.
	Bugs:
	See comments above.
	*/
	struct hbond_child
	{
		string acceptor_chain;
		string donor_chain;
		double persistence;
	};

	/*
	These are the helper functions to find if hydrogen bonds were already located between a donor and acceptor
	pair.
	Bugs:
	Mixture of case and underscores in parameter names.
	*/
	bool found_acceptor(vector < string > in_ACCEPTORS, string search_atom);
	bool found_donor(unordered_map < string, vector < hbond_child > >& in_DONORS, string acceptor_search_atom, string donor_search_atom);
}; 