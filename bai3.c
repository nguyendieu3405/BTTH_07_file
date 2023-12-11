#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

struct Contact {
    char name[50];
    char phone[20];
    char email[50];
};

void saveContactsToFile(const struct Contact contacts[], int count, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Không thể mở tệp tin");
        exit(EXIT_FAILURE);
    }

    fwrite(contacts, sizeof(struct Contact), count, file);

    fclose(file);
}

void loadContactsFromFile(struct Contact contacts[], int* count, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Không thể mở tệp tin");
        exit(EXIT_FAILURE);
    }

    *count = fread(contacts, sizeof(struct Contact), MAX_CONTACTS, file);

    fclose(file);
}

void displayContact(const struct Contact* contact) {
    printf("Tên: %s\n", contact->name);
    printf("Số điện thoại: %s\n", contact->phone);
    printf("Email: %s\n", contact->email);
    printf("\n");
}

void addContact(struct Contact contacts[], int* count) {
    if (*count < MAX_CONTACTS) {
        struct Contact newContact;
        printf("Nhập tên: ");
        scanf("%s", newContact.name);
        printf("Nhập số điện thoại: ");
        scanf("%s", newContact.phone);
        printf("Nhập email: ");
        scanf("%s", newContact.email);

        contacts[*count] = newContact;
        (*count)++;
        printf("Liên lạc đã được thêm.\n");
    } else {
        printf("Sổ liên lạc đã đầy. Không thể thêm thêm liên lạc.\n");
    }
}

void searchContact(const struct Contact contacts[], int count, const char* name) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            displayContact(&contacts[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Không tìm thấy liên lạc có tên '%s'.\n", name);
    }
}

void deleteContact(struct Contact contacts[], int* count, const char* name) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            // Xóa liên lạc bằng cách dịch chuyển các phần tử sau nó lên
            for (int j = i; j < *count - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            (*count)--;
            found = 1;
            printf("Liên lạc đã được xóa.\n");
            break;
        }
    }

    if (!found) {
        printf("Không tìm thấy liên lạc có tên '%s'. Không thể xóa.\n", name);
    }
}

int main() {
    struct Contact contacts[MAX_CONTACTS];
    int contactCount = 0;

    const char* filename = "contacts.dat";

    loadContactsFromFile(contacts, &contactCount, filename);

    int choice;
    char searchName[50];

    do {
        printf("1. Thêm liên lạc\n");
        printf("2. Tìm kiếm liên lạc\n");
        printf("3. Xóa liên lạc\n");
        printf("4. Hiển thị tất cả liên lạc\n");
        printf("5. Lưu và thoát\n");
        printf("Nhập lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact(contacts, &contactCount);
                break;
            case 2:
                printf("Nhập tên cần tìm kiếm: ");
                scanf("%s", searchName);
                searchContact(contacts, contactCount, searchName);
                break;
            case 3:
                printf("Nhập tên cần xóa: ");
                scanf("%s", searchName);
                deleteContact(contacts, &contactCount, searchName);
                break;
            case 4:
                for (int i = 0; i < contactCount; i++) {
                    displayContact(&contacts[i]);
                }
                break;
            case 5:
                saveContactsToFile(contacts, contactCount, filename);
                printf("Dữ liệu đã được lưu và thoát chương trình.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng chọn lại.\n");
        }
    } while (choice != 5);

    return 0;
}
