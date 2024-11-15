#include <stdio.h>
#include "students.h"

struct students ArrOfStudents[100];
int numStudents = 0;

void displayMenu() {
    printf("#############################################################\n");
    printf("| Select an option:\n");
    printf("|   Add - 0\n");
    printf("|   View - 1\n");
    printf("|   Update - 2\n");
    printf("|   Delete - 3\n");
    printf("|   Save & Exit - 4\n");
    printf("| Input: ");
}

void displaySortMenu() {
    printf("#############################################################\n");
    printf("| Select sorting criterion:\n");
    printf("|   1 - By Name\n");
    printf("|   2 - By Surname\n");
    printf("|   3 - By Age\n");
    printf("|   4 - By Program\n");
    printf("|   5 - By ID\n");
    printf("| Input: ");
}

void displayFilterMenu() {
    printf("#############################################################\n");
    printf("| Do you want to filter by program?\n");
    printf("|   1 - Yes\n");
    printf("|   2 - No\n");
    printf("| Input: ");
}

int main() {
    numStudents = loadStudentsFromFile(ArrOfStudents);

    while (1) {
        displayMenu();
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                addStudent(ArrOfStudents, &numStudents);
                break;
            case 1:
                displaySortMenu();
                int sortChoice;
                scanf("%d", &sortChoice);

                switch (sortChoice) {
                    case 1:
                        sortStudents(ArrOfStudents, numStudents, compareByName);
                        break;
                    case 2:
                        sortStudents(ArrOfStudents, numStudents, compareBySurname);
                        break;
                    case 3:
                        sortStudents(ArrOfStudents, numStudents, compareByAge);
                        break;
                    case 4:
                        sortStudents(ArrOfStudents, numStudents, compareByProgramm);
                        break;
                    case 5:
                        sortStudents(ArrOfStudents, numStudents, compareById);
                        break;
                    default:
                        printf("Invalid choice. Showing unsorted list.\n");
                        break;
                }

                displayFilterMenu();
                int filterChoice;
                scanf("%d", &filterChoice);

                if (filterChoice == 1) {
                    char program[50];
                    printf("| Enter the program to filter by (e.g., PX.24): ");
                    scanf("%s", program);

                    filterAndDisplayStudentsByProgram(ArrOfStudents, numStudents, program);
                } else if (filterChoice == 2) {
                    displayStudents(ArrOfStudents, numStudents);
                } else {
                    printf("Invalid choice. Showing all students.\n");
                    displayStudents(ArrOfStudents, numStudents);
                }
                break;
            case 2:
                updateStudent(ArrOfStudents, numStudents);
                break;
            case 3:
                deleteStudent(ArrOfStudents, &numStudents);
                break;
            case 4:
                saveStudentsToFile(ArrOfStudents, numStudents);
                printf("Data saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
