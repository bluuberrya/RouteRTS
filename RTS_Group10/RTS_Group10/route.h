#pragma once

#ifndef ROUTE_H
#define ROUTE_H


#include "main.h"

typedef struct {
    int startMallID;
    int endMallID;
    double distance; // Distance between malls
    double speed;    // Speed for the route (consider traffic conditions)
    double duration; // Duration to travel from start to end mall
} Route;

// Function to initialize a path
//Path* initPath(int numNodes);

// Function to free a path
//void freePath(Path* path);

// Function to find the three shortest routes from startMallID to endMallID
//Path** findShortestRoutes(Graph* graph, int startMallID, int endMallID);


//getShortestRoute(Graph* graph, int startMallID, int endMallID);

#endif