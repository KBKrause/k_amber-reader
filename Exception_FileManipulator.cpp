#include "Exception_FileManipulator.h"
#include <iostream>

Exception_FileManipulator::Exception_FileManipulator(string in_debug_info)
{
	debug_info = in_debug_info;
}
//--
void Exception_FileManipulator::print_debug_info()
{
	cout << debug_info;
}
//--
string Exception_FileManipulator::get_debug_info()
{
	return debug_info;
}