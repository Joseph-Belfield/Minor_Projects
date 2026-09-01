#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// a single struct holds a list of arrays, each induvidual bar accessed at its own index
struct BarManager
{
	int duration;	// the length of a single bar in seconds
	
	// all tracked metrics per bar - stored in arrays, where bar 1 is at index 0, etc.
	float* open;
	float* high;
	float* low;
	float* close;
	int* volume;
	float* VWAP;
}

// constructor, managers will keep entries for an hour before overwriting them
bool init_barManager(struct BarManager* manager, int barDuration)
{
	manager->duration = barDuration;
	
	// Calculate number of bars in one hour
	int secondsInHour = 3600;
	int numberOfBars = (secondInHour / barDuration);
	if (secondsInHour % barDuration) numberOfBars++;  // if there's remainder, add on overflow bar

	// Reserve space for arrays (for one hour worth of bars)
	manager->open = malloc(numberOfBars * sizeof(float));
	manager->high = malloc(numberOfBars * sizeof(float));
	manager->low = malloc(numberOfBars * sizeof(float));	
	manager->close = malloc(numberOfBars * sizeof(float));
	manager->volume = malloc(numberOfBars * sizeof(int));	
	manager->VWAP = malloc(numberOfBars * sizeof(float));

	// Malloc Error Management
	if (manager->open == NULL ||
		manager->high == NULL ||
		manager->low == NULL ||
		manager->close == NULL ||
		manager->volume == NULL ||
		manager->VWAP == NULL)
	{
		printf("Memory Allocation Error!\n");
		return false;
	}

	return true;
}


int main()
{
	// Initialize managing struct.
	struct BarManager manager;	
	init_barManager(&manager, 60);


}








