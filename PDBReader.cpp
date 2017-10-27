#include "PDBReader.h"

PDBReader::PDBReader(string filePath) : FileReader(filePath)
{
}

//--
string PDBReader::analyze(string s)
{
	pre_read_greeting(__FUNCTION__, "Fixes the PDB and replaces INT with " + s);
	string returnString = "";

	if (s.length() != 3)
	{
		cout << "ERROR: Input monomer = " << s << " must have exactly 3 letters" << endl;
		return returnString;
	}

	cout << "Fixing pdb ..." << endl;

	open_file();

	char thisChar;

	string thisString;
	vector < string > thisLine;

	while (this->ioFile.good())
	{
		ioFile.get(thisChar);

		if ((thisChar == ' ') || (thisChar == '\n'))
		{
			if (thisString == "INT")
			{
				thisString = s;
			}

			thisString.push_back(thisChar);
			thisLine.push_back(thisString);
			thisString.clear();

			if (thisChar == '\n')
			{
				if ((thisLine[0] != "LINK ") && (thisLine[0] != "CONECT ") && (thisLine[0] != "REMARK "))
				{
					for (size_t i = 0; i < thisLine.size(); i++)
					{
						returnString += thisLine[i];
					}
				}

				thisLine.clear();
			}
		}
		else
		{
			thisString.push_back(thisChar);
		}
	}

	thisString += "TER\nEND\n";

	close_file();

	return returnString;
}