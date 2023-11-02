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
double findThreeShortestRoutes(Graph* graph, int src, int dest, double speeds[3]);


bool isMallVisited(const Route* route, int mallID);
double calculateDuration(const Route* route);
//void findThreeRoutesBetweenMalls(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* shortestRoutes, int* routeCount);
//void findAndStoreThreeRoutes(Graph* graph, int startMallID, int endMallID, Route* shortestRoutes, int* routeCount);
//void findAndStoreThreeRoutesHelper(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* shortestRoutes, int* routeCount, int maxRoutes);
//void findRoutesBetweenMalls(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* allRoutes, int* routeCount);
//void findAndStoreRoutes(Graph* graph, int startMallID, int endMallID, Route* allRoutes, int* routeCount);
double compareRoutesByDistance(const void* a, const void* b);

//typedef struct {
//    int startMallID;
//    int endMallID;
//    double distance; // Distance between malls
//    double speed;    // Speed for the route (consider traffic conditions)
//    double duration; // Duration to travel from start to end mall
//} Route;


#endif