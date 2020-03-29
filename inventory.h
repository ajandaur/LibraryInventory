#pragma once

#include "book.h"
#include<vector>

class Inventory
{
  public:
    std::vector<Book> Books;

    void addBook(Book book);
    void removeBook (Book book);
    bool findBookByTitle(std::string title, Book &book);
    void checkOutBook(Book &book);
    void checkInBook(Book &book);

};
