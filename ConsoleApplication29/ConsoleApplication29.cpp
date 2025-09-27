#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
    char surname[50];
    char name[50];
    int age;
} Employee;

Employee* employees = NULL;
int count = 0;

void addEmployee() {
    employees = (Employee*)realloc(employees, (count + 1) * sizeof(Employee));
    if (employees == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    printf("Surname: ");
    scanf("%49s", employees[count].surname);
    printf("Name: ");
    scanf("%49s", employees[count].name);
    printf("Age: ");
    scanf("%d", &employees[count].age);
    count++;
}

void showAll() {
    if (count == 0) {
        printf("List is empty\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("%d) %s %s, %d years\n", i + 1,
            employees[i].surname,
            employees[i].name,
            employees[i].age);
    }
}
void deleteEmployee() {
    int index;
    printf("Enter index to delete (1-%d): ", count);
    scanf("%d", &index);
    index--;
    if (index < 0 || index >= count) {
        printf("Invalid index!\n");
        return;
    }
    for (int i = index; i < count - 1; i++) {
        employees[i] = employees[i + 1];
    }
    count--;
    employees = (Employee*)realloc(employees, count * sizeof(Employee));
}

int main() {
    int choice;
    do {
        printf("Menu\n");
        printf("1. Add employee\n");
        printf("2. Show all\n");
        printf("3. Delete employee\n");
        printf("0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addEmployee(); break;
        case 2: showAll(); break;
        case 3: deleteEmployee(); break;
        }
    } while (choice != 0);

    free(employees);
    return 0;
}







