#include "../include/Contact.h"

ContactNode::ContactNode(std::string n, std::string p, std::string e) 
    : name(n), phone(p), email(e), prev(nullptr), next(nullptr), callHistoryHead(nullptr) {}

// Destructor dọn dẹp danh sách CallLog để tránh Memory Leak
ContactNode::~ContactNode() {
    CallLog* current = callHistoryHead;
    while (current != nullptr) {
        CallLog* temp = current;
        current = current->next;
        delete temp;
    }
}