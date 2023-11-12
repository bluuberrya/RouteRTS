#include "main.h"
#include "mallData.h"
#include "route.h"

//void menu() {
//    //fileHandler();
//    //printf("Select Your Starting & Ending Point\n");
//    //routeSelection();
//    //system("pause");
//
//    fileHandler();
//    printf("Select Your Starting & Ending Point\n");
//    printMallList();
//
//    int startMallID, endMallID;
//    double speed;
//    printf("\n");
//
//    startMallID = getUserMallIDInput("Enter the starting mall's ID");
//    endMallID = getUserMallIDInput("Enter the ending mall's ID");
//
//    printf("Enter the speed (in kilometers per hour): ");
//    scanf("%lf", &speed);
//
//    Graph* graph = createGraph(NUM_MALLS);
//    for (int i = 0; i < NUM_MALLS; i++) {
//        for (int j = i + 1; j < NUM_MALLS; j++) {
//            addEdge(graph, i, j);
//        }
//    }
//
//    // Calculate and display the shortest route with the given speed
//    calculateShortestRoute(graph, startMallID - 1, endMallID - 1, speed);
//
//    free(graph); // Don't forget to free the memory for the graph when you're done.
//}

void menu() {
    fileHandler();
    printf("Select Your Starting & Ending Point\n");
    printMallList();

    int startMallID, endMallID;
    double speed = (double)rand() / RAND_MAX * 101.0 + 50.0;;
    printf("\n");

    //startMallID = getUserMallIDInput("Enter the starting mall's ID");
    //endMallID = getUserMallIDInput("Enter the ending mall's ID");

    startMallID = generateRandomMallID(-1);  // -1 indicates no exclusion
    endMallID = generateRandomMallID(startMallID);

    printf("Generated random values:\n");
    printf("Start Mall ID: %d\n", startMallID);
    printf("End Mall ID: %d\n", endMallID);

    printf("Random Speed: %lf", speed);

    Graph* graph = createGraph(NUM_MALLS);
    for (int i = 0; i < NUM_MALLS; i++) {
        for (int j = i + 1; j < NUM_MALLS; j++) {
            addEdge(graph, i, j);
        }
    }

    // Calculate and display the shortest route with the given speed
    double duration = calculateShortestRoute(graph, startMallID - 1, endMallID - 1, speed);

    // Print the duration of the shortest route
    printf("\nDuration of the Shortest Route: %.2lf hours\n", duration);

    free(graph); // Don't forget to free the memory for the graph when you're done.
}
