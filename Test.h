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

private:

	Test();
};