// Different sorting functions

#include <stdio.h>

#include <stdbool.h>
#include <string.h> // for memcpy

// ====================
//   HELPER FUNCTIONS
// ====================
void reverseElements(int* array, int arrayLength)
{
	if (arrayLength <= 1) return;

	// swap pointers closing in from front and back until they meet at the middle
	int* leftPtr = array;
	int* rightPtr = array + (arrayLength - 1);

	while (leftPtr < rightPtr)
	{
		int temp = *leftPtr;
		*leftPtr = *rightPtr;
		*rightPtr = temp;

		leftPtr++;
		rightPtr--;
	}
}

void rotateElements(int* array, int arrayLength, int stepsRotated, bool rotateLeft)
{
	// Uses Three-Reverse algorithm
	
	// normalize K to be less than array length
	stepsRotated %= arrayLength;

	// determine splitting point (depends on direction of rotation)
	int splittingPoint;
	if (rotateLeft) splittingPoint = stepsRotated;		// rotate first K elements, then the next (N - K) elements
	else splittingPoint = arrayLength - stepsRotated;	// rotate first (N - K) elements, then the next K elements

	// reverse elements up to (not including) splitting point
	reverseElements(array, splittingPoint);

	// reverse elements from splitting point to N
	reverseElements(array + splittingPoint, arrayLength - splittingPoint);

	// reverse whole array
	reverseElements(array, arrayLength);
}

// ===================
//  SORTING FUNCTIONS
// ===================

void bubbleSort(int* array, int arrayLength)
{
	for (int i = 0; i < arrayLength; i++)
	{	
		bool swapMade = false;
		for (int j = 0; j < arrayLength - 1; j++)
		{
			if (array[j] > array[j+1])
			{
				swapMade = true;

				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
		// break case (prevents excess loops)
		if (!swapMade) return;
	}
}

// returns the pointer to the most sorted list option
void merge_MergeSort(int* leftArray, int leftLength, int* rightArray, int rightLength, int* outputArray)
{
	int outputLength = leftLength + rightLength;
	for (int i = 0, leftIndex = 0, rightIndex = 0; i < outputLength; i++)
	{	
		if (leftIndex >= leftLength)
		{
			outputArray[i] = rightArray[rightIndex];
			rightIndex++;
		}
		else if (rightIndex >= rightLength)
		{
			outputArray[i] = leftArray[leftIndex];
			leftIndex++;
		}
		else if (rightArray[rightIndex] < leftArray[leftIndex])
		{
			outputArray[i] = rightArray[rightIndex];
			rightIndex++;
		}
		else 
		{
			outputArray[i] = leftArray[leftIndex];
			leftIndex++;
		}
	}
}

// Uses ping-pong strategy, where data is copied back and forth from one array to another, slowly merging upwards
int* split_MergeSort(int* srcArray, int* destArray, int arrayLength)
{
	// broken down as far as possible
	if (arrayLength <= 1) 
	{
		if (arrayLength == 1) destArray[0] = srcArray[0];
		return destArray;		
	}

	int midpoint = arrayLength / 2;

	int* sortedLeft = split_MergeSort(destArray, srcArray, midpoint);
	int* sortedRight = split_MergeSort(destArray + midpoint, srcArray + midpoint, arrayLength - midpoint);
	merge_MergeSort(sortedLeft, midpoint, sortedRight, arrayLength - midpoint, destArray);

	return destArray;
}

// This function acts as a wrapper around the recursive split function to ensure it can have stack memory allocated for it
void mergeSort(int* array, int arrayLength)
{
	int tempArray[arrayLength];

	int* destArray = split_MergeSort(array, tempArray, arrayLength);
	
	size_t arraySize = arrayLength * sizeof(int);
	if (destArray != array) memcpy(array, destArray, arraySize);	// ensures original array contains sorted response 	
}

void insertionSort(int* array, int arrayLength)
{
	for (int i = 0; i < arrayLength; i++)
	{
		int pivot = array[i];
		
		// find correct position of new pivot in sorted part of list
		int targetIndex = i;
		for (int j = 0; j < i; j++)
		{
			if (array[j] > pivot) 
			{
				targetIndex = j;
				break;
			}
		}

		// move pivot to correct place
		rotateElements(array + targetIndex, (i - targetIndex) + 1, 1, false);
	}
}

void quickSort(int* array, int arrayLength)
{
	// break case
	if (arrayLength <= 1) return;

	int pivot = array[arrayLength-1];
	int index = 0;	// index tracked seperately, as indexes can be repeated in case of shifts
	for (int i = 0; i < arrayLength - 1; i++)
	{
		if (array[index] > pivot)
		{
			// move item to end, move all other items down, repeat current index by not incrementing (new value in place)
			rotateElements(array + index, arrayLength - index, 1, false);		
		}
		else index++;
	}

	// pivot ends up at array[index]
	quickSort(array, index);									// left of pivot
	quickSort(array + index + 1, arrayLength - (index + 1));		// right of pivot
}

int main()
{
	int array[] = {5, 2, 4, 1, -24, 246, -21, 5235, 32, -21};
	mergeSort(array, 10);
	
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", array[i]);
	}
}
