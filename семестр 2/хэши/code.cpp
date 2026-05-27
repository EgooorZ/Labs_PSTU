#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cmath> // для modf
#include <cstdlib> // для rand и srand
#include <cstdio>
#include <ctime> // для time
using namespace std;

// Константы
const int SIZE = 100; // Размер хеш-таблицы
const double A = 0.6180339887; // Константа для хеш-функции


struct Student
{
    string fio;
    string phone;
    string passport;
    string birthDate;
};


struct Node
{
    Student student;
    Node* next;
};


int hashFunction(const string& key)
{
    int dot1 = key.find('.');
    int dot2 = key.find('.', dot1 + 1);

    int day = stoi(key.substr(0, dot1));
    int month = stoi(key.substr(dot1 + 1, dot2 - dot1 - 1));
    int year = stoi(key.substr(dot2 + 1));

    int k = day * 10000 + month * 100 + year;

    double fractional;
    modf(k * A, &fractional);

    return static_cast<int>(SIZE * fractional) % SIZE;
}


void insert(Node* table[], const Student& student, int& collisions)
{
    int index = hashFunction(student.birthDate);

    Node* newNode = new Node;
    newNode->student = student;
    newNode->next = nullptr;

    // Если ячейка пуста, создаём новый список
    if (table[index] == nullptr)
    {
        table[index] = newNode;
    }
    else
    {
        // Иначе добавляем элемент в конец списка
        Node* current = table[index];
        while (current->next != nullptr)
        {
            current = current->next;
            collisions++; 
        }
        current->next = newNode;
    }
}

Student* search(Node* table[], const string& birthDate)
{
    int index = hashFunction(birthDate);

    Node* current = table[index];
    while (current != nullptr)
    {
        if (current->student.birthDate == birthDate)
        {
            return &(current->student);
        }
        current = current->next;
    }

    return nullptr;
}

void remove(Node* table[], const string& birthDate)
{
    int index = hashFunction(birthDate);

    Node* current = table[index];
    Node* prev = nullptr;


    while (current != nullptr)
    {
        if (current->student.birthDate == birthDate)
        {
            if (prev == nullptr)
            {
                // Если это первый элемент списка
                table[index] = current->next;
            }
            else
            {
                // Если это не первый элемент
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void saveToFile(Node* table[])
{
    FILE* file = fopen("Students.txt", "w");

    for (int i = 0; i < SIZE; i++)
    {
        Node* current = table[i];
        while (current != nullptr)
        {
            fprintf(file, "%s %s %s %s\n", current->student.fio.c_str(), current->student.phone.c_str(), current->student.passport.c_str(), current->student.birthDate.c_str());
            current = current->next;
        }
    }

    fclose(file);
    cout << "Данные сохранены в файл." << endl;
}

void loadFromFile(Node* table[], int& collisions)
{
    FILE* file = fopen("Students.txt", "r");

    // Очищаем текущую таблицу
    for (int i = 0; i < SIZE; i++)
    {
        Node* current = table[i];
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }

    char fio[100], phone[20], passport[20], birthDate[20];
    while (fscanf(file, "%s %s %s %s", fio, phone, passport, birthDate) != EOF)
    {
        Student student;
        student.fio = fio;
        student.phone = phone;
        student.passport = passport;
        student.birthDate = birthDate;

        insert(table, student, collisions);
    }

    fclose(file);
    cout << "Данные загружены из файла." << endl;
}

string generateBirthDate()
{
    int day = rand() % 28 + 1;
    int month = rand() % 12 + 1;
    int year = rand() % 20 + 1980; // Годы от 1980 до 2000
    return to_string(day) + "." + to_string(month) + "." + to_string(year);
}

Student generateStudent()
{
    Student student;
    student.fio = "Student" + to_string(rand() % 1000);
    student.phone = "+7" + to_string(rand() % 1000000000);
    student.passport = to_string(rand() % 1000000000);
    student.birthDate = generateBirthDate();
    return student;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    Node* table[SIZE] = { nullptr };
    int collisions = 0;

    // Генерация и вставка 40 студентов
    for (int i = 0; i < 40; i++)
    {
        insert(table, generateStudent(), collisions);
    }
    cout << "Коллизии для 40 объектов: " << collisions << endl;

    saveToFile(table);
    collisions = 0;
    loadFromFile(table, collisions);
    cout << "Коллизии после загрузки из файла: " << collisions << endl;

    // Генерация и вставка 75 студентов
    for (int i = 40; i < 75; i++)
    {
        insert(table, generateStudent(), collisions);
    }
    cout << "Коллизии для 75 объектов: " << collisions << endl;

    // Генерация и вставка 90 студентов
    for (int i = 75; i < 90; i++)
    {
        insert(table, generateStudent(), collisions);
    }
    cout << "Коллизии для 90 объектов: " << collisions << endl;

    // Пример поиска и удаления
    Student example = { "Молочко Артём Анатольевич", "111", "111", "23.01.2006" };
    insert(table, example, collisions);

    string searchKey = "23.01.2006";
    Student* foundStudent = search(table, searchKey);
    if (foundStudent != nullptr)
    {
        cout << "Найден студент: " << foundStudent->fio << endl;
    }
    else
    {
        cout << "Студент с датой рождения " << searchKey << " не найден." << endl;
    }

    remove(table, searchKey);
    cout << "Студент с датой рождения " << searchKey << " удалён." << endl;

    // Освобождение памяти
    for (int i = 0; i < SIZE; i++)
    {
        Node* current = table[i];
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    return 0;
}