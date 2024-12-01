#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 6

struct fees {
    float total_fee;
    float paid_fee;
    float outstanding_fee;
};

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
    char name[50];
    char father_name[50];
    char section;
    char email[30];
    int num_courses;
    struct course courses[MAX_COURSES];
    struct fees fee_details;
};

void AddDummyData() {
    FILE *fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        printf("\n\n\t\t\tError creating file.\n");
        return;
    }

    struct student s = {
        1,
        "akbar",
        "ali",
        'A',
        "akbar@example.com",
        2, 
        {
            {"CS101", "maths", 3.5, {20.0, 30.0, 10.0}},
            {"CS102", "eng", 3.8, {22.0, 28.0, 12.0}}
        },
        {10000.0, 5000.0, 5000.0} 
    };

    fwrite(&s, sizeof(struct student), 1, fp);
    fclose(fp);
}
int validateEmail(char email[]) {
    if (email == NULL || email[0] == '\0') {
        return 0; 
    }

    int at_count = 0, dot_count = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            at_count++;
        } else if (email[i] == '.') {
            dot_count++;
        }
    }
    
    return (at_count == 1 && dot_count >= 1);
}

void startup() {
    printf("\t\t\t\t\t--------------------------------\n");
    printf("\t\t\t\t\t|                              |\n");
    printf("\t\t\t\t\t|       Welcome To FAST-NU     |\n");
    printf("\t\t\t\t\t|                              |\n");
    printf("\t\t\t\t\t--------------------------------\n");
}

void AddDetails() {
    struct student s;
    int x;
    FILE *fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter roll no: ");
    scanf("%d", &s.roll);
    getchar();
    
    printf("\n\n\t\t\tEnter name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    do {
        printf("\n\n\t\t\tEnter email (format: name@domain.com): ");
        fgets(s.email, sizeof(s.email), stdin);
        s.email[strcspn(s.email, "\n")] = '\0';
        x = validateEmail(s.email);
        if (x == 0) {
            printf("\n\n\t\t\tInvalid email format. Please try again.\n");
        }
    } while (x != 1);
    
    printf("\n\n\t\t\tEnter your father's name: ");
    fgets(s.father_name, sizeof(s.father_name), stdin);
    s.father_name[strcspn(s.father_name, "\n")] = '\0';

    printf("\n\n\t\t\tEnter section: ");
    scanf(" %c", &s.section);
    getchar();
    
    printf("\n\n\t\t\tEnter number of courses: ");
    scanf("%d",&s.num_courses);
    getchar();
    
    for (int j = 0; j < s.num_courses; j++) {
        printf("\n\n\t\t\tEnter course id: ");
        scanf("%s", s.courses[j].courseid);

        printf("\n\n\t\t\tEnter course name: ");
        scanf("%s", s.courses[j].course_name);

        printf("\n\n\t\t\tEnter GPA: ");
        scanf("%f", &s.courses[j].gpa);

        printf("\n\n\t\t\tEnter midterm marks: ");
        scanf("%f", &s.courses[j].course_marks.midterm);

        printf("\n\n\t\t\tEnter final marks: ");
        scanf("%f", &s.courses[j].course_marks.final);

        printf("\n\n\t\t\tEnter assignment marks: ");
        scanf("%f", &s.courses[j].course_marks.assignment);
    }

    fwrite(&s, sizeof(struct student), 1, fp);
    fclose(fp);

    printf("\n\n\t\t\tStudent details added successfully.\n");
}

void DisplayAllStudents() {
    struct student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tAll Student Details:\n");
    while (fread(&s, sizeof(struct student), 1, fp)) {
        printf("\n-------------------------------------------------\n");
        printf("\n\t\t\tStudent Roll: %d\n", s.roll);
        printf("\n\t\t\tName: %s\n", s.name);
        printf("\n\t\t\tEmail: %s\n", s.email);
        printf("\n\t\t\tFather's Name: %s\n", s.father_name);
        printf("\n\t\t\tSection: %c\n", s.section);

        for (int j = 0; j < s.num_courses; j++) {
            printf("\n\t\t\tCourse %d:\n", j + 1);
            printf("\n\t\t\t  Course ID: %s\n", s.courses[j].courseid);
            printf("\n\t\t\t  Course Name: %s\n", s.courses[j].course_name);
            printf("\n\t\t\t  GPA: %.2f\n", s.courses[j].gpa);
            printf("\n\t\t\t  Marks:\n");
            printf("\n\t\t\t    Midterm: %.2f\n", s.courses[j].course_marks.midterm);
            printf("\n\t\t\t    Final: %.2f\n", s.courses[j].course_marks.final);
            printf("\n\t\t\t    Assignment: %.2f\n", s.courses[j].course_marks.assignment);
        }
    }
    fclose(fp);
}

void UpdateDetails() {
    int roll, found = 0;
    struct student s;
    FILE *fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter roll number of the student to update: ");
    scanf("%d", &roll);
    getchar();
    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("\n\n\t\t\tEnter new name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            
            printf("\n\n\t\t\tEnter new email: ");
            fgets(s.email, sizeof(s.email), stdin);
            s.email[strcspn(s.email, "\n")] = '\0';

            printf("\n\n\t\t\tEnter new father's name: ");
            fgets(s.father_name, sizeof(s.father_name), stdin);
            s.father_name[strcspn(s.father_name, "\n")] = '\0';

            printf("\n\n\t\t\tEnter new section: ");
            scanf(" %c", &s.section);

            fseek(fp, sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);
            printf("\n\n\t\t\tStudent details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("\n\n\t\t\tStudent with roll number %d not found.\n", roll);
    }
    fclose(fp);
}

void delete_student() {
    struct student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter roll number: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("\n\n\t\t\tRecord of student with roll number %d deleted successfully.\n", roll);
        } else {
            fwrite(&s, sizeof(struct student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (!found) {
        printf("\n\n\t\t\tRecord not found.\n");
    }
}

void reportcard() {
    struct student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter roll number of the student to generate report card: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;

            printf("\n\n-------------------- REPORT CARD --------------------\n");
            printf("\n\t\t\tStudent Name: %s", s.name);
            printf("\n\t\t\tStudent email: %s", s.email);
            printf("\n\t\t\tFather's Name: %s", s.father_name);
            printf("\n\t\t\tRoll Number: %d", s.roll);
            printf("\n\t\t\tSection: %c", s.section);
            printf("\n----------------------------------------------------\n");
            printf("\n\t\t\tCourse ID   Course Name   Midterm   Final   Assignment   Total\n");

            float totalMarks = 0, averageMarks = 0;
            for (int j = 0; j < s.num_courses; j++) {
                float courseTotal = s.courses[j].course_marks.midterm +
                                    s.courses[j].course_marks.final +
                                    s.courses[j].course_marks.assignment;

                totalMarks += courseTotal;

                printf("\n\t\t\t%-10s %-13s %-9.2f %-7.2f %-11.2f %-6.2f",
                       s.courses[j].courseid, s.courses[j].course_name,
                       s.courses[j].course_marks.midterm, s.courses[j].course_marks.final,
                       s.courses[j].course_marks.assignment, courseTotal);
            }

            averageMarks = totalMarks / s.num_courses;
            printf("\n----------------------------------------------------\n");
            printf("\n\t\t\tOverall Total Marks: %.2f", totalMarks);
            printf("\n\t\t\tOverall Average Marks: %.2f", averageMarks);
            printf("\n----------------------------------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("\n\n\t\t\tStudent with roll number %d not found.\n", roll);
    }
    fclose(fp);
}



void searchStudent() {
    int roll, found = 0;
    struct student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter roll number of the student to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("\n\n\t\t\tStudent Found:\n");
            printf("\n\t\t\tRoll: %d\n", s.roll);
            printf("\t\t\tName: %s\n", s.name);
            printf("\n\t\t\tEmail: %s\n", s.email);
            printf("\t\t\tFather's Name: %s\n", s.father_name);
            printf("\t\t\tSection: %c\n", s.section);
            break;
        }
    }

    if (!found) {
        printf("\n\n\t\t\tStudent with roll number %d not found.\n", roll);
    }

    fclose(fp);
}
void searchStudentByName() {
    char name[50];
    int found = 0;
    struct student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter name of the student to search: ");
    getchar(); 
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; 

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (stricmp(s.name, name) == 0) {
            found = 1;
            printf("\n\n\t\t\tStudent Found:\n");
            printf("\n\t\t\tRoll: %d\n", s.roll);
            printf("\t\t\tName: %s\n", s.name);
            printf("\n\t\t\tEmail: %s\n", s.email);
            printf("\t\t\tFather's Name: %s\n", s.father_name);
            printf("\t\t\tSection: %c\n", s.section);
            break;
        }
    }

    if (!found) {
        printf("\n\n\t\t\tStudent with name %s not found.\n", name);
    }

    fclose(fp);
}

void addFees() {
    struct student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter roll number to add fee details: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("\n\n\t\t\tEnter total fee: ");
            scanf("%f", &s.fee_details.total_fee);

            printf("\n\n\t\t\tEnter paid fee: ");
            scanf("%f", &s.fee_details.paid_fee);

            s.fee_details.outstanding_fee = s.fee_details.total_fee - s.fee_details.paid_fee;

            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);
            printf("\n\n\t\t\tFee details added successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("\n\n\t\t\tStudent with roll number %d not found.\n", roll);
    }

    fclose(fp);
}

void displayFees() {
    struct student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter roll number to display fee details: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("\n\n\t\t\tStudent Fee Details:\n");
            printf("\n\t\t\tTotal Fee: %.2f", s.fee_details.total_fee);
            printf("\n\t\t\tPaid Fee: %.2f", s.fee_details.paid_fee);
            printf("\n\t\t\tOutstanding Fee: %.2f", s.fee_details.outstanding_fee);
            break;
        }
    }

    if (!found) {
        printf("\n\n\t\t\tStudent with roll number %d not found.\n", roll);
    }

    fclose(fp);
}

void updateFees() {
    struct student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("\n\n\t\t\tError opening file.\n");
        return;
    }

    printf("\n\n\t\t\tEnter roll number to update fee details: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("\n\n\t\t\tEnter total fee: ");
            scanf("%f", &s.fee_details.total_fee);

            printf("\n\n\t\t\tEnter paid fee: ");
            scanf("%f", &s.fee_details.paid_fee);

            s.fee_details.outstanding_fee = s.fee_details.total_fee - s.fee_details.paid_fee;

            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);
            printf("\n\n\t\t\tFee details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("\n\n\t\t\tStudent with roll number %d not found.\n", roll);
    }

    fclose(fp);
}
void generatecoursesReport() {
    struct student s;
    FILE *fptr = fopen("students.dat", "rb");
    if (fptr == NULL) {
        perror("Error opening file");
        return;
    }

    struct {
        char coursename[20];
        int count;
    } courseStats[100];
    int courseCount = 0;
    int i,j;
    while (fread(&s, sizeof(struct student), 1, fptr)) {
        for ( i = 0; i < s.num_courses; i++) {
            int found = 0;
            for ( j = 0; j < courseCount; j++) {
                if (strcmp(courseStats[j].coursename, s.courses[i].course_name) == 0) {
                    courseStats[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(courseStats[courseCount].coursename, s.courses[i].course_name);
                courseStats[courseCount].count = 1;
                courseCount++;
            }
        }
    }

    fclose(fptr);

    printf("\nCourse Enrollment Report:\n");
    for (i = 0; i < courseCount; i++) {
        printf("Course Name: %s, Enrolled Students: %d\n", courseStats[i].coursename, courseStats[i].count);
    }
}

int main() {
    int choice;

    startup();
    AddDummyData();
    while (1) {
        printf("\n\n\t\t\tMenu:\n");
        printf("\t\t\t1. Add student details\n");
        printf("\t\t\t2. Display all students\n");
        printf("\t\t\t3. Update student details\n");
        printf("\t\t\t4. Delete student\n");
        printf("\t\t\t5. Generate report card\n");
        printf("\t\t\t6. Add fee details\n");
        printf("\t\t\t7. Display fee details\n");
        printf("\t\t\t8. Update fee details\n");
        printf("\t\t\t9. Search student by roll number\n");
        printf("\t\t\t10. Search student by name\n");
        printf("\t\t\t11. Display courses report\n");
        printf("\t\t\t12. Exit\n");
        printf("\n\n\t\t\tEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AddDetails();
                break;
            case 2:
                DisplayAllStudents();
                break;
            case 3:
                UpdateDetails();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                reportcard();
                break;
            case 6:
                addFees();
                break;
            case 7:
                displayFees();
                break;
            case 8:
                updateFees();
                break;
            case 9:
                searchStudent();
                break;
            case 10:
                searchStudentByName();
                break;
            case 11: 
            	generatecoursesReport();
				break;
            case 12:
                exit(0);
            default:
                printf("\n\t\t\tInvalid choice.\n");
        }
    }

    return 0;
}
