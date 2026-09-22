// Different sorting functions

#include <stdio.h>
#include <stdbool.h>

bool bubbleSort(int* array, int arrayLength)
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

		if (!swapMade)
		{
			printf("returned early\n");
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
	for (int i = 0; i < arrayLength; i++)
	{
		for (int j = 0; j < i; j++)
		{
		
		}
	}
}

bool quickSort(int* array, int arrayLength)
{
	if (arrayLength == 1)
	{
		return true;
	}
	
	int pivot = array[0];
	for (int i = 1; i < arrayLength - 1; i++)
	{
		if (array[i] < pivot)
		{

		}

	}

}

int main()
{
	int array[] = {4,7,2,57,43,23,125,2};
	bubbleSort(array, 8);
	
	for (int i = 0; i < 8; i++)
	{
		printf("%d\n", array[i]);
	}
}
