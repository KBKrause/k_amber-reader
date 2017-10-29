/**
	k_amber-reader
    Exception_FileManipulator.h
	This is an exception class exclusively used by
		fmanip classes and all of their inherited classes.
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

inline void PRN_ERROR(const char* location) { cout << "ERROR: Invalidity at " << location << endl; };
inline void PRN_WARNING(const char* location) { cout << "WARNING: Unsafe behavior at " << location << endl; };

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
		This is the overrideable what() method provided by std::exception,
		which is inherited by all of the sub-exceptions.
		For now, it only returns a newline terminated char[].
		It cannot throw exceptions, as it is called when an exception is thrown.
		Parameters:
			none
		Returns:
			Immutable char[]
	*/
	const char* what() const noexcept;

};