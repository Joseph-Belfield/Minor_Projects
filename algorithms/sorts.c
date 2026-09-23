// Different sorting functions
#include <stdbool.h>

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

void mergeSort(int* array. int arrayLength)
{

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

