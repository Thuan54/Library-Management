#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "define.h"
#include "model.h"

//Kiểm tra năm nhuận
//year: năm cần kiểm tra
//Trả về true: năm nhuận, false: năm không nhuận
bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

//Ngày trong tháng
//month, year: dùng để tính toán ngày trong 1 tháng
//Trả về 31 nếu tháng 1,3,5,7,8,10,12
//Trả về 30 nếu tháng 4,6,9,11
//Trả về 29 nếu tháng 2 và năm nhuận, trả về 28 nếu tháng 2 và không phải năm nhuận
int daysInMonth(int month, int year) {
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return isLeapYear(year) ? 29 : 28;
	}
	return 30;
}

//Lấy kí tự chữ thường
//c: kí tự muốn trích xuất chữ thường
//Trả về kí tự thường của c
char tolower(char c) {
	if (c >= 65 && c <= 90) c += 32;
	return c;
}

//Tổng cộng ngày từ 1900 của 1 ngày
//day, month, year: Tính toán cộng ngày từ 1-1-1900 đến ngày nhập vào
//Trả về tổng cộng ngày
int totalDays(int day, int month, int year) {
	int totalDays = 0;
	for (int i = 1900; i < year; i++) {
		totalDays += isLeapYear(i) ? 366 : 365;
	}
	for (int i = 1; i < month; i++) {
		totalDays += daysInMonth(i, year);
	}
	totalDays += day;
	return totalDays;
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int toInt(char* s) {
	int res = 0;
	while (*s != '\0')
	{
		res = res * 10 + *s - '0';
		s++;
	}
	return res;
}
float toFloat(char* s)
{
	float res = 0;
	char* nextToken = NULL;
	char* token = strtok_s(s, ".",&nextToken);
	res += toInt(token);
	token = strtok_s(NULL, ".",&nextToken);
	if (token != NULL) {
		float temp = 0;
		for (int i = strlen(token) -1; i >=0 ; i--)
		{
			temp = (float)temp / 10 + token[i] - '0';
		}
		res += temp/10;
	}
	return res;
}
int diffTwoDates(Date* date1, Date* date2) {
	return totalDays(date1->day, date1->month, date1->year) - totalDays(date2->day, date2->month, date2->year);
}
void increaseDate(Date* date, int k) {
	while (k != 0)
	{
		if (date->day + k > daysInMonth(date->month, date->year)) {
			k = k - (daysInMonth(date->month, date->year) - date->day);
			if (date->month+ 1 > 12) {
				date->year++;
				date->month = 1;
				date->day = 1;
			}
			else {
				date->month++;
				date->day = 1;
			}
		}
		else date->day += 1;
		k--;
	}
}
void toDate(Date* date,char* s)
{
	char delimiter[] = ". /-";
	char* nextToken = NULL;
	char* token = strtok_s(s, delimiter,&nextToken);
	date->day = toInt(token);
	token = strtok_s(NULL, delimiter,&nextToken);
	date->month = toInt(token);
	token = strtok_s(NULL, delimiter,&nextToken);
	date->year= toInt(token);
}
void copyDate(Date* dateCopy, const Date* date)
{
	dateCopy->day = date->day;
	dateCopy->month = date->month;
	dateCopy->year = date->year;
}
void getToday(Date* today) {
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	today->day = localTime.tm_mday;
	today->month = localTime.tm_mon+1;
	today->year = localTime.tm_year+1900;
	return;
}
bool isEqualString(char* s1, char* s2, int accuracy)
{
	int length = strlen(s1);
	for (int j = 0; j < length; j++)
	{
		if (s1[j] == '\0' || s2[j] == '\0') {
			if (accuracy && (s1[j] != '\0' || s2[j] != '\0')) return false;
			return true;
		}
		if (tolower(s1[j]) != tolower(s2[j])) {
			return false;
		}
	}
	return strlen(s1) == strlen(s2);
}

void init(Member* member) {
	member->ID = 0;
	member->CCCD = create<char>(1, memCCCD, '\0');
	member->fullname = create<char>(1, memFullName, '\0');
	member->gender = create<char>(1, memGender, '\0');
	member->email = create<char>(1, memEmail, '\0');
	member->address = create<char>(1, memAddress, '\0');
	member->DOB = new Date;
	member->MFG = new Date;
	member->EXP = new Date;
}
void init(Book* book) {
	book->ISBN = create<char>(1, bookISBN, '\0');
	book->name = create<char>(1, bookName, '\0');
	book->genre = create<char>(1, bookGenre, '\0');
	book->author = create<char>(1, bookAuthor, '\0');
	book->publisher = create<char>(1, bookPublisher, '\0');
	book->price = 0;
	book->yearPB = 0;
	book->quantity = 0;
}
void init(BorrowCard* borrowCard) {
	borrowCard->member = NULL;
	borrowCard->books = create<Book*>(1, 7, NULL);
	borrowCard->dateBorrowed = create<Date*>(1, 7, NULL);
	borrowCard->expectDateReturn = create<Date*>(1, 7, NULL);
	borrowCard->actualDateReturn = create<Date*>(1, 7, NULL);
}

void destruct(Member* &member) {
	if (member == NULL) return;
	delete[] member->fullname;
	delete[] member->email;
	delete[] member->address;
	delete[] member->gender;
	delete[] member->CCCD;
	delete member->DOB;
	delete member->MFG;
	delete member->EXP;
	delete member;
	member = NULL;
}
void destruct(Book* &book) {
	if (book == NULL) return;
	delete[] book->name;
	delete[] book->author;
	delete[] book->publisher;
	delete[] book->genre;
	delete[] book->ISBN;
	delete book;
	book = NULL;
}
void destruct(BorrowCard* &borrowCard) {
	if (borrowCard == NULL) return;
	borrowCard->member = NULL;
	for (int i = 0; i < 7; i++)
	{
		borrowCard->books[i] = NULL;
		delete borrowCard->dateBorrowed[i];
		delete borrowCard->expectDateReturn[i];
		delete borrowCard->actualDateReturn[i];
	}
	delete[] borrowCard->books;
	delete[] borrowCard->dateBorrowed;
	delete[] borrowCard->expectDateReturn;
	delete[] borrowCard->actualDateReturn;
	delete borrowCard;
}

bool load(Members* members) {
	char fileName[] = "members.txt";
	FILE* memFile;
	errno_t err = fopen_s(&memFile,fileName, "r");
	if (err != 0) return false;
	
	fscanf_s(memFile, "%*[\n ]");
	for (int i = 0; i < MEMBERCAPACITY; i++) {
		char line[256] = "\0";
		if (fscanf_s(memFile, "%[^\n]", line, sizeof(line)) == EOF) break;
		
		members->current = i + 1;
		int index = members->storeVacant[members->current % MEMBERCAPACITY];
		members->storeVacant[members->current%MEMBERCAPACITY] = -1;
		members->storeIndex[i] = index;

		Member* member = new Member;
		init(member);
		members->members[index] = member;

		int* intAttribute[1] = { &member->ID };
		char* stringAttribute[5] = { member->CCCD,member->fullname,member->gender, member->email ,member->address };
		int lengthOfStringAttribute[] = {memCCCD,memFullName,memGender,memEmail,memAddress};
		Date* dateAttribute[3] = { member->DOB,member->MFG, member->EXP };

		char* nextToken = NULL;
		char* token = strtok_s(line, ",",&nextToken);
		int tokenCount = 0;
		while (token != NULL && tokenCount < 9) {
			int passToken = 0;
			if (tokenCount >= 0 && tokenCount < 1) {
				*intAttribute[tokenCount - passToken] = toInt(token);
			}
			else passToken += 1;
			if (tokenCount >= 1 && tokenCount < 6) {
				strcpy_s(stringAttribute[tokenCount - passToken], lengthOfStringAttribute[tokenCount - passToken], token);
			}
			else passToken += 5;
			if (tokenCount >= 6 && tokenCount < 9) {
				toDate(dateAttribute[tokenCount - passToken],token);
			}
			else passToken += 3;
			token = strtok_s(NULL, ",",&nextToken);
			tokenCount++;
		}
		fscanf_s(memFile, "%*[\n ]");
	}
	sortData(members->storeIndex,members->members, 0, members->current-1);
	fclose(memFile);
	return true;
}
bool load(Books* books) {
	char fileName[] = "books.txt";
	FILE* bookFile;
	errno_t err = fopen_s(&bookFile, fileName, "r");
	if (err != 0) return false;
	char line[256] = "\0";

	fscanf_s(bookFile, "%*[\n ]");
	for (int i = 0; i < ISBNCAPACITY; i++)
	{
		char line[256] = "\0";
		if (fscanf_s(bookFile, "%[^\n]", line, sizeof(line)) == EOF) break;
		char* nextToken = NULL;
		char* token = strtok_s(line, ",",&nextToken);
		int tokenCount = 0;
		books->current = i + 1;
		int index = books->storeVacant[books->current % ISBNCAPACITY];
		books->storeVacant[books->current % ISBNCAPACITY] = -1;
		books->storeIndex[i] = index;

		Book* book = new Book;
		init(book);
		books->books[index] = book;

		int* intAttribute[2] = { &book->yearPB, &book->quantity };
		float* floatAttribute[1] = { &book->price };
		char* stringAttribute[5] = { book->ISBN,book->name,book->author,book->publisher,book->genre };
		int lengthOfStringAttribute[] = { bookISBN,bookName,bookAuthor,bookPublisher,bookGenre };
		while (token != NULL && tokenCount < 8) {
			int passToken = 0;
			if (tokenCount >= 0 && tokenCount < 5) {
				strcpy_s(stringAttribute[tokenCount - passToken], lengthOfStringAttribute[tokenCount - passToken], token);
			}
			else passToken += 5;
			if (tokenCount >= 5 && tokenCount < 6) {
				*floatAttribute[tokenCount - passToken] = round(toFloat(token)*100)/100;
			}
			else passToken += 1;
			if (tokenCount >= 6 && tokenCount < 8) {
				*intAttribute[tokenCount - passToken] = toInt(token);
			}
			else passToken += 2;
			token = strtok_s(NULL, ",",&nextToken);
			tokenCount++;
		}
		fscanf_s(bookFile, "%*[\n ]");
	}
	sortData(books->storeIndex, books->books, 0, books->current-1);
	books->books[books->storeIndex[0]];
	fclose(bookFile);
	return true;
}
bool load(const Members* members, const Books* books,BorrowCardRecords* borrowCardRecords) {
	char fileName[] = "borrowCardRecords.txt";
	FILE* borrowCardFile;
	errno_t err = fopen_s(&borrowCardFile, fileName, "r");
	if (err != 0) return false;

	char line[256] = "\0";
	for (int i = 0; i < MEMBERCAPACITY; i++)
	{
		fscanf_s(borrowCardFile, "%*[\n ]");
		int memID;
		if(fscanf_s(borrowCardFile, "%d",&memID) == EOF) break;
		Member* member;
		int m = find(members, memID);
		if (m == -1) break;
		member = members->members[members->storeIndex[m]];
		borrowCardRecords->current = i + 1;
		borrowCardRecords->borrowCardRecords[i] = new BorrowCard;
		BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[i];
		init(borrowCard);
		borrowCard->member = member;
		
		fscanf_s(borrowCardFile, "%*[\n ]");
		for (int j = 0; j < 7 ; j++)
		{
			char line[256] = "\0";
			Book* book;
			if (fscanf_s(borrowCardFile, "%[^\n]", line, sizeof(line)) == EOF) break;
			char specialChar[] = "/";
			if (isEqualString(line, specialChar)) break;
			char* nextToken = NULL;
			char* token = strtok_s(line, ",",&nextToken);
			char* ISBN = token;
			int k = find(books, ISBN);
			if (k == -1) break;
			book = books->books[books->storeIndex[k]];
			borrowCard->books[j] = book;
			token = strtok_s(NULL, ",",&nextToken);

			borrowCard->dateBorrowed[j] = new Date;
			toDate(borrowCard->dateBorrowed[j], token);
			token = strtok_s(NULL, ",",&nextToken);
			
			borrowCard->expectDateReturn[j] = new Date;
			toDate(borrowCard->expectDateReturn[j],token);
			fscanf_s(borrowCardFile, "%*[\n ]");
		}
	}
	borrowCardRecords->borrowCardRecords[0]->expectDateReturn[1];
	fclose(borrowCardFile);
	return true;
}

bool save(const Members* members) {
	char fileName[] = "members.txt";
	FILE* file;
	errno_t err = fopen_s(&file,fileName, "w");
	if (err != 0) return false;

	for (int i = 0; i < members->current; i++)
	{
		int index = members->storeIndex[i];
		fprintf_s(file, "%d,", members->members[index]->ID);
		fprintf_s(file, "%s,", members->members[index]->CCCD);
		fprintf_s(file, "%s,", members->members[index]->fullname);
		fprintf_s(file, "%s,", members->members[index]->gender);
		fprintf_s(file, "%s,", members->members[index]->email);
		fprintf_s(file, "%s,", members->members[index]->address);
		fprintf_s(file, "%d ", members->members[index]->DOB->day);
		fprintf_s(file, "%d ", members->members[index]->DOB->month);
		fprintf_s(file, "%d,", members->members[index]->DOB->year);
		fprintf_s(file, "%d ", members->members[index]->MFG->day);
		fprintf_s(file, "%d ", members->members[index]->MFG->month);
		fprintf_s(file, "%d,", members->members[index]->MFG->year);
		fprintf_s(file, "%d ", members->members[index]->EXP->day);
		fprintf_s(file, "%d ", members->members[index]->EXP->month);
		fprintf_s(file, "%d\n", members->members[index]->EXP->year);
	}
	fclose(file);
	return true;
}
bool save(const Books* books) {
	char fileName[] = "books.txt";
	FILE* file;
	errno_t err = fopen_s(&file,fileName, "w");
	if (err != 0) return false;

	for (int i = 0; i < books->current; i++)
	{
		int index = books->storeIndex[i];
		fprintf_s(file, "%s,", books->books[index]->ISBN);
		fprintf_s(file, "%s,", books->books[index]->name);
		fprintf_s(file, "%s,", books->books[index]->author);
		fprintf_s(file, "%s,", books->books[index]->publisher);
		fprintf_s(file, "%s,", books->books[index]->genre);
		fprintf_s(file, "%f,", books->books[index]->price);
		fprintf_s(file, "%d,", books->books[index]->yearPB);
		fprintf_s(file, "%d\n", books->books[index]->quantity);
	}
	fclose(file);
	return true;
}
bool save(const BorrowCardRecords* borrowCardRecords) {
	char fileName[] = "borrowCardRecords.txt";
	FILE* file;
	errno_t err = fopen_s(&file, fileName, "w");
	if (err != 0) return false;
	for (int i = 0; i < borrowCardRecords->current; i++)
	{
		BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[i];
		fprintf(file, "%d\n", borrowCard->member->ID);
		for (int j = 0; j < 7; j++)
		{
			if (borrowCard->books[j] == NULL) break;
			char* ISBN = borrowCard->books[j]->ISBN;
			if (ISBN == NULL) break;
			fprintf(file, "%s,", ISBN);
			fprintf(file, "%d ", borrowCard->dateBorrowed[j]->day);
			fprintf(file, "%d ", borrowCard->dateBorrowed[j]->month);
			fprintf(file, "%d,", borrowCard->dateBorrowed[j]->year);
			fprintf(file, "%d ", borrowCard->expectDateReturn[j]->day);
			fprintf(file, "%d ", borrowCard->expectDateReturn[j]->month);
			fprintf(file, "%d\n", borrowCard->expectDateReturn[j]->year);
		}
		fprintf(file, "%/\n");
	}
	fclose(file);
	return true;
}

void add(Members* members, Member* member) {
	int low = 0;
	int high = members->current - 1;
	int i = -1;
	if (members->current == 0 || member->ID < members->members[members->storeIndex[low]]->ID) {
		i = 0;
	}
	else if (member->ID > members->members[members->storeIndex[low]]->ID) {
		i = high+1;
	}
	else {
		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (members->members[members->storeIndex[mid]]->ID > member->ID && members->members[members->storeIndex[mid - 1]]->ID < member->ID) {
				i = mid;
				break;
			}
			if (members->members[members->storeIndex[mid]]->ID < member->ID && members->members[members->storeIndex[mid+1]]->ID > member->ID) {
				i = mid+1;
				break;
			}
			if (members->storeIndex[mid] < member->ID) low = mid + 1;
			else high = mid - 1;
		}
	}
	members->current++;
	for (int k = members->current -1; k>i; k--)
	{
		members->storeIndex[k] = members->storeIndex[k - 1];
	}
	members->storeIndex[i] = members->storeVacant[members->current % MEMBERCAPACITY];
	int index = members->storeIndex[i];
	members->members[index] = member;
}
void add(Books* books, Book* book) {
	int low = 0;
	int high = books->current - 1;
	int i = -1;
	if (books->current == 0 || strcmp(book->ISBN,books->books[books->storeIndex[low]]->ISBN) < 0) {
		i = low;
	}
	else if (strcmp(book->ISBN, books->books[books->storeIndex[high]]->ISBN) > 0) {
		i = high + 1;
	}
	else {
		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (strcmp(books->books[books->storeIndex[mid]]->ISBN, book->ISBN)>0 && strcmp(books->books[books->storeIndex[mid - 1]]->ISBN , book->ISBN)<0) {
				i = mid;
				break;
			}
			if (strcmp(books->books[books->storeIndex[mid]]->ISBN, book->ISBN) < 0 && strcmp(books->books[books->storeIndex[mid+1]]->ISBN, book->ISBN) > 0) {
				i = mid + 1;
				break;
			}
			if (strcmp(books->books[books->storeIndex[mid]]->ISBN, book->ISBN)<0) low = mid + 1;
			else high = mid - 1;
		}
	}
	books->current++;
	for (int k = books->current - 1; k > i; k--)
	{
		books->storeIndex[k] = books->storeIndex[k - 1];
	}
	books->storeIndex[i] = books->storeVacant[books->current % MEMBERCAPACITY];
	int index = books->storeIndex[i];
	books->books[index] = book;
}
bool add(BorrowCardRecords* borrowCardRecords, Member* member, Book* book, Date* dateBorrowed) {
	int isExist = -1;
	int index = -1;

	for (int i = 0; i < borrowCardRecords->current; i++)
	{
		if (member == borrowCardRecords->borrowCardRecords[i]->member) {
			isExist = i;
			break;
		}
	}
	if (isExist == -1) {
		index = borrowCardRecords->current++;
		borrowCardRecords->borrowCardRecords[index] = new BorrowCard;
		init(borrowCardRecords->borrowCardRecords[index]);
	}
	else index = isExist;
	BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[index];
	int bookCount = 0;

	for (; borrowCard->books[bookCount] != NULL && bookCount < 7; bookCount++)
	{
		if (borrowCard->books[bookCount] == book) {
			return false;
		}
	}
	borrowCard->books[bookCount] = book;
	borrowCard->dateBorrowed[bookCount] = dateBorrowed;
	copyDate(borrowCard->expectDateReturn[bookCount],dateBorrowed);
	increaseDate(borrowCard->expectDateReturn[bookCount], 7);
	return true;
}

bool remove(Members* members, int ID) {
	int i = find(members, ID);
	if (i == -1) return false;
	int index = members->storeIndex[i];
	destruct(members->members[index]);
	members->members[index] = NULL;
	members->storeVacant[members->current % MEMBERCAPACITY] = -1;
	members->current--;
	if (i == MEMBERCAPACITY - 1) {
		members->storeIndex[i] = -1;
	}
	else {
		for (; i < members->current; i++)
		{
			members->storeIndex[i] = members->storeIndex[i + 1];
		}
		members->storeIndex[i] = -1;
	}
	return true;
}
bool remove(Books* books, char* ISBN) {
	int i = find(books, ISBN);
	if (i == -1) return false;
	int index = books->storeIndex[i];
	destruct(books->books[index]);
	books->books[index] = NULL;
	books->storeVacant[books->current % ISBNCAPACITY] = -1;
	books->current--;
	if (i == MEMBERCAPACITY - 1) {
		books->storeIndex[i] = -1;
	}
	else {
		for (; i < books->current; i++)
		{
			books->storeIndex[i] = books->storeIndex[i + 1];
		}
		books->storeIndex[i] = -1;
	}
	return true;
}
void remove(BorrowCardRecords* borrowCardRecords, int index, Member* member, Book* book, int bookBorrowedIndex, int bookCount) {
	BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[index];
	if (bookCount == 1) {
		borrowCard->books[0] = NULL;
		borrowCard->member = NULL;
		destruct(borrowCard);
		borrowCardRecords->borrowCardRecords[index] = NULL;
		borrowCardRecords->current--;
		if (index == borrowCardRecords->current) return;
		for (int i = index; i < borrowCardRecords->current; i++)
		{
			borrowCardRecords->borrowCardRecords[i] = borrowCardRecords->borrowCardRecords[i + 1];
		}
		return;
	}
	borrowCard->books[bookBorrowedIndex] = NULL;
	return;
}

int find(const Members* members,int ID) {
	int low = 0;
	int high = members->current - 1;
	int i = -1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		int index = members->storeIndex[mid];
		if (members->members[index]->ID == ID) {
			i = mid;
			break;
		}
		else if (members->members[index]->ID < ID) low = mid + 1;
		else high = mid - 1;
	}
	return i;
}
int findMemByCCCD(const Members* members, char* CCCD) {
	int length = strlen(CCCD);
	for (int i = 0; i < members->current; i++)
	{
		char* data = members->members[members->storeIndex[i]]->CCCD;
		if (isEqualString(data,CCCD)) {
			return members->storeIndex[i];
		}
	}
	return -1;
}
int* findMemByFullName(const Members* members, char* name, int accuracy)
{
	int* resultIndex = create<int>(members->current + 1, 1, -1);
	int size = 1;
	int length = strlen(name);
	for (int i = 0; i < members->current; i++)
	{
		char* data = members->members[members->storeIndex[i]]->fullname;
		if (isEqualString(data,name,accuracy)) {
			resultIndex[size] = members->storeIndex[i];
			size++;
		}
	}
	resultIndex[0] = size;
	return resultIndex;
}

int find(const Books* books, char* ISBN)
{
	int low = 0;
	int high = books->current - 1;
	int i = -1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		int index = books->storeIndex[mid];
		if (strcmp(books->books[index]->ISBN, ISBN) == 0) {
			i = mid;
			break;
		}
		else if (strcmp(books->books[index]->ISBN, ISBN) < 0) low = mid + 1;
		else high = mid - 1;
	}
	return i;
}
int* findBookByName(const Books* books, char* name, int accuracy)
{
	int* resultIndex = create<int>(books->current + 1, 1, -1);
	int size = 1;
	int length = strlen(name);
	for (int i = 0; i < books->current; i++)
	{
		char* data = books->books[books->storeIndex[i]]->name;
		if (isEqualString(data,name,accuracy)) {
			resultIndex[size] = books->storeIndex[i];
			size++;
		}
	}
	resultIndex[0] = size;
	return resultIndex;
}

//Chia mảng làm 2 phần lớn hơn và bé hơn 1 số
//storeIndex: lấy chỉ mục của dữ liệu, high: vị trí xa nhất của mảng, low: vị trí thấp nhất của mảng
//data: mảng cần chia, length: chiều dài của dữ liệu trong mảng
int partition(int* storeIndex, Member** data, int low, int high) {
	int pivot = data[storeIndex[high]]->ID;
	int i = low - 1;
	for (int j = low; j <= high; j++)
	{
		int index = storeIndex[j];
		if (data[index]->ID <= pivot) {
			i++;
			swap(storeIndex[i], storeIndex[j]);
		}
	}
	return i;
}


int partition(int* storeIndex, Book** data, int low, int high) {
	const char* pivot = data[storeIndex[high]]->ISBN;
	int i = low - 1;
	for (int j = low; j <= high; j++)
	{
		int index = storeIndex[j];
		if (strcmp(data[index]->ISBN,pivot) <=0 ) {
			i++;
			swap(storeIndex[i], storeIndex[j]);
		}
	}
	return i;
}

void sortData(int* storeIndex, Member **data,int low, int high) {
	if (low < high) {
		int pi = partition(storeIndex,data, low, high);
		sortData(storeIndex, data, low, pi - 1);
		sortData(storeIndex, data, pi + 1, high);
	}
}
void sortData(int* storeIndex, Book** data, int low, int high)
{
	if (low < high) {
		int pi = partition(storeIndex, data, low, high);
		sortData(storeIndex, data, low, pi - 1);
		sortData(storeIndex, data, pi+1, high);
	}
}
