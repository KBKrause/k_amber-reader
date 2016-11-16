#pragma once
#include <string>

using namespace std;

class Exception_FileManipulator
{
public:
	Exception_FileManipulator(string in_debug_info);

	void print_debug_info();
	
	string get_debug_info();
private:

	string debug_info;
};