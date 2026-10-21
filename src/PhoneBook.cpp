#include "../include/PhoneBook.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

PhoneBook::PhoneBook() : head(nullptr), tail(nullptr), size(0) {}

PhoneBook::~PhoneBook() {
    clear();
}

void PhoneBook::clear() {
    ContactNode* current = head;
    while (current != nullptr) {
        ContactNode* temp = current;
        current = current->next;
        delete temp; // Tự động gọi ~ContactNode() để giải phóng CallLog
    }
    head = tail = nullptr;
    size = 0;
}

string PhoneBook::toLower(const string& str) const {
    string res = str;
    transform(res.begin(), res.end(), res.begin(), [](unsigned char c) { return tolower(c); });
    return res;
}

// 1. Thêm liên hệ mới (Insertion Sort tự động theo tên)
void PhoneBook::addContact(const string& name, const string& phone, const string& email) {
    ContactNode* newNode = new ContactNode(name, phone, email);

    if (head == nullptr) {
        head = tail = newNode;
        size++;
        return;
    }

    if (toLower(newNode->name) < toLower(head->name)) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        size++;
        return;
    }

    ContactNode* current = head;
    while (current->next != nullptr && toLower(current->next->name) < toLower(newNode->name)) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != nullptr) {
        current->next->prev = newNode;
    } else {
        tail = newNode;
    }
    current->next = newNode;

    size++;
}

// 2. Xóa liên hệ theo SĐT hoặc Tên
bool PhoneBook::deleteContact(const string& query) {
    ContactNode* target = findContact(query);
    if (target == nullptr) return false;

    if (target == head) head = target->next;
    if (target == tail) tail = target->prev;
    if (target->prev != nullptr) target->prev->next = target->next;
    if (target->next != nullptr) target->next->prev = target->prev;

    delete target;
    size--;
    return true;
}

// 3. Duyệt danh bạ hai chiều A-Z
void PhoneBook::displayAZ() const {
    if (head == nullptr) {
        cout << "=> Danh ba rong!\n";
        return;
    }
    cout << "\n=== DANH SÁCH LIÊN HỆ (A -> Z) ===\n";
    cout << left << setw(20) << "Ho va Ten" << setw(15) << "So Dien Thoai" << setw(25) << "Email" << endl;
    cout << string(60, '-') << endl;

    ContactNode* curr = head;
    while (curr != nullptr) {
        cout << left << setw(20) << curr->name << setw(15) << curr->phone << setw(25) << curr->email << endl;
        curr = curr->next;
    }
}

// 4. Duyệt danh bạ hai chiều Z-A
void PhoneBook::displayZA() const {
    if (tail == nullptr) {
        cout << "=> Danh ba rong!\n";
        return;
    }
    cout << "\n=== DANH SÁCH LIÊN HỆ (Z -> A) ===\n";
    cout << left << setw(20) << "Ho va Ten" << setw(15) << "So Dien Thoai" << setw(25) << "Email" << endl;
    cout << string(60, '-') << endl;

    ContactNode* curr = tail;
    while (curr != nullptr) {
        cout << left << setw(20) << curr->name << setw(15) << curr->phone << setw(25) << curr->email << endl;
        curr = curr->prev;
    }
}