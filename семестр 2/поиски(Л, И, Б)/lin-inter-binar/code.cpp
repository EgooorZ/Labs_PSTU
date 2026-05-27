#include <iostream>
#include <string>

using namespace std;

int linearSubstringSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return 0;
    if (m > n) return -1;

    bool found;
    for (int i = 0; i <= n - m; i++) {
        found = true;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}


bool isSuffixLess(string text, int next, int cur) {
    int n = text.length();

    while (next < n && cur < n) {
        if (text[next] != text[cur]) {
            return text[next] < text[cur];
        }
        next++;
        cur++;
    }

    return next == n && cur < n;
}
void bubleSort(int* suffixArray, int n, string text) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (isSuffixLess(text, suffixArray[j + 1], suffixArray[j])) {
                int temp = suffixArray[j];
                suffixArray[j] = suffixArray[j + 1];
                suffixArray[j + 1] = temp;
            }
        }
    }
}
int binarySubstringSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return 0;
    if (m > n) return -1;

    int* suffixArray = new int[n];
    for (int i = 0; i < n; i++) {
        suffixArray[i] = i;
    }

    bubleSort(suffixArray, n, text);

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int suffixIdx = suffixArray[mid];

        bool equal = true;
        bool less = false;

        for (int j = 0; j < m; j++) {
            if (suffixIdx + j >= n) {
                equal = false;
                less = true;
                break;
            }

            if (pattern[j] != text[suffixIdx + j]) {
                equal = false;
                if (pattern[j] < text[suffixIdx + j]) {
                    less = true;
                }
                break;
            }
        }

        if (equal) {
            delete[] suffixArray;
            return suffixIdx;
        }

        if (less) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    delete[] suffixArray;
    return -1;
}


int interpolationSearch(int* arr, int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            return (arr[low] == target) ? low : -1;
        }

        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        if (pos < low || pos > high) return -1;

        if (arr[pos] == target) {
            return pos;
        }

        if (arr[pos] < target) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }

    return -1;
}


int main() {
    setlocale(LC_ALL, "ru");

    string text = "hello world, hello C++";

    cout << linearSubstringSearch(text, "world") << endl;
    cout << binarySubstringSearch(text, "hello") << endl;

    const int size = 10;
    int numbers[size] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

    cout << interpolationSearch(numbers, size, 20);

    return 0;
}