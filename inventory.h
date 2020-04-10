#pragma once

#include "book.h"
#include<vector>

class Inventory
{
  public:

    int maxBookId;


    Inventory();

    int getNextBookId();
    int numberOfBooks();
    Book* getBookByIndex(int index);
    void addBook(Book book);
    void removeBook (std::string title); //TODO
    int findBookByTitle(std::string title);
    void checkOutBook(Book* book);
    void checkInBook(Book* book);
    
  private:
    std::vector<Book> Books;
};
