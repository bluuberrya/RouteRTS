#include "main.h"
#include "mallData.h"
#include "route.h"

// Define your route calculation functions here
// Implement a DFS-based route finder, duration calculator, etc.
// Store routes in an array of Route structures

void findRoutesBetweenMalls(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* allRoutes, int* routeCount) {
    if (currentMallID == endMallID) {
        // We have reached the destination mall
        allRoutes[*routeCount] = *currentRoute;
        (*routeCount)++;
        return;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[currentMallID][i] > 0) {
            // There is a connection from the current mall to another mall
            if (!isMallVisited(currentRoute, i)) {
                // If the mall has not been visited in this route
                currentRoute->endMallID = i;
                currentRoute->distance += graph->adjMatrix[currentMallID][i];
                currentRoute->duration = calculateDuration(currentRoute);

                findRoutesBetweenMalls(graph, startMallID, endMallID, i, currentRoute, allRoutes, routeCount);

                // Backtrack to explore other routes
                currentRoute->endMallID = -1;
                currentRoute->distance -= graph->adjMatrix[currentMallID][i];
                currentRoute->duration = 0.0;
            }
        }
    }
}

// Function to check if a mall has already been visited in the current route
bool isMallVisited(const Route* route, int mallID) {
    for (int i = 0; i < MAX_ROUTE_LENGTH; i++) {
        if (route->visitedMalls[i] == mallID) {
            return true;
        }
    }
    return false;
}

// Function to calculate the duration of a route based on speed and distance
double calculateDuration(const Route* route) {
    // Assume a constant speed in this example, you can modify this as needed
    const double averageSpeedKmph = 60.0; // 60 kilometers per hour

    double duration = route->distance / averageSpeedKmph;
    return duration;
}


void findRoutesBetweenMalls(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* allRoutes, int* routeCount) {
    if (currentMallID == endMallID) {
        // We have reached the destination mall
        allRoutes[*routeCount] = *currentRoute;
        (*routeCount)++;
        return;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[currentMallID][i] > 0) {
            // There is a connection from the current mall to another mall
            if (!isMallVisited(currentRoute, i)) {
                // If the mall has not been visited in this route
                currentRoute->visitedMalls[currentRoute->routeLength] = i;
                currentRoute->routeLength++;
                currentRoute->endMallID = i;
                currentRoute->distance += graph->adjMatrix[currentMallID][i];
                currentRoute->duration = calculateDuration(currentRoute);

                findRoutesBetweenMalls(graph, startMallID, endMallID, i, currentRoute, allRoutes, routeCount);

                // Backtrack to explore other routes
                currentRoute->endMallID = -1;
                currentRoute->routeLength--;
                currentRoute->visitedMalls[currentRoute->routeLength] = -1;
                currentRoute->distance -= graph->adjMatrix[currentMallID][i];
                currentRoute->duration = 0.0;
            }
        }
    }
}

// Function to find and store routes between mall A and mall B
void findAndStoreRoutes(Graph* graph, int startMallID, int endMallID, Route* allRoutes, int* routeCount) {
    Route currentRoute;
    currentRoute.startMallID = startMallID;
    currentRoute.endMallID = -1; // Initialize endMallID as -1
    currentRoute.distance = 0.0;
    currentRoute.trafficConditions = 0.0;
    currentRoute.duration = 0.0;

    for (int i = 0; i < MAX_ROUTE_LENGTH; i++) {
        currentRoute.visitedMalls[i] = -1; // Initialize visited malls as -1
    }
    currentRoute.routeLength = 0;

    findRoutesBetweenMalls(graph, startMallID, endMallID, startMallID, &currentRoute, allRoutes, routeCount);
}
