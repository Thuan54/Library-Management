#pragma once
#include "define.h"
void appStart(Members* members, Books* books, BorrowCardRecords* borrowCardRecords);
void appEnd(Members* &members, Books* &books, BorrowCardRecords* &borrowCardRecords);

//lấy lựa chọn người dùng nhập vào
//max: số lựa chọn tối da
//trả về lựa chọn người dùng nhập vào
int inputChoice(int max);

//Member

//
void renderMems(const Members*members);

//Thêm độc giả
void addMem(Members* members);

//Cập nhật dữ liệu số nguyên độc giả
void updateMem(Members* members);

//Xóa độc giả
void deleteMem(Members* members);

//Tìm độc giả bằng CCCD
void findMemByCCCD(const Members* members);

////Tìm độc giả bằng têm
void findMemByFullName(const Members* members);

//Book

//
void renderBooks(const Books* books);

//Thêm sách
void addBook(Books* books);

//Cập nhật dữ liệu số nguyên cho sách
void updateBook(Books* books);

//Xóa sách
void deleteBook(Books* books);

//Tìm kiếm sách theo ISBN
void findBookByISBN(const Books* books);

//Tìm kiếm sách theo tên sách
void findBookByName(const Books* books);

//BorrowCard

//
void renderBorrowCardRecords(const BorrowCardRecords* borrowCardRecords);

//Mượn sách
void addBorrowCard(const Members* members, const Books* books, BorrowCardRecords* borrowCardRecords);

//Trả sách
void deleteBorrowCard(const Members* members, const Books* books, BorrowCardRecords* borrowCardRecords);

//Statistic

//Thống kê số lượng sách theo thể loại
void statisticBookByGenre(const Books* books);

//Thống kê số lượng sách đang trong thư viện
void statisticNumberOfBook(const Books* books);

//Thống kê số lượng độc giả theo giới tính
void statisticMemByGender(const Members* members);

//Thống kê số lượng độc giả trong thư viện
void statisticMemInLibrary(const Members* members);

//Thống kê số sách được mượn
void statisticBookBorrowed(const BorrowCardRecords* borrowCardRecords);

//Thống kê độc giả quá hạn trả sách
void statisticMemOverDue(const BorrowCardRecords* borrowCardRecords);