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

/**
 * Performs a sift down operation to maintain the heap property at a given index.
 *
 * @param array Array of integers
 * @param arraySize Size of the array
 * @param root Index of the root of the subtree which has to be converted to a heap
 */
void heapify(int array[], const int arraySize, const std::size_t root) {
    const std::size_t left = 2 * root + 1, right = left + 1;
    std::size_t largest; // Index of the largest amongst the elements at "root", "left" & "right" indices

    // Determine the largest element amongst the root element, left child element & right child element.
    if (left < arraySize && array[root] < array[left]) {
        largest = left;
    }
    else {
        largest = root;
    }
    if (right < arraySize && array[largest] < array[right]) {
        largest = right;
    }

    // If the largest element is not at the root, swap the root element with the largest element.
    // Heapify the affected subtree.
    if (largest != root) {
        std::swap(array[root], array[largest]);
        heapify(array, arraySize, largest);
    }
}
/**
 * Builds a max heap from a given array of integers.
 *
 * @param array Array of integers
 * @param arraySize Size of the array
 */
void buildHeap(int array[], const int arraySize) {
    // Heapify all non-leaf nodes in the array.
    for (int i = (arraySize / 2) - 1; i >= 0; i--) {
        heapify(array, arraySize, i);
    }
}

/**
 * Sorts a given array of integers using the heap sort algorithm.
 *
 * @param array Array to be sorted
 * @param arraySize Size of the array
*/
void heapSort(int array[], int arraySize) {
    // Build a max heap from the array.
    buildHeap(array, arraySize);

    // Extract elements one by one from the heap.
    // Heapify the remaining elements.
    for (int i = arraySize - 1; i >= 1; i--) {
        std::swap(array[0], array[i]);

        heapify(array, i, 0);
    }
}

int main() {
    int* array = nullptr;
    int arraySize = 0;
    int userInput;

    // Prompt the user to enter integers seperated by whitespaces and read them until an invalid input is provided.
    std::cout << "Enter integers: ";
    while (std::cin >> userInput) {
        int* temp = new int[arraySize + 1];

        for (int i = 0; i < arraySize; i++) {
            temp[i] = array[i];
        }
        temp[arraySize++] = userInput;
        delete array;
        array = temp;
    }

    // Display the array before sorting.
    std::cout << "Input array: " << std::endl;
    displayArray(array, arraySize);

    // Sort the array using heap sort algorithm.
    heapSort(array, arraySize);

    // Display the sorted array.
    std::cout << "Sorted array: "<< std::endl;
    displayArray(array, arraySize);
}
