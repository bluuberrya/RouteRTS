#pragma once

#ifndef ROUTE_H
#define ROUTE_H

#include "main.h"

#define MAX_ROUTE_LENGTH 50 // Define the maximum possible number of malls in a route

typedef struct {
    int startMallID;
    int endMallID;
    double distance;
    double trafficConditions;
    double duration;
    int visitedMalls[MAX_ROUTE_LENGTH];
    int routeLength;
    // Add more fields as needed
} Route;

//typedef struct {
//    int startMallID;
//    int endMallID;
//    double distance; // Distance between malls
//    double speed;    // Speed for the route (consider traffic conditions)
//    double duration; // Duration to travel from start to end mall
//} Route;


#endif