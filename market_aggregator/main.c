#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct BarManager
{
	int barDuration;
	int numOfBars;

	float* open;
	float* high;
	float* low;
	float* close;
	int* volume;
};

bool init_BarManager(struct BarManager *manager, int barDuration)
{
	manager->barDuration = barDuration;

	const int hour = 3600;
	manager->numOfBars = hour / barDuration;
	if (hour % barDuration) manager->numberOfBars++;	// if remainder, add overflow bar
	
	manager->open = malloc(manager->numberOfBars * sizeof(float));
	manager->high = malloc(manager->numberOfBars * sizeof(float));
	manager->low = malloc(manager->numberOfBars * sizeof(float));
	manager->close = malloc(manager->numberOfBars * sizeof(float));
	manager->volume = malloc(manager->numberOfBars * sizeof(int));

	if (manager->open == NULL || manager->high == NULL || manager->low == NULL || manager->close == NULL || manager->volume == NULL)
	{
		printf("Memory Allocation Error!\n");
		return false;
	}

	return true;
}

void delete_BarManager(struct BarManager *manager)
{
	free(manager->open);
	free(manager->high);
	free(manager->low);
	free(manager->close);
	free(manager->volume);
}



int main()
{
	



	return 0;
}
