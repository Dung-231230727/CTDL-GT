#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
using namespace std;

class SinhVien {
    private:
        string maSV;
        string hoTen;
        string gioiTinh;
        float diem;
        string lop;

    public:
        SinhVien() : maSV(""), hoTen(""), gioiTinh(""), diem(0.0f), lop("") {}

        friend istream& operator>>(istream& is, SinhVien& sv) {
            cout << "Nhap ma SV: ";
            is >> sv.maSV;
            cout << "Nhap ho ten: ";
            is.ignore();
            getline(is, sv.hoTen);
            cout << "Nhap gioi tinh: ";
            getline(is, sv.gioiTinh);
            cout << "Nhap diem: ";
            is >> sv.diem;
            cout << "Nhap lop: ";
            is.ignore();
            getline(is, sv.lop);
            return is;
        }

        friend ostream& operator<<(ostream& os, const SinhVien& sv) {
            os << "Ma SV: " << sv.maSV << endl;
            os << "Ho ten: " << sv.hoTen << endl;
            os << "Gioi tinh: " << sv.gioiTinh << endl;
            os << "Diem: " << sv.diem << endl;
            os << "Lop: " << sv.lop << endl;
            return os;
        }

        bool operator<(const SinhVien& other) const {
            return diem < other.diem;
        }

        bool operator>(const SinhVien& other) const {
            return diem > other.diem;
        }


        string getHoTen() const { return hoTen; }
        string getMaSV() const { return maSV; }
        float getDiem() const { return diem; }
        void setMaSV(const string& ma) { maSV = ma; }
        void setHoTen(const string& ten) { hoTen = ten; }
        void setGioiTinh(const string& gt) { gioiTinh = gt; }
        void setDiem(float d) { diem = d; }
        void setLop(const string& l) { lop = l; }
};

class DanhSachSinhVien {
    private:
        list<SinhVien> sinhViens;

    public:
        void docTuFile(const string& tenFile) {
            ifstream file(tenFile);
            if (!file.is_open()) {
                cout << "Khong the mo file: " << tenFile << endl;
                return;
            }

            while (true) {
                SinhVien sv;
                string maSV, hoTen, gioiTinh, lop;
                float diem;

                // Đọc mã SV
                if (!getline(file, maSV) || maSV.empty()) break;

                // Đọc họ tên
                if (!getline(file, hoTen) || hoTen.empty()) break;

                // Đọc giới tính
                if (!getline(file, gioiTinh) || gioiTinh.empty()) break;

                // Đọc điểm
                if (!(file >> diem)) break;
                file.ignore(); // Bỏ qua ký tự newline sau khi đọc điểm

                // Đọc lớp
                if (!getline(file, lop) || lop.empty()) break;

                // Gán giá trị cho sinh viên
                sv.setMaSV(maSV);
                sv.setHoTen(hoTen);
                sv.setGioiTinh(gioiTinh);
                sv.setDiem(diem);
                sv.setLop(lop);

                sinhViens.push_back(sv);
            }

            file.close();
            cout << "Da nhap danh sach sinh vien tu file: " << tenFile << endl;
        }


        void ghiVaoFile(const string& tenFile) {
            ofstream file(tenFile);
            if (!file.is_open()) {
                cout << "Khong the mo file: " << tenFile << endl;
                return;
            }

            list<SinhVien>::iterator it;
            for (it = sinhViens.begin(); it != sinhViens.end(); ++it) {
                file << *it << endl;
            }
            file.close();
        }

        void themSinhVien() {
            SinhVien sv;
            cin >> sv;
            sinhViens.push_back(sv);
        }

        void xoaSinhVien(const string& maSV) {
            list<SinhVien>::iterator it;
            for (it = sinhViens.begin(); it != sinhViens.end(); ++it) {
                if (it->getMaSV() == maSV) {
                    sinhViens.erase(it);
                    cout << "Da xoa sinh vien co ma: " << maSV << endl;
                    return;
                }
            }
            cout << "Khong tim thay sinh vien de xoa." << endl;
        }

        void hienThiDanhSach() {
            list<SinhVien>::iterator it;
            for (it = sinhViens.begin(); it != sinhViens.end(); ++it) {
                cout << *it << endl;
            }
        }

        void suaThongTinSinhVien(const string& maSV) {
            list<SinhVien>::iterator it;
            for (it = sinhViens.begin(); it != sinhViens.end(); ++it) {
                if (it->getMaSV() == maSV) {
                    string hoTen, gioiTinh, lop;
                    float diem;
                    cout << "Nhap ho ten moi: ";
                    cin.ignore();
                    getline(cin, hoTen);
                    cout << "Nhap gioi tinh moi: ";
                    getline(cin, gioiTinh);
                    cout << "Nhap diem moi: ";
                    cin >> diem;
                    cout << "Nhap lop moi: ";
                    cin.ignore();
                    getline(cin, lop);
                    it->setHoTen(hoTen);
                    it->setGioiTinh(gioiTinh);
                    it->setDiem(diem);
                    it->setLop(lop);
                    cout << "Da cap nhat thong tin!" << endl;
                    return;
                }
            }
            cout << "Khong tim thay sinh vien de sua." << endl;
        }

        void timKiemSinhVien(const string& hoTen) {
            list<SinhVien>::iterator it;
            for (it = sinhViens.begin(); it != sinhViens.end(); ++it) {
                if (it->getHoTen() == hoTen) {
                    cout << "Tim thay sinh vien: " << endl;
                    cout << *it << endl;
                    return;
                }
            }
            cout << "Khong tim thay sinh vien." << endl;
        }

        void sapXepTangDan() {
            sinhViens.sort();
        }

        void sapXepGiamDan() {
            sinhViens.sort(greater<SinhVien>());
        }
};


class App {
    private:
        DanhSachSinhVien danhSach;

    public:
        void hienThiMenu() {
            int choice;
            do {
                cout << "\n=== MENU QUAN LY SINH VIEN ===" << endl;
                cout << "1. Doc danh sach sinh vien tu file" << endl;
                cout << "2. Ghi danh sach sinh vien vao file" << endl;
                cout << "3. Nhap them sinh vien" << endl;
                cout << "4. Xoa sinh vien" << endl;
                cout << "5. Hien thi danh sach sinh vien" << endl;
                cout << "6. Sua thong tin sinh vien" << endl;
                cout << "7. Tim kiem sinh vien theo ho ten" << endl;
                cout << "8. Sap xep danh sach sinh vien tang dan theo diem" << endl;
                cout << "9. Sap xep danh sach sinh vien giam dan theo diem" << endl;
                cout << "0. Thoat" << endl;
                cout << "Chon: ";
                cin >> choice;
                cout << endl;

                switch (choice) {
                    case 1: {
                        string tenFile;
                        cout << "Nhap ten file: ";
                        cin >> tenFile;
                        danhSach.docTuFile(tenFile);
                        break;
                    }
                    case 2: {
                        string tenFile;
                        cout << "Nhap ten file: ";
                        cin >> tenFile;
                        danhSach.ghiVaoFile(tenFile);
                        break;
                    }
                    case 3:
                        danhSach.themSinhVien();
                        break;
                    case 4: {
                        string maSV;
                        cout << "Nhap ma sinh vien can xoa: ";
                        cin >> maSV;
                        danhSach.xoaSinhVien(maSV);
                        break;
                    }
                    case 5:
                        danhSach.hienThiDanhSach();
                        break;
                    case 6: {
                        string maSV;
                        cout << "Nhap ma sinh vien can sua: ";
                        cin >> maSV;
                        danhSach.suaThongTinSinhVien(maSV);
                        break;
                    }
                    case 7: {
                        string hoTen;
                        cout << "Nhap ho ten sinh vien can tim: ";
                        cin.ignore();
                        getline(cin, hoTen);
                        danhSach.timKiemSinhVien(hoTen);
                        break;
                    }
                    case 8:
                        danhSach.sapXepTangDan();
                        cout << "Da sap xep danh sach sinh vien tang dan theo diem." << endl;
                        break;
                    case 9:
                        danhSach.sapXepGiamDan();
                        cout << "Da sap xep danh sach sinh vien giam dan theo diem." << endl;
                        break;
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
