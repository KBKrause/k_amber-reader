/**
	k_amber-reader
    Exception_FileManipulator.h
	This is an exception class exclusively used by
		fmanip classes and all of their inherited classes.
		It protects the user from adding, removing, or making
		other changes that were not desired.

    Author(s): Kevin B. Krause
    Version:   unreleased
*/

#pragma once
#include <string>

using namespace std;

class Exception_FileManipulator
{
public:

	/**
		Constructor for exceptions
		Parameters:
			none
		Returns:
			An exception object
	*/
	Exception_FileManipulator();
};