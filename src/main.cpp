#include <iostream>
#include <string>
#include "PhoneBook.h"

using namespace std;

void displayMenu() {
    cout << "\n=========================================\n";
    cout << "       CHƯƠNG TRÌNH QUẢN LÝ DANH BẠ      \n";
    cout << "=========================================\n";
    cout << "1. Them lien he moi\n";
    cout << "2. Xoa lien he theo So dien thoai\n";
    cout << "3. Hien thi danh ba (A -> Z)\n";
    cout << "4. Hien thi danh ba (Z -> A)\n";
    cout << "5. Tim kiem lien he (Chinh xac)\n";
    cout << "6. Tim kiem lien he theo Tien to ten\n";
    cout << "7. Sap xep danh ba theo Ten (Bubble Sort)\n";
    cout << "8. Them lich su cuoc goi\n";
    cout << "9. Xem lich su cuoc goi cua lien he\n";
    cout << "10. Luu danh ba vao File (phonebook.txt)\n";
    cout << "11. Tai danh ba tu File (phonebook.txt)\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "=========================================\n";
    cout << "Lua chon cua ban: ";
}

int main() {
    PhoneBook myPhoneBook;
    const string filename = "phonebook.txt";

    // Tu dong tai du lieu tu file neu co
    myPhoneBook.loadFromFile(filename);

    int choice;
    do {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "=> Lua chon khong hop le! Vui long nhap so.\n";
            continue;
        }
        cin.ignore(); // Xoa bộ nho dem

        switch (choice) {
            case 1: {
                string name, phone, email;
                cout << "Nhap Ho va Ten: "; getline(cin, name);
                cout << "Nhap So Dien Thoai: "; getline(cin, phone);
                cout << "Nhap Email: "; getline(cin, email);
                myPhoneBook.addContact(name, phone, email);
                break;
            }
            case 2: {
                string phone;
                cout << "Nhap So Dien Thoai can xoa: "; getline(cin, phone);
                myPhoneBook.deleteContact(phone);
                break;
            }
            case 3:
                myPhoneBook.displayAZ();
                break;
            case 4:
                myPhoneBook.displayZA();
                break;
            case 5: {
                string query;
                cout << "Nhap Ten hoac So Dien Thoai can tim: "; getline(cin, query);
                ContactNode* res = myPhoneBook.findContact(query);
                if (res) {
                    cout << "\n=> TIM THAY LIEN HE:\n";
                    cout << "Ten: " << res->name << " | SDT: " << res->phone << " | Email: " << res->email << endl;
                } else {
                    cout << "=> Khong tim thay lien he phu hop.\n";
                }
                break;
            }
            case 6: {
                string prefix;
                cout << "Nhap tien to ten can tim: "; getline(cin, prefix);
                myPhoneBook.searchByPrefix(prefix);
                break;
            }
            case 7:
                myPhoneBook.bubbleSortByName();
                cout << "=> Da sap xep danh ba theo Ten (A-Z).\n";
                break;
            case 8: {
                string phone, dateTime, type;
                int duration;
                cout << "Nhap So Dien Thoai lien he: "; getline(cin, phone);
                cout << "Nhap Thoi Gian (VD: 2026-10-21 14:00): "; getline(cin, dateTime);
                cout << "Nhap Thoi Luong (giay): "; cin >> duration; cin.ignore();
                cout << "Nhap Loai Cuoc Goi (Goi den/Goi di/Nhan tin): "; getline(cin, type);
                myPhoneBook.addCallLog(phone, dateTime, duration, type);
                break;
            }
            case 9: {
                string query;
                cout << "Nhap Ten hoac So Dien Thoai lien he: "; getline(cin, query);
                myPhoneBook.displayCallHistory(query);
                break;
            }
            case 10:
                myPhoneBook.saveToFile(filename);
                break;
            case 11:
                myPhoneBook.loadFromFile(filename);
                break;
            case 0:
                myPhoneBook.saveToFile(filename);
                cout << "=> Cam on ban da su dung chuong trinh. Tam biet!\n";
                break;
            default:
                cout << "=> Lua chon khong hop le!\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
