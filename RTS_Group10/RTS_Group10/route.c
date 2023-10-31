#include "main.h"
#include "mallData.h"
#include "route.h"

/*

Djikstra, get three nearby malls based on coordinates to generate 3 shortest distance routes 
then apply speed to routes for duration of routes

*/


bool isMallVisited(const Route* route, int mallID) {
    for (int i = 0; i < MAX_ROUTES; i++) {
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

//// Function to find routes between mall A and mall B using DFS and store the three shortest routes
//void findThreeRoutesBetweenMalls(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* shortestRoutes, int* routeCount) {
//    if (currentMallID == endMallID) {
//        // We have reached the destination mall
//        // Compare the current route with the three shortest routes
//        int i;
//        for (i = 0; i < 3; i++) {
//            if (currentRoute->distance < shortestRoutes[i].distance) {
//                break;
//            }
//        }
//        if (i < 3) {
//            // Found a shorter route, shift others and insert this route
//            for (int j = 2; j > i; j--) {
//                shortestRoutes[j] = shortestRoutes[j - 1];
//            }
//            shortestRoutes[i] = *currentRoute;
//        }
//        return;
//    }
//
//    for (int i = 0; i < graph->numVertices; i++) {
//        if (graph->adjMatrix[currentMallID][i] > 0) {
//            // There is a connection from the current mall to another mall
//            if (!isMallVisited(currentRoute, i)) {
//                // If the mall has not been visited in this route
//                currentRoute->visitedMalls[currentRoute->routeLength] = i;
//                currentRoute->routeLength++;
//                currentRoute->endMallID = i;
//                currentRoute->distance += graph->adjMatrix[currentMallID][i];
//                currentRoute->duration = calculateDuration(currentRoute);
//
//                findThreeRoutesBetweenMalls(graph, startMallID, endMallID, i, currentRoute, shortestRoutes, routeCount);
//
//                // Backtrack to explore other routes
//                currentRoute->endMallID = -1;
//                currentRoute->routeLength--;
//                currentRoute->visitedMalls[currentRoute->routeLength] = -1;
//                currentRoute->distance -= graph->adjMatrix[currentMallID][i];
//                currentRoute->duration = 0.0;
//            }
//        }
//    }
//}

// Function to find and store the three shortest routes between mall A and mall B
//void findAndStoreThreeRoutes(Graph* graph, int startMallID, int endMallID, Route* shortestRoutes, int* routeCount) {
//    Route currentRoute;
//    currentRoute.startMallID = startMallID;
//    currentRoute.endMallID = -1; // Initialize endMallID as -1
//    currentRoute.distance = 0.0;
//    currentRoute.trafficConditions = 0.0;
//    currentRoute.duration = 0.0;
//
//    for (int i = 0; i < MAX_ROUTES; i++) {
//        currentRoute.visitedMalls[i] = -1; // Initialize visited malls as -1
//    }
//    currentRoute.routeLength = 0;
//
//    // Call the helper function with an additional parameter to limit the number of routes
//    findAndStoreThreeRoutes(graph, startMallID, endMallID, startMallID, &currentRoute, shortestRoutes, routeCount);
//}

double compareRoutesByDistance(const void* a, const void* b) {
    return ((Route*)a)->distance - ((Route*)b)->distance;
}
