#ifndef STUDENTS_H
#define STUDENTS_H

struct students {
    int id;
    char name[50];
    char surname[50];
    int age;
    char programm[50];
};

void addStudent(struct students ArrOfStudents[], int *numStudents);
int findStudentById(struct students ArrOfStudents[], int num, int id);
int loadStudentsFromFile(struct students ArrOfStudents[]);
void saveStudentsToFile(struct students ArrOfStudents[], int num);
void displayStudents(const struct students ArrOfStudents[], int num);
void updateStudent(struct students ArrOfStudents[], int num);
int deleteStudent(struct students ArrOfStudents[], int *num);
void sortStudents(struct students ArrOfStudents[], int num, int (*compare)(const struct students *, const struct students *));
int compareByName(const struct students *a, const struct students *b);
int compareBySurname(const struct students *a, const struct students *b);
int compareByAge(const struct students *a, const struct students *b);
int compareByProgramm(const struct students *a, const struct students *b);
int compareById(const struct students *a, const struct students *b);
void filterAndDisplayStudentsByProgram(const struct students ArrOfStudents[], int num, const char *program);


#endif
