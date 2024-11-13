#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

/* Structure */
struct students {
    int id;
    char name[100];
    char surname[100];
    int age;
    char programm[100];
};

/* Find student by ID */
int findStudentById(struct students ArrOfStudents[], int num, int id) {
    for (int i = 0; i < num; i++) {
        if (ArrOfStudents[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* String copy function */
void stringCopy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

/* Function similar to strcmp */
int stringCompare(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return (unsigned char)*str1 - (unsigned char)*str2;
        }
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

/* Comparison functions for sorting */
int compareByName(const struct students *a, const struct students *b) {
    return stringCompare(a->name, b->name);
}
int compareBySurname(const struct students *a, const struct students *b) {
    return stringCompare(a->surname, b->surname);
}
int compareByAge(const struct students *a, const struct students *b) {
    return a->age - b->age;
}
int compareByProgramm(const struct students *a, const struct students *b) {
    return stringCompare(a->programm, b->programm);
}
int compareById(const struct students *a, const struct students *b) {
    return a->id - b->id;
}

/* Bubble sort function */
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

/* Load students from file */
int loadStudentsFromFile(struct students ArrOfStudents[]) {
    FILE *file = fopen("Students.txt", "r");
    if (!file) {
        printf("!!! Error opening file 'Students.txt' for reading. !!!\n");
        return 0;
    }
    int i = 0;
    while (fscanf(file, "%d %s %s %d %s", &ArrOfStudents[i].id, ArrOfStudents[i].name, ArrOfStudents[i].surname, &ArrOfStudents[i].age, ArrOfStudents[i].programm) == 5) {
        i++;
    }
    fclose(file);
    return i;
}

/* Save students to file */
void saveStudentsToFile(struct students ArrOfStudents[], int num) {
    FILE *file = fopen("Students.txt", "w");
    if (!file) {
        printf("!!! Error opening file 'Students.txt' for writing. !!!\n");
        return;
    }
    for (int i = 0; i < num; i++) {
        fprintf(file, "%d %s %s %d %s\n", ArrOfStudents[i].id, ArrOfStudents[i].name, ArrOfStudents[i].surname, ArrOfStudents[i].age, ArrOfStudents[i].programm);
    }
    fclose(file);
}

int main() {
    struct students ArrOfStudents[MAX_STUDENTS];
    int num = loadStudentsFromFile(ArrOfStudents);
    int nextId = num > 0 ? ArrOfStudents[num - 1].id + 1 : 1;
    char tmpChar[100];
    int tmpInt;
    int found = 0;
    int exitProgram = 0;

    while (!exitProgram) {
        printf("##############################\n| Select an option:\n|   Add a student - 0\n|   Remove a student - 1\n|   Edit student details - 2\n|   View students - 3\n|   Exit - 4\n|\n| Input: ");
        int variant;
        scanf("%d", &variant);

        if (variant == 0) { /* Add a student */
            if (num < MAX_STUDENTS) {
                ArrOfStudents[num].id = nextId++;
                printf("##############################\n| Enter name: ");
                scanf("%s", ArrOfStudents[num].name);
                printf("| Enter surname: ");
                scanf("%s", ArrOfStudents[num].surname);
                printf("| Enter age: ");
                scanf("%d", &ArrOfStudents[num].age);
                printf("| Enter program [Example: PX.69]: ");
                scanf("%s", ArrOfStudents[num].programm);
                printf("##############################\n !!! Student added with ID %d! !!!\n", ArrOfStudents[num].id);
                num++;
                saveStudentsToFile(ArrOfStudents, num);
            } else {
                printf("!!! No more space to add students. !!!\n");
            }
        } else if (variant == 1) { /* Remove a student */
            if (num > 0) {
                int deleteId;
                printf("##############################\n| Enter the ID of the student to remove: ");
                scanf("%d", &deleteId);
                int deleteIndex = findStudentById(ArrOfStudents, num, deleteId);
                if (deleteIndex != -1) {
                    for (int i = deleteIndex; i < num - 1; i++) {
                        ArrOfStudents[i] = ArrOfStudents[i + 1];
                    }
                    num--;
                    printf("##############################\n !!! Student with ID %d removed! !!!\n", deleteId);
                    saveStudentsToFile(ArrOfStudents, num);
                } else {
                    printf("##############################\n| !!! Student with ID %d not found! !!!\n", deleteId);
                }
            } else {
                printf("##############################\n !!! No students to remove! !!!\n");
            }
        } else if (variant == 2) { /* Edit a student */
            if (num > 0) {
                int editId;
                printf("##############################\n| Enter the ID of the student to edit: ");
                scanf("%d", &editId);
                int editIndex = findStudentById(ArrOfStudents, num, editId);
                if (editIndex != -1) {
                    int dataVariant;
                    printf("|\n| What to edit:\n|   Name - 0\n|   Surname - 1\n|   Age - 2\n|   Program - 3\n|\n| Input: ");
                    scanf("%d", &dataVariant);
                    if (dataVariant == 0) {
                        printf("##############################\n| Enter new name: ");
                        scanf("%s", tmpChar);
                        stringCopy(ArrOfStudents[editIndex].name, tmpChar);
                    } else if (dataVariant == 1) {
                        printf("##############################\n| Enter new surname: ");
                        scanf("%s", tmpChar);
                        stringCopy(ArrOfStudents[editIndex].surname, tmpChar);
                    } else if (dataVariant == 2) {
                        printf("##############################\n| Enter new age: ");
                        scanf("%d", &tmpInt);
                        ArrOfStudents[editIndex].age = tmpInt;
                    } else if (dataVariant == 3) {
                        printf("##############################\n| Enter new program: ");
                        scanf("%s", tmpChar);
                        stringCopy(ArrOfStudents[editIndex].programm, tmpChar);
                    }
                    printf("##############################\n| !!! Student with ID %d successfully edited! !!!\n", editId);
                    saveStudentsToFile(ArrOfStudents, num);
                } else {
                    printf("##############################\n| !!! Student with ID %d not found! !!!\n", editId);
                }
            } else {
                printf("##############################\n !!! No students to edit! !!!\n");
            }
        } else if (variant == 3) { /* View students */
            if (num > 0) {
                int SortMethod;
                printf("##############################\n| Sorting method:\n|   By name - 0\n|   By surname - 1\n|   By age - 2\n|   By program - 3\n|   By ID - 4\n|   For one program - 5\n| Input: ");
                scanf("%d", &SortMethod);

                if (SortMethod == 0) {
                    sortStudents(ArrOfStudents, num, compareByName);
                } else if (SortMethod == 1) {
                    sortStudents(ArrOfStudents, num, compareBySurname);
                } else if (SortMethod == 2) {
                    sortStudents(ArrOfStudents, num, compareByAge);
                } else if (SortMethod == 3) {
                    sortStudents(ArrOfStudents, num, compareByProgramm);
                } else if (SortMethod == 4) {
                    sortStudents(ArrOfStudents, num, compareById);
                } else if (SortMethod == 5) {
                    printf("##############################\n| Enter program name to filter [Example: PX.69]: ");
                    scanf("%s", tmpChar);
                    printf("##############################\n");
                    for (int i = 0; i < num; i++) {
                        if (stringCompare(ArrOfStudents[i].programm, tmpChar) == 0) {
                            printf("| ID: %d    %s %s %d y.o. %s\n", ArrOfStudents[i].id, ArrOfStudents[i].name, ArrOfStudents[i].surname, ArrOfStudents[i].age, ArrOfStudents[i].programm);
                        }
                    }
                    continue;
                }

                printf("##############################\n");
                for (int i = 0; i < num; i++) {
                    printf("| ID: %d    %s %s %d y.o. %s\n", ArrOfStudents[i].id, ArrOfStudents[i].name, ArrOfStudents[i].surname, ArrOfStudents[i].age, ArrOfStudents[i].programm);
                }
            } else {
                printf("##############################\n !!! No students to view! !!!\n");
            }
        } else if (variant == 4) { /* Exit */
            printf("!!! Exiting program. !!!\n");
            exitProgram = 1;
        } else {
            printf("!!! Invalid option. !!!\n");
        }
    }

    return 0;
}
