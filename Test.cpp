#include "Test.h"
#include "SASAReader.h"
#include "PDBReader.h"

void Test::test_FileManipulator()
{
	assert(FileManipulator::isValidFile(FILE_HBOND));
	assert(FileManipulator::isValidFile(FILE_PDB));
	assert(FileManipulator::isValidFile(FILE_SASA));
}
void Test::test_Molecule()
{
	Molecule m1("s");
	Molecule m2("s");

	assert(m1.getMoleculeName() == m2.getMoleculeName());
}
//--
void Test::test_FileReader()
{
	FileReader fr("garbage");
	assert(!(fr.isValidFile(fr.getFilePath())));

	assert(fr.analyze() == "");

	assert(!(fr.set_file_path("a/bad/string")));
	assert(fr.set_file_path(FILE_HBOND));
	assert(fr.getFilePath() == FILE_HBOND);
	assert(fr.set_file_path("C:/Users/Kevin/Documents/Github/k_amber-reader/data/sull_oxp-r-1.pdb"));
	assert(fr.getFilePath() == FILE_PDB);
}
//--
void Test::test_PDBReader()
{
	PDBReader pdbr(FILE_PDB.c_str());
	assert(pdbr.getFilePath() == FILE_PDB);

	assert(pdbr.isValidFile(pdbr.getFilePath()));

	assert(pdbr.analyze("ULL") != "");
	assert(pdbr.analyze("longstr") == "");
	assert(pdbr.analyze(to_string(3)) == "");
}

void Test::test_SASAReader()
{
	SASAReader sasar(FILE_SASA.c_str());
	assert(sasar.getFilePath() == FILE_SASA);

	assert(sasar.isValidFile(sasar.getFilePath()));
	assert(sasar.analyze() != "");
}

void Test::test_HydrogenBondReader()
{
	HydrogenBondReader hbr(FILE_HBOND.c_str());
	assert(hbr.getFilePath() == FILE_HBOND);

	assert(hbr.isValidFile(hbr.getFilePath()));

	assert(hbr.analyze(100.0) == "");
	assert(hbr.analyze(0.0) == "");
	assert(hbr.analyze(-4832.0) == "");
	assert(hbr.analyze(104.0) == "");
}
