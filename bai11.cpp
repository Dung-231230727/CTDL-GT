#include <iostream>
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
        KhachHang(int ma, string ten, string phone) : maKH(ma), hoTen(ten), sdt(phone) {}

        int getMaKH() const { return maKH; }
        string getHoTen() const { return hoTen; }
        string getSDT() const { return sdt; }
        
        void setHoTen(string ten) { hoTen = ten; }
        void setSDT(string phone) { sdt = phone; }

        // Nhập thông tin khách hàng
        void nhap() {
            cout << "Nhap ma KH: ";
            cin >> maKH;
            cin.ignore();
            cout << "Nhap ho ten: ";
            getline(cin, hoTen);
            cout << "Nhap SDT: ";
            getline(cin, sdt);
        }

        // Xuất thông tin khách hàng
        void xuat() const {
            cout << "Ma KH: " << maKH << endl;
            cout << "Ho ten: " << hoTen << endl;
            cout << "SDT: " << sdt << endl;
        }
};

// Node
template<typename T>
class Node {
    public:
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

//Lớp DoublyLinkedList
template<typename T>
class DoublyLinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;

    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

        // Hàm hủy
        ~DoublyLinkedList() {
            Node<T>* current = head;
            while (current != nullptr) {
                Node<T>* next = current->next;
                delete current;
                current = next;
            }
        }

        // Thêm phần tử vào cuối danh sách
        void pushBack(const T& value) {
            Node<T>* newNode = new Node<T>(value);
            if (head == nullptr) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            size++;
        }

        // Xóa một node khỏi danh sách
        void removeNode(Node<T>* node) {
            if (node == nullptr) return;

            if (node->prev != nullptr)
                node->prev->next = node->next;
            else
                head = node->next;

            if (node->next != nullptr)
                node->next->prev = node->prev;
            else
                tail = node->prev;

            delete node;
            size--;
        }

        // Tìm kiếm khách hàng theo mã
        Node<T>* findByMaKH(int ma) {
            Node<T>* current = head;
            while (current != nullptr) {
                if (current->data.getMaKH() == ma)
                    return current;
                current = current->next;
            }
            return nullptr;
        }

        // Hiển thị toàn bộ danh sách
        void display() const {
            if (head == nullptr) {
                cout << "Danh sach trong!" << endl;
                return;
            }

            Node<T>* current = head;
            while (current != nullptr) {
                current->data.xuat();
                cout << endl;
                current = current->next;
            }
        }
};

// Lớp quản lý khách hàng
class QuanLyKhachHang {
    private:
        DoublyLinkedList<KhachHang> danhSach;

    public:
        void nhapTuFile(string tenFile) {
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
            cout << "Nhap file thanh cong!" << endl;
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

            Node<KhachHang>* node = danhSach.findByMaKH(ma);
            if (node == nullptr) {
                cout << "Khong tim thay khach hang!" << endl;
                return;
            }

            cout << "Tim thay khach hang:" << endl;
            node->data.xuat();

            int choice;
            do {
                cout << "1. Xoa khach hang";
                cout << "2. Sua thong tin khach hang";
                cout << "0. Thoat";
                cout << "Chon: ";
                cin >> choice;
                cout << endl;
                cin.ignore();

                switch (choice) {
                    case 1:
                        danhSach.removeNode(node);
                        cout << "Da xoa khach hang!" << endl;
                        return;
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
            danhSach.display();
        }
};

int main() {
    QuanLyKhachHang qlkh;
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
        cin.ignore();

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
                getline(cin, tenFile);
                qlkh.nhapTuFile(tenFile);
                break;
            }
            case 0:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);

    return 0;
}