/**
	k_amber-reader
	Test.h
	This is a testing class that makes extensive use of assert() to verify
		that the functions work as intended.

	Author(s): Kevin B. Krause
	Version:   unreleased
*/

#pragma once
#include "FileManipulator.h"
#include "Exception_FileManipulator.h"
#include "FileReader.h"
#include "HydrogenBondReader.h"
#include "Molecule.h"
#include <assert.h>

// "String Table"
const string FILE_HBOND = "C:/Users/Kevin/Documents/Github/k_amber-reader/data/SULL_ALP-R4_Hbond.dat";
const string FILE_SASA = "C:/Users/Kevin/Documents/Github/k_amber-reader/data/SULL_surface_ALP-R4_ligand.dat";
const string FILE_PDB = "C:/Users/Kevin/Documents/Github/k_amber-reader/data/sull_oxp-r-1.pdb";
const string DIR_OUT = "C:/Users/Kevin/Documents/Github/k_amber-reader/out/";

class Test
{
public:

	static void test_Compute_conversions();

	// individual classes
	static void test_Compute();
	static void test_ExceptionFileManipulator();
	static void test_FileManipulator();

	static void test_Molecule();
	static void test_FileReader();
	static void test_HydrogenBondReader();
	static void test_PDBReader();
	static void test_SASAReader();

private:

	Test();
};