#include "main.h"

clock_t getCurrentTime() {
    return clock();
}

// Function to calculate elapsed time in seconds
double calculateElapsedTime(clock_t startTime, clock_t endTime) {
    return (double)(endTime - startTime) / CLOCKS_PER_SEC;
}