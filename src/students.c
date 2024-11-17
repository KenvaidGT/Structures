#include "students.h"
#include <stdio.h>
#include <string.h>

const char *file_path = "data/students.bin"; /* Путь к файлу */

/* Функция для добавления студента */
void addStudent(struct students ArrOfStudents[], int *numStudents) {
    struct students newStudent;

    printf("#############################################################\n");
    printf("| Enter name: ");
    scanf("%s", newStudent.name);
    printf("| Enter surname: ");
    scanf("%s", newStudent.surname);
    printf("| Enter age: ");
    scanf("%d", &newStudent.age);
    printf("| Enter program: ");
    scanf("%s", newStudent.programm);

    newStudent.id = *numStudents + 1;

    ArrOfStudents[*numStudents] = newStudent;
    (*numStudents)++;

    printf("#############################################################\n");
    printf("\033[32m!!! Student with ID %d added successfully. !!!\033[0m\n", newStudent.id);
}

/* Функция для поиска студента по ID */
int findStudentById(struct students ArrOfStudents[], int num, int id) {
    for (int i = 0; i < num; i++) {
        if (ArrOfStudents[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Загрузка студентов из файла */
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


/* Сохранение студентов в файл */
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


/* Отображение студентов с фиксированными размерами столбцов */
void displayStudents(const struct students ArrOfStudents[], int num) {
    if (num == 0) {
        printf("#############################################################\n");    
        printf("\033[31m!!! No students to display. !!!\033[0m\n");
        return;
    }
    
    // Максимальная длина для каждого столбца
    const int MAX_NAME_LENGTH = 15;
    const int MAX_SURNAME_LENGTH = 15;
    const int MAX_PROGRAM_LENGTH = 10;

    printf("#############################################################\n");
    printf("| %-3s| %-15s | %-15s | %-3s | %-10s |\n", "ID", "Name", "Surname", "Age", "Program");
    printf("------------------------------------------------------------|\n");
    
    for (int i = 0; i < num; i++) {
        char name[MAX_NAME_LENGTH + 1], surname[MAX_SURNAME_LENGTH + 1], program[MAX_PROGRAM_LENGTH + 1];
        
        snprintf(name, sizeof(name), "%-*s", MAX_NAME_LENGTH, ArrOfStudents[i].name);
        snprintf(surname, sizeof(surname), "%-*s", MAX_SURNAME_LENGTH, ArrOfStudents[i].surname);
        snprintf(program, sizeof(program), "%-*s", MAX_PROGRAM_LENGTH, ArrOfStudents[i].programm);
        
        // Выводим данные с фиксированной шириной столбцов
        printf("| %-3d| %-15s | %-15s | %-3d | %-10s |\n", 
               ArrOfStudents[i].id, 
               name, 
               surname, 
               ArrOfStudents[i].age, 
               program);
    }
    printf("------------------------------------------------------------|\n");
}

void updateStudent(struct students ArrOfStudents[], int num) {
    int id;
    printf("#############################################################\n");
    printf("| Enter the ID of the student to update: ");
    scanf("%d", &id);

    int index = findStudentById(ArrOfStudents, num, id);
    if (index == -1) {
        printf("#############################################################\n");
        printf("\033[31m!!! Student with ID %d not found. !!!\033[0m\n", id);
        printf("#############################################################\n");
        return;
    }

    printf("#############################################################\n");
    printf("| \033[32mUpdating student with ID %d.\033[0m\n", id);
    printf("| Enter new name (current: %s): ", ArrOfStudents[index].name);
    scanf("%s", ArrOfStudents[index].name);

    printf("| Enter new surname (current: %s): ", ArrOfStudents[index].surname);
    scanf("%s", ArrOfStudents[index].surname);

    printf("| Enter new age (current: %d): ", ArrOfStudents[index].age);
    scanf("%d", &ArrOfStudents[index].age);

    printf("| Enter new program (current: %s): ", ArrOfStudents[index].programm);
    scanf("%s", ArrOfStudents[index].programm);

    printf("#############################################################\n");
    printf("\033[32m!!! Student updated successfully. !!!\033[0m\n");
}

int deleteStudent(struct students ArrOfStudents[], int *num) {
    int id;
    printf("#############################################################\n");
    printf("| Enter the ID of the student to delete: ");
    scanf("%d", &id);

    int index = findStudentById(ArrOfStudents, *num, id);
    if (index == -1) {
        printf("#############################################################\n");
        printf("\033[31m!!! Student with ID %d not found. !!!\n\033[0m", id);
        return 0;
    }

    for (int i = index; i < *num - 1; i++) {
        ArrOfStudents[i] = ArrOfStudents[i + 1];
    }
    (*num)--;

    printf("#############################################################\n");
    printf("\033[32m!!! Student with ID %d deleted successfully. !!!\033[0m\n", id);
    return 1;
}

/* Функция сортировки студентов */
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

int compareByAge(const struct students *a, const struct students *b) {
    return a->age - b->age;
}

int compareByProgramm(const struct students *a, const struct students *b) {
    return strcmp(a->programm, b->programm);
}

int compareById(const struct students *a, const struct students *b) {
    return a->id - b->id;
}

void filterAndDisplayStudentsByProgram(const struct students ArrOfStudents[], int num, const char *program) {
    int found = 0;
    printf("#############################################################\n");
    printf("| ID | Name       | Surname    | Age | Program |\n");
    printf("------------------------------------------------------------|\n");
    for (int i = 0; i < num; i++) {
        if (strcmp(ArrOfStudents[i].programm, program) == 0) {
            printf("| %-3d| %-10s | %-10s | %-3d | %-10s |\n", 
                ArrOfStudents[i].id, 
                ArrOfStudents[i].name, 
                ArrOfStudents[i].surname, 
                ArrOfStudents[i].age, 
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
