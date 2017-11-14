/**
	k_amber-reader
    Exception_FileManipulator.h
	This is an exception class exclusively used by the
		FileManipulator classes and all of its inherited classes.
		It protects the user from adding, removing, or making
		other changes that were not desired, as well as anything
		else undesireable.

	Notable Bugs:
		#define type safety.

    Author(s): Kevin B. Krause
    Version:   unreleased
*/

#pragma once
#include <string>
#include <exception>
#include <iostream>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

using namespace std;

// These inline functions provide some useful printouts for debugging.
// PRN_ERROR should be used in place of a throw.
// PRN_WARNING should be used where a function is being used without any "safety nets."
inline void PRN_ERROR(const char* location) { cout << "ERROR: Invalidity at " << location << endl; };
inline void PRN_WARNING(const char* location) { cout << "WARNING: Unsafe behavior at " << location << endl; };

class Exception_FileManipulator : exception
{
public:

	/**
		Constructor for generic exceptions.
		Parameters:
			none
		Returns:
			An exception object
	*/
	Exception_FileManipulator();
	/**
		This is the overrideable what() method provided by std::exception.
		For now, it only returns a newline terminated char[].
		It cannot throw exceptions, as it is called when an exception is thrown.
		The "const" annotation after the signature means that what() cannot change the state of any class variables.
		Parameters:
			none
		Returns:
			char[]
	*/
	const char* what() const noexcept;

};