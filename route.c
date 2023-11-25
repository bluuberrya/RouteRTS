#include "mainh.h"
#include "mallData.h"
#include "route.h"

Mall malls[50];
#define NUM_MALLS 50

// Print mall list for display
void printMallList() {
    printf("Mall ID\tMall Name\n");
    for (int i = 0; i < NUM_MALLS; i++) {
        printf("%d\t%s\n", malls[i].mallID, malls[i].name);
    }
    printf("\n");
}

// Manually input mall ID (testing purpose)
int getUserMallIDInput(const char* prompt, int excludeID) {
    int mallID;

reinputMallID:

    printf("%s: ", prompt);
    scanf("%d", &mallID);

    if (mallID <= 0 || mallID > NUM_MALLS || mallID == excludeID) {
        vPrintString("Invalid mall ID.\r\n");
        goto reinputMallID;
    }

    return mallID;
}

// Generate random mall ID based on number of malls
int generateRandomMallID(int excludeID, int nummalls) {
    int mallID;

    // Exclude start mall ID from rand
    do {
        mallID = rand() % nummalls + 1;
    } while (mallID == excludeID);

    return mallID;
}

// Function to find the distance between two malls based on mallID
double findDistanceBetweenMalls(Graph* graph, int startMallID, int endMallID) {
    if (startMallID < 1 || startMallID > NUM_MALLS || endMallID < 1 || endMallID > NUM_MALLS) {
        printf("\nInvalid mall IDs. Please enter valid IDs between 1 and %d.\n", NUM_MALLS);
        return -1.0; // Indicate an error
    }

    int startIndex = startMallID - 1; // Adjust for array indexing
    int endIndex = endMallID - 1;     // Adjust for array indexing

    double distance = graph->adjMatrix[startIndex][endIndex];       // Insert distance into vertex

    if (distance == 0.0) {
        printf("\nNo direct connection between these two malls.\n");
    }
    else {
        return distance;
    }
}

// Print route or path found
void printPath(int parent[], int dest, int mode) {
    if (parent[dest] == -1) {
        printf("%d", dest + 1);
        return;
    }
    // format "1 2 3 4"
    if (mode == 1) {
        printPath(parent, parent[dest], 1);
        printf(" %d", dest + 1);
    }
    // format "1 -> 2 -> 3"
    else {
        printPath(parent, parent[dest], 0);
        printf(" -> %d", dest + 1);
    }
}

// Dijkstra's algorithm to find the shortest time route
double dijkstra(Graph* graph, int src, int dest, double* speed, double* distance, int menu) {
    
    if (menu == 2)
    {
        Mall malls[4];
        #define num_malls 4;
    }
    
    int numVertices = graph->numVertices;
    double tim[1000];  // The output array tim[i] holds the shortest time from src to i
    bool sptSet[1000];  // sptSet[i] will be true if the vertex i is included in the shortest time path tree or the shortest time distance from src to i is finalized
    int parent[1000];    // Parent array to store the shortest time path tree
    double distances[NUM_MALLS][NUM_MALLS];

    int u;
    double speeds[100000];
    int numMotorists;
    double sum = 0.0;

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < numVertices; i++) {
        tim[i] = DBL_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    // Distance from the source vertex to itself is always 0
    tim[src - 1] = 0.0;  // Adjust for 0-based indexing

    //Function to find the vertex with the minimum distance/time value
    for (int count = 0; count < numVertices - 1; count++) {
        double min = DBL_MAX;
        int minIndex = -1;

        for (int v = 0; v < numVertices; v++) {
            if (!sptSet[v] && tim[v] < min) {
                min = tim[v];
                minIndex = v;
            }
        }

        u = minIndex;

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Random number of motorist in path
        numMotorists = rand() % (30 - 10 + 1) + 10;

        // Random speed of the current motorist
        for (int i = 0; i < numMotorists; i++) {
            speeds[i] = 60.0 + ((double)rand() / RAND_MAX) * (120.0 - 60.0);
            sum = sum + speeds[i];
            if (menu == 3) {
                printf("%d * Current Speed: %.2lf\n", i, speeds[i]);
                Sleep(1);
            }
        }

        // For display
        if (menu == 3) {
            printf(".\n.\n.\n");
            Sleep(250);
        }

        // Calculate the average speed after the loop
        *speed = sum / numMotorists / numVertices;

        // Looping through vertices for dijkstra
        for (int v = 0; v < numVertices; v++) {
            if (!sptSet[v] && graph->adjMatrix[u][v] && tim[u] != DBL_MAX) {
                // Get the distance between malls using findDistanceBetweenMalls
                distances[u][v] = findDistanceBetweenMalls(graph, u + 1, v + 1);

                // Found shortest time after applying distance and speed
                // Update array for shortest time
                if (tim[u] + distances[u][v] / *speed < tim[v]) {
                    tim[v] = tim[u] + distances[u][v] / *speed;
                    parent[v] = u;
                }
            }
        }
    }

    int current = dest - 1;
    double totalDistance = 0.0;

    //Get distance of the path
    for (int i = 0; i < numVertices; i++) {
        if (i == dest - 1) {
            // Reached the destination, accumulate the distance
            while (parent[current] != -1) {
                int previous = parent[current];

                // Get the distance between malls using findDistanceBetweenMalls
                *distance = findDistanceBetweenMalls(graph, previous + 1, current + 1);

                // Accumulate the distance to the total
                totalDistance += *distance;
                current = previous;
            }
            *distance = totalDistance;
        }
    }

    if (menu == 2) {
        // Print pathing solution
        printf("\nShortest Route from Mall %d:\n", src);

        for (int i = 0; i < numVertices; i++) {
            if (i == 0) {
                printf("Start Mall\t| End Mall\t| Path");
            }
            if (i != src) {
                printf("\n%d\t\t| %d\t\t| ", src, i + 1);
                printPath(parent, i, 1);
            }
        }
        printf("\n\n");
    }

    if (menu == 3) {
        // Print average speed for motorist
        printf("Average Speed\t: %.2lf\n", *speed);
    }

    if (menu == 2 || menu == 3) {
        // Print best path
        printf("Path\t\t: ");
        printPath(parent, dest - 1, 0);
        printf("\n");
    }

    return *distance / *speed;
}