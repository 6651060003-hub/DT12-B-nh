#ifndef CALLLOG_H
#define CALLLOG_H

#include <string>

// Struct Lưu trữ Lịch sử Cuộc gọi (Danh sách liên kết đơn)
struct CallLog {
    std::string timestamp; // Thời gian gọi (VD: "14:30 21/10/2026")
    std::string duration;  // Thời lượng (VD: "05:12")
    std::string type;      // Loại cuộc gọi: "Gọi đi", "Gọi đến", "Nhỡ"
    CallLog* next;

    CallLog(std::string ts, std::string dur, std::string t) 
        : timestamp(ts), duration(dur), type(t), next(nullptr) {}
};

#endif // CALLLOG_H
