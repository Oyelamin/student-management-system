
# Student Record System

## Description
This program is a command-line based Student Record System written in C. It allows users to add, view, search, modify, and delete student records. The records are stored in a text file named `students.txt`. The system supports operations like sorting students by their marks and calculating the average marks of all students.

## Features
- **Add Student**: Add a new student record to the system.
- **Display Students**: Display all student records.
- **Search Student by Roll Number**: Search for a student using their roll number.
- **Calculate Average Marks**: Calculate the average marks of all students.
- **Sort Students by Marks**: Sort student records based on their marks.
- **Delete Student Information**: Delete a specific student's information.
- **Modify Student Information**: Modify the details of an existing student.
- **Delete All Records**: Option to delete all records in the system.

## Program Structure
### Data Structures
- **Student Struct**: Holds the information of a student.
  - `name`: Student's name.
  - `rollNumber`: Student's roll number.
  - `mark`: Student's marks.
  - `grade`: Student's grade (determined based on marks).

### Functions
- **welcomePrompt**: Displays a welcome message.
- **promptUserName**: Prompts the user to input their name.
- **greetUser**: Greets the user using their inputted name.
- **printMainOptions**: Displays the main menu options.
- **handleMainOption**: Handles the user's main menu choice.
- **determineStudentGrade**: Determines the student's grade based on their mark.
- **addStudent**: Adds a new student record.
- **studentExists**: Checks if a student already exists in the records.
- **displayStudents**: Displays all student records.
- **searchStudentByRollNumber**: Searches for a student using their roll number.
- **calculateAverageMarks**: Calculates the average marks of all students.
- **sortStudentsByMarks**: Sorts student records based on their marks.
- **deleteStudentInformation**: Deletes a specific student's information.
- **modifyStudentInformation**: Modifies the details of an existing student.
- **saveStudentToFile**: Saves a student's record to the file.
- **getStudentsFromFile**: Retrieves all student records from the file.
- **saveAllStudentsToFile**: Saves all student records to the file.
- **deleteAllRecords**: Deletes all student records from the file.

## File Structure
- **`students.txt`**: The text file where all student records are stored. Each record is stored in the format: `Name,RollNumber,Mark,Grade`.

## Compilation and Execution
### Compilation
To compile the program, use the following command in the terminal:
```bash
gcc -o student_record_system student_record_system.c
```

### Execution
After compilation, run the program using:
```bash
./student_record_system
```

## Usage
1. Run the program.
2. Enter your name when prompted.
3. Choose an option from the main menu by entering the corresponding number.
4. Follow the on-screen instructions for the chosen operation.

## License
This program is provided as-is without any warranties. Feel free to modify and distribute it as you like.
