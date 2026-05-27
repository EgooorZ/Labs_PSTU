#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void upperFib(int n, int& a, int& b) {
    while (a + b < n) {
        int temp = a;
        a = a + b;
        b = temp;
    }
}

int countSeries(fstream& A) {
    A.close();
    A.open("A.txt", ios::in);
    long long INF = 1e18;
    int current_elem, ret = 0;
    long long last = -INF;
    bool flagRead = static_cast<bool>(A >> current_elem);
    while (flagRead) {
        while (flagRead && current_elem >= last) {
            last = current_elem;
            flagRead = static_cast<bool>(A >> current_elem);
        }
        last = -INF;
        ret++;
    }
    return ret;
}

void splitFile(fstream& A, fstream& B, fstream& C, int first) {
    long long INF = 1e18;
    int counter = 0;
    bool flag = true;
    A.close();
    A.open("A.txt", ios::in);
    B.close();
    B.open("B.txt", ios::out);
    C.close();
    C.open("C.txt", ios::out);
    int current_elem;
    long long last = -INF;
    bool flagRead = static_cast<bool>(A >> current_elem);
    while (flagRead) {
        if (counter == first && first != 0) {
            first = 0;
            counter = 0;
            flag = !flag;
        }
        if (flag) {
            while (flagRead && current_elem >= last) {
                last = current_elem;
                B << current_elem << ' ';
                flagRead = static_cast<bool>(A >> current_elem);
            }
            last = -INF;
            B << '/' << ' ';
        }
        else {
            while (flagRead && current_elem >= last) {
                last = current_elem;
                C << current_elem << ' ';
                flagRead = static_cast<bool>(A >> current_elem);
            }
            last = -INF;
            C << '/' << ' ';
        }
        counter++;
    }
}

streampos Merge(fstream& A, fstream& B, fstream& C, string& big, string& lower, string& empty, int& a, int& b, int real_b, streampos s) {
    A.close();
    B.close();
    C.close();
    A.open(empty, ios::out);
    B.open(big, ios::in);
    C.open(lower, ios::in);
    C.seekg(s);
    string elementB, elementC;
    bool flagB;
    bool flagC;
    int count = 0;
    bool flagEnd = false;

    while (count < real_b && !flagEnd) {
        flagB = static_cast<bool>(B >> elementB);
        flagC = static_cast<bool>(C >> elementC);
        if (!flagB && !flagC) {
            flagEnd = true;
        }

        while (flagB && elementB != "" || flagC && elementC != "") {
            int current_elem = 0;
            bool flag = false;

            if (!flagB || elementB == "") {
                current_elem = stoi(elementC);
                flag = false;
            }
            else if (!flagC || elementC == "") {
                current_elem = stoi(elementB);
                flag = true;
            }
            else {
                if (stoi(elementB) < stoi(elementC)) {
                    current_elem = stoi(elementB);
                    flag = true;
                }
                else {
                    current_elem = stoi(elementC);
                    flag = false;
                }
            }

            if (!flagEnd) {
                A << current_elem << ' ';
                if (flag) {
                    flagB = static_cast<bool>(B >> elementB);
                }
                else {
                    flagC = static_cast<bool>(C >> elementC);
                }
            }
        }
        A << '/' << ' ';
        count++;
    }

    int temp = a;
    a = b;
    b = temp - b;
    string temp_name = big;
    big = empty;
    empty = lower;
    lower = temp_name;

    return B.tellg();
}

int main() {
    int n;
    cin >> n;

    fstream A, B, C;
    A.close();
    A.open("A.txt", ios::out);
    for (int i = 0; i < n; ++i) {
        int elem = rand() % 101;
        cout << elem << ' ';
        A << elem << ' ';
    }
    cout << '\n';

    int series = countSeries(A);
    int a = 1, b = 0;
    upperFib(series, a, b);
    int first = a - (a + b - series) / 2;
    splitFile(A, B, C, first);

    string name1 = "B.txt", name2 = "C.txt", name3 = "A.txt";
    streampos s = 0;
    int real_b = -1;

    while (a != 1 || b != 0) {
        real_b = (real_b == -1 ? series - first : b);
        s = Merge(A, B, C, name1, name2, name3, a, b, real_b, s);
    }

    A.close();
    B.close();
    C.close();

    return 0;
}