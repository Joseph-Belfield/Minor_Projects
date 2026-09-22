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
		int pivot = array[i];
		int index = i;
		while (array[index-1] > array[index] && index > 0)
		{
			int temp = array[index];
			array[index] = array[index - 1];
			array[index-1] = temp;

			index--;
		}
	}

	return true;
}

bool quickSort(int* array, int arrayLength)
{

}

int main()
{
	int array[] = {4,7,2,57,-43,23,125,2,-5,36};
	bubbleSort(array, 10);
	
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", array[i]);
	}
}
