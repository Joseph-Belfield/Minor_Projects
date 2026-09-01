#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// forward declaration
struct BarManager;

typedef void (*ManagerOutput)(struct BarManager*, int);

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

	ManagerOutput printBarStats;
};

struct Tick
{
	int time;
	float price;
	int volume;
};

void printBarStats(struct BarManager* self, int barID)
{
	printf("Open: %f\n", self->open[barID]);
	printf("High: %f\n", self->high[barID]);
	printf("Low: %f\n", self->low[barID]);
	printf("Close: %f\n", self->close[barID]);
	printf("Volume: %d\n", self->volume[barID]);
	printf("VWAP: %f\n", self->VWAP[barID]);
}

// constructor, managers will keep entries for an hour before overwriting them
bool init_barManager(struct BarManager* manager, int barDuration)
{
	manager->duration = barDuration;
	
	// Calculate number of bars in one hour
	int secondsInHour = 3600;
	int numberOfBars = (secondsInHour / barDuration);
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

	manager->printBarStats = printBarStats;

	return true;
}

bool readLine(const char* filename, unsigned int lineNumber, char* lineBuffer, size_t sizeOfBuffer)
{
	FILE* fptr;
	fptr = fopen(filename, "r");

	for (int i = 0; i < lineNumber; i++)
	{
		if (fgets(lineBuffer, sizeOfBuffer, fptr) == NULL)
		{
			printf("File is too short! File has %d lines.\n", i);
		return false;
		}
	}

	fclose(fptr);
	return true;
}

bool getTickData(const char* filename, unsigned int lineNumber, struct Tick* tick)
{
	// Transfer line frome file to buffer.
	char lineBuffer[100];
	if (!readLine(filename, lineNumber, lineBuffer, 100 * sizeof(char)))
	{
		printf("Unable to read tick data on line %d.\n", lineNumber);
		return false;
	}

	// Split buffer into 3 pieces of data.
	char* timeString;
	char* priceString; 
	char* volumeString;
	
	// Time is first item of data in line.
	timeString = lineBuffer;

	int index = 0, commas = 0;
	while (commas < 2 && lineBuffer[index] != '\0')
	{
		if (lineBuffer[index] == ',')
		{
			if (commas == 0)
			{	
				priceString = lineBuffer + index + 1;
				lineBuffer[index] = '\0';
				commas = 1;
			}
			else if (commas == 1)
			{
				volumeString = lineBuffer + index + 1;
				lineBuffer[index] = '\0';
				commas = 2;
			}
		}

		index++;
	}

	if (commas != 2)
	{
		printf("Less than two data points on line %d!\n", lineNumber);
		return false;
	}

	tick->time = atoi(timeString);
	tick->price = atof(priceString);
	tick->volume = atoi(volumeString);
	
	return true;
}

void printTickData(struct Tick* tick)
{
	printf("Time: %d\n", tick->time);
	printf("Price: %.2f\n", tick->price);
	printf("Volume: %d\n", tick->volume);
}

void cleanup_barManager(struct BarManager* manager)
{
	free(manager->open);
	free(manager->high);
	free(manager->low);
	free(manager->close);
	free(manager->volume);
	free(manager->VWAP);
}

int main()
{
	// Initialize managing struct.
	struct BarManager manager;	
	if (!init_barManager(&manager, 60))
	{
		printf("Bar Manager unable to be initialized!\n");
		return -1;
	}

	struct Tick tick = {0, 0.0f, 0};
	getTickData("mock_data.csv", 2, &tick);
	printTickData(&tick);


	cleanup_barManager(&manager);
}








