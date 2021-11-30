#pragma once

#include "book.h"
#include "CheckInOutResult.h"
#include<vector>


class Inventory
{
  public:

    void DisplayCheckedOutBooks();
    void DisplayAllBooks();
    int numberOfBooks(); //returns number of books in vector
    Book getBookByIndex(int index); //returns book at index
    void addBook(Book book);
    void LoadBooks();
    void removeBook (std::string title);
    int findBookByTitle(std::string title);
    CheckInOrOutResult checkInOrOutBook(std::string title, bool checkOut);

  private:
    std::vector<Book> bookInventory;
};
