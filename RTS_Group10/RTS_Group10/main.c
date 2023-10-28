//TP061635	Yam Chen Xi
//TP060653	Ng Wen Xuan

#include "main.h"
#include "menu.h"

int main() {
	char cont;

	//Loop menu until user wants to end the program
	do {
		system("cls");
		printf("Welcome to the Mall Distance Calculator\n- - - - -\n");
		menu();

		//press x to exit
		printf("\nPress <enter> to continue OR 'X' to end: ");
		scanf("%c", &cont);
		
	} while ((cont != 'x') && (cont != 'X'));

	printf("\nThank you and have a great day! \n");
	return 0;
}


// 
//#include "main.h"
//
//int main()
//{
//    printf("Hello World!");
//
//    //commented help
//
//    // main is used in FreeRTOS
//
//    // Workflow
//    // 1. mallData.h
//    // 2. route.c -> route.h
//    // 3. apply time
//    // 3. main.c (input and output)
//
//    // display all 48 malls and user input mallID to select
//    // thread: get return from call routeDistance(mallA, mallB)
//    // thread: put return to routeDuration(distanceOfTwo)
//    // thread: get elapsed time (from user input to get result), prompt result static
//
//    return 0;
//}