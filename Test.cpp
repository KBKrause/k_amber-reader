#include "Test.h"

void Test::test_reader_methods()
{
	try
	{
		// Test hydrogen bond method.
		// Can break on: improper file (attempt to detect this), poor threshold values.
		//FileReader fr("C:/Users/Kevin/Documents/Github/k_amber-reader/data/SULL_ALP-R4_Hbond.dat");
		//assert(fr.hydrogen_bond_intra_average(0.0000001) != "");
		//assert(fr.hydrogen_bond_intra_average(100) != "");
		// add assertion for wrong file
		//assert(!(fr.set_file_path("a/bad/string")));
		//assert(fr.getFilePath() == "C:/Users/Kevin/Documents/Github/k_amber-reader/data/SULL_ALP-R4_Hbond.dat");
		// add assertion for wrong file
		//assert(fr.set_file_path("C:/Users/Kevin/Documents/Github/k_amber-reader/data/sull_oxp-r-1.pdb"));
	}
	catch (Exception_FileManipulator& e)
	{
		e.what();
	}
}
void Test::test_writer_methods()
{

}
void Test::test_manipulator_methods()
{

}
//--
void Test::test_constructors()
{
	// Add good constructor cases
	try
	{
		//FileReader r_badstring("a/bad/string");
		//FileReader r_nostring("");
		//FileWriter w_noString;
		//FileWriter w_badString("a/bad/string");
	}
	catch (Exception_FileManipulator& e)
	{
		e.what();
	}
}

void Test::test_Compute_conversions()
{

}
