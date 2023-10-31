#include "main.h"
#include "mallData.h"
#include "route.h"
//
//// Define your route calculation functions here
//// Implement a DFS-based route finder, duration calculator, etc.
//// Store routes in an array of Route structures
//
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

// Function to find routes between mall A and mall B using DFS and store the three shortest routes
void findThreeRoutesBetweenMalls(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* shortestRoutes, int* routeCount) {
    if (currentMallID == endMallID) {
        // We have reached the destination mall
        // Compare the current route with the three shortest routes
        int i;
        for (i = 0; i < 3; i++) {
            if (currentRoute->distance < shortestRoutes[i].distance) {
                break;
            }
        }
        if (i < 3) {
            // Found a shorter route, shift others and insert this route
            for (int j = 2; j > i; j--) {
                shortestRoutes[j] = shortestRoutes[j - 1];
            }
            shortestRoutes[i] = *currentRoute;
        }
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

                findThreeRoutesBetweenMalls(graph, startMallID, endMallID, i, currentRoute, shortestRoutes, routeCount);

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

// Function to find and store the three shortest routes between mall A and mall B
void findAndStoreThreeRoutes(Graph* graph, int startMallID, int endMallID, Route* shortestRoutes, int* routeCount) {
    Route currentRoute;
    currentRoute.startMallID = startMallID;
    currentRoute.endMallID = -1; // Initialize endMallID as -1
    currentRoute.distance = 0.0;
    currentRoute.trafficConditions = 0.0;
    currentRoute.duration = 0.0;

    for (int i = 0; i < MAX_ROUTES; i++) {
        currentRoute.visitedMalls[i] = -1; // Initialize visited malls as -1
    }
    currentRoute.routeLength = 0;

    // Call the helper function with an additional parameter to limit the number of routes
    findAndStoreThreeRoutesHelper(graph, startMallID, endMallID, startMallID, &currentRoute, shortestRoutes, routeCount, 3);
}

// Helper function to find and store the three shortest routes between mall A and mall B
void findAndStoreThreeRoutesHelper(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* shortestRoutes, int* routeCount, int maxRoutes) {
    if (currentMallID == endMallID) {
        // We have reached the destination mall
        // Compare the current route with the stored shortest routes
        for (int i = 0; i < *routeCount; i++) {
            if (currentRoute->distance < shortestRoutes[i].distance) {
                // Insert the current route in the appropriate position
                for (int j = *routeCount - 1; j >= i; j--) {
                    if (j + 1 < maxRoutes) {
                        shortestRoutes[j + 1] = shortestRoutes[j];
                    }
                }
                shortestRoutes[i] = *currentRoute;

                // Limit the number of stored routes to the maximum desired
                if (*routeCount < maxRoutes) {
                    (*routeCount)++;
                }
                return;
            }
        }
        // If the route is longer than the existing routes, do not store it
        return;
    }

    if (*routeCount >= maxRoutes) {
        // We already have the desired number of routes, no need to continue
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

                findAndStoreThreeRoutesHelper(graph, startMallID, endMallID, i, currentRoute, shortestRoutes, routeCount, maxRoutes);

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



//// Function to find and store the three shortest routes between mall A and mall B
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
//    findAndStoreThreeRoutes(graph, startMallID, endMallID, startMallID, &currentRoute, shortestRoutes, routeCount);
//}
//
//Unhandled exception at 0x00007FF619792C62 in RTS_Group10.exe: 0xC00000FD : Stack overflow(parameters : 0x0000000000000001, 0x000000CE15CF3FB8).

//// Function to find routes between mall A and mall B using DFS
//void findRoutesBetweenMalls(Graph* graph, int startMallID, int endMallID, int currentMallID, Route* currentRoute, Route* allRoutes, int* routeCount) {
//    if (currentMallID == endMallID) {
//        // We have reached the destination mall
//        allRoutes[*routeCount] = *currentRoute;
//        (*routeCount)++;
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
//                findRoutesBetweenMalls(graph, startMallID, endMallID, i, currentRoute, allRoutes, routeCount);
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
//
//// Function to find and store routes between mall A and mall B
//void findAndStoreRoutes(Graph* graph, int startMallID, int endMallID, Route* allRoutes, int* routeCount) {
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
//    findRoutesBetweenMalls(graph, startMallID, endMallID, startMallID, &currentRoute, allRoutes, routeCount);
//}

double compareRoutesByDistance(const void* a, const void* b) {
    return ((Route*)a)->distance - ((Route*)b)->distance;
}
