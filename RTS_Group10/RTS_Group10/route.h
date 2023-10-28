#pragma once

#ifndef ROUTE_H
#define ROUTE_H

typedef struct {
    int* nodes;     // Array of node indices (malls)
    int length;     // Length of the path
    double distance; // Total distance of the path
} Path;


#include "main.h"
#include "mallData.h"
#include "route.h"

// Function to initialize a path
Path* initPath(int numNodes);

// Function to free a path
void freePath(Path* path);

// Function to find the three shortest routes from startMallID to endMallID
Path** findShortestRoutes(Graph* graph, int startMallID, int endMallID);


getShortestRoute(Graph* graph, int startMallID, int endMallID);

#endif