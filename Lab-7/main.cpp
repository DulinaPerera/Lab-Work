#include <iostream>
#include <vector>


/**
 * @brief A node in a binary tree.
 *
 * This struct represents a node in a binary tree with a data field of type 'T' and pointers to the left and right child nodes.
 *
 * @tparam T The type of data stored in the node.
 */
template <typename T>
struct node {
    T data; // Data field to store 'data'.

    struct node* leftChild; // Pointer to the left child
    struct node* rightChild; // pointer to the right child

    /**
     * @brief Constructs a new node with the specified data.
     *
     * This constructor creates a new node with the specified data and null pointers to the left and right child nodes.
     *
     * @param data The data to store in the new node.
     */
    explicit node(T& data) : data(data), leftChild(nullptr), rightChild(nullptr) {}
};


/**
 * @brief Returns a pointer to the node containing the minimum value of the tree.
 *
 * This function takes a pointer to the root node of a binary search tree as input.
 * And, returns a pointer to the node containing the minimum value of the tree by traversing the tree iteratively.
 *
 * @tparam T The type of data stored in the nodes of the binary search tree
 * @param root A pointer to the root node of the binary search tree
 * @return A pointer to the node containing the minimum value of the tree
 */
template <typename T>
struct node<T>* minimum(struct node<T>* root) {
    struct node<T>* lookupNode = root; // Create a pointer pointing at the root.

    // Traverse the binary search tree till the leftmost node is found.
    while (lookupNode->leftChild) {
        lookupNode = lookupNode->leftChild;
    }
    return lookupNode; // Return a pointer to the leftmost node of the tree.
}


/**
 * @brief Performs an in-order traversal of a binary tree iteratively using a stack.
 *
 * This function takes a pointer to the root node of a binary tree as input and performs an in-order traversal of the binary tree iteratively using a stack.
 * The traversal visits the nodes of the tree in ascending order of their values.
 *
 * @tparam T The type of data stored in the nodes of the binary tree.
 * @param root A pointer to the root node of the binary tree to traverse.
 */
template <typename T>
void traverseInOrder(struct node<T> *root) {
    std::vector<struct node<T>*> nodePointers;
    struct node<T>* lookupNode = root;

    while (lookupNode != nullptr || !nodePointers.empty()) {
        while (lookupNode !=  nullptr) {
            nodePointers.push_back(lookupNode);
            lookupNode = lookupNode->leftChild;
        }

        lookupNode = nodePointers.back();
        nodePointers.pop_back();

        std::cout << lookupNode->data << ' ';

        lookupNode = lookupNode->rightChild;
    }
    std::cout << '\n';
}


/**
 * @brief Inserts a new node with the specified data into a binary tree.
 *
 * This function takes a pointer to the root node of a binary tree and a piece of data to insert as input, and inserts a new node containing the data into the binary tree. If the binary tree is empty, the new node becomes the root of the tree.
 *
 * @tparam T The type of data stored in the nodes of the binary tree.
 * @param root A pointer to the root node of the binary tree to insert into.
 * @param dataToInsert The data to store in the new node to be inserted.
 * @return A pointer to the root node of the binary tree.
 */
template <typename T>
struct node<T>* insertNode(struct node<T>* root, T dataToInsert) {
    struct node<T>* leadingPointer = root;
    struct node<T>* trailingPointer = nullptr;

    while (leadingPointer) {
        trailingPointer = leadingPointer;

        if (dataToInsert < leadingPointer->data) {
            leadingPointer = leadingPointer->leftChild;
        }
        else {
            leadingPointer = leadingPointer->rightChild;
        }
    }

    if (trailingPointer == nullptr) {
        root = new struct node<T>(dataToInsert);
    }
    else if (trailingPointer->data > dataToInsert) {
        trailingPointer->leftChild = new struct node<T>(dataToInsert);
    }
    else {
        trailingPointer->rightChild = new struct node<T>(dataToInsert);
    }
    return root;
}


/**
 * @brief Deletes a node with the specified key from a binary search tree.
 *
 * This function takes a pointer to the root node of a binary search tree and a key to delete from the tree as input. If a node with the specified key exists in the tree, it is removed from the tree and the root node of the modified tree is returned. If no node with the specified key exists in the tree, the original root node is returned.
 *
 * @tparam T The type of data stored in the nodes of the binary search tree.
 * @param root A pointer to the root node of the binary search tree.
 * @param key The key of the node to delete from the tree.
 * @return A pointer to the root node of the modified binary search tree.
 */
template <typename T>
struct node<T>* deleteNode(struct node<T> *root, int key) {
    // Case 1: The tree is empty
    if (root == nullptr) {
        return root;
    }

    // Find the node to delete
    if (key < root->data) {
        root->leftChild = deleteNode(root->leftChild, key);
    } else if (key > root->data) {
        root->rightChild = deleteNode(root->rightChild, key);
    } else {
        // Case 2: The node to be deleted has no children
        if (root->leftChild == nullptr && root->rightChild == nullptr) {
            delete root;
            root = nullptr;
        }
            // Case 3: The node to be deleted has one child
        else if (root->leftChild == nullptr) {
            struct node<T> *temp = root;
            root = root->rightChild;
            delete temp;
        }
        else if (root->rightChild == nullptr) {
            struct node<T> *temp = root;
            root = root->leftChild;
            delete temp;
        }
            // Case 4: The node to be deleted has two children
        else {
            // Find the minimum value node in the right subtree (or maximum value node in the left subtree)
            struct node<T> *temp = minimum(root->rightChild);

            // Copy the value of the minimum value node to the node to be deleted
            root->data = temp->data;

            // Delete the minimum value node
            root->rightChild = deleteNode(root->rightChild, temp->data);
        }
    }
    return root;
}


// Driver code
int main() {
    struct node<int>* root = nullptr;

    int operation;
    int operand;
    std::cin >> operation;

    while (operation != -1) {
        switch(operation) {
            case 1: // insert
                std::cin >> operand;
                root = insertNode(root, operand);
                std::cin >> operation;
                break;
            case 2: // delete
                std::cin >> operand;
                root = deleteNode(root, operand);
                std::cin >> operation;
                break;
            default:
                std::cout << "Invalid Operator!\n";
        }
    }
    traverseInOrder(root);
    return 0;
}


