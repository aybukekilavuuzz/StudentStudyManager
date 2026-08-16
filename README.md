# Student Study Manager

Student Study Manager is a console-based application developed in C to help university students manage their courses and grades.

## Features

- Add a new course
- Display all courses
- Calculate course average
- Search for a course
- Calculate GPA
- Save course data
- Load saved course data
- Show pass/fail status

## Technologies

- C
- Standard C Library
- File Handling
- Structures
- Arrays
- Functions

## How It Works

The user interacts with the application through a numbered menu.

For each course, the program stores:

- Course name
- Credit
- Midterm grade
- Final grade

The course average is calculated using:

`Midterm × 40% + Final × 60%`

The program also calculates GPA according to the course credits.

## How to Run

Compile the program with GCC:

```bash
gcc main.c -o StudentStudyManager
