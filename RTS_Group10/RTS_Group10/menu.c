#include "main.h"
#include "mallData.h"
#include "route.h"

void menu() {
    fileHandler();
    printf("Select Your Starting & Ending Point\n");
    //routeSelection();

    //get many routes
    //get three shortest in distance
    //add motorist data/ speed
    //get duration of three routes

    // Call route calculation and manipulation functions from route.c
    Graph* graph = createGraph(NUM_MALLS);
    for (int i = 0; i < NUM_MALLS; i++) {
        for (int j = i + 1; j < NUM_MALLS; j++) {
            addEdge(graph, i, j);
        }
    }
    printMallList();

    // Get input for startMallID and endMallID
    int startMallID = getUserMallIDInput("Enter the starting mall's ID");
    int endMallID = getUserMallIDInput("Enter the ending mall's ID");

    // Call the modified function to find and store the three shortest routes
    Route shortestRoutes[3]; // Define an array to store the three shortest routes
    int shortestRouteCount = 0;
    findAndStoreThreeRoutes(graph, startMallID, endMallID, shortestRoutes, &shortestRouteCount);

    // Display the three shortest routes
    printf("\nThree Shortest Routes between Mall %d and Mall %d (by distance):\n", startMallID, endMallID);
    for (int i = 0; i < shortestRouteCount; i++) {
        printf("Route %d: Distance=%.2lf km, Duration=%.2lf hours, Traffic=%.2lf\n",
            i + 1, shortestRoutes[i].distance, shortestRoutes[i].duration, shortestRoutes[i].trafficConditions);
    }



}
