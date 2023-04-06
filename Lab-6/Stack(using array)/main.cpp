#include <chrono>
#include <iostream>
using namespace std;

template<typename T>
class Stack {
    private:
        int top;
        int capacity;
        T *array;

    public:
        explicit Stack(int capacity) : top(-1), capacity(capacity){
            array = new T[capacity];
        }

        void display() {
            if (!isEmpty()) {
                cout << '[';
                for (int i = top; i > 0; i--) {
                    cout << array[i] << ", ";
                }
                cout << array[0] << ']' << endl;
            }
        }
        T stackTop() {
            if (isEmpty()) {
                throw out_of_range("Stack is empty.");
            }
            else {
                return array[top];
            }
        }
        bool isEmpty() {
            return top == -1;
        };
        bool isFull() {
            return top == capacity - 1;
        }

        void push(T key) {
            if (isFull()) {
                throw runtime_error("Stack is full.");
            }
            else {
                array[++top] = key;
            }
        }
        T pop() {
            if (isEmpty()) {
                throw out_of_range("Stack is empty");
            }
            else {
                return array[top--];
            }
        }

        ~Stack() {
            delete[] array;
        }
};

int main() {
    Stack<int> testStack(100);

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
