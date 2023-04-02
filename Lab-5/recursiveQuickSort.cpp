#include <chrono>
#include <iostream>
#include <random>
using namespace std;

int partition(int* pointerToArray, int startIndex, int endIndex) {
    int pivot = pointerToArray[endIndex], firstSubArrayEndIndex = startIndex - 1;

    for (int j = startIndex; j < endIndex; j++) {
        if (pointerToArray[j] <= pivot) {
            firstSubArrayEndIndex++;
            swap(pointerToArray[firstSubArrayEndIndex], pointerToArray[j]);
        }
    }
    swap(pointerToArray[firstSubArrayEndIndex + 1], pointerToArray[endIndex]);

    return firstSubArrayEndIndex + 1;
}

void quickSort(int* pointerToArray, int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int median = partition(pointerToArray, startIndex, endIndex);
        quickSort(pointerToArray, startIndex, median - 1);
        quickSort(pointerToArray, median + 1, endIndex);
    }
}

int main() {
    random_device randomDevice;
    mt19937 engine(randomDevice());
    uniform_int_distribution<> element(0, 1000);

    int arrayLength = 100;
    int* pointerToArray = new int[arrayLength];
    for (int i = 0; i < arrayLength; i++) {
        pointerToArray[i] = element(engine);
    }

    cout << "Unsorted Array: [";
    for (int i = 0; i < arrayLength - 1; i++) {
        cout << pointerToArray[i] << ", ";
    }
    cout << pointerToArray[arrayLength - 1] << ']' << "\n\n";

    auto start = chrono::high_resolution_clock::now();

    quickSort(pointerToArray, 0, arrayLength - 1);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Sorted Array: [";
    for (int i = 0; i < arrayLength - 1; i++) {
        cout << pointerToArray[i] << ", ";
    }
    cout << pointerToArray[arrayLength - 1] << ']' << '\n';

    cout << "Time taken by the algorithm is " << duration << " microseconds." << endl;
    return 0;
}
