#include <iostream>

using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void bucketSort(int arr[], int n) {
    if (n <= 1) return;

    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int bucketCount = n;
    int range = (maxVal - minVal) / bucketCount + 1;

    int** buckets = new int* [bucketCount];
    int* bucketSizes = new int[bucketCount]();

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        int bucketIndex = (arr[i] - minVal) / range;
        if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0) {
            quickSort(buckets[i], 0, bucketSizes[i] - 1);
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }
        delete[] buckets[i];
    }

    delete[] buckets;
    delete[] bucketSizes;
}

void countingSort(int arr[], int n) {
    if (n <= 1) return;

    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int* count = new int[maxVal + 1]();

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    int* output = new int[n];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

void draw(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    const int n = 7;

    int arr1[n] = { 64, 34, 25, 12, 22, 11, 90 };
    draw(arr1, n);

    quickSort(arr1, 0, n - 1);
    draw(arr1, n);
    cout << endl << endl;



    int arr2[n] = { 38, 27, 43, 3, 9, 82, 10 };
    draw(arr2, n);

    mergeSort(arr2, 0, n - 1);
    draw(arr2, n);
    cout << endl << endl;



    int arr3[n] = { 42, 32, 33, 52, 37, 47, 51 };
    draw(arr3, n);

    bucketSort(arr3, n);
    draw(arr3, n);
    cout << endl << endl;



    int arr4[n] = { 4, 2, 2, 8, 3, 3, 1 };
    draw(arr4, n);

    countingSort(arr4, n);
    draw(arr4, n);
    cout << endl << endl;


    return 0;
}