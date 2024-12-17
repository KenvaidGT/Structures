#include "students.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char *file_path = "data/students.bin";

/* Compare function for sorting by birthdate */
int compareByBirthDate(const struct students *a, const struct students *b) {
    return strcmp(a->birthDate, b->birthDate);
}

/* Calculate a student's age from their birthdate */
int calculateAge(const char *birthDate) {
    int year, month, day;
    sscanf(birthDate, "%d-%d-%d", &year, &month, &day);

    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    int age = local->tm_year + 1900 - year;
    if ((local->tm_mon + 1 < month) || 
        (local->tm_mon + 1 == month && local->tm_mday < day)) {
        age--;
    }

    return age;
}

/* Find a student by their ID */
int findStudentById(struct students ArrOfStudents[], int num, int id) {
    for (int i = 0; i < num; i++) {
        if (ArrOfStudents[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Load students from file */
int loadStudentsFromFile(struct students ArrOfStudents[]) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("\033[31mError: Could not open file '%s' for reading.\033[0m\n", file_path);
        return 0;
    }

    int count = 0;
    while (fread(&ArrOfStudents[count], sizeof(struct students), 1, file)) {
        count++;
    }

    fclose(file);
    return count; 
}

/* Save students to file */
void saveStudentsToFile(struct students ArrOfStudents[], int num) {
    FILE *file = fopen(file_path, "wb");
    if (!file) {
        printf("\033[31mError: Could not open file '%s' for writing.\033[0m\n", file_path);
        return;
    }

    fwrite(ArrOfStudents, sizeof(struct students), num, file);
    fclose(file);
}

/* Display all students */
void displayStudents(const struct students ArrOfStudents[], int num) {
    if (num == 0) {
        printf("\033[31mNo students to display.\033[0m\n");
        return;
    }

    printf("--------------------------------------------------------\n");
    printf("| \033[36mID\033[0m | Name        | Surname     | Age | Program       |\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < num; i++) {
        printf("| \033[36m%-2d\033[0m | %-11s | %-11s | %-3d | %-13s |\n",
               ArrOfStudents[i].id, 
               ArrOfStudents[i].name, 
               ArrOfStudents[i].surname, 
               calculateAge(ArrOfStudents[i].birthDate), 
               ArrOfStudents[i].programm);
    }
    printf("--------------------------------------------------------\n");
}

/* Delete a student by ID */
int deleteStudent(struct students ArrOfStudents[], int *numStudents, int id) {
    int index = findStudentById(ArrOfStudents, *numStudents, id);
    if (index == -1) {
        printf("\033[31mError: Student with ID %d not found.\033[0m\n", id);
        return 0;
    }

    for (int i = index; i < *numStudents - 1; i++) {
        ArrOfStudents[i] = ArrOfStudents[i + 1];
    }
    (*numStudents)--;

    /* Update IDs to be sequential */
    for (int i = 0; i < *numStudents; i++) {
        ArrOfStudents[i].id = i + 1;
    }

    return 1;
}

/* Sorting students using a comparator */
void sortStudents(struct students ArrOfStudents[], int num, int (*compare)(const struct students *, const struct students *)) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (compare(&ArrOfStudents[j], &ArrOfStudents[j + 1]) > 0) {
                struct students temp = ArrOfStudents[j];
                ArrOfStudents[j] = ArrOfStudents[j + 1];
                ArrOfStudents[j + 1] = temp;
            }
        }
    }
}

/* Comparator for sorting by name */
int compareByName(const struct students *a, const struct students *b) {
    return strcmp(a->name, b->name);
}

/* Comparator for sorting by surname */
int compareBySurname(const struct students *a, const struct students *b) {
    return strcmp(a->surname, b->surname);
}

/* Comparator for sorting by age */
int compareByAge(const struct students *a, const struct students *b) {
    return compareByBirthDate(a, b);
}

/* Comparator for sorting by program */
int compareByProgramm(const struct students *a, const struct students *b) {
    return strcmp(a->programm, b->programm);
}

/* Comparator for sorting by ID */
int compareById(const struct students *a, const struct students *b) {
    return a->id - b->id;
}

/* Filter and display students by program */
void filterAndDisplayStudentsByProgram(const struct students ArrOfStudents[], int num, const char *program) {
    int found = 0;

    printf("--------------------------------------------------------\n");
    printf("| \033[36mID\033[0m | Name        | Surname     | Age | Program       |\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < num; i++) {
        if (strcmp(ArrOfStudents[i].programm, program) == 0) {
            printf("| \033[36m%-2d\033[0m | %-11s | %-11s | %-3d | %-13s |\n",
                   ArrOfStudents[i].id, 
                   ArrOfStudents[i].name, 
                   ArrOfStudents[i].surname, 
                   calculateAge(ArrOfStudents[i].birthDate), 
                   ArrOfStudents[i].programm);
            found = 1;
        }
    }

    printf("--------------------------------------------------------\n");
    if (!found) {
        printf("\033[31mNo students found in program: %s\033[0m\n", program);
    }
}
