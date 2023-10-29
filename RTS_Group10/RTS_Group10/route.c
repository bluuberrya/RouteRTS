//#include "main.h"
//#include "mallData.h"
//#include "route.h"

// Function to find all routes from startMallID to endMallID using DFS
//void findAllRoutes(Graph* graph, int startMallID, int endMallID) {
//    // Implement DFS to traverse the graph and find all routes
//    // Calculate speed and duration for each route based on traffic conditions
//}

void printline() {
	printf("hehe");
}


//// Function to initialize a path
//Path* initPath(int numNodes) {
//    Path* path = (Path*)malloc(sizeof(Path));
//    path->nodes = (int*)malloc(numNodes * sizeof(int));
//    path->length = 0;
//    path->distance = 0.0;
//    return path;
//}
//
//// Function to free a path
//void freePath(Path* path) {
//    free(path->nodes);
//    free(path);
//}
//
//// Function to find the three shortest routes from startMallID to endMallID
//Path** findShortestRoutes(Graph* graph, int startMallID, int endMallID) {
//    int numNodes = graph->numVertices;
//
//    // Initialize arrays to track visited nodes and distances
//    int* visited = (int*)malloc(numNodes * sizeof(int));
//    double* minDistances = (double*)malloc(numNodes * sizeof(double));
//
//    for (int i = 0; i < numNodes; i++) {
//        visited[i] = 0;
//        minDistances[i] = DBL_MAX; // Initialize distances to infinity
//    }
//
//    // Initialize the start node
//    int startIndex = startMallID - 1;
//    minDistances[startIndex] = 0.0;
//
//    // Initialize an array to store the paths
//    Path** paths = (Path**)malloc(3 * sizeof(Path*));
//    for (int i = 0; i < 3; i++) {
//        paths[i] = initPath(numNodes);
//    }
//
//    // Dijkstra's algorithm
//    for (int count = 0; count < 3; count++) {
//        int u = -1;
//        for (int i = 0; i < numNodes; i++) {
//            if (!visited[i] && (u == -1 || minDistances[i] < minDistances[u])) {
//                u = i;
//            }
//        }
//
//        if (u == -1) {
//            break;
//        }
//
//        visited[u] = 1;
//
//        for (int v = 0; v < numNodes; v++) {
//            if (!visited[v] && graph->adjMatrix[u][v] > 0) {
//                double alt = minDistances[u] + graph->adjMatrix[u][v];
//                if (alt < minDistances[v]) {
//                    minDistances[v] = alt;
//
//                    // Update the path
//                    Path* path = paths[count];
//                    path->nodes[path->length] = u + 1; // Adjust for 1-based index
//                    path->length++;
//                    path->distance = minDistances[v];
//                }
//            }
//        }
//    }
//
//    // Free memory and return the paths
//    free(visited);
//    free(minDistances);
//    return paths;
//}
//
//
//getShortestRoute(Graph*graph, int startMallID, int endMallID) {
//    Path** shortestRoutes = findShortestRoutes(graph, startMallID, endMallID);
//
//    // Print the three shortest routes
//    printf("Three Shortest Routes from %s to %s:\n", malls[startMallID - 1].name, malls[endMallID - 1].name);
//    for (int i = 0; i < 3; i++) {
//        Path* path = shortestRoutes[i];
//        printf("Route %d: Distance %.2lf km, Path: ", i + 1, path->distance);
//        for (int j = 0; j < path->length; j++) {
//            printf("%s", malls[path->nodes[j] - 1].name); // Adjust for 1-based index
//            if (j < path->length - 1) {
//                printf(" -> ");
//            }
//        }
//        printf("\n");
//        freePath(path);
//    }
//    free(shortestRoutes);
//
//}