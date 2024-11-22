#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Marks {
    float midterm;
    float final;
    float assignment;
};

struct course {
    char courseid[20];
    char course_name[20];
    float gpa;
    struct Marks course_marks;
};

struct student {
    int roll;
    char name[20];
    char father_name[20];
    char section;
    struct course courses[6];
};
void startup(){
	printf("\t\t\t\t\t--------------------------------");
	printf("\n\t\t\t\t\t|                              |");
	printf("\n\t\t\t\t\t|       Welcome To FAST-NU     |");
	printf("\n\t\t\t\t\t|                              |");
	printf("\n\t\t\t\t\t--------------------------------");
}
void AddDetails() {
    struct student s;
    FILE *fp = fopen("students.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\nEnter roll no: ");
    scanf("%d", &s.roll);
    getchar(); // Consume leftover newline

    printf("Enter name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline

    printf("Enter your father's name: ");
    fgets(s.father_name, sizeof(s.father_name), stdin);
    s.father_name[strcspn(s.father_name, "\n")] = '\0'; // Remove newline

    printf("Enter section: ");
    scanf(" %c", &s.section);

    for (int j = 0; j < 3; j++) {
        printf("Enter course id: ");
        scanf("%s", s.courses[j].courseid);

        printf("Enter course name: ");
        scanf("%s", s.courses[j].course_name);

        printf("Enter GPA: ");
        scanf("%f", &s.courses[j].gpa);

        printf("Enter midterm marks: ");
        scanf("%f", &s.courses[j].course_marks.midterm);

        printf("Enter final marks: ");
        scanf("%f", &s.courses[j].course_marks.final);

        printf("Enter assignment marks: ");
        scanf("%f", &s.courses[j].course_marks.assignment);
    }

    // Write student details to file
    fprintf(fp, "%d\n%s\n%s\n%c\n", s.roll, s.name, s.father_name, s.section);
    for (int j = 0; j < 3; j++) {
        fprintf(fp, "%s %s %.2f %.2f %.2f %.2f\n", s.courses[j].courseid, s.courses[j].course_name,
                s.courses[j].gpa, s.courses[j].course_marks.midterm,
                s.courses[j].course_marks.final, s.courses[j].course_marks.assignment);
    }
    fprintf(fp, "END\n"); // Marker for end of one student record
    fclose(fp);

    printf("Student details added successfully.\n");
}

void DisplayAllStudents() {
    struct student s;
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\nAll Student Details:\n");
    while (fscanf(fp, "%d\n", &s.roll) != EOF) {
        fgets(s.name, sizeof(s.name), fp);
        s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline

        fgets(s.father_name, sizeof(s.father_name), fp);
        s.father_name[strcspn(s.father_name, "\n")] = '\0'; // Remove newline

        fscanf(fp, " %c\n", &s.section);

        printf("\n-------------------------------------------------\n");
        printf("Student Roll: %d\n", s.roll);
        printf("Name: %s\n", s.name);
        printf("Father's Name: %s\n", s.father_name);
        printf("Section: %c\n", s.section);

        for (int j = 0; j < 3; j++) {
            fscanf(fp, "%s %s %f %f %f %f\n", s.courses[j].courseid, s.courses[j].course_name,
                   &s.courses[j].gpa, &s.courses[j].course_marks.midterm,
                   &s.courses[j].course_marks.final, &s.courses[j].course_marks.assignment);

            printf("\n  Course %d:\n", j + 1);
            printf("    Course ID: %s\n", s.courses[j].courseid);
            printf("    Course Name: %s\n", s.courses[j].course_name);
            printf("    GPA: %.2f\n", s.courses[j].gpa);
            printf("    Marks:\n");
            printf("      Midterm: %.2f\n", s.courses[j].course_marks.midterm);
            printf("      Final: %.2f\n", s.courses[j].course_marks.final);
            printf("      Assignment: %.2f\n", s.courses[j].course_marks.assignment);
        }
        fscanf(fp, "END\n"); // Skip end marker
        printf("-------------------------------------------------\n");
    }

    fclose(fp);
}

void UpdateDetails() {
    int roll, found = 0;
    struct student s;
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        perror("\nError opening file");
        return;
    }

    printf("\nEnter roll number of the student to update: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d\n", &s.roll) != EOF) {
        fgets(s.name, sizeof(s.name), fp);
        s.name[strcspn(s.name, "\n")] = '\0';

        fgets(s.father_name, sizeof(s.father_name), fp);
        s.father_name[strcspn(s.father_name, "\n")] = '\0';

        fscanf(fp, " %c\n", &s.section);

        for (int j = 0; j < 3; j++) {
            fscanf(fp, "%s %s %f %f %f %f\n", s.courses[j].courseid, s.courses[j].course_name,
                   &s.courses[j].gpa, &s.courses[j].course_marks.midterm,
                   &s.courses[j].course_marks.final, &s.courses[j].course_marks.assignment);
        }
        fscanf(fp, "END\n");

        if (s.roll == roll) {
            found = 1;
            printf("1. Name\n");
            printf("2. Father's Name\n");
            printf("3. Section\n");
            printf("4. Courses\n");

            int option;
            printf("Enter option to update: ");
            scanf("%d", &option);
            getchar(); // Consume leftover newline

            switch (option) {
                case 1:
                    printf("Enter new name: ");
                    fgets(s.name, sizeof(s.name), stdin);
                    s.name[strcspn(s.name, "\n")] = '\0';
                    break;
                case 2:
                    printf("Enter new father's name: ");
                    fgets(s.father_name, sizeof(s.father_name), stdin);
                    s.father_name[strcspn(s.father_name, "\n")] = '\0';
                    break;
                case 3:
                    printf("Enter new section: ");
                    scanf(" %c", &s.section);
                    break;
                case 4:
                    for (int j = 0; j < 3; j++) {
                        printf("Enter course id: ");
                        scanf("%s", s.courses[j].courseid);

                        printf("Enter course name: ");
                        scanf("%s", s.courses[j].course_name);

                        printf("Enter GPA: ");
                        scanf("%f", &s.courses[j].gpa);

                        printf("Enter midterm marks: ");
                        scanf("%f", &s.courses[j].course_marks.midterm);

                        printf("Enter final marks: ");
                        scanf("%f", &s.courses[j].course_marks.final);

                        printf("Enter assignment marks: ");
                        scanf("%f", &s.courses[j].course_marks.assignment);
                    }
                    break;
                default:
                    printf("Invalid option.\n");
            }
        }

        // Write updated or unchanged record to the temp file
        fprintf(temp, "%d\n%s\n%s\n%c\n", s.roll, s.name, s.father_name, s.section);
        for (int j = 0; j < 3; j++) {
            fprintf(temp, "%s %s %.2f %.2f %.2f %.2f\n", s.courses[j].courseid, s.courses[j].course_name,
                    s.courses[j].gpa, s.courses[j].course_marks.midterm,
                    s.courses[j].course_marks.final, s.courses[j].course_marks.assignment);
        }
        fprintf(temp, "END\n");
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        printf("Student details updated successfully.\n");
    } else {
        printf("Student with roll number %d not found.\n", roll);
    }
}
int main() {
    int choice;
    startup();
    while (1) {
    	printf("\n\t\t\t********************************************************");
        printf("\n\t\t\t\t1. Add Student Details\n");
        printf("\n\t\t\t\t2. Update Student Details\n");
        printf("\n\t\t\t\t3. Display All Students\n");
        printf("\n\t\t\t\t4. Exit\n");
        printf("\n\t\t\t\t5. Delete a Record\n");
        printf("\n\t\t\t********************************************************");
        printf("\n\n\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AddDetails();
                break;
            case 2:
                UpdateDetails();
                break;
            case 3:
                DisplayAllStudents();
                break;
            case 4:
                return 0;
				break; 
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
