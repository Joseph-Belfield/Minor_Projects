// This project should take a molecule name (as a string), break it down into some data structure, then allow for a visual output, either in command line or in a window

#include <stdio.h>
#include <regex.h>

// first, parse molecule as tree structure
// then flatten tree structure into tables - atom table, indexed by global IDs, holding atom element, etc; bond table, which holds the two global IDs of the atoms involved, and the bond type (single, etc.)

// regex in C works by compiling a regex expression into a regex object (regcomp), then checking a string against it (regexec), where the positions of total match and substrings are returned in an array

int parseName(char* moleculeName)
{
	char* regexPattern = "Put regex expression here later.";
	regex_t regexObject;

	// Compile regex pattern into regex object, else error.
	if (regcomp(&regexObject, regexPattern, REG_EXTEND))
	{
		printf("Error! Could not compile Regex!\n");
		return 1;
	}


}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Please use format: ./<programName> \"<MoleculeName>\"\n");
		return -1;
	}
	
	char* moleculeName = argv[1];
	
	parseName(moleculeName);
	flattenTree();
	outputVisual();

	return 0;
}
