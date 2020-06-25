#include "inventory.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int Inventory::numberOfBooks()
{
  return Books.size();
}

Book Inventory::getBookByIndex(int index)
{
  return Books[index];
}

void Inventory::LoadBooks()
{
  Books.clear();

  std::ifstream in("books.txt");

  std::string bookData[4];
  //bookData[0] = Id
  //bookData[1] = Title
  //bookData[2] = Author
  //bookData[3] = Checked out

  std::string bookLine;
  while(getline(in, bookLine))
  {
  size_t  nextIndex = bookLine.find('|');
  bookData[0] = bookLine.substr(0, nextIndex);

  size_t prevIndex = nextIndex;
  nextIndex = bookLine.find('|', prevIndex+1);

  bookData[1] = bookLine.substr(prevIndex+1, nextIndex - prevIndex- 1);
  prevIndex = nextIndex;
  nextIndex = bookLine.find('|', prevIndex+1);

  bookData[2] = bookLine.substr(prevIndex+1, nextIndex - prevIndex - 1);
  prevIndex = nextIndex;
  nextIndex = bookLine.find('|', prevIndex+1);

  bookData[3] = bookLine.substr(prevIndex+1, nextIndex - prevIndex - 1);

  Book loadedBook(bookData[1],bookData[2]);
  loadedBook.Id = stoi(bookData[0]);
  loadedBook.CheckInOrOut(stoi(bookData[3]));

  Books.push_back(loadedBook);
  }
}

void Inventory::addBook(Book book)
{
  int nextBookId = 0;
  if(Books.size() > 0)
  {
    nextBookId = Books.back().Id + 1;
  }
  //always asssume that last book in vector has the highest ID

  book.Id = nextBookId;

  Inventory::Books.push_back(book);

  std::ofstream o("books.txt", ios_base::app);
  o << book.GetBookFileData() << std::endl;
  o.close();

}

void Inventory::removeBook(std::string title)
{
 std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book( title, ""));
 if (it != Inventory::Books.end()) //.end refers to past the end
  {
    Inventory::Books.erase(it);
  }
}
//find the book at the iterator and erase at that iterator

int Inventory::findBookByTitle(std::string title)
{
  std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book( title, ""));
 if (it == Inventory::Books.end()) //.end refers to past the end
  {
    return -1;
  }

    int index = it - Inventory::Books.begin();
}

CheckInOrOutResult Inventory::checkInOrOutBook(std::string title, bool checkOut) //pass by reference so value of book is changed
{
  int foundBookIndex = findBookByTitle(title); //gives index

  if(foundBookIndex < 0)//if you didn't find book
  {
    return CheckInOrOutResult::BookNotFound;
  }
  else if(checkOut == Books[foundBookIndex].IsCheckedOut())
  {
    if(checkOut)
    {
      return CheckInOrOutResult::AlreadyCheckedOut;
    }
    else
    {
      return CheckInOrOutResult::AlreadyCheckedIn;
    }

  }


  Books[foundBookIndex].CheckInOrOut(checkOut);

  std::ofstream o("books.txt");
  for (size_t i = 0; i < Books.size(); i++) {
    o << Books[i].GetBookFileData() << endl;
  }

  return CheckInOrOutResult::Success;
}

void Inventory::DisplayAllBooks()
{
  //access to vector since we are in Inventory class
  cout << "\nID\tTitle\tAuthor\n" <<endl;
  for (int i = 0; i < numberOfBooks(); i++)
  {
    Books[i].DisplayBook();
  }
  cout << endl;

}

void Inventory::DisplayCheckedOutBooks()
{
  //access to vector since we are in Inventory class
  cout << "\nID\tTitle\tAuthor\n" <<endl;
  for (int i = 0; i < numberOfBooks(); i++)
  {
    if(getBookByIndex(i).IsCheckedOut())
    {
      Books[i].DisplayBook();
    }
  }
  cout << endl;

}
