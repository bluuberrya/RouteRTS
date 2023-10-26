#pragma once

#ifndef ROUTE_H
#define ROUTE_H
#include "main.h"

//route struct
typedef struct {
    char mallA[100];
    char mallB[100];
    int routeID;
    double distance;
    double speed; // You can calculate speed based on time if needed
    double duration; // You can calculate duration based on speed if needed
} RouteData;

void routeDistance(const char* mallA, const char* mallB, RouteData* route) {
    // Search for mallA and mallB in mall data
    int indexA = -1, indexB = -1;
    for (int i = 0; i < NUM_MALLS; i++) {
        if (strcmp(mallA, malls[i].name) == 0) {
            indexA = i;
        }
        if (strcmp(mallB, malls[i].name) == 0) {
            indexB = i;
        }
    }

    // Check if both malls were found
    if (indexA != -1 && indexB != -1) {
        // Assign data to the route struct
        strcpy(route->mallA, mallA);
        strcpy(route->mallB, mallB);
        route->routeID = 1; // Assign a route ID (you can use a more complex logic)
        route->distance = distanceMatrix[indexA][indexB];
        route->speed = 0.0; // Set speed to 0 for now
        route->duration = 0.0; // Set duration to 0 for now
    }
    else {
        // Handle case where one or both malls were not found
        // (e.g., return an error code or message)
    }
}

void getRouteInfo(const char* startMall, const char* endMall) {
    RouteData route;
    routeDistance(startMall, endMall, &route);
    printf("\nRoute ID: %d\n", route.routeID);
    printf("Mall A: %s\n", route.mallA);
    printf("Mall B: %s\n", route.mallB);
    printf("Distance: %lf km\n", route.distance);
    printf("Speed: %lf\n", route.speed);
    printf("Duration: %lf hours\n", route.duration);
}

#endif