//function.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "datatype.h"
#include <ctype.h>
#include <conio.h>
#define MAX_BOOKS 100
#define MAX_MEMBERS 100 
#define MAX_ADMIN 50

struct Book books[MAX_BOOKS];
struct member Members[MAX_MEMBERS]; 
int bookCount = 0;
int memberCount = 0; 


void refresh(){
	printf("Press Enter to continue: ");
	while(getchar() != '\n');
	system("cls");
} 

void menuSach() { 
    printf("***Book Management System Using C***\n");
    printf("\n");
    printf("               MENU                     \n");
    printf("      ==========================\n");
    printf("      [1] Add A New Book.\n");
    printf("      [2] Show All Books.\n");
    printf("      [3] Search A Book.\n");
    printf("      [4] Edit A Book.\n");
    printf("      [5] Delete A Book.\n");
    printf("      [6] Sort Books by Price.\n");
    printf("      [7] Read Books From File.\n");
    printf("      [0] Exit the Program.\n");
    printf("      ==========================\n");
     
}

void displayMenuLibrary(){
	refresh();
	int choice;
	int valid;
    do {
        menuSach();
        valid = 0;
         do {
            char inputBuffer[10];
            printf("Enter your choice: ");
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
                addBook();
                
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBookByTitle();
                break;
            case 4:
                editBook();
                break;
            case 5:
                deleteBook();
                break;
            case 6:
                sortBooksByPrice();
                break;
            case 7:
            	ReadListBooksFromFile();
            	break; 
            case 0:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


//Tiet 1
void displayBooks() {
   
    if (bookCount == 0) {
        printf("There are no books in the list.\n");
        return;
    }

    printf("                         **** All Books ****\n");
    printf("|============|===========================|======================|============|============|=================|\n");
    printf("| %-10s | %-25s | %-20s | %-10s | %-10s | %-15s |\n", "ID", "Title", "Author", "Quantity", "Price", "Publication");
    printf("|============|===========================|======================|============|============|=================|\n");

	int i;  
    for (i = 0; i < bookCount; i++) {
        printf("| %-10s | %-25s | %-20s | %-10d | %-10d | %02d/%02d/%04d      |\n", 
               books[i].bookId, 
               books[i].title, 
               books[i].author, 
               books[i].quantity, 
               books[i].price,
               books[i].publication.day,
               books[i].publication.month,
               books[i].publication.year);
      
        printf("|------------|---------------------------|----------------------|------------|------------|-----------------|\n");
    }

    printf("\n");
    char choice;
    int valid;
    do {
       
       
         valid = 0;
        do {
            char inputBuffer[10];
             printf("Go back (b)? or Exit (0)?: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);

            inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; 

            if (strlen(inputBuffer) == 0) {
                printf("Error: Choice cannot be empty. Please try again.\n");
                continue;
            }

            if (sscanf(inputBuffer, "%s", &choice) != 1) {
                printf("Error: Invalid input. Please try again.\n");
                continue;
            }

            valid = 1;
        } while (!valid);
        
        if (choice == 'b') {
            return; 
        } else if (choice == '0') {
            printf("==========Thank You==========\n");
            printf("==========See You Soon==========\n\n");
            printf("--------------------------------------");
            exit(0); 
        } else {
            printf("Invalid choice. Please enter 'b' or '0'.\n");
        }
    } while (choice != 'b' && choice != '0');
    printf("\n");
    printf("\n");
    printf("\n");
}


//Tiet 4
int isValidDate(int day, int month, int year) {
   
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return 0;
    }

 
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29; 
    }

    if (day > daysInMonth[month - 1]) {
        return 0;
    }

    return 1;
}


//Tiet 1
void addBook() {
    refresh();
    printf("                         **** Add A New Book ****\n");
    if (bookCount >= MAX_BOOKS) {
        printf("Cannot add book, list is full.\n");
        return;
    }

    struct Book newBook;
    int valid;

    do {
        valid = 1;
        char inputBuffer[10];

        printf("Enter the Book ID: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        if (strlen(inputBuffer) == 0) {
            printf("Error: Book ID cannot be empty. Please try again.\n");
            valid = 0;
        } else if (strlen(inputBuffer) > 10) {
            printf("Error: Book ID must be <= 10 characters. Please try again.\n");
            valid = 0;
        } else {
            int i;
            for (i = 0; i < bookCount; i++) {
                if (strcmp(books[i].bookId, inputBuffer) == 0) {
                    printf("Error: Book ID '%s' already exists.\n", inputBuffer);
                    valid = 0;
                    break;
                }
            }
        }

        if (valid) {
            strcpy(newBook.bookId, inputBuffer);
        }

    } while (!valid);

    do {
        valid = 1;
        char inputBuffer[30];
        printf("Enter the Title: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        if (strlen(inputBuffer) == 0) {
            printf("Error: Title cannot be empty. Please try again.\n");
            valid = 0;
        } else if (strlen(inputBuffer) > 30) {
            printf("Error: Title must be <= 30 characters. Please try again.\n");
            valid = 0;
        } else {
            int i;
            for (i = 0; i < bookCount; i++) {
                if (strcmp(books[i].title, inputBuffer) == 0) {
                    printf("Error: Title '%s' already exists.\n", inputBuffer);
                    valid = 0;
                    break;
                }
            }
        }

        if (valid) {
            strcpy(newBook.title, inputBuffer);
        }

    } while (!valid);

    if (strcmp(newBook.bookId, newBook.title) == 0) {
        printf("Error: Book ID and Title cannot be the same. Please enter different values.\n");
        return;
    }

    do {
        valid = 1;
        char inputBuffer[20];
        printf("Enter the Author: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        if (strlen(inputBuffer) == 0) {
            printf("Error: Author cannot be empty. Please try again.\n");
            valid = 0;
        } else if (strlen(inputBuffer) > 20) {
            printf("Error: Author must be <= 20 characters. Please try again.\n");
            valid = 0;
        } else {
            valid = 1;
        }

        if (valid) {
            strcpy(newBook.author, inputBuffer);
        }

    } while (!valid);

    do {
        valid = 1;
        char inputBuffer[20];
        printf("Enter the Quantity: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        if (strlen(inputBuffer) == 0) {
            printf("Error: Quantity cannot be empty. Please enter a positive number.\n");
            valid = 0;
        } else {
            int quantity = atoi(inputBuffer);
            if (quantity <= 0) {
                printf("Error: Quantity must be a positive number.\n");
                valid = 0;
            } else {
                newBook.quantity = quantity;
            }
        }

    } while (!valid);

    do {
        valid = 1;
        char inputBuffer[20];
        printf("Enter the Price: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        if (strlen(inputBuffer) == 0) {
            printf("Error: Price cannot be empty. Please enter a positive number.\n");
            valid = 0;
        } else {
            int price = atoi(inputBuffer);
            if (price <= 0) {
                printf("Error: Price must be a positive number.\n");
                valid = 0;
            } else {
                newBook.price = price;
            }
        }

    } while (!valid);

    do {
        valid = 1;
        char inputBuffer[50];
        printf("Enter the Publication Date (dd mm yyyy): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        if (strlen(inputBuffer) == 0) {
            printf("Error: Publication date cannot be empty. Please enter a valid date.\n");
            valid = 0;
        } else {
            int day, month, year;
            if (sscanf(inputBuffer, "%d %d %d", &day, &month, &year) != 3 || !isValidDate(day, month, year)) {
                printf("Error: Invalid publication date. Please enter a valid date in the format dd mm yyyy.\n");
                valid = 0;
            } else {
                newBook.publication.day = day;
                newBook.publication.month = month;
                newBook.publication.year = year;
            }
        }

    } while (!valid);

    books[bookCount] = newBook;
    bookCount++;

    saveBooksToFile();

    printf("\n");
    printf("Book Added Successfully.\n");
    printf("\n");

    char choice;
    do {
        valid = 0;
        do {
            char inputBuffer[10];
            printf("Go back (b)? or Exit (0)?: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);

            inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

            if (strlen(inputBuffer) == 0) {
                printf("Error: Choice cannot be empty. Please try again.\n");
                continue;
            }

            if (sscanf(inputBuffer, "%s", &choice) != 1) {
                printf("Error: Invalid input. Please try again.\n");
                continue;
            }

            valid = 1;
        } while (!valid);

        if (choice == 'b') {
            return;
        } else if (choice == '0') {
            printf("==========Thank You==========\n");
            printf("==========See You Soon==========\n\n");
            printf("--------------------------------------");
            exit(0);
        } else {
            printf("Invalid choice. Please enter 'b' or '0'.\n");
        }

    } while (choice != 'b' && choice != '0');

    printf("\n");
    printf("\n");
    printf("\n");
}



//Tiet 2
void editBook() {
	refresh();
    printf("                         **** Edit A Book ****\n");
    char id[10];
    
    int valid = 0;
    do {
        char inputBuffer[10];
         printf("Enter the Book ID : ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; 

        if (strlen(inputBuffer) == 0) {
            printf("Error: Choice cannot be empty. Please try again.\n");
            continue;
        }

        if (sscanf(inputBuffer, "%10s", id) != 1) {
            printf("Error: Invalid input. Please enter the ID to Edit.\n");
            continue;
        }

        valid = 1; 
    } while (!valid); 

    int index = -1;
    int i;
    for (i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookId, id) == 0) {
            index = i;
            break;
        }
    }
    
  

    if (index == -1) {
        printf("Error: Book with ID '%s' not found.\n", id);
        return;
    }
    
    printf("One Book Found for ID: %s\n\n", books[index].bookId);
	printf("Book Information\n");
	printf("------------------------------\n");
	printf("%-15s: %s\n", "ID", books[index].bookId);
	printf("%-15s: %s\n", "Title", books[index].title);
	printf("%-15s: %s\n", "Author", books[index].author);
	printf("%-15s: %d\n", "Quantity", books[index].quantity);
	printf("%-15s: %d\n", "Price", books[index].price);
	printf("%-15s: %02d/%02d/%04d\n\n", "Publication Date", 
	       books[index].publication.day, 
	       books[index].publication.month, 
	       books[index].publication.year);
	printf("------------------------------\n");
	printf("                  ***************Update The New Book *****\n");
	valid;
    do {
        valid = 1; 
        char inputBuffer[30];
        printf("Enter the new Title: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
        
        if (strlen(inputBuffer) == 0) {
	        printf("Error: Title book cannot be empty. Please try again.\n");
	        valid = 0;
        }
        else if (strlen(inputBuffer) > 30) {
            printf("Error: Title must be <= 30 characters.\n");
            valid = 0;
        } else {
        	int i;
            for (i = 0; i < bookCount; i++) {
                if (strcmp(books[i].title, inputBuffer) == 0) {
                    printf("Error: Book Title '%s' already exists.\n", inputBuffer);
                    valid = 0;
                    break;
                }
            }
        }
	 if (valid) {
		strcpy(books[index].title, inputBuffer); 
	 }
    } while (!valid);

   
     do {
        valid = 1; 
        char inputBuffer[20];
        printf("Enter the new Author: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
        
        if (strlen(inputBuffer) == 0) {
	        printf("Error: Author book cannot be empty. Please try again.\n");
	        valid = 0;
        }
        else if (strlen(inputBuffer) > 30) {
            printf("Error: Author must be <= 20 characters.\n");
            valid = 0;
        } else {
            valid = 1;
        }
        if (valid) {
		   strcpy(books[index].author, inputBuffer); 
	    }
    } while (!valid);
    
    

    do {
	    valid = 1; 
	    char inputBuffer[20];
	    printf("Enter the Quantity: ");
	    fgets(inputBuffer, sizeof(inputBuffer), stdin);
	    inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; 
	
	    if (strlen(inputBuffer) == 0) {
	        printf("Error: Quantity cannot be empty. Please enter a positive number.\n");
	        valid = 0;
	    } else {
	        int quantity = atoi(inputBuffer); 
	        if (quantity <= 0) {
	            printf("Error: Quantity must be a positive number.\n");
	            valid = 0;
	        } else {
	            books[index].quantity = quantity;
	        }
	    }
	} while (!valid);

    do {
	    valid = 1; 
	    char inputBuffer[20];
	    printf("Enter the Price: ");
	    fgets(inputBuffer, sizeof(inputBuffer), stdin);
	    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
	
	    if (strlen(inputBuffer) == 0) {
	        printf("Error: Price cannot be empty. Please enter a positive number.\n");
	        valid = 0;
	    } else {
	        int price = atoi(inputBuffer); 
	        if (price <= 0) {
	            printf("Error: Price must be a positive number.\n");
	            valid = 0;
	        } else {
	            books[index].price = price;
	        }
	    }
	} while (!valid);

	 do {
	    valid = 1;
	    char inputBuffer[50];
	    printf("Enter the Publication Date (dd mm yyyy): ");
	    fgets(inputBuffer, sizeof(inputBuffer), stdin);
	    inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; // loai bo ky tu xuong dong 
	
	    if (strlen(inputBuffer) == 0) {
	        printf("Error: Publication date cannot be empty. Please enter a valid date.\n");
	        valid = 0;
	    } else {
	        int day, month, year;
	        if (sscanf(inputBuffer, "%d %d %d", &day, &month, &year) != 3 || 
	            !isValidDate(day, month, year)) {
	            printf("Error: Invalid publication date. Please enter a valid date in the format dd mm yyyy.\n");
	            valid = 0;
	        } else {
	            books[index].publication.day = day;
	            books[index].publication.month = month;
	            books[index].publication.year = year;
	        }
	    }
	} while (!valid);

    printf("Book Updated successfully.\n");
 	saveBooksToFile();
  
        printf("\n");
    char choice;
    valid;
    do {
       
       
        
         valid = 0;
        do {
            char inputBuffer[10];
             printf("Go back (b)? or Exit (0)?: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);

            inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; 

            if (strlen(inputBuffer) == 0) {
                printf("Error: Choice cannot be empty. Please try again.\n");
                continue;
            }

            if (sscanf(inputBuffer, "%s", &choice) != 1) {
                printf("Error: Invalid input. Please try again.\n");
                continue;
            }

            valid = 1;
        } while (!valid);
        
        if (choice == 'b') {
            return; 
        } else if (choice == '0') {
            printf("==========Thank You==========\n");
            printf("==========See You Soon==========\n\n");
            printf("--------------------------------------");
            exit(0); 
        } else {
            printf("Invalid choice. Please enter 'b' or '0'.\n");
        }
    } while (choice != 'b' && choice != '0');
    printf("\n");
    printf("\n");
    printf("\n");
}

//Tiet 3
void deleteBook() {
	refresh();
    printf("                         **** Delete A Book ****\n");
    char id[20];

    while (1) {
        printf("Enter the Book ID: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0'; 

        if (strlen(id) == 0) {
            printf("Error: Book ID cannot be empty. Please try again.\n");
        } else {
            break;
        }
    }

    // Search for the book by ID
    int index = -1;
    int i;
    for (i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Book with ID '%s' not found.\n", id);
        return;
    }

    printf("One Book Found for ID: %s\n\n", books[index].bookId);
    printf("Book Information\n");
    printf("------------------------------\n");
    printf("%-15s: %s\n", "ID", books[index].bookId);
    printf("%-15s: %s\n", "Title", books[index].title);
    printf("%-15s: %s\n", "Author", books[index].author);
    printf("%-15s: %d\n", "Quantity", books[index].quantity);
    printf("%-15s: %d\n", "Price", books[index].price);
    printf("%-15s: %02d/%02d/%04d\n\n", "Publication Date",
           books[index].publication.day,
           books[index].publication.month,
           books[index].publication.year);

    
    char confirm;
    printf("Are you sure you want to delete this book? (Y/N): ");
    while (1) {
        scanf(" %c", &confirm);
        confirm = toupper(confirm); 
        if (confirm == 'Y' || confirm == 'N') {
            break;
        } else {
            printf("Invalid input. Please enter 'Y' or 'N': ");
        }
    }

    if (confirm == 'Y') {
        
        int j;
        for (j = index; j < bookCount - 1; j++) {
            books[j] = books[j + 1];
        }
        bookCount--;
        printf("Book Deleted Successfully.\n");

        saveBooksToFile();
    } else {
        printf("Book Deletion Cancelled.\n");
    }

    char choice;
    while (1) {
        printf("Go back (b) or Exit (0): ");
        scanf(" %c", &choice);
        while (getchar() != '\n'); 

        if (choice == 'b') {
            return;
        } else if (choice == '0') {
            printf("========== Thank You ==========\n");
            printf("========== See You Soon ==========\n\n");
            printf("--------------------------------------\n");
            exit(0);
        } else {
            printf("Invalid choice. Please enter 'b' or '0'.\n");
        }
    }
}


//Tiet 3
void sortBooksByPrice() {
	refresh();
    int choice;
    printf("Choose sorting order:\n");
    printf("[1] Ascending (Low to High)\n");
    printf("[2] Descending (High to Low)\n");
    printf("Enter your choice: ");
    int valid = 0;
    do {
        char inputBuffer[10];
        printf("Enter your choice: ");
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

	int i;
    for (i = 0; i < bookCount - 1; i++) {
    	int j;
        for (j = i + 1; j < bookCount; j++) {
            if ((choice == 1 && books[i].price > books[j].price) ||
                (choice == 2 && books[i].price < books[j].price)) {
                struct Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    printf("Books sorted successfully.\n");
    displayBooks();
}

void toLowerCase(char* str) {
	int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

//Tiet 4
void searchBookByTitle() {
	refresh();
    char keyword[30];
    char keywordLower[30];    
    int valid = 0;
    do {
        char inputBuffer[10];
        printf("Enter the title keyword to search: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; 

        if (strlen(inputBuffer) == 0) {
            printf("Error: The title keyword cannot be empty. Please try again.\n");
            continue;
        }

        if (sscanf(inputBuffer, "%50s", keyword) != 1) {
            printf("Error: Invalid input. Please enter the ID.\n");
            continue;
        }

        valid = 1; 
    } while (!valid); 
    
    strcpy(keywordLower, keyword);
    toLowerCase(keywordLower);
    
    int found = 0;
    printf("\nBooks matching '%s':\n", keyword);
    printf("|============|===========================|======================|============|============|=================|\n");
    printf("| %-10s | %-25s | %-20s | %-10s | %-10s | %-15s |\n", "ID", "Title", "Author", "Quantity", "Price", "Publication");
    printf("|============|===========================|======================|============|============|=================|\n");

	int i;
    for (i = 0; i < bookCount; i++) {
    	char titleLower[30];
        strcpy(titleLower, books[i].title); 
        toLowerCase(titleLower);
        
        if (strstr(titleLower, keywordLower) != NULL) { 
             printf("| %-10s | %-25s | %-20s | %-10d | %-10d | %02d/%02d/%04d      |\n", 
               books[i].bookId, 
               books[i].title, 
               books[i].author, 
               books[i].quantity, 
               books[i].price,
               books[i].publication.day,
               books[i].publication.month,
               books[i].publication.year);
      
        printf("|------------|---------------------------|----------------------|------------|------------|-----------------|\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found with the keyword '%s'.\n", keyword);
    }
}


//Tiet 5
void ReadListBooksFromFile() {
	refresh();
    FILE *file = fopen("book.txt", "rb");
    
    if (file == NULL) {
        printf("Error: Could not open file for reading book.txt.\n");
        return;
    }
    
  
    while (fscanf(file, "%[^,], %[^,], %[^,], %d, %d, %d, %d, %d\n", 
                   books[bookCount].bookId,
                   books[bookCount].title,
                   books[bookCount].author,
                   &books[bookCount].quantity,
                   &books[bookCount].price,
                   &books[bookCount].publication.day,
                   &books[bookCount].publication.month,
                   &books[bookCount].publication.year) == 8) {
        bookCount++;
        
        if (bookCount >= MAX_BOOKS) {
            break;
        }
    }
    
    fclose(file);
    
    printf("Data loaded successfully from book.txt\n");
}


//Tiet 5
void saveBooksToFile() {
    FILE *file = fopen("book.txt", "w"); 
    if (file == NULL) {
        printf("Error: Could not open file for writing book.txt.\n");
        return;
    }
	int i;
    for (i = 0; i < bookCount; i++) {
        fprintf(file, "%s, %s, %s, %d, %d, %d, %d, %d\n", 
                books[i].bookId,
                books[i].title,
                books[i].author,
                books[i].quantity,
                books[i].price,
                books[i].publication.day,
                books[i].publication.month,
                books[i].publication.year);
    }

    fclose(file);
    printf("Data saved successfully to book.txt\n");
}




//Main Menu 
void mainMenu() {
    printf("***Book Management System Using C***\n");
    printf("\n");
    printf("           CHOOSE YOUR ROLE                    \n");
    printf("      ==========================\n");
    printf("      [1] Admin.\n");
	printf("      [2] Manager.\n");
    printf("      [3] Member.\n");
    printf("      [0] Exit the Program.\n");
    printf("      ==========================\n");
    printf("Enter The Choice: ");
}



//Login admin
void loginAdmin() {
	system("cls");
	system("color 6"); 
    printf("***Book Management System Using C***\n");
    printf("\n");
    printf("               LOGIN                    \n");
    printf("      =======================\n");
    int result = authenticate();
   
    printf("Enter The Choice: ");
}


int authenticate() {
    char username[MAX_ADMIN], password[MAX_ADMIN];
    char inputUser[MAX_ADMIN], inputPass[MAX_ADMIN];

   
    FILE *file = fopen("admin.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open admin.txt file.\n");
        exit(1);
    }

   
    if (fscanf(file, "%[^,],%s", username, password) != 2) {
        printf("Error: Invalid admin.txt format.\n");
        fclose(file);
        exit(1);
    }
    fclose(file);

    while (1) {
      
        while (1) {
            printf("Enter Username: ");
            fgets(inputUser, sizeof(inputUser), stdin);
            inputUser[strcspn(inputUser, "\n")] = '\0';

            if (strlen(inputUser) == 0) {
                printf("Error: Username cannot be empty. Please try again.\n");
            } else {
                break;
            }
        }

       
        while (1) {
            printf("Enter Password: ");
            getPassword(inputPass);

            if (strlen(inputPass) == 0) {
                printf("Error: Password cannot be empty. Please try again.\n");
            } else {
                break;
            }
        }

       
        if (strcmp(username, inputUser) == 0 && strcmp(password, inputPass) == 0) {
            printf("Login successful!\n");
            printf("      ==========================\n");
            displayMenuManagement();
            return 1; 
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }
}


void getPassword(char *password) {
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r') { 
        if (ch == '\b' && i > 0) { 
            printf("\b \b");
            i--;
        } else if (ch != '\b' && i < MAX_ADMIN - 1) { 
            printf("*");
            password[i++] = ch;
        }
    }
    password[i] = '\0';
    printf("\n");
}


void menuManagement() {
    printf("***Book Management System Using C***\n");
    printf("\n");
    printf("               MENU                    \n");
    printf("      ==========================\n");
    printf("      [1] Library management.\n");
    printf("      [2] Customer management.\n");
	printf("      [0] Exit the Program.\n");
    printf("      ==========================\n");
   
}


void displayMenuManagement(){
	int choice;
    do {
        menuManagement();
		int valid = 0;
        do {
            char inputBuffer[10];
            printf("Enter your choice: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);

            inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; 

            if (strlen(inputBuffer) == 0) {
                printf("Error: Choice cannot be empty. Please try again.\n");
                continue;
            }

            if (sscanf(inputBuffer, "%d", &choice) > 2) {
                printf("Error: Invalid input. Please enter a number.\n");
                continue;
            }

            valid = 1;
        } while (!valid);
        
        switch (choice) {
            case 1:
                displayMenuLibrary();
                break;
            case 2:
            	displayMenuMembers();
				break;    
            case 0:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}

//=====================================fuction for member============================================= 

void menuManageMembers() { 
    printf("***Book Management System Using C***\n");
    printf("\n");
    printf("           Member Management Menu                     \n");
    printf("      ==========================\n");
    printf("      [1] Add A New Member.\n");
    printf("      [2] Show All Member.\n");
    printf("      [3] Edit A Member.\n");
    printf("      [4] Search A Member.\n");
    printf("      [5] Read Members From File.\n");
    printf("      [0] Exit the Program.\n");
    printf("      ==========================\n");
     
}

 
void displayMenuMembers(){
	refresh();
	int choice;
	int valid;
    do {
        menuManageMembers();
        valid = 0;
         do {
            char inputBuffer1[10];
            printf("Enter your choice: ");
            fgets(inputBuffer1, sizeof(inputBuffer1), stdin);

            inputBuffer1[strcspn(inputBuffer1, "\n")] = '\0'; 

            if (strlen(inputBuffer1) == 0) {
                printf("Error: Choice cannot be empty. Please try again.\n");
                continue;
            }

            if (sscanf(inputBuffer1, "%d", &choice) != 1) {
                printf("Error: Invalid input. Please enter a number.\n");
                continue;
            }

            valid = 1;
        } while (!valid);
		
        switch (choice) {
            case 1:
                addMember(); 
                break;
            case 2:
                displayMembers();
                break;
            case 3:
                searchBookByTitle();
                break;
            case 4:
                editBook();
                break;
            case 5:
            	ReadListMemberFromFile();
            	break; 
            case 0:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}



void ReadListMemberFromFile() {
	refresh();
    FILE *file = fopen("member.txt", "rb");
    
    if (file == NULL) {
        printf("Error: Could not open file for reading member.txt.\n");
        return;
    }
    
  
    while (fscanf(file, "%[^,], %[^,], %[^,], %d\n", 
                   Members[memberCount].memberId,
                   Members[memberCount].name,
                   Members[memberCount].phone,
				   Members[memberCount].status) ){
				   
        memberCount++;
        
        if (memberCount >= MAX_MEMBERS) {
            break;
        }
    }
    
    fclose(file);
    
    printf("Data loaded successfully from member.txt\n");
}


void saveMemberToFile() {
    FILE *file = fopen("member.txt", "w"); 
    if (file == NULL) {
        printf("Error: Could not open file for writing member.txt.\n");
        return;
    }
	int i;
    for (i = 0; i < memberCount; i++) {
        fprintf(file, "%s, %s, %s, %d\n", 
                Members[i].memberId,
                Members[i].name,
                Members[i].phone,
				Members[i].status);
    }

    fclose(file);
    printf("Data saved successfully to member.txt\n");
}



void addMember() {
	system("color 3"); 
    refresh();
    printf("                         **** Add A New Member ****\n");
    if (memberCount >= MAX_MEMBERS) {
        printf("Cannot add member, list is full.\n");
        return;
    }

    struct member newMember;
    int valid;

    do {
        valid = 1;
        char inputBuffer1[10];

        printf("Enter the Member ID: ");
        fgets(inputBuffer1, sizeof(inputBuffer1), stdin);

        inputBuffer1[strcspn(inputBuffer1, "\n")] = '\0';

        if (strlen(inputBuffer1) == 0) {
            printf("Error: Member ID cannot be empty. Please try again.\n");
            valid = 0;
        } else if (strlen(inputBuffer1) > 10) {
            printf("Error: Member ID must be <= 10 characters. Please try again.\n");
            valid = 0;
        } else {
            int i;
            for (i = 0; i < memberCount; i++) {
                if (strcmp(Members[i].memberId, inputBuffer1) == 0) {
                    printf("Error: Member ID '%s' already exists.\n", inputBuffer1);
                    valid = 0;
                    break;
                }
            }
        }

        if (valid) {
            strcpy(newMember.memberId, inputBuffer1);
        }

    } while (!valid);

    do {
        valid = 1;
        char inputBuffer1[30];
        printf("Enter the Name: ");
        fgets(inputBuffer1, sizeof(inputBuffer1), stdin);
        inputBuffer1[strcspn(inputBuffer1, "\n")] = '\0';

        if (strlen(inputBuffer1) == 0) {
            printf("Error: Name cannot be empty. Please try again.\n");
            valid = 0;
        } else if (strlen(inputBuffer1) > 20) {
            printf("Error: Name must be <= 20 characters. Please try again.\n");
            valid = 0;
        } else {
            int i;
            for (i = 0; i < memberCount; i++) {
                if (strcmp(Members[i].name, inputBuffer1) == 0) {
                    printf("Error: Name '%s' already exists.\n", inputBuffer1);
                    valid = 0;
                    break;
                }
            }
        }

        if (valid) {
            strcpy(newMember.name, inputBuffer1);
        }

    } while (!valid);

    if (strcmp(newMember.memberId, newMember.name) == 0) {
        printf("Error: Member ID and Name cannot be the same. Please enter different values.\n");
        return;
    }

    do {
        valid = 1;
        char inputBuffer1[20];
        printf("Enter the Phone number: ");
        fgets(inputBuffer1, sizeof(inputBuffer1), stdin);
        inputBuffer1[strcspn(inputBuffer1, "\n")] = '\0';

        if (strlen(inputBuffer1) == 0) {
            printf("Error: Phone number cannot be empty. Please try again.\n");
            valid = 0;
        } else if (strlen(inputBuffer1) > 10) {
            printf("Error: Phone number must be <= 10 characters. Please try again.\n");
            valid = 0;
        } else {
            valid = 1;
        }

        if (valid) {
            strcpy(newMember.phone, inputBuffer1);
        }

    } while (!valid);


    Members[memberCount] = newMember;
    memberCount++;

    saveMemberToFile();

    printf("\n");
    printf("Member Added Successfully.\n");
    printf("\n");

    char choice;
    do {
        valid = 0;
        do {
            char inputBuffer[10];
            printf("Go back (b)? or Exit (0)?: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);

            inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

            if (strlen(inputBuffer) == 0) {
                printf("Error: Choice cannot be empty. Please try again.\n");
                continue;
            }

            if (sscanf(inputBuffer, "%s", &choice) != 1) {
                printf("Error: Invalid input. Please try again.\n");
                continue;
            }

            valid = 1;
        } while (!valid);

        if (choice == 'b') {
            return;
        } else if (choice == '0') {
            printf("==========Thank You==========\n");
            printf("==========See You Soon==========\n\n");
            printf("--------------------------------------");
            exit(0);
        } else {
            printf("Invalid choice. Please enter 'b' or '0'.\n");
        }

    } while (choice != 'b' && choice != '0');

    printf("\n");
    printf("\n");
    printf("\n");
}



void displayMembers() {
   
    if (memberCount == 0) {
        printf("There are no members in the list.\n");
        return;
    }

    printf("                         **** All Member ****\n");
    printf("|============|===========================|======================|============|\n");
    printf("| %-10s | %-25s | %-20s | %-10d |\n", "ID", "Name", "Phone", "Status");
    printf("|============|===========================|======================|============|\n");

	int i;  
    for (i = 0; i < memberCount; i++) {
        printf("| %-10s | %-25s | %-20s | %-10d |\n", 
               Members[i].memberId, 
               Members[i].name, 
               Members[i].phone, 
               Members[i].status);
      
        printf("|------------|---------------------------|----------------------|------------|\n");
    }

    printf("\n");
    char choice;
    int valid;
    do {
       
       
         valid = 0;
        do {
            char inputBuffer2[10];
             printf("Go back (b)? or Exit (0)?: ");
            fgets(inputBuffer2, sizeof(inputBuffer2), stdin);

            inputBuffer2[strcspn(inputBuffer2, "\n")] = '\0'; 

            if (strlen(inputBuffer2) == 0) {
                printf("Error: Choice cannot be empty. Please try again.\n");
                continue;
            }

            if (sscanf(inputBuffer2, "%s", &choice) != 1) {
                printf("Error: Invalid input. Please try again.\n");
                continue;
            }

            valid = 1;
        } while (!valid);
        
        if (choice == 'b') {
            return; 
        } else if (choice == '0') {
            printf("==========Thank You==========\n");
            printf("==========See You Soon==========\n\n");
            printf("--------------------------------------");
            exit(0); 
        } else {
            printf("Invalid choice. Please enter 'b' or '0'.\n");
        }
    } while (choice != 'b' && choice != '0');
    printf("\n");
    printf("\n");
    printf("\n");
}
 

 


