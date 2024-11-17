#include "students.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char *file_path = "data/students.bin";

int compareByBirthDate(const struct students *a, const struct students *b) {
    return strcmp(a->birthDate, b->birthDate);
}

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

void addStudent(struct students ArrOfStudents[], int *numStudents) {
    struct students newStudent;

    printf("#############################################################\n");
    printf("| Enter name: ");
    scanf("%s", newStudent.name);
    printf("| Enter surname: ");
    scanf("%s", newStudent.surname);
    printf("| Enter birth date (YYYY-MM-DD): ");
    scanf("%s", newStudent.birthDate);
    printf("| Enter program: ");
    scanf("%s", newStudent.programm);

    newStudent.id = *numStudents + 1;

    ArrOfStudents[*numStudents] = newStudent;
    (*numStudents)++;

    printf("#############################################################\n");
    printf("\033[32m!!! Student with ID \033[36m%d\033[32m added successfully. !!!\033[0m\n", newStudent.id);
}


int findStudentById(struct students ArrOfStudents[], int num, int id) {
    for (int i = 0; i < num; i++) {
        if (ArrOfStudents[i].id == id) {
            return i;
        }
    }
    return -1;
}

int loadStudentsFromFile(struct students ArrOfStudents[]) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("!!! Error opening file 'students.bin' for reading. !!!\n");
        return 0;
    }

    int i = 0;
    while (fread(&ArrOfStudents[i], sizeof(struct students), 1, file)) {
        i++;
    }

    fclose(file);
    return i; 
}

void saveStudentsToFile(struct students ArrOfStudents[], int num) {
    FILE *file = fopen(file_path, "wb");
    if (!file) {
        printf("!!! Error opening file 'students.bin' for writing. !!!\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        fwrite(&ArrOfStudents[i], sizeof(struct students), 1, file);
    }

    fclose(file);
    printf("Students saved successfully to 'students.bin'.\n");
}

void displayStudents(const struct students ArrOfStudents[], int num) {
    if (num == 0) {
        printf("#############################################################\n");    
        printf("\033[31m!!! No students to display. !!!\033[0m\n");
        return;
    }

    const int MAX_NAME_LENGTH = 15;
    const int MAX_SURNAME_LENGTH = 15;
    const int MAX_PROGRAM_LENGTH = 10;

    printf("#############################################################\n");
    printf("| \033[36m%-3s\033[0m| %-15s | %-15s | %-3s | %-10s |\n", "ID", "Name", "Surname", "Age", "Program");
    printf("------------------------------------------------------------|\n");

    for (int i = 0; i < num; i++) {
        char name[MAX_NAME_LENGTH + 1], surname[MAX_SURNAME_LENGTH + 1], program[MAX_PROGRAM_LENGTH + 1];

        snprintf(name, sizeof(name), "%-*s", MAX_NAME_LENGTH, ArrOfStudents[i].name);
        snprintf(surname, sizeof(surname), "%-*s", MAX_SURNAME_LENGTH, ArrOfStudents[i].surname);
        snprintf(program, sizeof(program), "%-*s", MAX_PROGRAM_LENGTH, ArrOfStudents[i].programm);

        printf("| \033[36m%-3d\033[0m| %-15s | %-15s | %-3d | %-10s |\n", 
               ArrOfStudents[i].id, 
               name, 
               surname, 
               calculateAge(ArrOfStudents[i].birthDate), 
               program);
    }
    printf("------------------------------------------------------------|\n");
}

void getInput(char *prompt, char *currentValue, char *buffer, int bufferSize) {
    printf("%s (current: %s): ", prompt, currentValue);
    fgets(buffer, bufferSize, stdin);

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (strlen(buffer) == 0) {
        strcpy(buffer, currentValue);
    }
}

void updateStudent(struct students ArrOfStudents[], int num) {
    int id;
    printf("#############################################################\n");
    printf("| Enter the ID of the student to update:\033[36m ");
    scanf("%d", &id);
    printf("\033[0m");
    getchar();

    int index = findStudentById(ArrOfStudents, num, id);
    if (index == -1) {
        printf("#############################################################\n");
        printf("\033[31m!!! Student with ID \033[36m %d \033[31m not found. !!!\033[0m\n", id);
        return;
    }

    char inputBuffer[100];

    printf("#############################################################\n");
    printf("| Updating student with ID \033[36m%d\033[0m (\033[4mU can press enter for keep info, without rewrite name, surnam etc...\033[0m).\n", id);

    getInput("| Enter new name", ArrOfStudents[index].name, inputBuffer, sizeof(inputBuffer));
    strcpy(ArrOfStudents[index].name, inputBuffer);

    getInput("| Enter new surname", ArrOfStudents[index].surname, inputBuffer, sizeof(inputBuffer));
    strcpy(ArrOfStudents[index].surname, inputBuffer);

    getInput("| Enter new birth date (YYYY-MM-DD)", ArrOfStudents[index].birthDate, inputBuffer, sizeof(inputBuffer));
    strcpy(ArrOfStudents[index].birthDate, inputBuffer);

    getInput("| Enter new program", ArrOfStudents[index].programm, inputBuffer, sizeof(inputBuffer));
    strcpy(ArrOfStudents[index].programm, inputBuffer);

    printf("#############################################################\n");
    printf("\033[32m!!! Student updated successfully. !!!\033[0m\n");
}

int deleteStudent(struct students ArrOfStudents[], int *num) {
    int id;
    printf("#############################################################\n");
    printf("| Enter the ID of the student to delete: \033[36m ");
    scanf("%d", &id);
    printf("\033[0m");

    int index = findStudentById(ArrOfStudents, *num, id);
    if (index == -1) {
        printf("#############################################################\n");
        printf("\033[31m!!! Student with ID \033[36m %d \033[31m not found. !!!\n\033[0m", id);
        return 0;
    }

    for (int i = index; i < *num - 1; i++) {
        ArrOfStudents[i] = ArrOfStudents[i + 1];
    }
    
    for (int i = index; i < *num - 1; i++) {
        ArrOfStudents[i].id = i + 1;
    }

    (*num)--;

    printf("#############################################################\n");
    printf("\033[32m!!! Student with ID \033[36m%d\033[32m deleted successfully. !!!\033[0m\n", id);
    return 1;
}
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

int compareByName(const struct students *a, const struct students *b) {
    return strcmp(a->name, b->name);
}

int compareBySurname(const struct students *a, const struct students *b) {
    return strcmp(a->surname, b->surname);
}

#include <time.h>

// Сравнивает даты рождения (yyyy-mm-dd).
int compareByAge(const struct students *a, const struct students *b) {
    struct tm dateA = {0}, dateB = {0};
    sscanf(a->birthDate, "%d-%d-%d", &dateA.tm_year, &dateA.tm_mon, &dateA.tm_mday);
    sscanf(b->birthDate, "%d-%d-%d", &dateB.tm_year, &dateB.tm_mon, &dateB.tm_mday);

    // tm_year считается от 1900, tm_mon начинается с 0
    dateA.tm_year -= 1900;
    dateB.tm_year -= 1900;
    dateA.tm_mon -= 1;
    dateB.tm_mon -= 1;

    // Сравниваем даты рождения (меньшая означает старшего человека).
    return mktime(&dateA) - mktime(&dateB);
}


int compareByProgramm(const struct students *a, const struct students *b) {
    return strcmp(a->programm, b->programm);
}

int compareById(const struct students *a, const struct students *b) {
    return a->id - b->id;
}

void filterAndDisplayStudentsByProgram(const struct students ArrOfStudents[], int num, const char *program) {
    int found = 0;
    time_t now = time(NULL);
    struct tm *currentDate = localtime(&now);

    printf("#############################################################\n");
    printf("| ID | Name       | Surname    | Age | Program |\n");
    printf("------------------------------------------------------------|\n");

    for (int i = 0; i < num; i++) {
        if (strcmp(ArrOfStudents[i].programm, program) == 0) {
            struct tm birthDate = {0};
            int age = 0;

            // Разбираем дату рождения
            sscanf(ArrOfStudents[i].birthDate, "%d-%d-%d", &birthDate.tm_year, &birthDate.tm_mon, &birthDate.tm_mday);
            birthDate.tm_year -= 1900;
            birthDate.tm_mon -= 1;

            // Расчёт возраста
            age = currentDate->tm_year - birthDate.tm_year;
            if (currentDate->tm_mon < birthDate.tm_mon || 
                (currentDate->tm_mon == birthDate.tm_mon && currentDate->tm_mday < birthDate.tm_mday)) {
                age--;
            }

            printf("| %-3d| %-10s | %-10s | %-3d | %-10s |\n", 
                ArrOfStudents[i].id, 
                ArrOfStudents[i].name, 
                ArrOfStudents[i].surname, 
                age, 
                ArrOfStudents[i].programm);
            found = 1;
        }
    }
    printf("------------------------------------------------------------|\n");

    if (!found) {
        printf("#############################################################\n");
        printf("\033[31m!!! No students found in the program: %s !!!\033[0m\n", program);
    }
}

