#ifndef model
#pragma once
#include "define.h"

template <typename T> T* create(int rows, int cols, T initVal) {
	int size = rows * cols;
	T* arr = new T[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = initVal;
	}
	return arr;
}
int toInt(const char*s);
float toFloat(char*s);
void toDate(Date* date,char* s);
void copyDate(Date* dateCopy, const Date* date);
void getToday(Date*);
bool isEqualString(char* s1, char* s2, int accuracy = 1);
char tolower(char c);

void init(Member* member);
void init(Book* book);
void init(BorrowCard* borrowCard);

void destruct(Member* &member);
void destruct(Book* &book);
void destruct(BorrowCard* &SborrowCard);

bool load(Members* members);
bool load(Books* books);
bool load(const Members* members,const Books* books,BorrowCardRecords* borrowCardRecords);

bool save(const Members*members);
bool save(const Books*books);
bool save(const BorrowCardRecords* borrowCardRecords);

void add(Members* members, Member* member);
void add(Books* books, Book* book);
bool add(BorrowCardRecords* borrowCardRecords, Member* member, Book* book, Date* dateBorrowed);

bool remove(Members* members, int ID);
bool remove(Books* books, char* ISBN);
void remove(BorrowCardRecords* borrowCardRecords, int index, Member* member, Book* book, int bookBorrowedIndex, int bookCount);

int find(const Members* members, int ID);
int findMemByCCCD(const Members* members, char* CCCD);
int* findMemByFullName(const Members* members, char* name, int accuracy = 1);

int find(const Books* books, char* ISBN);
int* findBookByName(const Books* books, char* name, int accuracy = 1);

//Hoán đổi 2 số
// a,b: 2 số cần hoán đổi
void swap(int& a, int& b);

//Kiểm tra năm nhuận
//year: năm cần kiểm tra
//Trả về kiểu bool cho biết có phải năm nhuận không
bool isLeapYear(int year);

//Sắp xếp dữ liệu chuỗi
//storeIndex: nơi lưu chỉ mục(index) của dữ liệu, data: nơi lưu dữ liệu, low: chỉ mục đầu tiên của storeIndex, high: chỉ mục cuối cùng của storeIndex hay current -1, length: chiều dài chuỗi
void sortData(int* storeIndex, Member** members, int low, int high);


void sortData(int* storeIndex, Book** books, int low, int high);

//Khoảng cách giữa 2 ngày
//date1, date2: lấy dữ liệu để tính toán khoảng cách giữa 2 ngày
//Trả về số lượng ngày là khoảng cách giữa 2 ngày
int diffTwoDates(Date* date1, Date* date2);

//Tăng ngày lên k ngày
//Date: lấy dữ liệu để tăng lên k ngày, k: số lượng ngày muốn tăng
void increaseDate(Date* Date, int k);
#endif