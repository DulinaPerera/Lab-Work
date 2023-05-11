#include <string>
#include <iostream>

struct HashTable {
    int MAX_LENGTH;
    std::string* password;

    explicit HashTable(int maxLength) : MAX_LENGTH(maxLength), password(new std::string[MAX_LENGTH]) {
        for (int i = 0; i < MAX_LENGTH; i++){
            password[i].clear();
        }
    }
    ~HashTable() {
        delete[] password;
    }

    [[nodiscard]] int hashFunction(const std::string& userName) const {
        int sum = 0;

        for (char c : userName) {
            sum += int(c);
        }
        return sum % MAX_LENGTH;
    }

    [[nodiscard]] bool isFull() const {
        bool isFull = true;
        int count = 0;
        for (int i = 0; i < MAX_LENGTH; i++) {
            if(password[i].empty()){
                isFull = false;
                break;
            }
        }
        return isFull;
    }
    [[nodiscard]] bool isSlotEmpty(int slotIndex) const {
        return password[slotIndex].empty();
    }

    void insertPair(const std::string& userName, const std::string& userPassword) const {
        int hashValue = hashFunction(userName);

        if (!isSlotEmpty(hashValue)) {
            std::cout << "Enter a different username." << std::endl;
        }
        else {
             password[hashValue] = userName + '\t' + userPassword;
        }
    }
    void deletePair(const std::string& userName) const {
        int hashValue = hashFunction(userName);

        if(isSlotEmpty(hashValue)) {
            std::cout << "User not found!" << std::endl;
        }
        else {
            size_t tabPosition = password[hashValue].find('\t');

            std::string retrievedUserName = password[hashValue].substr(0, tabPosition);
            if (userName != retrievedUserName) {
                std::cout << "Wrong username!" << std::endl;
            }

            password[hashValue].clear();
            std::cout << "User deleted." << std::endl;
        }

    }

    void lookup(const std::string& userName) const {
        int hashValue = hashFunction(userName);

        if (isSlotEmpty(hashValue)) {
            std::cout << "User not found!" << std::endl;
        }
        else {
            size_t tabPosition = password[hashValue].find('\t');

            std::string retrievedUserName = password[hashValue].substr(0, tabPosition);
            if (userName != retrievedUserName) {
                std::cout << "Wrong username!" << std::endl;
            }

            std::string retrievedPassword = password[hashValue].substr(tabPosition + 1);
            std::cout << "Password:" << retrievedPassword << std::endl;
        }
    }

    void printHashtable() const {
        for(int i = 0; i < MAX_LENGTH; i++) {
            std::string pair = password[i];

            if (pair.empty()) {
                std::cout << "[" << i << "]-->" << "NULL" << std::endl;
            }
            else {
                std::cout << "[" << i << "]-->" << password[i] << std::endl;
            }
        }
    }
};

/*int main() {
    auto* table = new HashTable(4);

    std::cout << table->isFull() << std::endl;

    int command = 0;
    std::string userName;
    std::string password;
    while (command != -1) {
        std::cout << "Enter command: ";
        std::cin >> command;
        switch (command) {
            case 1:
                // Insertion
                std::cout << "Enter userName: ";
                std::cin >> userName;
                std::cout << "Enter password: ";
                std::cin >> password;

                table->insertPair(userName, password);
                break;
            case 2:
                // Deletion
                std::cout << "Enter item to be deleted: ";
                std::cin >> userName;
                table->deletePair(userName);
                break;
            case 3:
                // Lookup for password
                std::cout << "Enter user name to look up password:";
                std::cin >> userName;
                table->lookup(userName);
                break;
            case 4:
                // Print hashtable
                table->printHashtable();
                break;
            case -1:
                std::cout << "Exiting...\n";
                break;

        }
    }
    return 0;
}*/

