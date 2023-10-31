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


void fileHandler();
Graph* createGraph(int numVertices);
double haversine(double lat1, double lon1, double lat2, double lon2);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
int getUserMallIDInput(const char* prompt);
double findDistanceBetweenMalls(Graph* graph, int startMallID, int endMallID);
void printMallList();
void routeSelection();

#endif
