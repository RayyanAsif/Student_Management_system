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
        printf("\t\t\t\nError opening file");
        return;
    }

    printf("\n\n\t\t\tEnter roll no: ");
    scanf("%d", &s.roll);
    getchar();
    printf("\n\n\t\t\tEnter name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline

    printf("\n\n\t\t\tEnter your father's name: ");
    fgets(s.father_name, sizeof(s.father_name), stdin);
    s.father_name[strcspn(s.father_name, "\n")] = '\0'; // Remove newline

    printf("\n\n\t\t\tEnter section: ");
    scanf(" %c", &s.section);

    for (int j = 0; j < 3; j++) {
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
    fprintf(fp, "%d\n%s\n%s\n%c\n", s.roll, s.name, s.father_name, s.section);
    for (int j = 0; j < 3; j++) {
        fprintf(fp, "%s %s %.2f %.2f %.2f %.2f\n", s.courses[j].courseid, s.courses[j].course_name,
                s.courses[j].gpa, s.courses[j].course_marks.midterm,
                s.courses[j].course_marks.final, s.courses[j].course_marks.assignment);
    }
    fprintf(fp, "END\n"); // Marker for end of one student record
    fclose(fp);

    printf("\n\n\t\t\tStudent details added successfully.\n");
}

void DisplayAllStudents() {
    struct student s;
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        perror("\n\n\t\t\tError opening file");
        return;
    }

    printf("\n\n\t\t\tAll Student Details:\n");
    while (fscanf(fp, "%d\n", &s.roll) != EOF) {
        fgets(s.name, sizeof(s.name), fp);
        s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline

        fgets(s.father_name, sizeof(s.father_name), fp);
        s.father_name[strcspn(s.father_name, "\n")] = '\0'; // Remove newline

        fscanf(fp, " %c\n", &s.section);

        printf("\n-------------------------------------------------\n");
        printf("\n\n\t\t\tStudent Roll: %d\n", s.roll);
        printf("\n\n\t\t\tName: %s\n", s.name);
        printf("\n\n\t\t\tFather's Name: %s\n", s.father_name);
        printf("\n\n\t\t\tSection: %c\n", s.section);

        for (int j = 0; j < 3; j++) {
            fscanf(fp, "%s %s %f %f %f %f\n", s.courses[j].courseid, s.courses[j].course_name,
                   &s.courses[j].gpa, &s.courses[j].course_marks.midterm,
                   &s.courses[j].course_marks.final, &s.courses[j].course_marks.assignment);

            printf("\n\n\t\t\t  Course %d:\n", j + 1);
            printf("\n\n\t\t\t    Course ID: %s\n", s.courses[j].courseid);
            printf("\n\n\t\t\t    Course Name: %s\n", s.courses[j].course_name);
            printf("\n\n\t\t\t    GPA: %.2f\n", s.courses[j].gpa);
            printf("\n\n\t\t\t    Marks:\n");
            printf("\n\n\t\t\t      Midterm: %.2f\n", s.courses[j].course_marks.midterm);
            printf("\n\n\t\t\t      Final: %.2f\n", s.courses[j].course_marks.final);
            printf("\n\n\t\t\t     Assignment: %.2f\n", s.courses[j].course_marks.assignment);
        }
        fscanf(fp, "END\n");
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
        perror("\n\n\t\t\t\tError opening file");
        return;
    }

    printf("\n\n\t\t\t\tEnter roll number of the student to update: ");
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
            printf("\n\n\t\t\t\t1. Name\n");
            printf("\n\n\t\t\t\t2. Father's Name\n");
            printf("\n\n\t\t\t\t3. Section\n");
            printf("\n\n\t\t\t\t4. Courses\n");

            int option;
            printf("\n\n\t\t\t\tEnter option to update: ");
            scanf("%d", &option);
            getchar();
			switch (option) {
                case 1:
                    printf("\n\n\t\t\t\tEnter new name: ");
                    fgets(s.name, sizeof(s.name), stdin);
                    s.name[strcspn(s.name, "\n")] = '\0';
                    break;
                case 2:
                    printf("\n\n\t\t\t\tEnter new father's name: ");
                    fgets(s.father_name, sizeof(s.father_name), stdin);
                    s.father_name[strcspn(s.father_name, "\n")] = '\0';
                    break;
                case 3:
                    printf("\n\n\t\t\t\tEnter new section: ");
                    scanf(" %c", &s.section);
                    break;
                case 4:
                    for (int j = 0; j < 3; j++) {
                        printf("\n\n\t\t\t\tEnter course id: ");
                        scanf("%s", s.courses[j].courseid);

                        printf("\n\n\t\t\t\tEnter course name: ");
                        scanf("%s", s.courses[j].course_name);

                        printf("\n\n\t\t\t\tEnter GPA: ");
                        scanf("%f", &s.courses[j].gpa);

                        printf("\n\n\t\t\t\tEnter midterm marks: ");
                        scanf("%f", &s.courses[j].course_marks.midterm);

                        printf("\n\n\t\t\t\tEnter final marks: ");
                        scanf("%f", &s.courses[j].course_marks.final);

                        printf("\n\n\t\t\t\tEnter assignment marks: ");
                        scanf("%f", &s.courses[j].course_marks.assignment);
                    }
                    break;
                default:
                    printf("\n\n\t\t\t\tInvalid option.\n");
            }
        }
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
        printf("\n\n\t\t\tStudent details updated successfully.\n");
    } else {
        printf("\n\n\t\t\tStudent with roll number %d not found.\n", roll);
    }
}
void delete_student(){
	struct student s;
	int roll;
	int found=0;
	printf("\t\t\t\nEnter roll number: ");
	scanf("%d",&roll);
	FILE *ptr,*temp;
	ptr = fopen("students.txt","r");
	temp = fopen("temp.txt","w");
	while (fscanf(ptr, "%d\n", &s.roll) != EOF){
        fgets(s.name, sizeof(s.name), ptr);
        s.name[strcspn(s.name, "\n")] = '\0';
		fgets(s.father_name, sizeof(s.father_name), ptr);
        s.father_name[strcspn(s.father_name, "\n")] = '\0';
		fscanf(ptr, " %c\n", &s.section);
		for (int j = 0; j < 3; j++) {
            fscanf(ptr, "%s %s %f %f %f %f\n", s.courses[j].courseid, s.courses[j].course_name,
                   &s.courses[j].gpa, &s.courses[j].course_marks.midterm,
                   &s.courses[j].course_marks.final, &s.courses[j].course_marks.assignment);
        }
        fscanf(ptr, "END\n");
		if (s.roll == roll) {
            found = 1;
            printf("\n\n\t\t\t\tRecord of student with roll number %d deleted successfully.\n", roll);
        } else {
            fprintf(temp, "%d\n%s\n%s\n%c\n", s.roll, s.name, s.father_name, s.section);
            for (int j = 0; j < 3; j++) {
                fprintf(temp, "%s %s %.2f %.2f %.2f %.2f\n", s.courses[j].courseid, s.courses[j].course_name,
                        s.courses[j].gpa, s.courses[j].course_marks.midterm,
                        s.courses[j].course_marks.final, s.courses[j].course_marks.assignment);
            }
            fprintf(temp, "END\n");
        }
    }
	fclose(ptr);
	fclose(temp);
	if(found==0){
		printf("\n\n\t\t\t\tRecord not found\n");
	}
	else{
		remove("student.txt");
		rename("temp.txt","students.txt");
	}
}
void reportcard() {
    struct student s;
    int roll, found = 0;
    FILE *ptr = fopen("students.txt", "r");
	if (ptr == NULL) {
        printf("\t\t\t\nError opening file\n");
        return;
    }
	printf("\t\t\t\nEnter roll number of the student to generate report card: ");
    scanf("%d", &roll);
	while (fscanf(ptr, "%d\n", &s.roll) != EOF){
        fgets(s.name, sizeof(s.name),ptr);
        s.name[strcspn(s.name, "\n")] = '\0';
		fgets(s.father_name, sizeof(s.father_name), ptr);
        s.father_name[strcspn(s.father_name, "\n")] = '\0';

        fscanf(ptr, " %c\n", &s.section);

        for (int j = 0; j < 3; j++) {
            fscanf(ptr, "%s %s %f %f %f %f\n", s.courses[j].courseid, s.courses[j].course_name,
                   &s.courses[j].gpa, &s.courses[j].course_marks.midterm,
                   &s.courses[j].course_marks.final, &s.courses[j].course_marks.assignment);
        }
        fscanf(ptr, "END\n");

        if (s.roll == roll) {
            found = 1;

            printf("\n\n-------------------- REPORT CARD --------------------\n");
            printf("\t\t\t\nStudent Name: %s\n", s.name);
            printf("\t\t\t\nFather's Name: %s\n", s.father_name);
            printf("\t\t\t\nRoll Number: %d\n", s.roll);
            printf("\t\t\t\nSection: %c\n", s.section);
            printf("----------------------------------------------------\n");
            printf("\t\t\t\nCourse ID   Course Name   Midterm   Final   Assignment   Total\n");

            float totalMarks = 0, averageMarks = 0;
            for (int j = 0; j < 3; j++) {
                float courseTotal = s.courses[j].course_marks.midterm +
                                    s.courses[j].course_marks.final +
                                    s.courses[j].course_marks.assignment;

                totalMarks += courseTotal;

                printf("\t\t\t\n%-10s %-13s %-9.2f %-7.2f %-11.2f %-6.2f\n",
                       s.courses[j].courseid, s.courses[j].course_name,
                       s.courses[j].course_marks.midterm, s.courses[j].course_marks.final,
                       s.courses[j].course_marks.assignment, courseTotal);
            }

            averageMarks = totalMarks / 3.0;
            printf("----------------------------------------------------\n");
            printf("\t\t\t\nOverall Total Marks: %.2f\n", totalMarks);
            printf("\t\t\t\nOverall Average Marks: %.2f\n", averageMarks);
            printf("----------------------------------------------------\n");
            break;
        }
    }

    if (found==0){
        printf("Student with roll number %d not found.\n", roll);
    }

    fclose(ptr);
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
        printf("\n\t\t\t\t6. Generate Report Card\n");
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
            case 5:
				delete_student();
				break; 
			case 6:
				reportcard();
				break;	
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
