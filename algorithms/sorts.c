// Different sorting functions

#include <stdbool.h>

bool bubbleSort(int* array, int arrayLength)
{
	for (int i = 0; i < arrayLength - 1; i++)
	{	
		bool swapMade = false;
		for (int j = 0; j < arrayLength - 2; j++)
		{
			if (array[j] > array[j+1])
			{
				swapMade = true;

				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}

		if (!swapMade)
		{
			return true;
		}
	}

	return true;
}

bool mergeSort(int* array, int arrayLength)
{

}

bool insertionSort(int* array, int arrayLength)
{

}

bool quickSort(int* array, int arrayLength)
{

}

