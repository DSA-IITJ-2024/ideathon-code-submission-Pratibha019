#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 100
#define MAX_BOOKS 100
#define MAX_BOOK_NAME_LENGTH 50

// Structure to store student details
typedef struct Student {
    char name[50];
    int id_no;
    char stream[50];
    char book1[MAX_BOOK_NAME_LENGTH];
    char book2[MAX_BOOK_NAME_LENGTH];
    int book_no;
    int issued_books; // Use a more descriptive name
} Student;

// Function prototypes
Student* createStudent(char *name, int id_no, char *stream);
void displayStudent(Student *student);
Student* readStudentFromFile(FILE *fp, int *id);
void writeStudentToFile(FILE *fp, Student *student);
void updateStudentIssuedBooks(Student *students, int student_count, int id, int change);
void searchStudent(Student *students, int student_count, int id);
void issueBook(Student *students, int *student_count, char *book_name);
void returnBook(Student *students, int *student_count, char *book_name);
void printStudents(Student *students, int student_count);

// Global variables
Student students[MAX_STUDENTS];
int student_count = 0;
FILE *fp_students;

int main() {
    int choice, id;
    char name[50], stream[50], book_name[MAX_BOOK_NAME_LENGTH];

    fp_students = fopen("students.txt", "a+");

    if (fp_students == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Load student data from file
    while (feof(fp_students) == 0) {
        Student *student = readStudentFromFile(fp_students, &id);
        if (student != NULL) {
            students[student_count] = *student;
            student_count++;
            free(student); // Free memory allocated for temporary student
        }
    }

    while (1) {
        printf("\n.....................................\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Print Students\n");
        printf("6. Exit\n");

        printf("\n.....................................\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name of student: ");
                scanf(" %s", name);
                printf("Enter ID number: ");
                scanf("%d", &id);
                printf("Enter stream: ");
                scanf(" %s", stream);
                students[student_count] = *createStudent(name, id, stream);
                student_count++;
                break;
            case 2:
                printf("Enter student ID to search: ");
                scanf("%d", &id);
                searchStudent(students, student_count, id);
                break;
            case 3:
                printf("Enter name of book to issue: ");
                scanf(" %s", book_name);
                issueBook(students, &student_count, book_name);
                break;
            case 4:
                printf("Enter name of book to return: ");
                scanf(" %s", book_name);
                returnBook(students, &student_count, book_name);
                break;
            case 5:
                printStudents(students, student_count);
                break;
            case 6:
                // Write student data back to file
                rewind(fp_students);
                for (int i = 0; i < student_count; i++) {
                    writeStudentToFile(fp_students, &students[i]);
                }
                fclose(fp_students);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0; // To avoid compiler warnings
}
