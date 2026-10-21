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
// Thêm cuộc gọi mới cho một liên hệ
void PhoneBook::addCallLog(const string& phone, const string& dateTime, int duration, const string& type) {
    ContactNode* contact = findContact(phone);
    if (contact == nullptr) {
        cout << "=> Khong tim thay so dien thoai de ghi nhan cuoc goi!\n";
        return;
    }

    CallLog* newLog = new CallLog(dateTime, duration, type);
    newLog->next = contact->callHistoryHead;
    contact->callHistoryHead = newLog;
    cout << "=> Da them lich su cuoc goi cho " << contact->name << endl;
}

// Hiển thị lịch sử cuộc gọi của một liên hệ
void PhoneBook::displayCallHistory(const string& query) const {
    ContactNode* contact = const_cast<PhoneBook*>(this)->findContact(query);
    if (contact == nullptr) {
        cout << "=> Khong tim thay lien he!\n";
        return;
    }

    cout << "\n=== LỊCH SỬ CUỘC GỌI CỦA: " << contact->name << " (" << contact->phone << ") ===\n";
    CallLog* curr = contact->callHistoryHead;
    if (curr == nullptr) {
        cout << "=> Chưa co lich su cuoc goi.\n";
        return;
    }

    cout << left << setw(25) << "Thoi Gian" << setw(15) << "Thoi Luong (s)" << setw(15) << "Loai Cuoc Goi" << endl;
    cout << string(55, '-') << endl;
    while (curr != nullptr) {
        cout << left << setw(25) << curr->dateTime << setw(15) << curr->duration << setw(15) << curr->type << endl;
        curr = curr->next;
    }
}

// Lưu danh bạ vào File
void PhoneBook::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "=> Loi: Khong the mo file de ghi!\n";
        return;
    }

    ContactNode* curr = head;
    while (curr != nullptr) {
        outFile << "CONTACT|" << curr->name << "|" << curr->phone << "|" << curr->email << "\n";
        CallLog* log = curr->callHistoryHead;
        while (log != nullptr) {
            outFile << "LOG|" << log->dateTime << "|" << log->duration << "|" << log->type << "\n";
            log = log->next;
        }
        curr = curr->next;
    }
    outFile.close();
    cout << "=> Da luu danh ba vao file thành cong: " << filename << endl;
}

// Đọc danh bạ từ File
void PhoneBook::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "=> File chua ton tai hoac khong the mo. Bat dau voi danh ba rong.\n";
        return;
    }

    string line;
    ContactNode* lastAddedContact = nullptr;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string tag;
        getline(ss, tag, '|');

        if (tag == "CONTACT") {
            string name, phone, email;
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, email, '|');
            addContact(name, phone, email);
            lastAddedContact = findContact(phone);
        } else if (tag == "LOG" && lastAddedContact != nullptr) {
            string dateTime, type, durationStr;
            getline(ss, dateTime, '|');
            getline(ss, durationStr, '|');
            getline(ss, type, '|');
            int duration = stoi(durationStr);

            CallLog* newLog = new CallLog(dateTime, duration, type);
            newLog->next = lastAddedContact->callHistoryHead;
            lastAddedContact->callHistoryHead = newLog;
        }
    }
    inFile.close();
    cout << "=> Da tai danh ba tu file thanh cong!\n";
}