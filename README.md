Student Grading and Resulting System
A C program for managing student grades and results with data persistence.
Description
This program allows users to add students, input grades for five subjects, calculate averages and grades (A-F), determine pass/fail status, and save/load data to/from grades.txt. A student passes if their average is ≥60 and no subject score is <40.
How to Use

Compile the program using a C compiler (e.g., gcc StudentGrading.c -o StudentGrading).
Run the executable (e.g., ./StudentGrading on Linux or StudentGrading.exe on Windows).
Choose options from the menu to:
Add a student (ID and name).
Add grades for a student (marks for five subjects).
View results for a specific student or all students.
Exit (saves data automatically).


Data is saved to grades.txt and loaded on startup.

Example
Student Grading and Resulting System
1. Add Student
2. Add Grades
3. View Results
4. Exit
Enter your choice (1-4): 2
Enter student ID: 101
Enter marks for John Doe (ID: 101) for 5 subjects:
Subject 1 (0-100): 85
Subject 2 (0-100): 90
Subject 3 (0-100): 78
Subject 4 (0-100): 92
Subject 5 (0-100): 88
Grades added and result calculated successfully!

License
This project is licensed under the MIT License. See the LICENSE file for details.
