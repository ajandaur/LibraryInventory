#include "inventory.h"
#include <vector>

using namespace std;



Inventory::Inventory()
{
  Inventory::maxBookId = 0;
}

int Inventory::getNextBookId()
{
  Inventory::maxBookId++;
  return Inventory::maxBookId;
}

int Inventory::numberOfBooks()
{
  return Inventory::Books.size();
}

Book* Inventory::getBookByIndex(int index)
{
  return &Inventory::Books[index];
}



void Inventory::addBook(Book book)
{
  Inventory::Books.push_back(book);
  //send the book that wanted to be added onto the vector
}

void Inventory::removeBook(std::string title)
{
  std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(0, title, ""));
 if (it != Inventory::Books.end()) //.end refers to past the end
  {
    Inventory::Books.erase(it);
  }
}
//find the book at the iterator and erase at that iterator

int Inventory::findBookByTitle(std::string title)
{
  std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(0, title, ""));
 if (it == Inventory::Books.end()) //.end refers to past the end
  {
    return -1;
  }

    int index = it - Inventory::Books.begin();
}

void Inventory::checkOutBook(Book* book) //pass by reference so value of book is changed
{
  book-> checkedOut = true;
}

void  Inventory::checkInBook(Book* book)
{
  book-> checkedOut = false;
}
