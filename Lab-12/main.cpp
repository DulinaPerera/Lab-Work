#include <iostream>
#include <limits>
#include <vector>

const int INF = std::numeric_limits<int>::max();

struct Vertex {
    int label;                  // Label of the vertex
    int shortestPathEstimate;   // Shortest path estimate from the source vertex
    int parentLabel;            // Label of the parent vertex in the shortest path

    /**
     * Constructor for Vertex
     * @param label The label of the vertex
     */
    explicit Vertex(int label) : label(label), shortestPathEstimate(INF), parentLabel(-1) {}

    /**
     * Less than (<) operator overload
     * @param other The other Vertex object to compare with
     * @return True if the shortestPathEstimate of this vertex is less than the other vertex
     */
    bool operator<(const Vertex& other) const {
        return shortestPathEstimate < other.shortestPathEstimate;
    }

    /**
     * Less than or equal to (<=) operator overload
     * @param other The other Vertex object to compare with
     * @return True if the shortestPathEstimate of this vertex is less than or equal to the other vertex
     */
    bool operator<=(const Vertex& other) const {
        return shortestPathEstimate <= other.shortestPathEstimate;
    }

    /**
     * Greater than (>) operator overload
     * @param other The other Vertex object to compare with
     * @return True if the shortestPathEstimate of this vertex is greater than the other vertex
     */
    bool operator>(const Vertex& other) const {
        return shortestPathEstimate > other.shortestPathEstimate;
    }

    /**
     * Greater than or equal to (>=) operator overload
     * @param other The other Vertex object to compare with
     * @return True if the shortestPathEstimate of this vertex is greater than or equal to the other vertex
     */
    bool operator>=(const Vertex& other) const {
        return shortestPathEstimate >= other.shortestPathEstimate;
    }

    /**
     * Equality (==) operator overload
     * @param other The other Vertex object to compare with
     * @return True if the shortestPathEstimate of this vertex is equal to the other vertex
     */
    bool operator==(const Vertex& other) const {
        return shortestPathEstimate == other.shortestPathEstimate;
    }

    /**
     * Inequality (!=) operator overload
     * @param other The other Vertex object to compare with
     * @return True if the shortestPathEstimate of this vertex is not equal to the other vertex
     */
    bool operator!=(const Vertex& other) const {
        return shortestPathEstimate != other.shortestPathEstimate;
    }
};

class MinHeap {
private:
    int heapSize;                     // Current heap size of the heap

public:
    std::vector<Vertex*> heap;        // Vector to store pointers to the heap elements

    /**
     * Heap constructor
     */
    MinHeap() : heapSize(0) {}

    /**
     * Returns the current heap size.
     *
     * @returns Current heap size
     */
    [[nodiscard]] int getSize() const {
        return heapSize;
    }

    /**
     * Checks if the heap is empty.
     *
     * @returns True if the heap is empty, false otherwise.
     */
    [[nodiscard]] bool isEmpty() const {
        return heapSize == 0;
    }

    /**
     * Given an index in the heap, retains heap property in the tree rooted at that index.
     *
     * @param parentIndex The index of the parent element
     */
    void heapify(int parentIndex) {
        // Calculate the indices of the left child & the right child.
        const int leftChildIndex = 2 * parentIndex + 1, rightChildIndex = leftChildIndex + 1;
        int indexOfSmallest;

        if (leftChildIndex < this->heapSize && *this->heap[parentIndex] > *this->heap[leftChildIndex]) {
            indexOfSmallest = leftChildIndex;
        } else {
            indexOfSmallest = parentIndex;
        }

        if (rightChildIndex < this->heapSize && *this->heap[indexOfSmallest] > *this->heap[rightChildIndex]) {
            indexOfSmallest = rightChildIndex;
        }

        if (indexOfSmallest != parentIndex) {
            std::swap(this->heap[parentIndex], this->heap[indexOfSmallest]);
            heapify(indexOfSmallest);
        }
    };

    /**
     * Inserts a new pointer into the heap.
     *
     * @param pointer A pointer to the new element to be inserted into the heap
     */
    void insert(Vertex* pointer) {
        // Add the pointer to the end of the heap.
        this->heap.push_back(pointer);
        // Increment 'heapSize' by 1.
        this->heapSize++;

        int indexOfPointer = this->heapSize - 1; // Index of the new pointer

        // Perform "swim up" operation to maintain the min heap property.
        while (indexOfPointer > 0) {
            int parentIndex = (indexOfPointer - 1) / 2; // Index of the parent

            // If the new element is smaller than its parent, swap the pointers & update the index of the new pointer.
            if (*pointer < *this->heap[parentIndex]) {
                std::swap(this->heap[indexOfPointer], this->heap[parentIndex]);
                indexOfPointer = parentIndex;
            }
                // Otherwise, stop the loop.
            else {
                break;
            }
        }
    };

    /**
     * Removes the pointer at the heap root.
     *
     * @return The pointer to the root element that was removed from the heap
     */
    Vertex* remove() {
        if (this->isEmpty()) {
            throw std::runtime_error("Heap is empty!");
        } else {
            std::swap(this->heap[0], this->heap[this->heapSize - 1]);

            Vertex* removed = this->heap.back();
            this->heap.pop_back();
            this->heapSize--;

            heapify(0);
            return removed;
        }
    };
};

void dijkstra(const std::vector<std::vector<int>>& cityGraph, int source) {
    std::size_t cityCount = cityGraph.size();
    Vertex* cities[cityCount];

    // Create vertices for each city and initialize shortest path estimates
    for (int i = 0; i < cityCount; i++) {
        cities[i] = new Vertex(i);
    }
    cities[source]->shortestPathEstimate = 0;

    MinHeap* minHeap = new MinHeap();

    // Insert all vertices into the min heap
    for (int i = 0; i < cityCount; i++) {
        minHeap->insert(cities[i]);
    }

    // Dijkstra's algorithm
    while (!minHeap->isEmpty()) {
        int u = minHeap->remove()->label;

        // Update the shortest path estimates for neighboring cities
        for (int i = 0; i < cityCount; i++) {
            if (cityGraph[u][i] != 0) {
                if (cities[i]->shortestPathEstimate > cities[u]->shortestPathEstimate + cityGraph[u][i]) {
                    cities[i]->shortestPathEstimate = cities[u]->shortestPathEstimate + cityGraph[u][i];
                    cities[i]->parentLabel = u;
                }
            }
        }
        minHeap->heapify(0);
    }

    // Print shortest paths from source city to all other cities
    for (int i = 0; i < cityCount; i++) {
        if (i != source) {
            printf("Shortest time from city_%d to city_%d is %d units along %d", source, i,
                   cities[i]->shortestPathEstimate, source);

            int j = i;
            std::string path = "";

            // Construct the shortest path
            while (cities[j]->parentLabel != -1) {
                path += std::to_string(j) + " >- ";
                j = cities[j]->parentLabel;
            }
            std::reverse(path.begin(), path.end());
            std::cout << path << ".\n";
        }
    }
}

int main() {
    std::vector<std::vector<int>> cityGraph = {
            {0, 10, 0, 0, 15, 5},
            {10, 0, 10, 30, 0, 0},
            {0, 10, 0, 12, 5, 0},
            {0, 30, 12, 0, 0, 20},
            {15, 0, 5, 0, 0, 0},
            {5, 0, 0, 20, 0, 0},
    };

    // Run Dijkstra's algorithm for each city in the graph
    for (int i = 0; i < cityGraph.size(); i++) {
        dijkstra(cityGraph, i);
        std::cout << '\n';
    }
}
