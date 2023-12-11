#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "bai1.txt";
    char buffer[1000]; 

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("invalid");
        return 1;
    }
    while (fgets(buffer, 1000, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);

    return 0;
}
