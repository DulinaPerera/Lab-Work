#include <chrono>
#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T key;
    struct Node *next;
};

template<typename T>
class Stack {
    private:
        Node<T> *top;
        int size;

    public:
        Stack() : top(nullptr), size(0){}

        void display() {
            if (top != nullptr) {
                Node<T> *iterator = top;

                cout << '[';
                while (iterator) {
                    cout << iterator->key;

                    if (iterator->next) {
                        cout << ", ";
                    }
                    iterator = iterator->next;
                }
                cout << "]\n";
            }
        }
        T stackTop() {
            if (top == nullptr) {
                throw out_of_range("Stack is empty.");
            }
            return top->key;
        }
        [[nodiscard]] bool isEmpty() const {
        return size == 0;
    }

        void push(T key) {
            try {
                auto *toPush = new Node<T>(key, top);
                top = toPush;
                size++;
            } catch (const bad_alloc& e) {
                throw runtime_error("Stack is full.");
            }
        }
        T pop() {
            if (top == nullptr) {
                throw out_of_range("Stack is empty.");
            }

            Node<T> *prevTop = top;
            T key = prevTop->key;

            top = top->next;
            delete prevTop;
            return key;
        }
};

int main() {
    Stack<int> testStack;

    auto start = chrono::high_resolution_clock::now();

    testStack.push(8);
    testStack.push(10);
    testStack.push(5);
    testStack.push(11);
    testStack.push(15);
    testStack.push(23);
    testStack.push(6);
    testStack.push(18);
    testStack.push(20);
    testStack.push(17);
    testStack.display();
    cout << testStack.pop() << endl;
    cout << testStack.pop() << endl;
    cout << testStack.pop() << endl;
    cout << testStack.pop() << endl;
    cout << testStack.pop() << endl;
    testStack.display();
    testStack.push(4);
    testStack.push(30);
    testStack.push(3);
    testStack.push(1);
    testStack.display();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    std::cout << "Time taken: " << duration << " microseconds" << std::endl;
    return 0;
}
