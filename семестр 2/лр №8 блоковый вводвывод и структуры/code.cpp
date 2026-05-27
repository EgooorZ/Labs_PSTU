#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

struct Stadion {
	string name = "безымянный";
	string address = "безадресный";
	int capacity = 0;
	string typesSport = "бесспортный";

	void print() {
		cout << "     Имя:    \t" << name << endl;
		cout << "    Адрес:   \t" << address << endl;
		cout << "Вместимость: \t" << capacity << endl;
		cout << "Виды спорта: \t" << typesSport	<< endl;
	}
};


Stadion* deleteElements(Stadion* stadion, int& size, string name) {

	int count = 0;
	for (int i = 0; i < size; i++) {
		if (stadion[i].name == name) {
			count++;
		}
	}

	Stadion* s = new Stadion[size - count];

	for (int i = 0, j = 0; i < size; i++) {
		if (stadion[i].name != name) {
			s[j] = stadion[i];
			j++;
		}
	}

	delete[] stadion;
	size -= count;

	return s;
}

Stadion* addElement(Stadion* stadion, int& size, int index) {
	string name, address, capacity, typesSport;
	
	cout << "введите имя: "; getline(cin, name);
	cout << "введите адрес: "; getline(cin, address);
	cout << "введите вместимость: "; getline(cin, capacity);
	cout << "введите виды спорта: "; getline(cin, typesSport);

	Stadion stad = { name, address, stoi(capacity), typesSport };
	cout << endl << "создан новый стадион" << endl;
	stad.print();
	cout << endl;

	Stadion* s = new Stadion[size + 1];

	for (int i = 0; i < size; i++) {
		if (i < index) s[i] = stadion[i];
		else if (i > index) s[i+1] = stadion[i];
		else s[i] = stad;
	}

	size += 1;
	delete[] stadion;

	return s;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	fstream file("init_stadions.txt");
	string buff;

	int stadionCount = 10;
	Stadion* stadions = new Stadion[stadionCount];


	string name, address, capacity, typesSport;

	for (int i = 0; i < stadionCount; i++) {
		getline(file, name);
		getline(file, address);
		getline(file, capacity);
		getline(file, typesSport);

		stadions[i] = { name, address, stoi(capacity), typesSport };
				
		getline(file, buff);
	}

	stadions = deleteElements(stadions, stadionCount, "Юность");

	stadions = addElement(stadions, stadionCount, 5);
	stadions = addElement(stadions, stadionCount, 6);


	for (int i = 0; i < stadionCount; i++) {
		cout << "\tCтадион номер: " << i+1 << endl;
		stadions[i].print();
		cout << endl;
	}

	delete[] stadions;
}