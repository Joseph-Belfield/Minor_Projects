// A file dedicated to search functions. Include the header file to use these functions in other files.

#include <stdbool.h>

// Linear Search
//  - Returns the index into the array where the target is found.
//  - If the array does not contain the target, returns error code (-1).
int linearSearch(int* array, int arrayLength, int target)
{
	for (int i = 0; i < arrayLength; i++)
	{
		if (array[i] == target)
		{
			return i;
		}
	}

	return -1;
}

// Binary Search
//  - Returns the index into the array where the target is found.
//  - Array must be sorted ascendingly.
//  - If the array does not contain the target, return error code (-1).
int binarySearch(int* array, int arrayLength, int target)
{
	int* leftPtr = array;
	int* rightPtr = array + (arrayLength - 1);

	while (rightPtr > leftPtr)
	{
		if (leftPtr[arrayLength / 2] == target)
		{
			return (leftPtr - array) + (arrayLength / 2);
		}
		else if (leftPtr[arrayLength / 2] > target)
		{
			arrayLength /= 2;
			rightPtr = leftPtr + (arrayLength);
		}
		else
		{
			arrayLength -= arrayLength / 2;
			leftPtr += arrayLength;
		}
	}
	
	if (*leftPtr == target) return leftPtr - array;	

	return -1;
}

