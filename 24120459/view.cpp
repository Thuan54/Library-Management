#include <iostream>
#include <iomanip>
#include "define.h"
using namespace std;

void clearScreen() {
	cout << "\033[2J\033[1;1H";
	cout << endl;
}
void hold() {
	cin.clear();
	char c;
	cin.ignore();
	while ((c = getchar()) != '\n');
}
void renderMenu() {
	clearScreen();
	cout << "1. Quan li doc gia" << endl;
	cout << "2. Quan li sach" << endl;
	cout << "3. Phieu muon tra" << endl;
	cout << "4. Thong ke" << endl;
	cout << "0. Thoat" << endl;
}
void renderSubMenu(int num) {
	clearScreen();
	switch (num)
	{
	case 1: {
		cout << "1. Xem danh sach doc gia" << endl;
		cout << "2. Them doc gia" << endl;
		cout << "3. Chinh sua doc gia" << endl;
		cout << "4. Xoa doc gia" << endl;
		cout << "5. Tim kiem doc gia theo CCCD" << endl;
		cout << "6. Tim kiem doc gia theo ho ten" << endl;
		cout << "0. Tro lai" << endl;
		break;
	}
	case 2: {
		cout << "1. Xem danh sach sach" << endl;
		cout << "2. Them sach" << endl;
		cout << "3. Chinh sua sach" << endl;
		cout << "4. Xoa sach" << endl;
		cout << "5. Tim kiem sach theo ISBN" << endl;
		cout << "6. Tim kiem sach theo ten" << endl;
		cout << "0. Tro lai" << endl;
		break;
	}
	case 3: {
		cout << "1. Xem danh sach da muon" << endl;
		cout << "2. Muon sach" << endl;
		cout << "3. Tra sach" << endl;
		cout << "0. Tro lai" << endl;
		break;
	}
	case 4: {
		cout << "1. Thong ke so luong doc gia trong thu vien" << endl;
		cout << "2. Thong ke so luong doc gia theo gioi tinh" << endl;
		cout << "3. Thong ke so luong sach trong thu vien" << endl;
		cout << "4. Thong ke so luong sach theo the loai" << endl;
		cout << "5. Thong ke so luong sach dang duoc muon" << endl;
		cout << "6. Thong ke so luong doc gia tre han" << endl;
		cout << "0. Tro lai" << endl;
		break;
	}
	}
}
void renderMemberUpdateMenu() {
	clearScreen();
	cout << "1. Cap nhat ma doc gia" << endl;
	cout << "2. Cap nhat ho ten doc gia" << endl;
	cout << "3. Cap nhat CCCD doc gia" << endl;
	cout << "4. Cap nhat ngay thang nam sinh doc gia" << endl;
	cout << "5. Cap nhat gioi tinh doc gia" << endl;
	cout << "6. Cap nhat email doc gia" << endl;
	cout << "7. Cap nhat dia chi doc gia" << endl;
	cout << "8. Cap nhat ngay lap the doc gia" << endl;
	cout << "9. Cap nhat ngay het han the doc gia" << endl;
	cout << "0. Tro lai" << endl;
}
void renderBookUpdateMenu() {
	clearScreen();
	cout << "1. Cap nhat ISBN" << endl;
	cout << "2. Cap nhat ten sach" << endl;
	cout << "3. Cap nhat tac gia" << endl;
	cout << "4. Cap nhat nha xuat ban" << endl;
	cout << "5. Cap nhat nam xuat ban" << endl;
	cout << "6. Cap nhat the loai sach" << endl;
	cout << "7. Cap nhat gia sach" << endl;
	cout << "8. Cap nhat so quyen sach" << endl;
	cout << "0. Tro lai" << endl;
}

void renderData(const char* data, int length) {
	int i;
	for (i = 0; data[i] != '\0' && i < length; i++)
	{
		cout << data[i];
	}
	for (;i < length + 2;i++) cout << " ";
}
void renderData(int data, int length) {
	cout << setw(length) << left << data;
}
void renderData(float data, int length) {
	cout << setw(length) << left << data;
}
void renderData(const Date* date,int length) {
	cout << date->day << "-" << date->month << "-" <<setw(length-10)<<left << date->year;
}

void renderMemAttribute() {
	cout << setw(12) << left << "Ma doc gia";
	cout << setw(15) << left << "CCCD";
	cout << setw(22) << left << "Ho ten";
	cout << setw(10) << left << "Gioi tinh";
	cout << setw(22) << left << "Email";
	cout << setw(15) << left << "Dia chi";
	cout << setw(20) << left << "Ngay thanh lap the";
	cout << setw(10) << left << "Ngay het han the";
	cout << endl;
}
void renderBookAttribute() {
	cout << setw(14) << left << "Ma sach";
	cout << setw(22) << left << "Ten sach";
	cout << setw(22) << left << "Tac gia";
	cout << setw(22) << left << "Nha xuat ban";
	cout << setw(22) << left << "The loai";
	cout << setw(8) << left << "Gia";
	cout << setw(15) << left << "Nam xuat ban";
	cout << setw(10) << left << "So luong";
	cout << endl;
}
void renderBorrowCardAttribute() {
	cout << setw(15) << left << "Ma doc gia";
	cout << setw(20) << left << "Ma sach";
	cout << setw(20) << left << "Ngay muon";
	cout << setw(20) << left << "Ngay tra du kien";
	cout << endl;
}

void render(const Member* member) {
	renderData(member->ID, 12);
	renderData(member->CCCD, 15);
	renderData(member->fullname, 22);
	renderData(member->gender, 10);
	renderData(member->email, 22);
	renderData(member->address, 15);
	renderData(member->MFG,20);
	renderData(member->EXP,10);
	cout << endl;
}
void render(const Book* book) {
	renderData(book->ISBN,14);
	renderData(book->name, 21);
	renderData(book->author, 21);
	renderData(book->publisher, 21);
	renderData(book->genre, 21);
	renderData(book->price, 8);
	renderData(book->yearPB, 15);
	renderData(book->quantity, 10);
	cout << endl;
}
void render(const BorrowCard* borrowCard) {
	renderData(borrowCard->member->ID, 15);
	for (int i = 0; i < 7; i++)
	{
		if (borrowCard->books[i] == NULL) break;
		renderData(borrowCard->books[i]->ISBN, 20);
		renderData(borrowCard->dateBorrowed[i], 20);
		renderData(borrowCard->expectDateReturn[i], 20);
		if (borrowCard->books[i + 1] != NULL) cout <<endl<<setw(15) << " ";
	}
	cout << endl;
}