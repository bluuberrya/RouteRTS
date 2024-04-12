#ifndef ROUTE_H
#define ROUTE_H

//#include <stdio.h>

//Define the Motorist struct
typedef struct {
    int startMallID;
    int endMallID;
    double distance;
    double speed;
    double time;      // Time taken to complete the distance
} Motorist;

int generateRandomMallID(int excludeID, int nummalls);
int getUserMallIDInput(const char* prompt, int excludeID);
double findDistanceBetweenMalls(Graph* graph, int startMallID, int endMallID);
double generateSpeed(int menu);
//int minTimeVertex(double dist[], bool sptSet[], int numVertices);
void printPath(int parent[], int dest, int mode);
double dijkstra(Graph* graph, int src, int dest, double* speed, double* distance, int menu);


#include "mainh.h"
#include "mallData.h"
#include "route.h"

Mall malls[50];
#define NUM_MALLS 50

void printMallList();
int getUserMallIDInput(const char* prompt, int excludeID);
int generateRandomMallID(int excludeID, int nummalls);
double findDistanceBetweenMalls(Graph* graph, int startMallID, int endMallID);
void printPath(int parent[], int dest, int mode);
double dijkstra(Graph* graph, int src, int dest, double* speed, double* distance, int menu);

#endif
