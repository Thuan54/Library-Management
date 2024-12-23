#pragma once
#include "define.h"
//Xóa màn hình
void clearScreen();

//Giữ màn hình cho đến khi nhấn Enter
void hold();

//In ra các lựa chọn
void renderMenu();

//In ra các lựa chọn của các lựa chọn
//num: thứ tự của lựa chọn
void renderSubMenu(int num);

//In ra danh sách lựa chọn cập nhật cho độc giả
void renderMemberUpdateMenu();

//In ra danh sách lựa chọn cập nhật cho sách
void renderBookUpdateMenu();

void renderMemAttribute();
void renderBookAttribute();
void renderBorrowCardAttribute();

void render(const Member* member);
void render(const Book* book);
void render(const BorrowCard* borrowCard);