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
	int numberOfBars;

	// all tracked metrics per bar - stored in arrays, where bar 1 is at index 0, etc.
	float* open;
	float* high;
	float* low;
	float* close;
	int* volume;

	ManagerOutput printBarStats;
	ManagerOutput printVWAP;
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
}

float calculateVWAP(struct BarManager* manager, int barID)
{
	// VWAP must be calculated using sum(typical price x volume) / sum(volume)
	// typical price = (high + low + close) / 3
	int VWAP;

	if (barID > manager->numberOfBars) 
	{
		printf("Bar outside range!\n");
		return -1.0f;
	}

	float numerator;		// sum(typical price x volume)
	float denominator;		// sum(volume)
	
	for (int i = 0; i < barID; i++)
	{
		float typicalPrice = (manager->high[i] + manager->low[i] + manager->close[i]) / 3.0f;
		numerator += typicalPrice * manager->volume[i];

		denominator += manager->volume[i];
	}

	// prevent divide by zero errors
	if (denominator <= 0.0f)
	{
		printf("Divide by 0 error!\n");
		return -1.0f;
	}

	VWAP = (float)numerator / denominator;

	return VWAP;
}

void printVWAP(struct BarManager* self, int barID)
{
	float currentVWAP = calculateVWAP(self, barID);
	printf("The VWAP at bar %d is %.2f.\n", barID, currentVWAP);

}

// constructor, managers will keep entries for an hour before overwriting them
bool init_barManager(struct BarManager* manager, int barDuration)
{
	manager->duration = barDuration;
	
	// Calculate number of bars in one hour
	int secondsInHour = 3600;
	manager->numberOfBars = (secondsInHour / barDuration);
	if (secondsInHour % barDuration) manager->numberOfBars++;  // if there's remainder, add one

	// Reserve space for arrays (for one hour worth of bars)
	manager->open = malloc(manager->numberOfBars * sizeof(float));
	manager->high = malloc(manager->numberOfBars * sizeof(float));
	manager->low = malloc(manager->numberOfBars * sizeof(float));	
	manager->close = malloc(manager->numberOfBars * sizeof(float));
	manager->volume = malloc(manager->numberOfBars * sizeof(int));	

	// Malloc Error Management
	if (manager->open == NULL ||
		manager->high == NULL ||
		manager->low == NULL ||
		manager->close == NULL ||
		manager->volume == NULL)
	{
		printf("Memory Allocation Error!\n");
		return false;
	}

	manager->printBarStats = printBarStats;
	manager->printVWAP = printVWAP;

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
}

int main()
{
	int barLength = 60;	// length of bar in seconds
	char* filename = "mock_data.csv";

	// Initialize managing struct.
	struct BarManager manager;	
	if (!init_barManager(&manager, barLength))
	{
		printf("Bar Manager unable to be initialized!\n");
		return -1;
	}

	// Iterate through ticks, accumulating data, until one bar worth of time has passed.
	// - get start time of current bar
	// - while less than one bar of time has passed, track stats accordingly
	// - at end of bar, move stats to bar manager and move on
	// - repeat until end of data	
	
	struct Tick tick;	// struct to hold data every tick
	getTickData(filename, 1, &tick);
	const int startTime = tick.time;

	int currentLine = 1;
	int currentBar = 0;
	bool firstBar = true;
	bool isLinesRemaining = true;
	while (isLinesRemaining)
	{
		isLinesRemaining = getTickData(filename, currentLine, &tick);

		// if beginning of new bar
		if (currentBar < (tick.time - startTime) % barLength || firstBar)
		{
			firstBar = false;
			currentBar = (tick.time - startTime) / barLength;
			manager.open[currentBar] = tick.price;
			manager.high[currentBar] = tick.price;
			manager.low[currentBar] = tick.price;
		}
		
		
		if (tick.price > manager.high[currentBar]) manager.high[currentBar] = tick.price;
		if (tick.price < manager.low[currentBar]) manager.low[currentBar] = tick.price;

		manager.volume[currentBar] += tick.volume;

		manager.close[currentBar] = tick.price;
		currentLine++;
	}

	for (int i = 0; i < 60; i += 9)
	{
		manager.printBarStats(&manager, i);
	}

	manager.printVWAP(&manager, 10);
	manager.printVWAP(&manager, 30);
	manager.printVWAP(&manager, manager.numberOfBars); 

	cleanup_barManager(&manager);
}








