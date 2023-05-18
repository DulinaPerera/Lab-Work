#include <iostream>
#include <list>

/**
 * This structure represents a vertex in a graph.
 *
 * @struct Vertex
 *
 * @brief This structure represents a vertex in a graph.
 *
 * @memberof Graph
 *
 * @var label The label of the vertex
 * @var neighbours The list of vertices that are neighbours of this vertex
 */
struct Vertex {
    int label; // The label of the vertex
    std::list<int>* neighbours; // The list of vertices that are neighbours of this vertex

    // This is the default constructor for the vertex structure.
    Vertex() = default;
    // This constructor creates a vertex structure with the specified label and the list of neighbours.
    Vertex(int label, std::list<int>* neighbours) : label(label), neighbours(neighbours) {}
};

/**
 * This structure represents a graph.
 *
 * @struct Graph
 *
 * @brief This structure represents a graph.
 *
 * @var verticesCount The number of vertices in the graph
 * @var vertices The array of vertices
 *
 * @func intializeVertices This function initializes the vertices in the graph.
 * @func addEdge This function adds an edge between the specified vertices.
 * @func print This function prints the graph.
 */
struct Graph {
    const int verticesCount; // The number of vertices in the graph
    Vertex* vertices; // The array of vertices

    // This constructor creates a Graph struct with the specified number of vertices.
    explicit Graph(const int verticesCount) : verticesCount(verticesCount), vertices(new Vertex[verticesCount]) {
        intializeVertices();
    }

    // This function initializes the vertices in the graph.
    void intializeVertices() const {
        for (int i = 1; i <= verticesCount; i++) {
            vertices[i - 1].label = i;
            vertices[i - 1].neighbours = new std::list<int>();
        }
    }

    // This function adds an edge between the specified vertices.
    void addEdge(const int u, const int v) const {
        vertices[u - 1].neighbours->push_back(v);
        vertices[v - 1].neighbours->push_back(u);
    }

    // This function prints the graph.
    void print() const {
        for (int i = 0; i < verticesCount; i++) {
            std::cout << vertices[i].label << " --> ";

            for (int& neighbour : *vertices[i].neighbours) {
                std::cout << neighbour << ' ';
            }
            std::cout << '\n';
        }
    }
};

// This is the main function of the program.
int main() {
    // Create a new graph with 8 vertices.
    auto* g = new Graph(8);

    // Add edges to the graph.
    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(1, 4);
    g->addEdge(1, 5);
    g->addEdge(2, 3);
    g->addEdge(2, 6);
    g->addEdge(4, 6);
    g->addEdge(4, 7);
    g->addEdge(4, 8);
    g->addEdge(5, 6);
    g->addEdge(5, 7);
    g->addEdge(5, 8);

    // Print the graph.
    g->print();

    // Delete the graph.
    delete g;
    return 0;
}
