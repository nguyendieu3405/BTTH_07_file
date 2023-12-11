#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int age;
    float gpa;
};

void writeBinaryFile(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
       printf("invalid");
        exit(1);
    }
    struct Student student1 = {"N..ntd", 18, 3.9};
    struct Student student2 = {"T...tmq", 24, 3.5};

    fwrite(&student1, sizeof(struct Student), 1, file);
    fwrite(&student2, sizeof(struct Student), 1, file);

  
    fclose(file);
}

void readBinaryFile(const char* filename) {
    
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("invalid");
        exit(1);
    }
    struct Student student;
    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        printf("Ten: %s\n", student.name);
        printf("Tuoi: %d\n", student.age);
        printf("GPA: %.2f\n", student.gpa);
        printf("\n");
    }
    fclose(file);
}

int main() {
    const char* filename = "students.dat";
    writeBinaryFile(filename);
    readBinaryFile(filename);

    return 0;
}
