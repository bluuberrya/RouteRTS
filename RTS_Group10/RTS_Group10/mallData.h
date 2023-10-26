#pragma once

#ifndef MALLDATA_H
#define MALLDATA_H
#include "main.h"

#define _USE_MATH_DEFINES // This is needed for Windows
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

typedef struct {
    char name[100];
    double latitude;
    double longitude;
} Mall;

Mall malls[48]; // Assuming 48 malls
#define NUM_MALLS 48

double distanceMatrix[NUM_MALLS][NUM_MALLS];

void fileHandler() {
    FILE* file = fopen("RTS Mall.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    int mallIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        strcpy(malls[mallIndex].name, token);

        token = strtok(NULL, ",");
        malls[mallIndex].latitude = atof(token);

        token = strtok(NULL, ",");
        malls[mallIndex].longitude = atof(token);

        mallIndex++;
    }

    fclose(file);

    // Access the contents of the first struct in the array
    // for testing, should delete in actual system
    printf("Mall Name: %s\n", malls[0].name);
    printf("Latitude: %lf\n", malls[0].latitude);
    printf("Longitude: %lf\n", malls[0].longitude);

}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // Radius of the Earth in kilometers
    double R = 6371.0;

    // Convert latitude and longitude from degrees to radians
    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;

    // Haversine formula
    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;
}

void createMatrix() {
    for (int i = 0; i < NUM_MALLS; i++) {
        for (int j = 0; j < NUM_MALLS; j++) {
            if (i != j) {
                distanceMatrix[i][j] = calculateDistance(malls[i].latitude, malls[i].longitude, malls[j].latitude, malls[j].longitude);
            }
        }
    }
}

#ifndef GRAPH_H
#define GRAPH_H
#endif // GRAPH_H

typedef struct {
    int numVertices;
    Mall* vertices;
    double** adjMatrix;
} Graph;

Graph* createGraph(int numVertices, Mall* malls) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->vertices = malls;

    // Allocate memory for the adjacency matrix and initialize it
    graph->adjMatrix = (double**)malloc(numVertices * sizeof(double*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = (double*)malloc(numVertices * sizeof(double));
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0.0;
        }
    }

    return graph;
}

void addEdge(Graph* graph, int start, int end, double distance) {
    // Add an edge between the two malls with the given distance
    graph->adjMatrix[start][end] = distance;
    graph->adjMatrix[end][start] = distance;
}

void destroyGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}

void printGraph(Graph* graph) {
    printf("Graph (Adjacency Matrix):\n");

    for (int i = 0; i < graph->numVertices; i++) {
        printf("%s: ", graph->vertices[i].name);

        for (int j = 0; j < graph->numVertices; j++) {
            printf("%lf ", graph->adjMatrix[i][j]);
        }

        printf("\n");
    }
}

int minDistance(double* dist, bool* visited, int numVertices) {
    double min = INFINITY;
    int minIndex = -1;

    for (int v = 0; v < numVertices; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Helper function to print the top 3 shortest routes
void printShortestRoutes(Graph*graph, double* dist, int* prev, int numVertices, int src) {
    // Create an array to store the results
    double shortestDistances[3] = { INFINITY, INFINITY, INFINITY };
    int shortestPaths[3] = { -1, -1, -1 };

    // Iterate through all vertices
    for (int v = 0; v < numVertices; v++) {
        if (v != src) {
            // If a shorter distance is found, update the results
            if (dist[v] < shortestDistances[0]) {
                shortestDistances[2] = shortestDistances[1];
                shortestPaths[2] = shortestPaths[1];
                shortestDistances[1] = shortestDistances[0];
                shortestPaths[1] = shortestPaths[0];
                shortestDistances[0] = dist[v];
                shortestPaths[0] = v;
            }
            else if (dist[v] < shortestDistances[1]) {
                shortestDistances[2] = shortestDistances[1];
                shortestPaths[2] = shortestPaths[1];
                shortestDistances[1] = dist[v];
                shortestPaths[1] = v;
            }
            else if (dist[v] < shortestDistances[2]) {
                shortestDistances[2] = dist[v];
                shortestPaths[2] = v;
            }
        }
    }

    // Print the top 3 shortest routes
    printf("\nTop 3 Shortest Routes from %s:\n", graph->vertices[src].name);
    for (int i = 0; i < 3; i++) {
        int destination = shortestPaths[i];
        if (destination != -1) {
            printf("Route %d: %s to %s, Distance: %lf km\n", i + 1, graph->vertices[src].name, graph->vertices[destination].name, shortestDistances[i]);
        }
    }
}

// Function to calculate the top 3 shortest routes using Dijkstra's algorithm
void calculateShortestRoutes(Graph* graph, int src) {
    int numVertices = graph->numVertices;
    double* dist = (double*)malloc(numVertices * sizeof(double));
    bool* visited = (bool*)malloc(numVertices * sizeof(bool));
    int* prev = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INFINITY;
        visited[i] = false;
        prev[i] = -1;
    }

    dist[src] = 0.0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minDistance(dist, visited, numVertices);
        visited[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph->adjMatrix[u][v] != 0 && dist[u] != INFINITY &&
                dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }

    // Print the top 3 shortest routes
    printShortestRoutes(graph, dist, prev, numVertices, src);

    free(dist);
    free(visited);
    free(prev);
}

void graphRoute(int sourceMallIndex) {
    // Create the graph
    Graph* mallGraph = createGraph(NUM_MALLS, malls);

    // Populate the graph with edges and distances
    for (int i = 0; i < NUM_MALLS; i++) {
        for (int j = i + 1; j < NUM_MALLS; j++) {
            double distance = calculateDistance(malls[i].latitude, malls[i].longitude, malls[j].latitude, malls[j].longitude);
            addEdge(mallGraph, i, j, distance);
        }
    }

    // Calculate and print the top 3 shortest routes from the specified source mall
    calculateShortestRoutes(mallGraph, sourceMallIndex);

    // Don't forget to destroy the graph when you're done
    destroyGraph(mallGraph);
}

#endif