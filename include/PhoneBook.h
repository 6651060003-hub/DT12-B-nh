#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <string>
#include "Contact.h"

class PhoneBook {
private:
    ContactNode* head;
    ContactNode* tail;
    int size;

    // Hàm phụ trợ chuyển chuỗi về chữ thường
    std::string toLower(const std::string& str) const;

public:
    PhoneBook();
    ~PhoneBook();

    void clear();
    void addContact(const std::string& name, const std::string& phone, const std::string& email = "");
    bool deleteContact(const std::string& query);
    void displayAZ() const;
    void displayZA() const;

    // Các phương thức cho Nhánh 3 & 4 (sẽ được cài đặt ở các nhánh sau)
    ContactNode* findContact(const std::string& query);
    void searchByPrefix(const std::string& prefix) const;
    void bubbleSortByName();
    void addCallLog(const std::string& query, const std::string& timestamp, const std::string& duration, const std::string& type);
    void showCallHistory(const std::string& query);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

#endif // PHONEBOOK_H
