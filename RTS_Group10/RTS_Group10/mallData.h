#ifndef MALLDATA_H
#define MALLDATA_H

#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

// Define the Mall struct
typedef struct {
    int mallID;
    char name[100];
    double latitude;
    double longitude;
} Mall;

// Declare the array of malls and the number of malls
extern Mall malls[48]; // Assuming 48 malls
#define NUM_MALLS 48

// Define the Graph struct
typedef struct {
    int numVertices;
    double** adjMatrix; // Adjacency matrix with distances
} Graph;

// Function to read data from a file
void fileHandler();

// Function to create a graph
Graph* createGraph(int numVertices);

// Haversine formula to calculate distance between two points on the Earth's surface
double haversine(double lat1, double lon1, double lat2, double lon2);

// Function to add an edge with the calculated distance to the graph
void addEdge(Graph* graph, int src, int dest);

// Function to print the graph
void printGraph(Graph* graph);

// Function to get user input for a mall ID
int getUserMallIDInput(const char* prompt);

// Function to find the distance between two malls based on mallID
double findDistanceBetweenMalls(Graph* graph, int startMallID, int endMallID);

// Function to print the list of malls
void printMallList();

// Function to handle route selection
void routeSelection();

#endif
