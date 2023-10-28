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
    int mallID;
    char name[100];
    double latitude;
    double longitude;
} Mall;

Mall malls[48]; // Assuming 48 malls
#define NUM_MALLS 48

// Define the Graph struct
typedef struct {
    int numVertices;
    double** adjMatrix; // Adjacency matrix with distances
} Graph;

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
        malls[mallIndex].mallID = atoi(token); // Read and store the mall ID

        token = strtok(NULL, ",");
        strcpy(malls[mallIndex].name, token);

        token = strtok(NULL, ",");
        malls[mallIndex].latitude = atof(token);

        token = strtok(NULL, ",");
        malls[mallIndex].longitude = atof(token);

        mallIndex++;
    }

    fclose(file);
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->adjMatrix = (double**)malloc(numVertices * sizeof(double*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = (double*)malloc(numVertices * sizeof(double));
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0.0; // Initialize distances to 0
        }
    }

    return graph;
}

// Haversine formula to calculate distance between two points on the Earth's surface
double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // Radius of the Earth in kilometers
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}

// Function to add an edge with the calculated distance to the graph
void addEdge(Graph* graph, int src, int dest) {
    double distance = haversine(malls[src].latitude, malls[src].longitude, malls[dest].latitude, malls[dest].longitude);
    graph->adjMatrix[src][dest] = distance;
    graph->adjMatrix[dest][src] = distance;
}

// Function to print the graph
void printGraph(Graph* graph) {
    printf("Graph with pairwise distances between shopping malls:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%.2lf\t", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int getUserMallIDInput(const char* prompt) {
    int mallID;
    printf("%s: ", prompt);
    scanf("%d", &mallID);
    return mallID;
}

// Function to find the distance between two malls based on mallID
double findDistanceBetweenMalls(Graph* graph, int startMallID, int endMallID) {
    if (startMallID < 1 || startMallID > NUM_MALLS || endMallID < 1 || endMallID > NUM_MALLS) {
        printf("Invalid mall IDs. Please enter valid IDs between 1 and %d.\n", NUM_MALLS);
        return -1.0; // Indicate an error
    }

    int startIndex = startMallID - 1; // Adjust for array indexing
    int endIndex = endMallID - 1;     // Adjust for array indexing

    double distance = graph->adjMatrix[startIndex][endIndex];

    if (distance == 0.0) {
        printf("No direct connection between these two malls.\n");
    }
    else {
        printf("Distance between %s and %s: %.2lf kilometers\n", malls[startIndex].name, malls[endIndex].name, distance);
    }

    return distance;
}

void printMallList() {
    printf("Mall ID\tMall Name\n");
    for (int i = 0; i < NUM_MALLS; i++) {
        printf("%d\t%s\n", malls[i].mallID, malls[i].name);
    }
}

void routeSelection() {
    int startMallID, endMallID;
    double distance;

    // Create the graph and add edges
    Graph* graph = createGraph(NUM_MALLS);
    for (int i = 0; i < NUM_MALLS; i++) {
        for (int j = i + 1; j < NUM_MALLS; j++) {
            addEdge(graph, i, j);
        }
    }

    printMallList();

    do {
        startMallID = getUserMallIDInput("Enter the starting mall's ID");
        endMallID = getUserMallIDInput("Enter the ending mall's ID");

        distance = findDistanceBetweenMalls(graph, startMallID, endMallID);
    } while (distance == -1.0);
}

#endif