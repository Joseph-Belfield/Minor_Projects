// This project should take a molecule name (as a string), break it down into some data structure, then allow for a visual output, either in command line or in a window


#include <stdio.h>


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Please use format: ./<programName> \"<MoleculeName>\"\n");
		return -1;
	}

	return 0;
}
