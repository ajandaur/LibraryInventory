#include "inventory.h"

using namespace std;


void Inventory::addBook(Book book)
{
  Inventory::Books.push_back(book);
  //send the book that wanted to be added onto the vector
}

bool Inventory::findBookByTitle(std::string title, Book &book)
{
  std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(0, title, ""));
 if (it != Inventory::Books.end())
  {
    book = *it;
    return true;
  }
  else {
    return false;
  }
}

void Inventory::checkOutBook(Book &book) //pass by reference so value of book is changed
{
  book.checkedOut = true;
}

void  Inventory::checkInBook(Book &book)
{
  book.checkedOut = false;
}
