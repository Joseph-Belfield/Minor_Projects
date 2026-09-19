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

struct Trade
{
	int time;
	float price;
	int volume;
};

bool init_BarManager(struct BarManager *manager, int barDuration)
{
	manager->barDuration = barDuration;

	const int hour = 3600;
	manager->numOfBars = hour / barDuration;
	if (hour % barDuration) manager->numOfBars++;	// if remainder, add overflow bar
	
	manager->open = malloc(manager->numOfBars * sizeof(float));
	manager->high = malloc(manager->numOfBars * sizeof(float));
	manager->low = malloc(manager->numOfBars * sizeof(float));
	manager->close = malloc(manager->numOfBars * sizeof(float));
	manager->volume = malloc(manager->numOfBars * sizeof(int));

	if (manager->open == NULL || manager->high == NULL || manager->low == NULL || manager->close == NULL || manager->volume == NULL)
	{
		printf("Memory Allocation Error!\n");
		return false;
	}

	return true;
}

void cleanup_BarManager(struct BarManager *manager)
{
	free(manager->open);
	free(manager->high);
	free(manager->low);
	free(manager->close);
	free(manager->volume);
}

bool get_TradeInfo(char* filename, int line, struct Trade* trade)
{
	FILE* fptr;
	fptr = fopen(filename, "r");
	if (fptr == NULL) 
	{
		printf("Unable to open file!\n");
		fclose(fptr);
		return false;
	}
	
	char* buffer = malloc(50 * sizeof(char));
	for (int i = 0; i < line; i++)
	{
		if (fgets(buffer, sizeof(buffer), fptr) == NULL)
		{
			printf("Line out of bounds. File only has %d lines.\n", i);
			fclose(fptr);
			return false;
		}
	}
	
	int commas = 0;
	int index = 0;
	char* temp;
	while (buffer[index] != '\0' && commas < 2)
	{
		if (buffer[index] == ',')
		{
			temp = buffer;
			buffer[index] = '\0';
			buffer += index + 1;

			if (commas == 0)
			{
				trade->time = atoi(temp);
				commas++;
			}
			else if (commas == 1)
			{
				trade->price = atof(temp);
				commas++;
			}
		}

		index++;
	}
	
	if (commas < 2) 
	{
		printf("Not enough commas, file formatted incorrectly.\n");
		fclose(fptr);
		return false;
	}

	trade->volume = atoi(buffer);

	fclose(fptr);
	return true;
}


bool fill_BarManager(struct BarManager* manager, const char* filename)
{
	// Parse each line of data
	// Add appropriately to bar manager
	
	struct Trade currentTrade;
	



	return true;
}


int main()
{
	
	struct BarManager manager;
	const int minute = 60;
	init_BarManager(&manager, minute);

	fill_BarManager(&manager, "mock_data.csv");

	// Read entries from file.
	// When current bar begins/ends, log open/close price accordingly and begin tracking new bar.	
	// Continue until last data entry reached.

	struct Trade trade;
	get_TradeInfo("mock_data.csv", 2, &trade);
	printf("%d, %.2f, %d\n", trade.time, trade.price, trade.volume);


	cleanup_BarManager(&manager);
	return 0;
}












