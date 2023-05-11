#include <iostream>
#include "linkedlist.cpp"

struct HashTable {
    int MAX_LENGTH;
    int MAX_CHAIN_LENGTH;
    LinkedList* password;

    HashTable(int MAX_LENGTH, int MAX_CHAIN_LENGTH) : MAX_LENGTH(MAX_LENGTH), MAX_CHAIN_LENGTH(MAX_CHAIN_LENGTH),
    password(new LinkedList[MAX_LENGTH]) {}

    int hashFunction(std::string userName) {
        int sum = 0;

        for(char c : userName){
            sum += int(c);
        }
        return sum % MAX_LENGTH;
    }

    bool isFull() {
        for (int i = 0; i < MAX_LENGTH; i++) {
            if(password[i].length < MAX_CHAIN_LENGTH) {
                return false;
            }
        }
        return true;
    }
    bool isSlotEmpty(int slotIndex) {
        if(password[slotIndex].head == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    void insert(std::string userName, std::string userPassword) {
        int hashValue = hashFunction(userName);

        if(password[hashValue].length < MAX_CHAIN_LENGTH) {
            password[hashValue].insert(userName, userPassword);

        }
        else {
            std::cout << "Linked List has reached MAX CAP!" << std::endl;
        }
    }

    void printHashtable() {
        for(int i = 0; i < MAX_LENGTH; i++){
            std::cout << "[" << i << "]-->";
            password[i].printList();
        }
    }

    void lookup(std::string userName) {
        int hashValue = hashFunction(userName);

        if (isSlotEmpty(hashValue)) {
            std::cout << "User not found!" << std::endl;
        }
        else {
            password[hashValue].search(userName);
        }
    }
};

int main() {
    auto* table = new HashTable(4, 2);

    std::cout << table->isFull() << std::endl;

    int command=0;
    std::string userName;
    std::string password;
    while (command != -1) {
        std::cout << "Enter command: ";
        std::cin >> command;
        switch (command) {
            case 1:
                // Insertion
                std::cout << "Enter user name: ";
                std::cin >> userName;
                std::cout << "Enter password: ";
                std::cin >> password;

                table->insert(userName,password);
                break;
            case 2:
                // Lookup for password
                std::cout << "Enter user name to look up password: ";
                std::cin >> userName;
                table->lookup(userName);
                break;
            case 3:
                // Print hashtable
                table->printHashtable();
                break;
            case -1:
                std::cout << "Exiting..." << std::endl;
                break;

        }

    }
    return 0;
}
