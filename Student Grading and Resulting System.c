#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_SUBJECTS 5

// Structure for student details and grades
struct Student {
    int id;
    char name[MAX_NAME];
    float marks[MAX_SUBJECTS];
    float average;
    char grade;
    int pass; // 1 for pass, 0 for fail
};

// Global array to store students
struct Student students[MAX_STUDENTS];
int student_count = 0;

// Function prototypes
void addStudent();
void addGrades();
void calculateResult(int index);
void viewResults();
void saveData();
void loadData();
int findStudent(int id);

int main() {
    loadData(); // Load existing data from file
    int choice;
    char continue_program;

    do {
        // Display menu
        printf("\nStudent Grading and Resulting System\n");
        printf("1. Add Student\n");
        printf("2. Add Grades\n");
        printf("3. View Results\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        // Process user choice
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                addGrades();
                break;
            case 3:
                viewResults();
                break;
            case 4:
                saveData();
                printf("Exiting program. Data saved.\n");
                return 0;
            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &continue_program);
    } while (continue_program == 'y' || continue_program == 'Y');

    saveData(); // Save data before exiting
    return 0;
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Error: Maximum student limit reached!\n");
        return;
    }

    struct Student new_student;
    printf("Enter student ID: ");
    scanf("%d", &new_student.id);

    // Check for duplicate ID
    if (findStudent(new_student.id) != -1) {
        printf("Error: Student ID already exists!\n");
        return;
    }

    printf("Enter student name: ");
    scanf(" %[^\n]s", new_student.name); // Read string with spaces

    // Initialize marks and other fields
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        new_student.marks[i] = -1; // Indicates no marks entered
    }
    new_student.average = 0;
    new_student.grade = ' ';
    new_student.pass = 0;

    students[student_count++] = new_student;
    printf("Student added successfully!\n");
}

void addGrades() {
    int id;
    printf("Enter student ID: ");
    scanf("%d", &id);

    int index = findStudent(id);
    if (index == -1) {
        printf("Error: Student ID not found!\n");
        return;
    }

    printf("Enter marks for %s (ID: %d) for %d subjects:\n", students[index].name, id, MAX_SUBJECTS);
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        do {
            printf("Subject %d (0-100): ", i + 1);
            scanf("%f", &students[index].marks[i]);
            if (students[index].marks[i] < 0 || students[index].marks[i] > 100) {
                printf("Error: Marks must be between 0 and 100!\n");
            }
        } while (students[index].marks[i] < 0 || students[index].marks[i] > 100);
    }

    calculateResult(index);
    printf("Grades added and result calculated successfully!\n");
}

void calculateResult(int index) {
    float sum = 0;
    int valid_marks = 0;
    int fail_subject = 0;

    // Calculate average
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        if (students[index].marks[i] >= 0) { // Check if marks are entered
            sum += students[index].marks[i];
            valid_marks++;
            if (students[index].marks[i] < 40) {
                fail_subject = 1; // Fail if any subject < 40
            }
        }
    }

    if (valid_marks > 0) {
        students[index].average = sum / valid_marks;
        // Assign grade
        if (students[index].average >= 90) {
            students[index].grade = 'A';
        } else if (students[index].average >= 80) {
            students[index].grade = 'B';
        } else if (students[index].average >= 70) {
            students[index].grade = 'C';
        } else if (students[index].average >= 60) {
            students[index].grade = 'D';
        } else {
            students[index].grade = 'F';
        }
        // Determine pass/fail
        students[index].pass = (students[index].average >= 60 && !fail_subject) ? 1 : 0;
    }
}

void viewResults() {
    int id;
    printf("Enter student ID (or 0 for all students): ");
    scanf("%d", &id);

    if (id == 0) {
        for (int i = 0; i < student_count; i++) {
            printf("\nStudent: %s, ID: %d\n", students[i].name, students[i].id);
            printf("Marks: ");
            for (int j = 0; j < MAX_SUBJECTS; j++) {
                if (students[i].marks[j] >= 0) {
                    printf("Subject %d: %.2f, ", j + 1, students[i].marks[j]);
                }
            }
            if (students[i].average > 0) {
                printf("\nAverage: %.2f, Grade: %c, Status: %s\n",
                       students[i].average, students[i].grade,
                       students[i].pass ? "Pass" : "Fail");
            } else {
                printf("\nNo grades entered.\n");
            }
        }
    } else {
        int index = findStudent(id);
        if (index == -1) {
            printf("Error: Student ID not found!\n");
            return;
        }

        printf("\nStudent: %s, ID: %d\n", students[index].name, students[index].id);
        printf("Marks: ");
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            if (students[index].marks[j] >= 0) {
                printf("Subject %d: %.2f, ", j + 1, students[index].marks[j]);
            }
        }
        if (students[index].average > 0) {
            printf("\nAverage: %.2f, Grade: %c, Status: %s\n",
                   students[index].average, students[index].grade,
                   students[index].pass ? "Pass" : "Fail");
        } else {
            printf("\nNo grades entered.\n");
        }
    }
}

int findStudent(int id) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

void saveData() {
    FILE *file = fopen("grades.txt", "w");
    if (file) {
        for (int i = 0; i < student_count; i++) {
            fprintf(file, "%d,%s", students[i].id, students[i].name);
            for (int j = 0; j < MAX_SUBJECTS; j++) {
                fprintf(file, ",%.2f", students[i].marks[j]);
            }
            fprintf(file, ",%.2f,%c,%d\n",
                    students[i].average, students[i].grade, students[i].pass);
        }
        fclose(file);
    }
}

void loadData() {
    FILE *file = fopen("grades.txt", "r");
    if (file) {
        while (student_count < MAX_STUDENTS &&
               fscanf(file, "%d,%[^,]", &students[student_count].id,
                      students[student_count].name) == 2) {
            for (int j = 0; j < MAX_SUBJECTS; j++) {
                fscanf(file, ",%f", &students[student_count].marks[j]);
            }
            fscanf(file, ",%f,%c,%d\n",
                   &students[student_count].average,
                   &students[student_count].grade,
                   &students[student_count].pass);
            student_count++;
        }
        fclose(file);
    }
}