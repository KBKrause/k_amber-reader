/**
	k_amber-reader
	Compute.h
	This class contains mathematical functions and other
		tools used to calculate probability, statistics, etc.,
		useful in some of the simulation analyses.
	This class is not related to the similarly named package
		provided by Boost.

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#pragma once
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/*
inline double kcal_to_j(double kcal) {return kcal / 0.000239};
*/

class Compute
{
public:

	/*	Finds the standard deviation of a collection of numbers.
		Parameters:
			vector <double>& values - The set of data being analyzed
		Returns:
			A double representing the standard deviation
		Bugs:
			none
		Other:
			Add overloads
	*/
	static double standard_deviation(vector <double>& values);
	/*	Averages the values of the parameter
		Parameters:
			vector <double>& values - The set of data being analyzed
		Returns:
			A double representing the average
		Bugs:
			none
		Other:
			Add overloads
	*/
	static double average(vector <double>& values);

private:

	/*
		The constructor of this class is private because it has no associated data members
		or mutability.
		For use, any static function of the class can be called with
		Compute::function_name(args);
	*/
	Compute();

};