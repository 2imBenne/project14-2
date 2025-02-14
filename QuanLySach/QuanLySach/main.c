#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() { 
    int choice;
	int valid;
    do {
    	system("color 5") ;
        mainMenu();
        valid = 0;
        do {
            char inputBuffer[10];
            
            fgets(inputBuffer, sizeof(inputBuffer), stdin);

            inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; 

            if (strlen(inputBuffer) == 0) {
                printf("Error: Choice cannot be empty. Please try again.\n");
                continue;
            }

            if (sscanf(inputBuffer, "%d", &choice) != 1) {
                printf("Error: Invalid input. Please enter a number.\n");
                continue;
            }

            valid = 1;
        } while (!valid);
        
        switch (choice) {
            case 1:
                loginAdmin();
                break;  
            case 0:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

