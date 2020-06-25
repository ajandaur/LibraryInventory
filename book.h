#pragma once
#include <iostream>

class Book {
  public:
    int Id;

    Book(); //zero constructor
    Book(std::string title, std::string author); //default constructor

    void CheckInOrOut(bool checkOut);
    void DisplayBook();
    bool IsCheckedOut();
    std::string GetBookFileData();

    //overload operator to see if book titles are the same = same book
    bool operator ==(const Book& book) const
    {
      if(Title == book.Title)
        return true;
      else
        return false;
    }

  private:
    std::string Title;
    std::string Author;
    bool checkedOut;
};
