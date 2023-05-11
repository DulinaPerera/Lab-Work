#include <iostream>
#include <utility>
#include "LinkedList.h"

struct Node {
    std::string userName;
    std::string password;
    Node* link;

    Node(std::string userName, std::string password) : userName(std::move(userName)), password(std::move(password)), link(nullptr) {}
};

struct LinkedList {
    struct Node* head;
    struct Node* tail;
    int length;

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~LinkedList() {
        Node* temp = head;
        Node* next;

        while (temp != nullptr) {
            next = temp->link;
            delete temp;
            temp = next;
        }
    }

    void insert(const std::string& userName, const std::string& password) {
        auto* temp = new Node(userName, password);

        if (head == nullptr) {
            head = temp;
            tail = temp;
        }
        else {
            tail->link = temp;
        }
        length++;
    }

    void search(const std::string& userName) const {
        struct Node* temp = head;

        while (temp) {
            if (temp->userName == userName) {
                std::cout << "Password: " << temp->password << std::endl;
                return;
            }
            else {
                temp = temp->link;
            }
        }
        std::cout << "Username not found!" << std::endl;
    }

    void printList() const {
        if (head == nullptr) {
            std::cout << "[]" << std::endl;
        }
        else{
            struct Node* temp = head;

            std::cout<< "[";
            while (temp->link != nullptr) {
                std::cout << temp->userName << ", ";
                temp = temp->link;
            }
            std::cout << temp->userName << "]"<< std::endl;
        }
    }
};
