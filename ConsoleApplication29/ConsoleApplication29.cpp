#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;



struct Employee {
    string surname;
    string name;
    int age;
};

Employee* employees = NULL;
int countEmployees = 0;
string filename;

void addEmployee() {
    employees = (Employee*)realloc(employees, (countEmployees + 1) * sizeof(Employee));
    cout << "Surname: ";
    cin >> employees[countEmployees].surname;
    cout << "Name: ";
    cin >> employees[countEmployees].name;
    cout << "Age: ";
    cin >> employees[countEmployees].age;
    countEmployees++;
}

void showAll() {
    if (countEmployees == 0) {
        cout << "List is empty\n";
        return;
    }
    for (int i = 0; i < countEmployees; i++) {
        cout << i + 1 << ") " << employees[i].surname << " "
            << employees[i].name << ", " << employees[i].age << " years\n";
    }
}

void editEmployee() {
    int index;
    cout << "Enter index to edit (1-" << countEmployees << "): ";
    cin >> index;
    index--;
    if (index < 0 || index >= countEmployees) {
        cout << "Invalid index\n";
        return;
    }
    cout << "New surname: ";
    cin >> employees[index].surname;
    cout << "New name: ";
    cin >> employees[index].name;
    cout << "New age: ";
    cin >> employees[index].age;
}

void deleteEmployee() {
    int index;
    cout << "Enter index to delete (1-" << countEmployees << "): ";
    cin >> index;
    index--;
    if (index < 0 || index >= countEmployees) {
        cout << "Invalid index\n";
        return;
    }
    for (int i = index; i < countEmployees - 1; i++) {
        employees[i] = employees[i + 1];
    }
    countEmployees--;
    employees = (Employee*)realloc(employees, countEmployees * sizeof(Employee));
}

void searchBySurname() {
    string s;
    cout << "Enter surname to search: ";
    cin >> s;
    ofstream fout("search_result.txt");
    for (int i = 0; i < countEmployees; i++) {
        if (employees[i].surname == s) {
            cout << employees[i].surname << " " << employees[i].name
                << ", " << employees[i].age << " years\n";
            fout << employees[i].surname << " " << employees[i].name
                << ", " << employees[i].age << " years\n";
        }
    }
    fout.close();
}

void filterByAge() {
    int a;
    cout << "Enter age: ";
    cin >> a;
    ofstream fout("filter_result.txt");
    for (int i = 0; i < countEmployees; i++) {
        if (employees[i].age == a) {
            cout << employees[i].surname << " " << employees[i].name
                << ", " << employees[i].age << " years\n";
            fout << employees[i].surname << " " << employees[i].name
                << ", " << employees[i].age << " years\n";
        }
    }
    fout.close();
}

void filterByInitial() {
    char c;
    cout << "Enter initial letter: ";
    cin >> c;
    ofstream fout("filter_result.txt");
    for (int i = 0; i < countEmployees; i++) {
        if (!employees[i].surname.empty() && employees[i].surname[0] == c) {
            cout << employees[i].surname << " " << employees[i].name
                << ", " << employees[i].age << " years\n";
            fout << employees[i].surname << " " << employees[i].name
                << ", " << employees[i].age << " years\n";
        }
    }
    fout.close();
}

void saveToFile() {
    ofstream fout(filename);
    for (int i = 0; i < countEmployees; i++) {
        fout << employees[i].surname << " "
            << employees[i].name << " "
            << employees[i].age << "\n";
    }
    fout.close();
}

void loadFromFile() {
    ifstream fin(filename);
    if (!fin) return;
    Employee e;
    while (fin >> e.surname >> e.name >> e.age) {
        employees = (Employee*)realloc(employees, (countEmployees + 1) * sizeof(Employee));
        employees[countEmployees] = e;
        countEmployees++;
    }
    fin.close();
}

int main() {
    cout << "Enter file name: ";
    cin >> filename;
    loadFromFile();
    int choice;
    do {
        cout << "Menu\n";
        cout << "1 Add employee\n";
        cout << "2 Show all\n";
        cout << "3. Edit employee\n";
        cout << "4 Delete employee\n";
        cout << "5 Search by surname\n";
        cout << "6 Filter by age\n";
        cout << "7. Filter by initial letter\n";
        cout << "8 Save to file\n";
        cout << "0 Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: addEmployee(); break;
        case 2: showAll(); break;
        case 3: editEmployee(); break;
        case 4: deleteEmployee(); break;
        case 5: searchBySurname(); break;
        case 6: filterByAge(); break;
        case 7: filterByInitial(); break;
        case 8: saveToFile(); break;
        }
    } while (choice != 0);
    saveToFile();
    free(employees);
    return 0;
}












