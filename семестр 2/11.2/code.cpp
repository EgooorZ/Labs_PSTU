#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

void invertSort(int* arr, int size) {
	int tmp;
	for (int j = 0; j < size - 1; j++) {
		for (int i = 0; i < size - j - 1; i++) {
			if (arr[i] < arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
}

// Очередь
struct Queue {
private:
	struct Node {
		string data;
		Node* nextElementAddress = nullptr;
	};

public:
	int size = 0;
	Node* firstElementAddress = nullptr;
	Node* endElementAddress = nullptr;

	void print() {
		Node* node = firstElementAddress;
		if (size == 0) {
			cout << " список пустой" << endl;
		}
		else {
			for (int i = 0; i < size; i++) {
				// cout << " " << i << ": \t" << node->data << "\t" << node << "\t" << node->nextElementAddress << endl;
				cout << " " << i << ": \t" << node->data << endl;
				node = node->nextElementAddress;
			}
		}
		cout << endl;
	}

	//////////////// commands ////////////////
	void push(string data) {
		Node* newNode = new Node{ data };
		if (size == 0) {
			endElementAddress = newNode;
			firstElementAddress = newNode;
		}
		else {
			endElementAddress->nextElementAddress = newNode;
			endElementAddress = newNode;
		}
		size++;
	}
	string pop() {
		if (size == 0) return "";

		string data = firstElementAddress->data;

		if (size == 1) {
			delete firstElementAddress;
			firstElementAddress = nullptr;
			endElementAddress = nullptr;
		}
		else {
			Node* node = firstElementAddress->nextElementAddress;
			// Находим предпоследний элемент

			delete firstElementAddress;
			firstElementAddress = node;
		}

		size--;
		return data;
	}
	//////////////////////////////////////////

	void add(string data, int node_i) {
		if (node_i == size) {
			push(data);
			return;
		}
		else if (node_i > size) {
			cout << endl << "номер добавляемого элемента больше чем размер очереди, элемент будет добавлен в конец  " << node_i << " > " << size << endl;
			node_i = size;
		}

		int arrSize = size;
		string* arr = new string[arrSize];

		for (int i = 0; i < arrSize; i++) {
			arr[i] = pop();
		}

		for (int i = 0; i < arrSize+1; i++) {
			if (i < node_i) push(arr[i]);
			else if (i > node_i) push(arr[i - 1]);
			else push(data);
		}

		delete[] arr;
	}
	void del(int node_i) {
		if (node_i > size) {
			cout << endl << "номер удаляемого элемента больше чем размер очереди, будет удален последний элемент  " << node_i << " > " << size << endl;
			node_i = size - 1;
		}
		if (node_i == 0) {
			pop();
			return;
		}

		int arrSize = size;
		string* arr = new string[arrSize];

		for (int i = 0; i < arrSize; i++) {
			if (i < node_i) 
				arr[i] = pop();
			else if (i > node_i) 
				arr[i-1] = pop();
			else 
				pop();
		}

		for (int i = 0; i < arrSize-1; i++) {
			push(arr[i]);
		}

		delete[] arr;
	}

	void addKElements(int k, ...) {
		// addKElements(int k, "data1", index1, "data2", index2, ...)
		//					   |____k = 1____|   |____k = 2____|	

		va_list args;
		va_start(args, k);

		const char* data; // string не работает
		int index;

		for (int i = 0; i < k; i++) {
			data = va_arg(args, const char*);
			index = va_arg(args, int);

			add(data, index);
		}

		va_end(args);
	}
	void delKElements(int k, ...) {
		va_list args;
		va_start(args, k);

		int* arr = new int[k];


		for (int i = 0; i < k; i++) {
			arr[i] = va_arg(args, int);
		}
		invertSort(arr, k); // нужно удалять начиная с наибольшего
		// индекса, чтобы сохранить индексацию

		for (int i = 0; i < k; i++) {
			del(arr[i]);
		}

		delete[] arr;
		va_end(args);
	}

	Queue() {}
	Queue(int k, ...) {
		// тоже самое что и addKElements()

		va_list args;
		va_start(args, k);

		const char* data; // string не работает
		int index;

		for (int i = 0; i < k; i++) {
			data = va_arg(args, const char*);
			index = va_arg(args, int);

			add(data, index);
		}

		va_end(args);

	}

	////////////////// file //////////////////
	void saveInFile(string name) {
		ofstream file(name);

		Node* node = firstElementAddress;
		for (int i = 0; i < size; i++) {
			file << node->data << "\n";
			node = node->nextElementAddress;
		}
		cout << " список сохранен в файл: " << name << endl;
		file.close();
	}

	void loadFromFileAddInEnd(string name) {
		ifstream file(name);
		string str = " ";
		while (getline(file, str)) {
			push(str);
		}
		file.close();
		cout << " список загружен из файла: " << name << endl;
	}
	void loadFromFileOverwriting(string name) {
		deleteList();
		loadFromFileAddInEnd(name);
	}
	/////////////////////////////////////////

	void deleteQueue() {
		for (int i = 0; i < size; i++) {
			pop();
		}
		size = 0;
		cout << " список удален" << endl;
	}
	~Queue() {
		if (size > 0) deleteQueue();
	}
};


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "ru");


	////////////////// 	1  //////////////////
	Queue queue(5,
		"data0", 0,
		"data1", 1,
		"data2", 2,
		"data3", 3,
		"data4", 4
	);


	cout << "\n //////////////////  2  //////////////////" << endl;
	Queue emptyList;
	cout << "  emptyQueue:" << endl;
	emptyList.print();

	cout << "    queue:" << endl;
	queue.print();

	emptyList.deleteQueue(); // лист удаляется автоматически, и без этого


	cout << "\n //////////////////  3  //////////////////" << endl;
	cout << " добавление элементов на позиции 2, 6, 4" << endl;
	queue.addKElements(3,
		"newData1", 2,
		"newData2", 6,
		"newData3", 4
	);
	queue.print();

	cout << " удаление элементов на позициях 3, 1, 5" << endl;
	queue.delKElements(3, 3, 1, 5);
	queue.print();

	cout << " //////////////////  7  //////////////////" << endl;
	queue.saveInFile("myQueue.txt");
	cout << "     queue:" << endl;
	queue.deleteQueue();
	queue.print();

	cout << " //////////////////  9  //////////////////" << endl;
	queue.loadFromFileOverwriting("myQueue.txt");
	cout << "     queue:" << endl;
	queue.print();


	cout << " ////////////////// 1 0 //////////////////" << endl;
	queue.deleteQueue();

}