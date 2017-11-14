/**
	k_amber-reader
	HydrogenBondReader.h
	The HydrogenBondReader class analyzes .dat files generated from the hbond command, which is
		used in conjunction with cpptraj.

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#pragma once
#include "FileReader.h"

class HydrogenBondReader : public FileReader
{
public:

	/**
		Constructor for HydrogenBondReader objects.
		Parameters:
			string filePath - Path to the file being used
		Returns:
			A HydrogenBondReader object
	*/
	HydrogenBondReader(string filePath);
	/**
		Hydrogen bond calculation to aggregate average amount of bonds and percentages
			per acceptor/donor pair. The list output by AMBER is not easy to read and must be
			tabulated by hand. Ideally, this function will reduce AMBER's output and provide
			something that can be piped into another program as a substitute.
		Parameters:
			double threshold - the percent at which to stop reading the configured file; once bonds last less
			than threshold% of the simulation, stop reading.
			A 5% threshold, for examaple, should be passed as 0.05. The standard threshold is 10%.
		Returns:
			A string aggregate of all output ... [ELABORATE]
		Bugs:
			TBD
		Other:
			Alias: hbond_intra_avg.
	*/
	string analyze(double threshold) override;

private:

	/*
		This is the "helper" struct used to create hydrogen bonds in hydrogen_bond_intra_average. Each "child"
			consists of two interacting monomers of the micelle and how long they were interacting.
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