/*
                    CT087-3-3-RTS Realtime Systems
        Ng Wen Xuan   TP060653   APD3F2308CS(DA)
        Yam Chen Xi   TP061635   APD3F2308CS
        ======================================================
                           Workload Matrix
                       - - - - - - - - - - - - -
                                Ng Wen Xuan  Yam Chen Xi
        Road Data	                 80%	    20%
        Motorist Simulation	         80%	    20%
        Best Route	                 20%	    80%
        User Query	                 20%	    80%
        FreeRTOS Implementation	     50%	    50%
            - Task Create            50%        50%
            - Task Scheduling        30%        70%
            - Queue Handling         70%        30%
        Overall----------------------50%        50%
        ======================================================
*/

#include "mainh.h"
#include "malLData.h"
#include "route.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "supporting_functions.h"

QueueHandle_t xQueue;

Motorist user_query[100000];

// Function to create a Motorist struct
Motorist createMotorist(Graph* graph, int i, int numMotorists, int menu) {
    Motorist motorist;
    int startMallID, endMallID;

    if (menu == 1) {
        motorist.startMallID = generateRandomMallID(-1, NUM_MALLS);
        motorist.endMallID = generateRandomMallID(motorist.startMallID, NUM_MALLS);
        motorist.time = dijkstra(graph, motorist.startMallID, motorist.endMallID, &motorist.speed, &motorist.distance, 1);
    }
    else if (menu == 2) {
        motorist.startMallID = generateRandomMallID(-1, NUM_MALLS2);
        motorist.endMallID = generateRandomMallID(motorist.startMallID, NUM_MALLS2);
        motorist.time = dijkstra(graph, motorist.startMallID, motorist.endMallID, &motorist.speed, &motorist.distance, 2);
    }
    else if (menu == 3) {
        motorist.startMallID = generateRandomMallID(-1, NUM_MALLS);
        motorist.endMallID = generateRandomMallID(motorist.startMallID, NUM_MALLS);
        motorist.time = dijkstra(graph, motorist.startMallID, motorist.endMallID, &motorist.speed, &motorist.distance, 3);
    }

    user_query[i] = motorist;

    return motorist;
}

// Task to send value
static void vSenderTask(void* pvParameters) {
    Motorist lValueToSend;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(1000);

    int32_t i = 0;

    for (;;) {
        lValueToSend = user_query[i];

        xStatus = xQueueSendToBack(xQueue, &lValueToSend, xTicksToWait);

        if (i >= 100000) {
            i = 0;
            lValueToSend = user_query[i];
        }
        else {
            lValueToSend = user_query[i];
            i++;
        }

        if (xStatus != pdPASS) {
            vPrintString("Could not send to the queue.\r\n");
        }
    }
}

// Task to test performance of the system
static void vPerformanceTask(void* pvParameters) {
    Motorist lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

    clock_t start, end;
    double totalElapsedTime = 0.0;
    double minElapsedTime = DBL_MAX;
    double maxElapsedTime = 0.0;

    // Create graph using mall data
    Graph* graph = createGraph(NUM_MALLS);
    for (int i = 0; i < NUM_MALLS; i++) {
        for (int j = i + 1; j < NUM_MALLS; j++) {
            addEdge(graph, i, j);
        }
    }

    int numQueries = 50000;

    for (int i = 0; i < numQueries; i++) {

        if (uxQueueMessagesWaiting(xQueue) != 0) {
            vPrintString("Queue should have been empty!\r\n");
        }

        // Start elapsed time for each query
        start = clock();
        user_query[i] = createMotorist(graph, i, numQueries, 1);
        end = clock();

        double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
        xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);
        if (xStatus == pdPASS) {

            // Convert time to Min and Sec format
            int hours = lReceivedValue.time;
            double minutesRemainder = (lReceivedValue.time - hours) * 60;
            int minutes = minutesRemainder;
            double secondsRemainder = (minutesRemainder - minutes) * 60;
            int seconds = secondsRemainder;

            // Get elapsed time
            totalElapsedTime += elapsedTime;
            minElapsedTime = (elapsedTime < minElapsedTime) ? elapsedTime : minElapsedTime;
            maxElapsedTime = (elapsedTime > maxElapsedTime) ? elapsedTime : maxElapsedTime;

            double avgTime = totalElapsedTime / i;
            
            int q = i + 1;

            if (q == 1000) {
                printf("User Query\t| Total Elapsed Time\t| Min Elapsed Time\t| Max Elapsed Time\t| Average Elapsed Time\n");
                printf("%-10d\t| %-20.4lf\t| %-20.4lf\t| %-20.4lf\t| %-20.4lf\n", q, totalElapsedTime, minElapsedTime, maxElapsedTime, avgTime);
            }
            // Print result for every 5000th queries run
            else if (q >= 1000 && q % 5000 == 0 || q == numQueries) {
                printf("%-10d\t| %-20.4lf\t| %-20.4lf\t| %-20.4lf\t| %-20.4lf\n", q, totalElapsedTime, minElapsedTime, maxElapsedTime, avgTime);
            }
        }
        else {
            vPrintString("Could not receive from the queue.\r\n");
        }
    }

    printf("\n\n\n");
    vTaskEndScheduler();
}

// Task to check correctness of the system
static void vCorrectnessTask(void* pvParameters) {
    Motorist lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(1000);

    clock_t start, end;
    double totalElapsedTime = 0.0;
    double minElapsedTime = DBL_MAX;
    double maxElapsedTime = 0.0;

    Graph* graph = createGraph(NUM_MALLS2);
    for (int i = 0; i < NUM_MALLS2; i++) {
        for (int j = i + 1; j < NUM_MALLS2; j++) {
            addEdge(graph, i, j);
        }
    }

    int numQueries = 1000;

    for (int i = 0; i < numQueries; i++) {

        if (uxQueueMessagesWaiting(xQueue) != 0) {
            vPrintString("Queue should have been empty!\r\n");
        }

        printf("\n-------------------------------------------\n   \t\tQuery %d \t\t   \n", i + 1);

        start = clock();
        user_query[i] = createMotorist(graph, i, numQueries, 2);
        end = clock();

        double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
        xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);
        if (xStatus == pdPASS) {

            // Print received value of every query
            printf("Start Mall\t: %d - %s\n", lReceivedValue.startMallID, malls[lReceivedValue.startMallID - 1].name);
            printf("End Mall\t: %d - %s\n", lReceivedValue.endMallID, malls[lReceivedValue.endMallID - 1].name);

            printf("Distance\t: %.2lf kilometers\n", lReceivedValue.distance);
            printf("Speed\t\t: %.2lf km/h\n", lReceivedValue.speed);

            int hours = lReceivedValue.time;
            double minutesRemainder = (lReceivedValue.time - hours) * 60;
            int minutes = minutesRemainder;
            double secondsRemainder = (minutesRemainder - minutes) * 60;
            int seconds = secondsRemainder;
            printf("Time taken\t: %d min %d sec\n", minutes, seconds);
            printf("   \t\t%.4lf sec\t\t   \n-------------------------------------------\n\n", elapsedTime);
        }
        else {
            vPrintString("Could not receive from the queue.\r\n");
        }
    }

    printf(".\n.\n.\n===========================================================================\n");
    vTaskEndScheduler();
}

// Task to simulate motorist update
static void vMotoristTask(void* pvParameters) {
    Motorist lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(1000);

    clock_t start, end;
    double totalElapsedTime = 0.0;
    double minElapsedTime = DBL_MAX;
    double maxElapsedTime = 0.0;

    Graph* graph = createGraph(NUM_MALLS);
    for (int i = 0; i < NUM_MALLS; i++) {
        for (int j = i + 1; j < NUM_MALLS; j++) {
            addEdge(graph, i, j);
        }
    }

    int numQueries = 2;

    for (int i = 0; i < numQueries; i++) {

        if (uxQueueMessagesWaiting(xQueue) != 0) {
            vPrintString("Queue should have been empty!\r\n");
        }

        printf("\n\n-------------------------------------------\n   \t\tQuery %d \t\t   \n", i + 1);

        start = clock();
        user_query[i] = createMotorist(graph, i, numQueries, 3);
        end = clock();

        double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
        xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);
        if (xStatus == pdPASS) {

            printf("Start Mall\t: %d - %s\n", lReceivedValue.startMallID, malls[lReceivedValue.startMallID - 1].name);
            printf("End Mall\t: %d - %s\n", lReceivedValue.endMallID, malls[lReceivedValue.endMallID - 1].name);

            printf("Distance\t: %.2lf kilometers\n", lReceivedValue.distance);
            printf("Speed\t\t: %.2lf km/h\n", lReceivedValue.speed);

            int hours = lReceivedValue.time;
            double minutesRemainder = (lReceivedValue.time - hours) * 60;
            int minutes = minutesRemainder;
            double secondsRemainder = (minutesRemainder - minutes) * 60;
            int seconds = secondsRemainder;
            printf("Time taken\t: %d min %d sec", minutes, seconds);
            printf("\n-------------------------------------------\n");
        }
        else {
            vPrintString("Could not receive from the queue.\r\n");
        }
    }

    printf(".\n.\n.\n===========================================================================\n");
    vTaskEndScheduler();
}

void menu() {
    fileHandler();
    printf("----------------------------------------------------------------\n");
    printf("| %-60s |\n", "          Real Time Best Route Recommendation System");
    printf("----------------------------------------------------------------\n");
    printf("| %-60s |\n", "  1. Performance");
    printf("| %-60s |\n", "  2. Correctness");
    printf("| %-60s |\n", "  3. Motorist Simulation");
    printf("| %-60s |\n", "  4. Quit");
    printf("----------------------------------------------------------------\n");

    int option;

reinputOption:

    printf("Option: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        system("cls");
        printf("\t\t===========================================================================\n");
        printf("\t\t\t\t\t\tPerformance\n");
        printf("\t\t===========================================================================\n");
        xTaskCreate(vSenderTask, "motorist", 1024, NULL, 1, NULL);
        xTaskCreate(vPerformanceTask, "performance", 1024, NULL, 2, NULL);
        vTaskStartScheduler();
    case 2:
        system("cls");
        printf("\n\n\t\t===========================================================================\n");
        printf("\t\t\t\t\t\tCorrectness\n");
        printf("\t\t===========================================================================\n");
        xTaskCreate(vSenderTask, "motorist", 1024, NULL, 1, NULL);
        xTaskCreate(vCorrectnessTask, "correctness", 1024, NULL, 2, NULL);
        vTaskStartScheduler();
    case 3:
        system("cls");
        printf("\n\n\t\t===========================================================================\\n");
        printf("\t\t\t\t\tMotorist Simulation\n");
        printf("\t\t===========================================================================\\n");
        xTaskCreate(vSenderTask, "motorist", 1024, NULL, 1, NULL);
        xTaskCreate(vMotoristTask, "correctness", 1024, NULL, 2, NULL);
        vTaskStartScheduler();
    case 4:
        printf(".\n.\n.\nEnding Program");
        vTaskEndScheduler();

    default:
        printf("Option invalid");
        goto reinputOption;
    }
}


int main(void) {
    xQueue = xQueueCreate(20, sizeof(Motorist));

    if (xQueue != NULL) {
        menu();
    }
    else {
        // Queue creation failed
    }

    for (;;);

    return 0;
}