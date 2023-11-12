#include "main.h"
#include "mallData.h"
#include "route.h"

void menu() {
    fileHandler();
    printf("Select Your Starting & Ending Point\n");
    printMallList();

    int startMallID, endMallID;
    double speed = (double)rand() / RAND_MAX * 101.0 + 50.0;;
    printf("\n");

    //startMallID = getUserMallIDInput("Enter the starting mall's ID");
    //endMallID = getUserMallIDInput("Enter the ending mall's ID");

    clock_t startTime = getCurrentTime();

    startMallID = generateRandomMallID(-1);  // -1 indicates no exclusion
    endMallID = generateRandomMallID(startMallID);

    Graph* graph = createGraph(NUM_MALLS);
    for (int i = 0; i < NUM_MALLS; i++) {
        for (int j = i + 1; j < NUM_MALLS; j++) {
            addEdge(graph, i, j);
        }
    }

    // Calculate and display the shortest route with the given speed
    double duration = calculateShortestRoute(graph, startMallID - 1, endMallID - 1, speed);

    //free(graph); // Don't forget to free the memory for the graph when you're done.

    clock_t endTime = getCurrentTime();

    // Calculate and print the elapsed time
    double elapsedTime = calculateElapsedTime(startTime, endTime);

    // Print result
    printf("Generated random values\n");
    printf("Start Mall\t: %d - %s\n", startMallID, malls[startMallID - 1].name);
    printf("End Mall\t: %d - %s\n", endMallID, malls[endMallID - 1].name);
    printf("Speed\t\t: %lf\n", speed);
    printf("Duration\t: %.2lf hours\n", duration);

    printf("\nElapsed Time\t: %.6lf seconds\n", elapsedTime);
}