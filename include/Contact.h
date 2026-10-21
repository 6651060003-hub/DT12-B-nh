#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include "CallLog.h"

// Node Danh bạ (Danh sách liên kết đôi)
struct ContactNode {
    std::string name;      // Tên liên hệ
    std::string phone;     // Số điện thoại
    std::string email;     // Email
    ContactNode* prev;
    ContactNode* next;
    
    // Lịch sử cuộc gọi riêng cho từng liên hệ (Danh sách đơn)
    CallLog* callHistoryHead;

    ContactNode(std::string n, std::string p, std::string e = "");
    ~ContactNode(); // Destructor giải phóng bộ nhớ CallLog
};

#endif // CONTACT_H