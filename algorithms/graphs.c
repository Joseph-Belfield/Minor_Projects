// For different graph-related algorithms

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

struct Node
{
	int ID;				// ID should match index in graph node array
	int nodeCount;
	int coords[3];		// location of node (used to generate heuristics for A* algorithm)
	int* weights;
	struct Node* nodes;
};

struct Graph
{
	int nodeCount;
	struct Node* nodes;
};

// ===============
//  SHORTEST PATH
// ===============

struct ShortestPathResult
{
	int* path;		// holds IDs of nodes in order
	int pathCount;
	int pathUsedCount;
	int totalCost;
};

struct Bitmap
{
	uint8_t* data;
	int length;			// length of array
}

void init_ShortestPathResult(struct ShortestPathResult* result, int maxNodes)
{
	result->path = malloc(maxNodes * sizeof(int));
	result->pathCount = maxNodes;
	result->pathUsedCount = 0;
	result->totalCost = 0;
}

void init_Bitmap(struct Bitmap* bitmap, int numbersTracked)
{
	bitmap->length = numbersTracked / 8;
	if (numbersTracked % 8) bitmap->length++; 

	bitmap->data = calloc(bitmap->length, sizeof(uint8_t));
}

bool markFound(struct Bitmap* bitmap, unsigned int ID)
{
	int IDindex = ID / 8;
	if (ID % 8) IDindex++;

	if (IDindex > bitmap->length)
	{
		printf("ID out of bitmap range!\n");
		return false;
	}
	
	bitmap->data[IDindex] |= 1 << (ID % 8);
	return true;
}


bool dijkstra(struct Graph* graph, int startID, int endID, struct ShortestPathResult* result)
{
	// Check both start and end IDs are valid
	if (startID > graph->nodeCount || endID > graph->nodeCount)
	{
		printf("Invalid start/end ID!\n");
		return false;
	}

	// Initialize return struct
	init_ShortestPathResult(result, graph->nodeCount);

	// Initialize bitmap to store if node is visited
	struct Bitmap isVisited;
	init_Bitmap(&isVisted, graph->nodeCount);
	
	// Start at first node
	struct Node* currentNode = graph->nodes[startID];
	markFound(isVisited, startID);	

	
}

bool aStar(struct Graph* graph, int startID, int endID, struct ShortestPathResult* result)
{

}


// =============================
//  MINIMUM SPANNING TREE (MST)
// =============================


