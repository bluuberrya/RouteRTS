#pragma once

#ifndef ROUTE_H
#define ROUTE_H

#define MAX_ROUTES 3 // Define the maximum possible number of malls in a route

typedef struct {
    int startMallID;
    int endMallID;
    double distance;
    double trafficConditions;
    double duration;
    int visitedMalls[MAX_ROUTES];
    int routeLength;
    // Add more fields as needed
} Route;

int minDistance(double dist[], bool sptSet[], int numVertices);
void printShortestPath(int parent[], int j);
double calculateShortestRoute(Graph* graph, int src, int dest, double speed);

#endif