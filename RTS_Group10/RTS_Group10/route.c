// routeDistance(mallA, mallB)
// search for mallA mallB in mallData struct and put into routeData struct
// call routeDistance calculation function (use matrix data)
// return "mallA", "mallB" , "routeID", "distance", "speed(null) , "duration(null)", as struct


// routeDuration(distanceOfTwo)			//motorist data
// get routeID and distance, process it (distance/time=speed)
// jam level (1 to 5), set speed in route
// constantly update duration in all routes using struct
// call get3() and return the top 3 routes every 2 seconds


// get3()
// process all routes duration and get top 3 routes
// use sort and get shortest time
// -- display --
// Mall A to B
// route 1: 12km	| normal		| 30km/h	| 13mins
// route 2: 15km	| heavy traffic	| 10km/h	| 20mins
// route 3: 9km		| barely moving	| 3km/h		| 30mins

#include "main.h"
#include "mallData.h"
#include "route.h"

int main() {// act as main before transferring to a more concise main.c

    fileHandler();
    createMatrix();
    getRouteInfo("Pavilion Kuala Lumpur", "Pavilion Bukit Jalil");//should be converted to user input later

    graphRoute(8);

    return 0;
}