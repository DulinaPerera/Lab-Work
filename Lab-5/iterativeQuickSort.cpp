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
    // Create an auxiliary stack
    int stack[endIndex - startIndex + 1];

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[++top] = startIndex;
    stack[++top] = endIndex;

    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        endIndex = stack[top--];
        startIndex = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int p = partition(pointerToArray, startIndex, endIndex);

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > startIndex) {
            stack[++top] = startIndex;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < endIndex) {
            stack[++top] = p + 1;
            stack[++top] = endIndex;
        }
    }
}

int main() {
    random_device randomDevice;
    mt19937 engine(randomDevice());
    uniform_int_distribution<> element(0, 1000);

    int arrayLength = 10000;
    int* pointerToArray = new int[arrayLength];
    for (int i = 0; i < arrayLength; i++) {
        pointerToArray[i] = element(engine);
    }

    /*cout << "Unsorted Array: [";
    for (int i = 0; i < arrayLength - 1; i++) {
        cout << pointerToArray[i] << ", ";
    }
    cout << pointerToArray[arrayLength - 1] << ']' << "\n\n";*/

    auto start = chrono::high_resolution_clock::now();

    quickSort(pointerToArray, 0, arrayLength - 1);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    /*cout << "Sorted Array: [";
    for (int i = 0; i < arrayLength - 1; i++) {
        cout << pointerToArray[i] << ", ";
    }
    cout << pointerToArray[arrayLength - 1] << ']' << '\n';*/

    cout << "Time taken by the algorithm is " << duration << " microseconds." << endl;
    return 0;
}
