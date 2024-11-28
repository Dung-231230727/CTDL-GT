#include <iostream>
#include "DoublyLinkedList.hpp"
#include <string>
#include <fstream>
using namespace std;

// Lớp KhachHang
class KhachHang {
    private:
        int maKH;
        string hoTen;
        string sdt;

    public:
        KhachHang() : maKH(0), hoTen(""), sdt("") {}
        KhachHang(int ma, string ten, string sodt) : maKH(ma), hoTen(ten), sdt(sodt) {}

        // Nhập
        void nhap() {
            cout << "Nhap ma KH: ";
            cin >> maKH;
            cin.ignore();
            cout << "Nhap ho ten: ";
            getline(cin, hoTen);
            cout << "Nhap SDT: ";
            getline(cin, sdt);
        }

        // Xuất
        void xuat() const {
            cout << "Ma KH: " << maKH << endl;
            cout << "Ho ten: " << hoTen << endl;
            cout << "SDT: " << sdt << endl;
        }

        int getMaKH() const { return maKH; }
        string getHoTen() const { return hoTen; }
        string getSDT() const { return sdt; }
        void setHoTen(string ten) { hoTen = ten; }
        void setSDT(string sodt) { sdt = sodt; }

        bool operator==(const KhachHang& other) {
            return maKH == other.maKH;
        }
};

// Lớp quản lý khách hàng
class QuanLyKhachHang {
    private:
        DoublyLinkedList<KhachHang> danhSach;

    public:
        void nhapTuFile(const string& tenFile) {
            ifstream file(tenFile);
            if (!file.is_open()) {
                cout << "Khong the mo file!" << endl;
                return;
            }

            int n;
            file >> n;
            file.ignore();

            for (int i = 0; i < n; i++) {
                int ma;
                string ten, sdt;

                // Đọc thông tin
                file >> ma;
                file.ignore();
                getline(file, ten);
                getline(file, sdt);

                // Tạo và thêm
                KhachHang kh(ma, ten, sdt);
                danhSach.pushBack(kh);
            }

            file.close();
            cout << "Da nhap danh sach khach hang tu file: " << tenFile << endl;
        }

        // Nhập thêm khách hàng
        void nhapKhachHang() {
            char tiepTuc;
            do {
                KhachHang kh;
                kh.nhap();
                danhSach.pushBack(kh);

                cout << "Ban co muon nhap tiep khong? (y/n): ";
                cin >> tiepTuc;
                cin.ignore();
            } while (tiepTuc == 'y' || tiepTuc == 'Y');
        }

        // Tìm kiếm và xử lý khách hàng
        void timVaXuLyKhachHang() {
            int ma;
            cout << "Nhap ma KH can tim: ";
            cin >> ma;

            Node<KhachHang>* node = danhSach.find(ma);
            if (node == nullptr) {
                cout << "Khong tim thay khach hang!" << endl;
                return;
            }

            cout << "Tim thay khach hang:" << endl;
            node->data.xuat();

            int choice;
            do {
                cout << "1. Xoa khach hang" << endl;
                cout << "2. Sua thong tin khach hang" << endl;
                cout << "0. Thoat" << endl;
                cout << "Chon: ";
                cin >> choice;
                cout << endl;
                cin.ignore();

                switch (choice) {
                    case 1: {
                        // Tìm vị trí của node cần xóa
                        Node<KhachHang>* current = danhSach.getHead();
                        int position = 0;
                        while (current != nullptr) {
                            if (current == node) {
                                danhSach.removeAt(position);
                                break;
                            }
                            current = current->next;
                            position++;
                        }
                        cout << "Da xoa khach hang!" << endl;
                        return;
                    }
                    case 2: {
                        string hoTenMoi, sdtMoi;
                        cout << "Nhap ho ten moi: ";
                        getline(cin, hoTenMoi);
                        cout << "Nhap SDT moi: ";
                        getline(cin, sdtMoi);
                        node->data.setHoTen(hoTenMoi);
                        node->data.setSDT(sdtMoi);
                        cout << "Da cap nhat thong tin!" << endl;
                        break;
                    }
                    case 0:
                        break;
                    default:
                        cout << "Lua chon khong hop le!" << endl;
                }
            } while (choice != 0);
        }

        // Hiển thị danh sách khách hàng
        void hienThiDanhSach() {
            cout << "DANH SACH KHACH HANG:" << endl;
            danhSach.printList();
        }
};

class App {
    private:
        QuanLyKhachHang qlkh;
    public:
        void hienThiMenu() {
            int choice;
            do {
                cout << "=== QUAN LY KHACH HANG ===" << endl;
                cout << "1. Nhap them khach hang" << endl;
                cout << "2. Tim kiem va xu ly khach hang" << endl;
                cout << "3. Hien thi danh sach khach hang" << endl;
                cout << "4. Nhap tu file" << endl;
                cout << "0. Thoat" << endl;
                cout << "Chon: ";
                cin >> choice;
                cout << endl;

                switch (choice) {
                    case 1:
                        qlkh.nhapKhachHang();
                        break;
                    case 2:
                        qlkh.timVaXuLyKhachHang();
                        break;
                    case 3:
                        qlkh.hienThiDanhSach();
                        break;
                    case 4: {
                        string tenFile;
                        cout << "Nhap ten file: ";
                        cin >> tenFile;
                        qlkh.nhapTuFile(tenFile);
                        break;
                    }
                    case 0:
                        cout << "Thoat chuong trinh." << endl;
                        break;
                    default:
                        cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                }
            } while (choice != 0);
        }
};

int main() {
    App app;
    app.hienThiMenu();
    return 0;
}
