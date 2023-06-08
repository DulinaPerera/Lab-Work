#include <iostream>
#include <limits>
#include <vector>

// Define the maximum value for an integer.
const int INF = std::numeric_limits<int>::max();

// Represents a vertex in the graph.
struct Vertex {
    int label;          // The label of the vertex

    int key;            // The key value used in Prim's algorithm
    int parentLabel;    // The label of the parent vertex in the minimum spanning tree
    bool isIn;          // Flag indicating whether the vertex is in the min-priority queue

    /**
     * Vertex constructor
     *
     * @param label The label of the vertex
     */
    explicit Vertex(int label) : label(label), key(INF), parentLabel(-1) {}

    /**
     * Overloaded 'less than' operator
     *
     * @param other The other Vertex to compare with
     * @return True if the key of this vertex is less than that of the other vertex.
     */
    bool operator<(const Vertex& other) const {
        return key < other.key;
    }

    /**
     * Overloaded 'less than or equal to' operator
     *
     * @param other The other Vertex object to compare with
     * @return True if the key of this vertex is less than or equal to that of the other vertex
     */
    bool operator<=(const Vertex& other) const {
        return key <= other.key;
    }

    /**
     * Overloaded 'greater than' operator
     *
     * @param other The other Vertex object to compare with
     * @return True if the key of this vertex is greater than that of the other vertex
     */
    bool operator>(const Vertex& other) const {
        return key > other.key;
    }

    /**
     * Overloaded 'greater than or equal to' operator
     *
     * @param other The other Vertex object to compare with
     * @return True if the key of this vertex is greater than or equal to that of the other vertex
     */
    bool operator>=(const Vertex& other) const {
        return key >= other.key;
    }

    /**
     * Overloaded 'equality' operator
     *
     * @param other The other Vertex object to compare with
     * @return True if the key of this vertex is equal to that of the other vertex
     */
    bool operator==(const Vertex& other) const {
        return key == other.key;
    }

    /**
     * Overloaded 'inequality' operator
     *
     * @param other The other Vertex object to compare with
     * @return True if the key of this vertex is not equal to that of the other vertex
     */
    bool operator!=(const Vertex& other) const {
        return key != other.key;
    }
};

// Implements a min heap.
class MinHeap {
private:
    std::vector<Vertex*>* heap;      // Vector to store heap elements
    int heapSize;                   // Size of the heap
public:
    // Min heap constructor
    MinHeap() : heap(new std::vector<Vertex*>()), heapSize(0) {}

    // Min heap Destructor
    ~MinHeap() {
        heap->clear();
        delete heap;
    }

    /**
     * Returns the size of the heap.
     *
     * @return The size of the heap
     */
    [[nodiscard]] int getSize() const {
        return heapSize;
    }

    /**
     * Checks if the heap is empty.
     * @return True if the heap is empty, false otherwise.
     */
    [[nodiscard]] bool isEmpty() const {
        return heapSize == 0;
    }

    /**
     * Performs the heapify operation at the given rootIndex to maintain the min heap property of the subtree rooted there.
     *
     * @param rootIndex The index of the subtree root
     */
    void heapify(int rootIndex) {
        // Calculate the indices of the left child and the right child.
        const int leftChildIndex = 2 * rootIndex + 1;
        const int rightChildIndex = leftChildIndex + 1;
        int indexOfSmallest;

        // Find the index of the smallest element amongst the parent, left child, and right child.
        if (leftChildIndex < this->heapSize && *(*this->heap)[rootIndex] > *(*this->heap)[leftChildIndex]) {
            indexOfSmallest = leftChildIndex;
        }
        else {
            indexOfSmallest = rootIndex;
        }

        if (rightChildIndex < this->heapSize && *(*this->heap)[indexOfSmallest] > *(*this->heap)[rightChildIndex]) {
            indexOfSmallest = rightChildIndex;
        }

        // If the smallest element is not the parent, swap the parent with the smallest element and recursively heapify.
        if (indexOfSmallest != rootIndex) {
            std::swap((*this->heap)[rootIndex], (*this->heap)[indexOfSmallest]);
            heapify(indexOfSmallest);
        }
    };

    /**
     * Inserts a new element into the heap.
     *
     * @param pointer Pointer to the new element
     */
    void insert(Vertex* pointer) {
        // Add the pointer to the end of the heap.
        this->heap->push_back(pointer);
        // Increment heap size by 1.
        this->heapSize++;

        int indexOfPointer = this->heapSize - 1; // Index of the new pointer

        // Perform "swim up" operation to maintain the min heap property.
        while (indexOfPointer > 0) {
            int parentIndex = (indexOfPointer - 1) / 2; // Index of the parent

            // If the new element is smaller than its parent, swap the pointers and update the index of the new pointer.
            if (*pointer < *(*this->heap)[parentIndex]) {
                std::swap((*this->heap)[indexOfPointer], (*this->heap)[parentIndex]);
                indexOfPointer = parentIndex;
            }
                // Otherwise, stop the loop.
            else {
                break;
            }
        }
    };

    /**
     * Removes the minimum element of the heap.
     *
     * @return Pointer to the minimum element
     */
    Vertex* remove() {
        if (this->isEmpty()) {
            throw std::runtime_error("Heap is empty!");
        }
        else {
            // Swap the root (minimum) element with the last element.
            std::swap((*this->heap)[0], (*this->heap)[this->heapSize - 1]);

            // Get the removed element.
            Vertex* removed = this->heap->back();
            // Remove the last element from the heap.
            this->heap->pop_back();
            // Decrement the heap size by 1.
            this->heapSize--;

            // Perform heapify to restore the min heap property.
            heapify(0);

            return removed;
        }
    };
};

// Prim's algorithm for finding the minimum spanning tree
void prim(int** wireLengths, int poleCount, int source) {
    Vertex* poles[poleCount];

    // Create vertices for each pole and initialize their properties
    for (int i = 0; i < poleCount; i++) {
        poles[i] = new Vertex(i);
    }
    poles[source]->key = 0;

    MinHeap* minHeap = new MinHeap();
    for (int i = 0; i < poleCount; i++) {
        minHeap->insert(poles[i]);
        poles[i]->isIn = true;
    }

    // Perform Prim's algorithm
    while (!minHeap->isEmpty()) {
        int u = minHeap->remove()->label;
        poles[u]->isIn = false;

        for (int i = 0; i < poleCount; i++) {
            if (wireLengths[u][i] != 0) {
                if (poles[i]->isIn && wireLengths[u][i] < poles[i]->key) {
                    poles[i]->parentLabel = u;
                    poles[i]->key = wireLengths[u][i];
                }
            }
        }

        for (int i = minHeap->getSize() / 2; i >= 0; i--) {
            minHeap->heapify(i);
        }
    }

    // Print the minimum spanning tree edges
    std::cout << "Label\t" << "Parent label\t" << "Edge Weight" << std::endl;
    for (int i = 0; i < poleCount; i++) {
        if (i == source) {
            std::cout << i << "\tNIL\t\t" << 0 << std::endl;
        } else {
            std::cout << i << '\t' << poles[i]->parentLabel << "\t\t" << poles[i]->key << std::endl;
        }
    }

    delete minHeap;
}

int main() {
    int poleCount = 6;
    int** wireLengths = new int*[poleCount];
    wireLengths[0] = new int[poleCount]{0, 3, 0, 0, 0, 1};
    wireLengths[1] = new int[poleCount]{3, 0, 2, 1, 10, 0};
    wireLengths[2] = new int[poleCount]{0, 2, 0, 3, 0, 5};
    wireLengths[3] = new int[poleCount]{0, 1, 3, 0, 5, 0};
    wireLengths[4] = new int[poleCount]{0, 10, 0, 5, 0, 4};
    wireLengths[5] = new int[poleCount]{1, 0, 5, 0, 4, 0};

    for (int source = 0; source < poleCount; source++) {
        prim(wireLengths, poleCount, source);
        std::cout << '\n';
    }

    // Free the memory for wireLengths
    for (int i = 0; i < poleCount; i++) {
        delete[] wireLengths[i];
    }
    delete[] wireLengths;

    return 0;
}
