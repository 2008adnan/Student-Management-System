#include <stdio.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student{
    int roll;
    char name[30];
    float marks;
};

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF){

    };
}

//returning 1 if roll number exists else 0
int rollExists(int roll){
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Student s;

    while(fread(&s, sizeof(s),1,fp)==1){
        if(s.roll == roll){
            fclose(fp);
            return 1;
        }
    }
    if(fp == NULL){
        return 0;
    }

    fclose(fp);
    return 0;
}

void addStudent(){
    FILE *fp;
    struct Student s;
    printf("--Add Student--\n");
    printf("Enter Roll Number: ");
    if(scanf("%d", &s.roll)!=1){
        clearBuffer();
        printf("Invalid roll number\n");
        return;
    }
    clearBuffer();

    if(rollExists(s.roll)){
        printf("A student with Roll no. %d already exists.\n", s.roll);
        return;
    }
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name),stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter marks: ");
    if (scanf("%f", &s.marks) != 1) {
        printf("Invalid marks!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    fp = fopen(FILE_NAME, "a");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudent(){
    FILE *fp = fopen(FILE_NAME, "rb");
    printf("\n--- All Students ---\n");
    if(fp == NULL){
        printf("No record found. Add a Student first.\n");
        return;
    }
    int count = 0;
    struct Student s;

    printf("%-10s %-25s %-10s\n", "Roll No", "Name", "Marks");
    printf("---------------------------------------------\n");

    while(fread(&s, sizeof(s), 1, fp) == 1){
        printf("%-10d %-25s %-10.2f\n", s.roll, s.name, s.marks);
        count++;
    }
    fclose(fp);

    if(count == 0){
        printf("No record found. Add a Student first.\n");
    }else {
        printf("---------------------------------------------\n");
        printf("Total students: %d\n", count);
    }

}
    
void searchStudent(){
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Student s;
    int roll,found = 0;
    if (fp == NULL) {
        printf("No records found. Add a student first.\n");
        return;
    }
    printf("\n--- Search Student ---\n");
    printf("Enter roll number to search: ");
    if (scanf("%d", &roll) != 1) {
        printf("Invalid roll number!\n");
        clearBuffer();
        fclose(fp);
        return;
    }
    clearBuffer();

    while(fread(&s, sizeof(s),1,fp) == 1){
        if(s.roll = roll){
        printf("\nStudent found!\n");
        printf("Roll No : %d\n", s.roll);
        printf("Name    : %s\n", s.name);
        printf("Marks   : %.2f\n", s.marks);
        found = 1;
        break;
        }
    }
    if(found == 0){
        printf("No student found with roll number %d.\n", roll);
    }
}

void rusticateStudent(){
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;
    char confirm;

    printf("\n--- Rusticate Student ---\n");
    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No records found. Add a student first.\n");
        return;
    }
    printf("Enter roll number to rusticate: ");
    if (scanf("%d", &roll) != 1) {
        printf("Invalid roll number!\n");
        clearBuffer();
        fclose(fp);
        return;
    }
    clearBuffer();
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
        printf("\nStudent found:\n");
        printf("Roll No : %d\n", s.roll);
        printf("Name    : %s\n", s.name);
        printf("Marks   : %.2f\n", s.marks);
        found = 1;
        break;
        }
    }
    if (found==0) {
        printf("No student found with roll number %d.\n", roll);
        fclose(fp);
        return;
    }

    printf("\nAre you sure you want to rusticate this student? (y/n): ");
    scanf("%c", &confirm);
    clearBuffer();
 
    if (confirm != 'y' && confirm != 'Y') {
        printf("Cancelled. Student was NOT rusticated.\n");
        fclose(fp);
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error: could not create temporary file!\n");
        fclose(fp);
        return;
    }
 
    rewind(fp);                             // go back to the start of the file 
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
 
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
 
    printf("Student with roll number %d has been rusticated.\n", roll);
}

int main(){

    int choice;
    do{
    printf("\n==============================\n");
    printf("  STUDENT MANAGEMENT SYSTEM\n");
    printf("==============================\n");
    printf("1. Add\n");
    printf("2. Display\n");
    printf("3. Search\n");
    printf("4. Rusticate\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");       

    if(scanf("%d", &choice) != 1){
        clearBuffer();
        choice =0;
    }else{
        clearBuffer();
    }

    switch(choice){
        case 1:
            addStudent();
            break;
        case 2:
            displayStudent();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            rusticateStudent();
            break;
        case 5:
            printf("\n--Thank You & Good Bye--\n");
            break;
        default:
            printf("\nInvalid choice! Please enter 1-5\n");
    }

    }while(choice != 5);

    
    return 0;
}