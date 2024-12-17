# Student Structures

This program allows you to manage a list of students. You can add, update, delete, view, sort, and filter students using various commands. The students are stored in an array and saved to a file for persistent storage.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
  - [Add Student](#add-student)
  - [View Students](#view-students)
  - [Update Student](#update-student)
  - [Delete Student](#delete-student)
  - [Sort Students](#sort-students)
  - [Filter Students](#filter-students)

## Features
- **Add Student**: Adds a new student to the system.
- **View Students**: Displays all students in a tabular format.
- **Update Student**: Modifies an existing student's information.
- **Delete Student**: Removes a student from the system.
- **Sort Students**: Sorts students by various criteria (name, surname, age, program, id).
- **Filter Students**: Filters students based on their program.

## Requirements
- **GCC**: Compiler to build the program.
- **Make**: To build and run the program.

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/KenvaidGT/Structures
   ```

2. Build the program:
   ```bash
   make
   ```

3. Run the program with the following commands:
   ```bash
   make run
   ```

Alternatively, if you'd like to run it directly using the `student` command, follow the steps below:

1. Make the `student` command executable:
   ```bash
   chmod +x student
   ```

2. Add the directory to your PATH (so you can use `student` from anywhere):
   ```bash
   echo 'export PATH=$PATH:/workspaces/Structures' >> ~/.bashrc
   source ~/.bashrc
   ```

## Usage

### Add Student
To add a new student, use the following command:
```bash
student add <name> <surname> <birthdate> <program>
```
For example:
```bash
student add Janis Oluh 2000-05-12 PX.22
```

### View Students
To view all students in the system, use:
```bash
student view
```

### Update Student
To update a student's information, use:
```bash
student update <id> <new_name> <new_surname> <new_birthdate> <new_program>
```
For example:
```bash
student update 1 Janis Oluh 1999-04-15 PX.22
```

### Delete Student
To delete a student by their ID, use:
```bash
student delete <id>
```
For example:
```bash
student delete 1
```

### Sort Students
To sort students by a certain criterion (name, surname, age, program, id), use:
```bash
student sort <criterion>
```
For example:
```bash
student sort name
```

### Filter Students
To filter students by their program, use:
```bash
student filter <program>
```
For example:
```bash
student filter PX.20
```
