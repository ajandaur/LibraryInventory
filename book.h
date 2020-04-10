#pragma once
#include <iostream>

class Book {
  public:
    int Id;
    std::string Title;
    std::string Author;
    bool checkedOut = false;

    Book();
    Book(int id, std::string title, std::string author);


    //Comparing two books if they are the same
    
    bool operator ==(const Book& book) const
    {
      if(Title == book.Title)
        return true;
      else
        return false;
    }
};
