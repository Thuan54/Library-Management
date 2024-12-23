#include <iostream>
#include <math.h>
#include "View.h"
#include "model.h"
#include "define.h"

using namespace std;

int inputChoice(int max) {
    int input;
    bool condition = true;
    do
    {
        cout << "Nhap lua chon: ";
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            hold();
            cout << "\033[A\033[K";
            condition = false;
        }
        else if (!(condition = input >= 0 && input <= max)) {

            cout << "Lua chon khong hop le. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (!condition);
    char c;
    while (c = getchar() != '\n');
    return input;
}

//Lấy giá trị nhập vào của 1 số
//min, max: giới hạn của số
//Trả về giá trị của số nhập vào
template<typename T> T inputNum(T min = -99999999, T max = 999999999) {
    T input = 0;
    bool condition = true;
    cout << endl;
    do
    {
        cin >> input;
        condition = !cin.fail();
        if (!condition) {
            cin.clear();
            cout << "So nhap khong hop le. Vui long nhap lai. Enter" << endl;
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
        else {
            condition = input >= min && input <= max;
            if (!condition) {
                cin.clear();
                cout << "So nhap khong dung. Vui long nhap lai. Enter" << endl;
                hold();
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
            }
            else return input;
        }
    } while (!condition);
    return input;
};

//Lấy giá trị ngày nhập vào
//day, month, year: nơi chứa giá trị nhập vào
void inputDate(Date* date) {
    int day, month, year;
    bool condition = true;
    do
    {
        cout << "Nhap ngay: ";
        day = inputNum<int>(1, 31);
        cout << "Nhap thang: ";
        month = inputNum<int>(1, 12);
        cout << "Nhap nam: ";
        year = inputNum<int>();
        switch (month)
        {
        case 1: case 3: case 5: case 7: case 8:case 10: case 12:
            condition = true;
            break;
        case 2:
            if (isLeapYear(year) && day < 30) condition = true;
            if (!isLeapYear(year) && day < 29) condition = true;
            break;
        default:
            if (day > 30) condition = false;
            break;
        }
        if (!condition) {
            cout << "Ngay nhap khong dung. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (!condition);
    date->day = day;
    date->month = month;
    date->year = year;
    cin.ignore(1000, '\n');
}

//Lấy dữ liệu chuỗi nhập vào
//s: nơi lưu giá trị nhập vào, length: độ dài chuỗi
void getStringInput(char* s, int length) {
    int i = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (i < length - 1) {
            s[i] = c;
            i++;
        }
    }
    s[i] = '\0';
}

void appStart(Members* members,Books* books,BorrowCardRecords* borrowCardRecords) {
    members->current = 0;
    members->storeIndex = create<int>(1,MEMBERCAPACITY,-1);
    members->storeVacant = create<int>(1, MEMBERCAPACITY, -1);
    for (int i = 0; i < MEMBERCAPACITY; i++)
    {
        members->storeVacant[i] = i;
    }
    members->members = create<Member*>(MEMBERCAPACITY,1, NULL);
    
    books->current = 0;
    books->storeIndex = create<int>(1, ISBNCAPACITY, -1);
    books->storeVacant = create<int>(1, ISBNCAPACITY, -1);
    for (int i = 0; i < ISBNCAPACITY; i++)
    {
        books->storeVacant[i] = i;
    }
    books->books = create<Book*>(ISBNCAPACITY, 1, NULL);

    borrowCardRecords->current = 0;
    borrowCardRecords->borrowCardRecords = create<BorrowCard*>(MEMBERCAPACITY,1, NULL);

    if (!load(members)) cout << "Khong the mo file chua thong tin cac doc gia de doc" << endl;
    if (!load(books)) cout << "Khong the mo file chua thong tin cac sach de doc" << endl;
    if (!load(members,books,borrowCardRecords)) cout << "Khong the mo file chua thong tin cac the muon sach de doc" << endl;
}
void appEnd(Members* &members, Books* &books, BorrowCardRecords* &borrowCardRecords) {
    if (!save(members)) cout << "Khong the mo file chua thong tin cac doc gia de ghi" << endl;
    if (!save(books)) cout << "Khong the mo file chua thong tin cac sach de ghi" << endl;
    if(!save(borrowCardRecords)) cout << "Khong the mo file chua thong tin the muon de ghi" << endl;
    
    delete[] members->storeIndex;
    delete[] members->storeVacant;
    for (int i = 0; i < MEMBERCAPACITY; i++)
    {
        destruct(members->members[i]);
    }
    delete[] members->members;
    delete members;

    delete[] books->storeIndex;
    delete[] books->storeVacant;
    for (int i = 0; i < ISBNCAPACITY; i++)
    {
        destruct(books->books[i]);
    }
    delete[] books->books;
    delete books;

    for (int i = 0; i < MEMBERCAPACITY; i++)
    {
        destruct(borrowCardRecords->borrowCardRecords[i]);
    }
    delete borrowCardRecords->borrowCardRecords;
    delete borrowCardRecords;
}

//Member
void renderMems(const Members* members){
    clearScreen();
    renderMemAttribute();
    for (int i = 0; i < members->current; i++)
    {
        int index = members->storeIndex[i];
        render(members->members[index]);
    }
    hold();
}
void addMem(Members* members) {
    int ID;
    char CCCD[memCCCD] = "\0";
    Date* today = new Date;
    getToday(today);
    bool condition = false;
    if (members->current >= MEMBERCAPACITY) {
        cout << "Doc gia day. Vui long nang cap co so du lieu!" << endl;
        hold();
        return;
    }
    do
    {
        cout << "Nhap ma doc gia (8 chu so): ";
        ID = inputNum<int>(9999999, 99999999);
        condition = find(members,ID) == -1;
        if (condition) {
            do
            {
                cout << "Nhap CCCD doc gia (12 chu so): ";
                getStringInput(CCCD, sizeof(CCCD));
                condition = findMemByCCCD(members, CCCD) == -1;
                if (!condition) {
                    cout << "CCCD doc gia da ton tai. Vui long nhap lai. Enter";
                    hold();
                    cout << "\033[A\033[K";
                    cout << "\033[A\033[K";
                }
            } while (!condition);
        }
        else {
            cout << "Ma doc gia da ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (!condition);

    Member* member = new Member;
    init(member);
    member->ID = ID;
    strcpy_s(member->CCCD, memCCCD, CCCD);
    while (getchar() != '\n');
    cout << "Nhap ten doc gia: ";
    getStringInput(member->fullname, memFullName);

    cout << "Nhap gioi tinh: ";
    getStringInput(member->gender, memGender);

    cout << "Nhap email doc gia: ";
    getStringInput(member->email, memEmail);

    cout << "Nhap dia chi doc gia: ";
    getStringInput(member->address, memAddress);

    cout << "Nhap ngay sinh doc gia" << endl;
    inputDate(member->DOB);

    copyDate(member->MFG, today);
    delete today;
    copyDate(member->EXP, member->MFG);

    if (member->EXP->month == 2 && member->EXP->day == 29) {
        if (isLeapYear(member->DOB->year + 4)) member->EXP->year += 4;
        else {
            member->EXP->day = 1;
            member->EXP->month = 3;
            member->EXP->year += 4;
        }
    }
    else member->EXP->year += 4;
    add(members, member);
    cout << endl << "Da them doc gia!";
    hold();
}
void updateMem(Members* members) {
    int ID = 0, index = -1;
    do
    {
        cout << "Nhap ma doc gia can chinh sua (8 chu so): ";
        ID = inputNum<int>(9999999, 99999999);
        int i = find(members, ID);
        if (i == -1) {
            cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
        else {
            index = members->storeIndex[i];
            break;
        }
    } while (true);
    renderMemberUpdateMenu();
    Member* member = members->members[index];
    int choice = inputChoice(9);
    switch (choice)
    {
        case 1: {
            do {
                cout << "Nhap ma doc gia moi (8 chu so): ";
                int ID2 = inputNum<int>(9999999, 99999999);
                int i2 = find(members, ID2);
                if (i2 != -1) {
                    cout << "Ma doc gia da ton tai. Vui long nhap lai. Enter";
                    hold();
                    cout << "\033[A\033[K";
                    cout << "\033[A\033[K";
                }
                else {
                    member->ID = ID2;
                    sortData(members->storeIndex, members->members, 0, members->current - 1);
                    cout << "Da cap nhat!";
                    hold();
                    break;
                }
            } while (true);
            break;
        }
        case 2: {
            cout << "Nhap ten moi (toi da 20 ki tu): ";
            getStringInput(member->fullname, memFullName);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 3: {
            cout << "Nhap CCCD moi (12 chu so): ";
            char CCCD[memCCCD];
            do
            {
                getStringInput(CCCD, memCCCD);
                if (findMemByCCCD(members, CCCD) != -1) {
                    cout << "CCCD da ton tai. Vui long nhap lai!" << endl;
                    hold();
                    cout << "\033[A\033[K";
                }
                else {
                    strcpy_s(member->CCCD,memCCCD, CCCD);
                    break;
                }
            } while (true);
            cout << "Da cap nhat";
            hold();
            break;
        }
        case 4: {
            cout << "Nhap ngay thang nam sinh moi: " << endl;
            inputDate(member->DOB);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 5: {
            cout << "Nhap gioi tinh khac: ";
            getStringInput(member->gender, memGender);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 6: {
            cout << "Nhap email moi (toi da 20 ki tu): ";
            getStringInput(member->email, memEmail);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 7: {
            cout << "Nhap dia chi moi (toi da 20 ki tu): ";
            getStringInput(member->address, memAddress);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 8: {
            cout << "Nhap ngay thanh lap moi: " << endl;
            inputDate(member->MFG);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 9: {
            cout << "Nhap ngay het han moi: " << endl;
            inputDate(member->EXP);
            cout << "Da cap nhat!";
            hold();
            break;
        }
    }

}
void deleteMem(Members* members) {
    int ID, index;
    if (members->current == 0) {
        cout << "Khong co doc gia de xoa!" << endl;
        hold();
        return;
    }
    do
    {
        cout << "Nhap ma doc gia can xoa (8 chu so): ";
        ID = inputNum<int>(9999999, 99999999);
        if (!remove(members, ID)) {
            cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
        else break;
    } while (true);

    cout << "Thanh cong!";
    hold();
}
void findMemByCCCD(const Members* members) {
    cout << "Nhap CCCD muon tim (12 chu so): ";
    char CCCD[memCCCD];
    getStringInput(CCCD, sizeof(CCCD));
    int index = findMemByCCCD(members, CCCD);
    Member* member = members->members[index];
    render(member);
    hold();
}
void findMemByFullName(const Members* members) {
    char fullName[memFullName];
    while (getchar() != '\n');
    cout << "Nhap ho ten muon tim: ";
    getStringInput(fullName, sizeof(memFullName));
    cout << "Do chinh xac" << endl;
    cout << "1. Chinh xac tuyet doi" << endl;
    cout << "0. Chinh xac den ki tu cuoi" << endl;
    int accuracy = inputChoice(1);
    int* indexes = findMemByFullName(members, fullName, accuracy);
    for (int i = 1; i < indexes[0]; i++)
    {
        render(members->members[indexes[i]]);
    }
    delete[] indexes;
    hold();
}

//Book
void renderBooks(const Books* books) {
    clearScreen();
    renderBookAttribute();
    for (int i = 0; i < books->current; i++)
    {
        int index = books->storeIndex[i];
        render(books->books[index]);
    }
    hold();
}
void addBook(Books* books) {
    char ISBN[bookISBN];
    bool condition = false;
    if (books->current >= ISBNCAPACITY) {
        cout << "Sach day. Vui long nang cap co so du lieu!";
        hold();
        return;
    }
    do
    {
        cout << "Nhap ma sach (13 chu so): ";
        getStringInput(ISBN, sizeof(ISBN));
        condition = find(books,ISBN) == -1;
        if (!condition) {
            cout << "Ma sach da ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (!condition);

    Book* book = new Book;
    init(book);
    strcpy_s(book->ISBN, bookISBN, ISBN);

    cout << "Nhap ten sach: ";
    getStringInput(book->name, bookName);

    cout << "Nhap ten tac gia: ";
    getStringInput(book->author, bookAuthor);

    cout << "Nhap ten nha xuat ban: ";
    getStringInput(book->publisher, bookPublisher);

    cout << "Nhap ten the loai sach: ";
    getStringInput(book->genre, bookGenre);

    cout << "Nhap nam xuat ban: ";
    book->yearPB = inputNum<int>(999, 9999);

    cout << "Nhap gia sach: ";
    book->price = inputNum<float>(0);

    cout << "Nhap so luong sach: ";
    book->quantity = inputNum<int>(0);
    add(books, book);
    cout << "Da them sach!";
    hold();
}
void updateBook(Books* books) {
    int index= -1;
    char ISBN[bookISBN] = "\0";
    do
    {
        cout << "Nhap ma sach can chinh sua (8 chu so): ";
        getStringInput(ISBN, sizeof(ISBN));
        int i = find(books, ISBN);
        if (i == -1) {
            cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
        else {
            index = books->storeIndex[i];
            break;
        }
    } while (true);
    renderBookUpdateMenu();
    Book* book = books->books[index];
    int choice = inputChoice(8);

    switch (choice)
    {
        case 1: {
            do {
                cout << "Nhap ma sach can chinh sua (8 chu so): ";
                char ISBN2[bookISBN];
                getStringInput(ISBN2, sizeof(ISBN2));
                int i2 = find(books, ISBN2);
                if (i2 != -1) {
                    cout << "Ma sach da ton tai. Vui long nhap lai. Enter";
                    hold();
                    cout << "\033[A\033[K";
                    cout << "\033[A\033[K";
                }
                else {
                    strcpy_s(book->ISBN,bookISBN, ISBN2);
                    sortData(books->storeIndex, books->books, 0, books->current);
                    cout << "Da cap nhat!";
                    hold();
                    break;
                }
            } while (true);
            break;
        }
        case 2: {
            cout << "Nhap ten sach moi (toi da 20 ki tu): ";
            getStringInput(book->name, bookName);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 3: {
            cout << "Nhap ten tac gia moi (toi da 20 ki tu): ";
            getStringInput(book->author, bookAuthor);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 4: {
            cout << "Nhap ten nha xuat ban moi (toi da 20 ki tu): ";
            getStringInput(book->publisher, bookPublisher);
            cout << "Da cap nhat!";
            hold();
            break;
        }
        case 5: {
            cout << "Nhap nam xuat ban moi: ";
            book->yearPB = inputNum<int>(999, 9999);
            cout << "Da cap nhat";
            hold();
            break;
        }
        case 6: {
            cout << "Nhap the loai moi (toi da 20 ki tu): ";
            getStringInput(book->genre, bookGenre);
            cout << "Da cap nhat!";
            break;
        }
        case 7: {
            cout << "Nhap gia sach moi: ";
            book->price = inputNum<float>(0);
            cout << "Da cap nhat";
            hold();
            break;
        }
        case 8: {
            cout << "Nhap so quyen sach moi: ";
            book->quantity = inputNum<int>(0);
            cout << "Da cap nhat";
            hold();
            break;
        }
    }
}
void deleteBook(Books* books) {
    char ISBN[bookISBN];
    if (books->current == 0) {
        cout << "Khong co sach de xoa!";
        hold();
        return;
    }
    do
    {
        cout << "Nhap ma sach can xoa (13 chu so): ";
        getStringInput(ISBN, bookISBN);
        if (!remove(books, ISBN)) {
            cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
        else break;
    } while (true);

    cout << "Thanh cong!";
    hold();
}
void findBookByISBN(const Books* books) {
    cout << "Nhap ISBN muon tim (13 chu so): ";
    char ISBN[bookISBN];
    getStringInput(ISBN, bookISBN);
    int i = find(books, ISBN);
    int index = books->storeIndex[i];
    render(books->books[index]);
    cout << "Thanh cong!";
    hold();
}
void findBookByName(const Books* books) {
    char name[bookName];
    while (getchar() != '\n');
    cout << "Nhap ten sach muon tim: ";
    getStringInput(name, bookName);
    cout << "Do chinh xac" << endl;
    cout << "1. Chinh xac tuyet doi" << endl;
    cout << "0. Chinh xac den ki tu cuoi" << endl;
    int accuracy = inputChoice(1);
    int* indexes = findBookByName(books,name,accuracy);
    
    for (int i = 1; i < indexes[0]; i++)
    {
        render(books->books[i]);
    }

    delete[] indexes;
    cout << "Thanh cong!";
    hold();
}

//LibCard
void renderBorrowCardRecords(const BorrowCardRecords* borrowCardRecords) {
    clearScreen();
    renderBorrowCardAttribute();
    for (int i = 0; i < borrowCardRecords->current; i++)
    {
        if (borrowCardRecords->borrowCardRecords[i] == NULL) break;
        render(borrowCardRecords->borrowCardRecords[i]);
    }
    hold();
}
void addBorrowCard(const Members* members,const Books* books,BorrowCardRecords* borrowCardRecords) {
    int memIndex = -1,bookIndex = -1, bookCount = 0;
    bool condition = true;
    Date* today = new Date;
    getToday(today);
    do {
        int index = -1;
        do
        {
            cout << "Nhap ma doc gia (8 chu so): ";
            int memID = inputNum<int>(9999999, 99999999);
            int i = find(members,memID);
            if (i == -1) {
                cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
                hold();
                cout << "\033[A\033[K";
            }
            else {
                index = members->storeIndex[i];
                break;
            };
        } while (true);
        Member* member = members->members[index];
        for (int i = 0; i < borrowCardRecords->current; i++)
        {
            if (borrowCardRecords->borrowCardRecords[i] != NULL) {
                if (borrowCardRecords->borrowCardRecords[i]->member == member) {
                    memIndex = i;
                    break;
                }
            }
        }
        if (memIndex != -1) {
            
            bookCount = 0;
            for (int i = 0; i < 7; i++)
            {
                if (borrowCardRecords->borrowCardRecords[memIndex]->books[i] == NULL) break;
                condition = diffTwoDates(borrowCardRecords->borrowCardRecords[memIndex]->dateBorrowed[i], today) <= 7;
                if (!condition) {
                    cout << "Doc gia co sach qua han chua tra. Hay tra truoc khi muon sach moi!" << endl;
                    hold();
                    cout << "\033[A\033[K";
                    break;
                }
                bookCount++;
            }
        }
        else break;
    } while (!condition);

    if (bookCount == 7) {
        cout << "Doc gia da muon toi da 7 cuon" << endl;
        hold();
        return;
    }
    cout << "Doc gia duoc phep muon " << 7 - bookCount << " quyen sach" << endl;
    cout << "Nhap so luong sach muon: ";
    int bookBorrow = inputNum<int>(0, 7 - bookCount);
    char ISBN[bookISBN];

    for (int i = 0; i < bookBorrow; )
    {
        do
        {
            int j = -1;
            cout << "Nhap ma sach (13 chu so): ";
            getStringInput(ISBN, bookISBN);
            if ((j =find(books,ISBN)) == -1) {
                cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
                hold();
                cout << "\033[A\033[K";
            }
            else {
                bookIndex = books->storeIndex[i];
                condition = books->books[bookIndex]->quantity > 0;
                if (!condition) {
                    cout << "So luong sach da het. Vui long muon sach khac";
                    hold();
                    cout << "\033[A\033[K";
                }
                else break;
            }
        } while (true);
        Member* member = members->members[memIndex];
        Book* book = books->books[bookIndex];
        Date* dateBorrowed = new Date;
        copyDate(dateBorrowed, today);
        if (!add(borrowCardRecords, member, book, dateBorrowed)) {
            cout << "Ban da muon sach nay. Vui long muon sach khac" << endl;
            hold();
            cout << "\033[A\033[K";
        }
        else i++;
    }
    cout << "Muon thanh cong!";
    hold();
    delete today;
}
void deleteBorrowCard(const Members* members, const Books* books, BorrowCardRecords* borrowCardRecords) {
    Date* today = new Date;
    getToday(today);
    int index = -1, memIndex = -1,bookCount = 0;
    bool condition = false;
    float charge = 0;
    do {
        do
        {
            cout << "Nhap ma doc gia (8 chu so): ";
            int memID = inputNum<int>(9999999, 99999999);
            int i = find(members, memID);
            if (i == -1) {
                cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
                hold();
                cout << "\033[A\033[K";
            }
            else {
                memIndex = members->storeIndex[i];
                break;
            }
        } while (true);
        Member* member = members->members[memIndex];
        for (int j = 0; j < borrowCardRecords->current; j++)
        {
            BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[j];
            if (borrowCard == NULL) break;
            if (borrowCard->member == member) {
                index = j;
                condition = true;
                break;
            }
        }
        if (!condition) {
            cout << "Doc gia chua muon sach nao!" << endl;
            cout << "Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
        else {
            BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[index];
            for (int j = 0; j < 7; j++)
            {
                if (borrowCard->books[j] != NULL) bookCount++;
            }
        }
    } while (!condition);
    
    cout << "Doc gia da muon " << bookCount << " sach" << endl;
    cout << "Nhap so luong sach tra: ";
    int bookReturn = inputNum<int>(1, bookCount);
    for (int j = 0; j < bookReturn; j++)
    {
        do
        {
            cout << "Nhap ma sach (13 chu so): ";
            char ISBN[bookISBN];
            getStringInput(ISBN, sizeof(ISBN));
            int i = -1;
            if ((i = find(books,ISBN)) == -1) {
                cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
                hold();
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
            }
            else {
                int bookIndex = books->storeIndex[i];
                Member* member = members->members[memIndex];
                Book* book = books->books[bookIndex];
                BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[index];
                int k = 0;
                for (; k < bookCount; k++)
                {
                    if (borrowCard->books[k] == book) {
                        cout << "Mat sach" << endl;
                        cout << "1. Co" << endl;
                        cout << "0. Khong" << endl;
                        int choice = inputChoice(2);
                        if (choice == 1) {
                            charge += book->price * 2;
                            book->quantity--;
                        }
                        int overDueDate = diffTwoDates(borrowCard->expectDateReturn[k], today);
                        if (overDueDate > 0) {
                            charge += overDueDate * 2000;
                        }
                        cout << "Tien phat: " << charge << endl;
                        remove(borrowCardRecords, index, member, book, k, bookCount);
                        book->quantity++;
                        break;
                    }
                }if (k >= bookCount) {
                    cout << "Doc gia chua muon sach nay!" << endl;
                    cout << "Vui long nhap lai. Enter";
                    hold();
                    cout << "\033[A\033[K";
                    cout << "\033[A\033[K";
                }
                else break;
            }
        } while (true);
    }
    cout << "Tra sach thanh cong!";
    hold();
    delete today;
}

//Statistic
void statisticBookByGenre(const Books* books) {
    int count = 0;
    int* groupGenres = create<int>(1, books->current, -1);
    int* I = create<int>(1, books->current, 0);
    for (int i = 0; i < books->current; i++)
    {
        if (I[i] == -1) continue;
        Book* originalBook = books->books[books->storeIndex[i]];
        for (int j = i; j < books->current; j++)
        {
            Book* book = books->books[books->storeIndex[j]];
            if (I[j] == -1) continue;
            if (isEqualString(originalBook->genre, book->genre)) {
                I[j] = -1;
                groupGenres[count] = books->storeIndex[j];
                count++;
            }
        }
    }
    clearScreen();
    renderBookAttribute();
    for (int i = 0; i < books->current; i++)
    {
        render(books->books[groupGenres[i]]);
    }
    delete I;
    delete groupGenres;
    hold();
}
void statisticNumberOfBook(const Books* books) {
    int total = 0;
    for (int i = 0; i < books->current; i++)
    {
        int index = books->storeIndex[i];
        total += books->books[index]->quantity;
    }
    cout << "Dang co " << total << " sach trong thu vien" << endl;
    hold();
}
void statisticMemByGender(const Members* members) {
    int count = 0;
    int* groupGenders = create<int>(1, members->current, -1);
    int* I = create<int>(1, members->current, 0);
    for (int i = 0; i < members->current; i++)
    {
        if (I[i] == -1) continue;
        Member* originalMem = members->members[members->storeIndex[i]];
        for (int j = i; j < members->current; j++)
        {
            Member* member = members->members[members->storeIndex[j]];
            if (I[j] == -1) continue;
            if (isEqualString(originalMem->gender, member->gender)) {
                I[j] = -1;
                groupGenders[count] = members->storeIndex[j];
                count++;
            }
        }
    }
    clearScreen();
    renderMemAttribute();
    for (int i = 0; i < members->current; i++)
    {
        render(members->members[groupGenders[i]]);
    }
    delete I;
    delete groupGenders;
    hold();
}
void statisticMemInLibrary(const Members* members) {
    cout << "Dang co " << members->current << " doc gia trong he thong thu vien" << endl;
    hold();
}
void statisticBookBorrowed(const BorrowCardRecords* borrowCardRecords) {
    int bookBorrowedCount = 0;
    for (int i = 0; i < borrowCardRecords->current; i++)
    {
        BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[i];
        if (borrowCard == NULL) break;
        for (int j = 0; j < 7; j++)
        {
            if (borrowCard->books[j] == NULL) break;
            bookBorrowedCount++;
        }
    }
    cout << "Dang co " << bookBorrowedCount << " duoc muon" << endl;
    hold();
}
void statisticMemOverDue(const BorrowCardRecords* borrowCardRecords) {
    Date* today = new Date;
    getToday(today);
    int countMemOverDue = 0;
    clearScreen();
    renderBorrowCardAttribute();
    for (int i = 0; i < borrowCardRecords->current; i++)
    {
        BorrowCard* borrowCard = borrowCardRecords->borrowCardRecords[i];
        if (borrowCard == NULL) break;
        BorrowCard* memOverDue = new BorrowCard;
        init(memOverDue);
        int count = 0;
        int isOverDue = false;
        for (int j = 0; j < 7 ; j++)
        {
            if (borrowCard->books[j] == NULL) break;
            int overDueDays = diffTwoDates(today, borrowCard->expectDateReturn[j]);
            if (overDueDays > 0) {
                isOverDue = true;
                memOverDue->books[count] = borrowCard->books[j];
                count++;
                countMemOverDue++;
            }
        }
        if (isOverDue) {
            memOverDue->member = borrowCard->member;
            memOverDue->dateBorrowed = borrowCard->dateBorrowed;
            memOverDue->expectDateReturn = borrowCard->expectDateReturn;
            render(memOverDue);
        }
        destruct(memOverDue);
    }
    delete today;
    hold();
}
