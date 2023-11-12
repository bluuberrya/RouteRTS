#include "main.h"
#include "mallData.h"
#include "route.h"


/*

Djikstra, get three nearby malls based on coordinates to generate 3 shortest distance routes 
then apply speed to routes for duration of routes

*/


//bool isMallVisited(const Route* route, int mallID) {
//    for (int i = 0; i < MAX_ROUTES; i++) {
//        if (route->visitedMalls[i] == mallID) {
//            return true;
//        }
//    }
//    return false;
//}

// Function to calculate the duration of a route based on speed and distance
// motorist data
//double calculateDuration(const Route* route) {
//    // Assume a constant speed in this example, you can modify this as needed
//    double randomValue = (double)rand() / RAND_MAX * 101.0 + 50.0;
//
//    const double averageSpeedKmph = randomValue; // 60 kilometers per hour
//
//    double duration = route->distance / averageSpeedKmph;
//    return duration;
//}

//double compareRoutesByDistance(const void* a, const void* b) {
//    return ((Route*)a)->distance - ((Route*)b)->distance;
//}

// -----------------------------------------------------------------------

int minDistance(double dist[], bool sptSet[], int numVertices) {
    double min = DBL_MAX;
    int min_index;

    for (int v = 0; v < numVertices; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void printShortestPath(int parent[], int j) {
    if (j == -1)
        return;

    /*printShortestPath(parent, parent[j]);*/
    printf(" -> %s", malls[j].name);
}

//double findThreeShortestRoutes(Graph* graph, int src, int dest, double speeds[3]) {
//    double* shortestDurations = (double*)malloc(3 * sizeof(double));
//    int** shortestRoutes = (int**)malloc(3 * sizeof(int*));
//
//    for (int i = 0; i < 3; i++) {
//        shortestRoutes[i] = (int*)malloc(graph->numVertices * sizeof(int));
//        shortestDurations[i] = DBL_MAX;
//        for (int j = 0; j < graph->numVertices; j++) {
//            shortestRoutes[i][j] = -1;
//        }
//    }
//
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < graph->numVertices; j++) {
//            int previousMall = src;
//            int currentMall = j;
//
//            if (currentMall == src) {
//                continue;
//            }
//
//            if (currentMall == dest) {
//                continue;
//            }
//
//            if (currentMall == previousMall) {
//                continue;
//            }
//
//            double duration = calculateShortestRoute(graph, src, currentMall, speeds[i]);
//
//            if (duration < shortestDurations[i]) {
//                shortestDurations[i] = duration;
//                shortestRoutes[i][0] = src;
//                shortestRoutes[i][1] = currentMall;
//                shortestRoutes[i][2] = dest;
//            }
//        }
//
//        src = shortestRoutes[i][1];
//    }
//
//    // Find the shortest duration route among the three
//    int shortestIndex = 0;
//    for (int i = 1; i < 3; i++) {
//        if (shortestDurations[i] < shortestDurations[shortestIndex]) {
//            shortestIndex = i;
//        }
//    }
//
//    int durationInMinutes = shortestDurations[shortestIndex] * 60;
//
//    // Display the shortest route
//    printf("\nShortest Route from %s to %s:", malls[src].name, malls[dest].name);
//    printShortestPath(shortestRoutes[shortestIndex], dest);
//    printf("\n");
//
//    //printf("Distance: %.2lf kilometers\n", shortestDurations[shortestIndex]);
//
//    printf("Duration: %.5lf minutes\n", shortestDurations[shortestIndex]);
//
//    // Free the dynamically allocated memory
//    for (int i = 0; i < 3; i++) {
//        free(shortestRoutes[i]);
//    }
//    free(shortestRoutes);
//    free(shortestDurations);
//
//    return shortestDurations[shortestIndex];
//}



double calculateShortestRoute(Graph* graph, int src, int dest, double speed) {
    int numVertices = graph->numVertices;
    double* dist = (double*)malloc(numVertices * sizeof(double));
    bool* sptSet = (bool*)malloc(numVertices * sizeof(bool));
    int* parent = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        dist[i] = DBL_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minDistance(dist, sptSet, numVertices);
        sptSet[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!sptSet[v] && graph->adjMatrix[u][v] && dist[u] != DBL_MAX &&
                dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    // Calculate the shortest path and its distance
    double distance = dist[dest];
    free(dist);
    free(sptSet);

    // Calculate duration based on distance and speed (duration = distance / speed)
    double duration = distance / speed;

    //printf("Shortest Route from %s to %s:", malls[src].name, malls[dest].name);
    //printShortestPath(parent, dest);
    //printf("\n");

    //printf("Distance: %.2lf kilometers\n", distance);
    //printf("Duration: %.2lf hours\n", duration);

    free(parent); // Don't forget to free the parent array

    return duration;
}


