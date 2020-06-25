#pragma once

#include "book.h"
#include "CheckInOutResult.h"
#include<vector>


class Inventory
{
  public:

    void DisplayCheckedOutBooks();
    void DisplayAllBooks();
    int numberOfBooks();
    Book getBookByIndex(int index); //pointer
    void addBook(Book book);
    void LoadBooks();
    void removeBook (std::string title);
    int findBookByTitle(std::string title);
    CheckInOrOutResult checkInOrOutBook(std::string title, bool checkOut); //pointer

  private:
    std::vector<Book> Books;
};
