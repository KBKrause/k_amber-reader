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
#include <exception>
#include <iostream>

static const char* _SAFETY_FILE_NAME = __FILE__;
static const char* SAFETY_WARNING = "WARNING: Unsafe code used at " + *(_SAFETY_FILE_NAME) + (char)__LINE__;

using namespace std;

inline void PRN_WARNING() { cout << SAFETY_WARNING<< endl; };

class Exception_FileManipulator : exception
{
public:

	/**
		Constructor for generic exceptions
		Parameters:
			none
		Returns:
			An exception object
	*/
	Exception_FileManipulator();
	/**
		Constructor for exceptions that takes a file and line number
		Parameters:
			string file - The file where the exception was thrown from
			string line - The line number of this exception
		Returns:
			An exception object
		Bugs:
			It is not useful to have the line number of the exception. Perhaps find a way
				to determine which line of code is the one triggering the exception.
	*/
	Exception_FileManipulator(string file, string line);

private:

	// If applicable, the file name where the exception happened.
	string exceptionFile;
	// If applicable, the line number in the file where the exception happened.
	string exceptionFileLine;

};