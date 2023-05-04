#include <iostream>

/**
 * Displays the elements of an array.
 *
 * @param array Array of integers
 * @param arraySize Size of the array
 */
void displayArray(int array[], int arraySize) {
    for (std::size_t i = 0; i < arraySize; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

void heapify(int array[], const int arraySize, const std::size_t root) {
    const std::size_t left = 2 * root + 1, right = left + 1;
    int largest; // Index of the largest amongst "root", "left" & "right"

    if (left < arraySize && array[root] < array[left]) {
        largest = left;
    }
    else {
        largest = root;
    }

    if (right < arraySize && array[largest] < array[right]) {
        largest = right;
    }

    if (largest != root) {
        std::swap(array[root], array[largest]);
        heapify(array, arraySize, largest);
    }
}
void buildHeap(int arr[], const int n) {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void heapSort(int arr[], int n) {
    buildHeap(arr, n);

    for (int i = n - 1; i >= 1; i--) {
        std::swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

int main() {
    int* heap = nullptr;
    int heapSize = 0;
    int userInput;

    std::cout << "Enter integers: ";
    while (std::cin >> userInput) {
        int* temp = new int[heapSize + 1];

        for (int i = 0; i < heapSize; i++) {
            temp[i] = heap[i];
        }
        temp[heapSize++] = userInput;
        delete heap;
        heap = temp;
    }

    std::cout << "Input array: " << std::endl;
    displayArray(heap,heapSize);

    heapSort(heap, heapSize);

    std::cout << "Sorted array: "<< std::endl;
    displayArray(heap, heapSize);
}
