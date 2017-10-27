#pragma once
#include "FileManipulator.h"
#include "Exception_FileManipulator.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <assert.h>

class Test
{
public:

	static void test_reader_methods();
	static void test_writer_methods();
	static void test_manipulator_methods();
	static void test_constructors();

	static void test_Compute_conversions();

	// individual classes
	static void test_Compute();
	static void test_ExceptionFileManipulator();
	static void test_FileManipulator();
	static void test_FileReader();
	static void test_FileWriter();
	static void test_HydrogenBondReader();
	static void test_PDBReader();
	static void test_SASAReader();

private:

	Test();
};