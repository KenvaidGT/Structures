#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "students.h"

struct students ArrOfStudents[100];
int numStudents = 0;

void printUsage() {
    printf("\033[33mUsage:\n");
    printf("  ./main add <name> <surname> <birthdate(YYYY-MM-DD)> <program>\n");
    printf("  ./main view\n");
    printf("  ./main update <id> <new_name> <new_surname> <new_birthdate> <new_program>\n");
    printf("  ./main delete <id>\n");
    printf("  ./main sort <criterion()>\n");
    printf("    Criteria: name, surname, age, program, id\n");
    printf("  ./main filter <program>\033[0m\n");
}

int main(int argc, char *argv[]) {
    numStudents = loadStudentsFromFile(ArrOfStudents);

    if (argc < 2) {
        printf("\033[31mError: Missing command.\033[0m\n");
        printUsage();
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc != 6) {
            printf("\033[31mError: Incorrect arguments for 'add'.\033[0m\n");
            printUsage();
            return 1;
        }

        struct students newStudent;
        strncpy(newStudent.name, argv[2], sizeof(newStudent.name));
        strncpy(newStudent.surname, argv[3], sizeof(newStudent.surname));
        strncpy(newStudent.birthDate, argv[4], sizeof(newStudent.birthDate));
        strncpy(newStudent.programm, argv[5], sizeof(newStudent.programm));

        newStudent.id = numStudents + 1;
        ArrOfStudents[numStudents] = newStudent;
        numStudents++;

        printf("\033[32mStudent added successfully.\033[0m\n");
        printf("\033[33mSaving changes...\033[0m\n");
        saveStudentsToFile(ArrOfStudents, numStudents);

    } else if (strcmp(argv[1], "view") == 0) {
        displayStudents(ArrOfStudents, numStudents);

    } else if (strcmp(argv[1], "update") == 0) {
        if (argc != 7) {
            printf("\033[31mError: Incorrect arguments for 'update'.\033[0m\n");
            printUsage();
            return 1;
        }

        int id = atoi(argv[2]);
        int index = findStudentById(ArrOfStudents, numStudents, id);
        if (index == -1) {
            printf("\033[31mError: Student with ID \033[36m%d\033[31m not found.\033[0m\n", id);
            return 1;
        }

        strncpy(ArrOfStudents[index].name, argv[3], sizeof(ArrOfStudents[index].name));
        strncpy(ArrOfStudents[index].surname, argv[4], sizeof(ArrOfStudents[index].surname));
        strncpy(ArrOfStudents[index].birthDate, argv[5], sizeof(ArrOfStudents[index].birthDate));
        strncpy(ArrOfStudents[index].programm, argv[6], sizeof(ArrOfStudents[index].programm));

        printf("\033[32mStudent updated successfully.\033[0m\n");
        printf("\033[33mSaving changes...\033[0m\n");
        saveStudentsToFile(ArrOfStudents, numStudents);

    } else if (strcmp(argv[1], "delete") == 0) {
        if (argc != 3) {
            printf("\033[31mError: Incorrect arguments for 'delete'.\033[0m\n");
            printUsage();
            return 1;
        }

        int id = atoi(argv[2]);
        if (deleteStudent(ArrOfStudents, &numStudents, id)) {
            printf("\033[32mStudent with ID \033[36m%d\033[32m deleted successfully.\033[0m\n", id);
            printf("\033[33mSaving changes...\033[0m\n");
            saveStudentsToFile(ArrOfStudents, numStudents);
        } else {
            printf("\033[31mError: Student with ID \033[36m%d\033[31m not found.\033[0m\n", id);
        }

    } else if (strcmp(argv[1], "sort") == 0) {
        if (argc != 3) {
            printf("\033[31mError: Incorrect arguments for 'sort'.\033[0m\n");
            printUsage();
            return 1;
        }

        if (strcmp(argv[2], "name") == 0) {
            sortStudents(ArrOfStudents, numStudents, compareByName);
        } else if (strcmp(argv[2], "surname") == 0) {
            sortStudents(ArrOfStudents, numStudents, compareBySurname);
        } else if (strcmp(argv[2], "age") == 0) {
            sortStudents(ArrOfStudents, numStudents, compareByAge);
        } else if (strcmp(argv[2], "program") == 0) {
            sortStudents(ArrOfStudents, numStudents, compareByProgramm);
        } else if (strcmp(argv[2], "id") == 0) {
            sortStudents(ArrOfStudents, numStudents, compareById);
        } else {
            printf("\033[31mError: Unknown sort criterion '%s'.\033[0m\n", argv[2]);
            printUsage();
            return 1;
        }

        printf("\033[32mStudents sorted successfully.\033[0m\n");
        displayStudents(ArrOfStudents, numStudents);

    } else if (strcmp(argv[1], "filter") == 0) {
        if (argc != 3) {
            printf("\033[31mError: Incorrect arguments for 'filter'.\033[0m\n");
            printUsage();
            return 1;
        }

        filterAndDisplayStudentsByProgram(ArrOfStudents, numStudents, argv[2]);

    } else {
        printf("\033[31mError: Unknown command '\033[36m%s\033[31m'.\033[0m\n", argv[1]);
        printUsage();
        return 1;
    }

    return 0;
}
