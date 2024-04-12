#include "mainh.h"
#include "mallData.h"
#include "route.h"

Mall malls[50];
#define NUM_MALLS 50

// Read data from CSV file and store into malls struct
void fileHandler() {
    FILE* file = fopen("RTS_Mall.csv", "r");
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

// Create graph using malls data
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

// Add edge with the calculated distance to the graph
void addEdge(Graph* graph, int src, int dest) {
    double distance = haversine(malls[src].latitude, malls[src].longitude, malls[dest].latitude, malls[dest].longitude);
    graph->adjMatrix[src][dest] = distance;
    graph->adjMatrix[dest][src] = distance;
}

// Function to print the graph (testing purpose)
void printGraph(Graph* graph) {
    printf("Graph with pairwise distances between shopping malls:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%.2lf\t", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}