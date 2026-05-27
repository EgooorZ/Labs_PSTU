#include <iostream>
#include <string>

using namespace std;

int naivniySubstringSearch(string text, string pattern) {
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

    return -1; // Не найдено
}

int main() {
    string text = "hello world, hello C++";
    
    cout << naivniySubstringSearch(text, "world");
    return 0;
}