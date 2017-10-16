/**
	k_amber-reader
	Exception_FileManipulator.cpp
	Implementation of Exception_FileManipulator.h
		It will eventually be renamed ExceptionFileManipulator (to be more
		stylistically pleasing).

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#include "Exception_FileManipulator.h"
#include <iostream>

Exception_FileManipulator::Exception_FileManipulator()
{

}
//--
const char* Exception_FileManipulator::what() const noexcept
{
	return "FileManipulator exception thrown\n";
}
