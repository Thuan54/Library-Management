#ifndef define
#pragma once
#define MEMBERCAPACITY 20
#define ISBNCAPACITY 20

#pragma pack(push,1)
struct Date {
	int day;
	int month;
	int year;
};

#define memFullName 21
#define memCCCD 13
#define memGender 7
#define memEmail 21
#define memAddress 16
struct Member {
	int ID;
	char* fullname;
	char* CCCD;
	char* gender;
	char* email;
	char* address;
	Date* DOB;
	Date* MFG;
	Date* EXP;
};

#define bookISBN 14
#define bookName 21
#define bookAuthor 21
#define bookPublisher 21
#define bookGenre 21
struct Book {
	char* ISBN;
	char* name;
	char* author;
	char* publisher;
	char* genre;
	int   yearPB;
	float price;
	int	  quantity;
};
struct BorrowCard {
	Member* member;
	Book** books;
	Date** dateBorrowed;
	Date** expectDateReturn;
	Date** actualDateReturn;
};
struct Members {
	int current;
	int* storeIndex;
	int* storeVacant;
	Member** members;
};
struct Books {
	int current;
	int* storeIndex;
	int* storeVacant;
	Book** books;
};
struct BorrowCardRecords {
	int current;
	BorrowCard** borrowCardRecords;
};
#pragma pack(pop)
#endif