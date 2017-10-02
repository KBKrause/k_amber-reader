/**
	k_amber-reader
    FileReader.h
	FileReader (freader) inherits from FileManipulator. Its main use
		is to read output from AMBER and print results to the screen.
		freader will not generate any files.

    Author(s): Kevin B. Krause
    Version:   unreleased
*/

#pragma once
#include "FileManipulator.h"
#include <vector>
#include <unordered_map>

class FileReader : FileManipulator
{
public:

	/**
		Constructor for freader objects. Because freader does not
		   have any private data members, it is an empty constructor
		   that also calls the constructor for FileManipulator.
   		Parameters:
      		string filePath - Path to the file being used
   		Returns:
      		An freader object
	*/
	FileReader(string filePath);
	/**
   		Asks the user for n strings and searches for those n strings in a file
   		Parameters:
      		none
   		Returns:
			none
		Bugs:
			This function matches punctuation and case when searching. It should not.
		It should remove all puncutation and change all case to lower case.
	*/
	void count_string();
	/**
   		Hydrogen bond calculation to aggregate average amount of bonds and percentages
			per acceptor/donor pair. The list output by AMBER is not easy to read and must be
			tabulated by hand. Ideally, this function will reduce AMBER's output and provide
			something that can be piped into another program as a substitute for calculating
			everything by hand.
   		Parameters:
      		double threshold_persistence - the percent at which to stop reading the configured file
				A 5% threshold should be passed as 0.05.
   		Returns:
			  none
		Bugs:
			TBD
		Other:
			Alias: hbond_intra_avg.
	*/
	void hydrogen_bond_intra_average(double threshold_persistence);

	/**
		Determines the distances between two atoms. It is used in conjunction with
			hbond_intra_avg to determine which frames frpm the simulation can best represent a
			hydrogen bond.
		Parameters:
			double threshold_persistence - the percent at which to stop reading the configured file
				A 5% threshold should be passed as 0.05.
		Returns:
			none
		Bugs:
			none
	*/
	void distance_atoms(double threshold_distance);

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


	// -- //
};