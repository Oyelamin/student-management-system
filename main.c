#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_BUFFER_SIZE 100
#define FILE_NAME "students.txt"
#define PASS_MARK 41

typedef struct {
    char    name[MAX_NAME_LENGTH];
    int     rollNumber;
    int     mark;
    char    grade[MAX_NAME_LENGTH];
} Student;

void welcomePrompt();
void promptUserName(char *name);
void greetUser(const char *name);
void printMainOptions();
void handleMainOption(int choice);
char *determineStudentGrade(int mark);
void addStudent();
int studentExists(int studentRollNumber);
void displayStudents();
void searchStudentByRollNumber();
void calculateAverageMarks();
void sortStudentsByMarks();
void deleteStudentInformation();
void modifyStudentInformation();
void saveStudentToFile(const Student *student);
Student* getStudentsFromFile(int *count);
void saveAllStudentsToFile(const Student *students, int count);
void deleteAllRecords();

int main(void) {
    char username[MAX_NAME_LENGTH];
    int mainOptionChoice;

    welcomePrompt();
    promptUserName(username);
    greetUser(username);

    while (1) {
        printMainOptions();
        printf("Enter your choice: ");
        scanf("%d", &mainOptionChoice);
        getchar(); // Consume newline character left in the buffer
        handleMainOption(mainOptionChoice);
    }

    return 0;
}

void welcomePrompt() {
    printf("-- Welcome to the Student Record System --\n");
}

void promptUserName(char *name) {
    printf("Please enter your name: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // Remove the trailing newline character
}

void greetUser(const char *name) {
    printf("Hello %s, welcome to the student record system.\n\n", name);
}

void printMainOptions() {
    printf("\nMain Options:\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student by Roll Number\n");
    printf("4. Calculate Average Marks\n");
    printf("5. Sort Students by Marks\n");
    printf("6. Delete Student Information\n");
    printf("7. Modify Student Information\n");
    printf("8. EXIT\n");
    printf("9. Exit & Delete All Records\n");
}

void handleMainOption(int choice) {
    switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudentByRollNumber();
            break;
        case 4:
            calculateAverageMarks();
            break;
        case 5:
            sortStudentsByMarks();
            break;
        case 6:
            deleteStudentInformation();
            break;
        case 7:
            modifyStudentInformation();
            break;
        case 8:
            printf("Goodbye!\n");
            exit(0);
        case 9:
            deleteAllRecords();
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
}

void addStudent() {
    Student student;
    char inputBuffer[MAX_BUFFER_SIZE];

    printf("Enter student name: ");
    fgets(student.name, MAX_NAME_LENGTH, stdin);
    student.name[strcspn(student.name, "\n")] = 0; // Remove trailing newline

    printf("Enter student roll number: ");
    fgets(inputBuffer, MAX_BUFFER_SIZE, stdin);
    sscanf(inputBuffer, "%d", &student.rollNumber);

    if (studentExists(student.rollNumber)) {
        printf("Student with roll number [%d] already exist in the record.\n", student.rollNumber);
        return;
    }

    printf("Enter student mark: ");
    fgets(inputBuffer, MAX_BUFFER_SIZE, stdin);
    sscanf(inputBuffer, "%d", &student.mark);

    strcpy(student.grade, determineStudentGrade(student.mark));

    saveStudentToFile(&student);

    int subChoice;
    printf("\n1. Add New Entry\n");
    printf("2. Save & Return Back\n");
    printf("3. EXIT\n");
    printf("Enter your choice: ");
    scanf("%d", &subChoice);
    getchar(); // Consume newline character left in the buffer

    switch (subChoice) {
        case 1:
            addStudent();
            break;
        case 2:
            break;
        case 3:
            printf("Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Returning to main options.\n");
    }
}

void displayStudents() {
    int count;
    Student *students = getStudentsFromFile(&count);

    if (count == 0) {
        printf("No student records found.\n");
        free(students);
        return;
    }

    printf("** Student Records **\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Roll Number: %d, Mark: %d, Grade: %s\n", students[i].name, students[i].rollNumber, students[i].mark, students[i].grade);
    }
    free(students);
}

int studentExists(int studentRollNumber) {
    int count;
    Student *students = getStudentsFromFile(&count);

    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == studentRollNumber) {
            free(students);
            return 1;
        }
    }

    free(students);
    return 0;
}

void searchStudentByRollNumber() {
    int rollNumber;
    int count;
    Student *students = getStudentsFromFile(&count);

    printf("Enter student roll number: ");
    scanf("%d", &rollNumber);
    getchar(); // Consume newline character left in the buffer

    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("** Student found **\nName: %s, Roll Number: %d, Mark: %d, Grade: %s\n", students[i].name, students[i].rollNumber, students[i].mark, students[i].grade);
            free(students);
            return;
        }
    }

    printf("Student with roll number %d not found.\n", rollNumber);
    free(students);
}

void calculateAverageMarks() {
    int count;
    Student *students = getStudentsFromFile(&count);

    if (count == 0) {
        printf("No student records found.\n");
        free(students);
        return;
    }

    int totalMarks = 0;
    for (int i = 0; i < count; i++) {
        totalMarks += students[i].mark;
    }

    float averageMarks = (float)totalMarks / count;
    printf("The average mark is: %f\n", averageMarks);
    free(students);
}

void sortStudentsByMarks() {
    int count;
    Student *students = getStudentsFromFile(&count);

    if (count == 0) {
        printf("No student records found.\n");
        free(students);
        return;
    }

    int sortChoice;
    printf("1. Sort in Ascending Order\n");
    printf("2. Sort in Descending Order\n");
    printf("Enter your choice: ");
    scanf("%d", &sortChoice);
    getchar(); // Consume newline character left in the buffer

    // Sort student records based on marks
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((sortChoice == 1 && students[j].mark > students[j + 1].mark) ||
                (sortChoice == 2 && students[j].mark < students[j + 1].mark)) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("** Sorted Student Records **\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Roll Number: %d, Mark: %d, Grade: %s\n", students[i].name, students[i].rollNumber, students[i].mark, students[i].grade);
    }
    free(students);
}

void deleteStudentInformation() {
    int rollNumber;
    printf("Enter student roll number to delete: ");
    scanf("%d", &rollNumber);
    getchar(); // Consume newline character left in the buffer

    int count;
    Student *students = getStudentsFromFile(&count);

    int studentFound = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            studentFound = 1;
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            saveAllStudentsToFile(students, count);
            printf("Student with roll number %d deleted successfully.\n", rollNumber);
            break;
        }
    }

    if (!studentFound) {
        printf("Student with roll number %d not found.\n", rollNumber);
    }

    free(students);
}

void modifyStudentInformation() {
    int rollNumber;
    int count;
    Student *students = getStudentsFromFile(&count);

    printf("Enter student roll number to modify: ");
    scanf("%d", &rollNumber);
    getchar(); // Consume newline character left in the buffer

    int studentFound = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            studentFound = 1;
            int modifyChoice;
            printf("Modify Options:\n");
            printf("1. Update Student Name\n");
            printf("2. Update Student Roll Number\n");
            printf("3. Update Student Mark\n");
            printf("4. Update All\n");
            printf("Enter your choice: ");
            scanf("%d", &modifyChoice);
            getchar(); // Consume newline character left in the buffer

            char inputBuffer[MAX_BUFFER_SIZE];
            switch (modifyChoice) {
                case 1:
                    printf("Enter new student name: ");
                    fgets(students[i].name, MAX_NAME_LENGTH, stdin);
                    students[i].name[strcspn(students[i].name, "\n")] = 0; // Remove trailing newline
                    break;
                case 2:
                    printf("Enter new student roll number: ");
                    fgets(inputBuffer, MAX_BUFFER_SIZE, stdin);
                    sscanf(inputBuffer, "%d", &students[i].rollNumber);
                    break;
                case 3:
                    printf("Enter new student mark: ");
                    fgets(inputBuffer, MAX_BUFFER_SIZE, stdin);
                    sscanf(inputBuffer, "%d", &students[i].mark);
                    break;
                case 4:
                    printf("Enter new student name: ");
                    fgets(students[i].name, MAX_NAME_LENGTH, stdin);
                    students[i].name[strcspn(students[i].name, "\n")] = 0; // Remove trailing newline

                    printf("Enter new student roll number: ");
                    fgets(inputBuffer, MAX_BUFFER_SIZE, stdin);
                    sscanf(inputBuffer, "%d", &students[i].rollNumber);

                    printf("Enter new student mark: ");
                    fgets(inputBuffer, MAX_BUFFER_SIZE, stdin);
                    sscanf(inputBuffer, "%d", &students[i].mark);
                    break;
                default:
                    printf("Invalid choice. Returning to main options.\n");
                    return;
            }

            strcpy(students[i].grade, determineStudentGrade(students[i].mark));
            saveAllStudentsToFile(students, count);
            printf("Student information updated successfully.\n");
            break;
        }
    }

    if (!studentFound) {
        printf("Student with roll number %d not found.\n", rollNumber);
    }

    free(students);
}

void saveStudentToFile(const Student *student) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%s,%d,%d,%s\n", student->name, student->rollNumber, student->mark, student->grade);
    fclose(file);
}

char *determineStudentGrade(int mark) {
    return mark < PASS_MARK ? "FAILED" : "PASSED";
}

Student* getStudentsFromFile(int *count) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        *count = 0;
        return NULL;
    }

    int allocatedSize = 10;
    int totalStudents = 0;
    Student *students = malloc(allocatedSize * sizeof(Student));

    while (fscanf(file, "%99[^,],%d,%d,%99[^\n]\n", students[totalStudents].name, &students[totalStudents].rollNumber, &students[totalStudents].mark, students[totalStudents].grade) != EOF) {
        totalStudents++;
        if (totalStudents >= allocatedSize) {
            allocatedSize *= 2;
            students = realloc(students, allocatedSize * sizeof(Student));
        }
    }

    fclose(file);
    *count = totalStudents;
    return students;
}

void saveAllStudentsToFile(const Student *students, int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,%d,%s\n", students[i].name, students[i].rollNumber, students[i].mark, students[i].grade);
    }

    fclose(file);
}

void deleteAllRecords() {
    char confirmation;
    printf("Are you sure you want to delete all records? This action cannot be undone. (y/n): ");
    scanf("%c", &confirmation);
    getchar(); // Consume newline character left in the buffer

    if (confirmation == 'y' || confirmation == 'Y') {
        FILE *file = fopen(FILE_NAME, "w");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }
        fclose(file);
        printf("All student records have been deleted.\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}
