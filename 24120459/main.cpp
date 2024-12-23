#include <iostream>
#include "Controller.h"
#include "view.h"
#include "define.h"
#include <iomanip>

using namespace std;
int main() {
    Members* members = new Members;
    Books* books = new Books;
    BorrowCardRecords* borrowCardRecords = new BorrowCardRecords;
    //Start
    appStart(members,books,borrowCardRecords);

    int choice, subChoice;
    do
    {
        renderMenu();
        choice = inputChoice(4);
        switch (choice)
        {
        case 1: {
            do
            {
                renderSubMenu(1);
                subChoice = inputChoice(6);
                switch (subChoice)
                {
                case 1:
                    renderMems(members);
                    break;
                case 2:
                    addMem(members);
                    break;
                case 3:
                    updateMem(members);
                    break;
                case 4:
                    deleteMem(members);
                    break;
                case 5:
                    findMemByCCCD(members);
                    break;
                case 6:
                    findMemByFullName(members);
                    break;
                }
            } while (subChoice != 0);
            break;
        }
        case 2: {
            do
            {
                renderSubMenu(2);
                subChoice = inputChoice(6);
                switch (subChoice)
                {
                case 1:
                    renderBooks(books);
                    break;
                case 2:
                    addBook(books);
                    break;
                case 3:
                    updateBook(books);
                    break;
                case 4:
                    deleteBook(books);
                    break;
                case 5:
                    findBookByISBN(books);
                    break;
                case 6:
                    findBookByName(books);
                    break;
                }
            } while (subChoice != 0);
            break;
        }
        case 3: {
            do {
                renderSubMenu(3);
                subChoice = inputChoice(3);
                if (subChoice == 0) break;
                void (*feat[2])(const Members* members,const Books* books,BorrowCardRecords* borrowCardRecords) = {addBorrowCard,deleteBorrowCard };
                if (subChoice == 1) renderBorrowCardRecords(borrowCardRecords);
                else feat[subChoice - 2](members, books, borrowCardRecords);
            } while (true);
            break;
        }
        case 4: {
            do {
                renderSubMenu(4);
                subChoice = inputChoice(6);
                if (subChoice == 0) break;
                int passFeat = 0;
                if (subChoice > 0 && subChoice < 3) {
                    void (*feat[2])(const Members* members) = { statisticMemInLibrary,statisticMemByGender };
                    feat[subChoice - 1](members);
                }
                else passFeat += 2;
                if (subChoice>=3 && subChoice < 5) {
                    void (*feat[2])(const Books* member) = { statisticNumberOfBook,statisticBookByGenre };
                    feat[subChoice - passFeat - 1](books);
                }
                else passFeat += 2;
                if (subChoice>=5 && subChoice <= 6) {
                    void (*feat[2])(const BorrowCardRecords* borrowCardRecords) = { statisticBookBorrowed,statisticMemOverDue };
                    feat[subChoice - passFeat - 1](borrowCardRecords);
                }
                else passFeat += 2;
            } while (true);
            break;
        }
        }

    } while (choice != 0);

    //End
    appEnd(members,books,borrowCardRecords);
    return 0;
}
