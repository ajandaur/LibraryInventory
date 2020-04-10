#include <iostream>
#include "book.h"
#include "inventory.h"
#include <string>

using namespace std;

Inventory _inventory;

void displayStartupmenu()
{
  cout << "Please input which option you desire." <<endl;
  cout << "1. Add a book" <<endl;
  cout << "2. List all books" <<endl;
  cout << "3. Check out book" <<endl;
  cout << "4. Check in book" <<endl;
  cout << "5. Remove book from library" <<endl;
  cout << "6. List all checked out books" << endl;
  cout << "0. Exit Library Inventory" <<endl;
}

void addNewBook()
{
  cout << "What is the title of the book you want to add?" <<endl;
  string bookTitle;
  getline(cin, bookTitle); //use getline to get the full title

  cout << "What is the author of the book?"<<endl;
  string bookAuthor;
  getline(cin, bookAuthor); //use getline to get the full title

  int id = _inventory.getNextBookId();
  //temporary solution, problem when removing books

  Book newBook(id, bookTitle, bookAuthor);

  _inventory.addBook(newBook);
}

void listAllBooks()
{
  cout << "\nID\tTitle\tAuthor\n";
  for (int i = 0; i < _inventory.numberOfBooks(); i++)
  {
    cout << _inventory.getBookByIndex(i)-> Id << "\t" << _inventory.getBookByIndex(i)-> Title << "\t" << _inventory.getBookByIndex(i)-> Author << endl;
  }
  cout << endl;
}

void checkInOrOutBook(bool checkIn)
{
  string inOrOut;
  if(checkIn)
  {
    inOrOut = "in";
  }
  else
  {
    inOrOut = "out";
  }
  cout << "Enter the title of the book you would like to check " + inOrOut + ": ";
  string title;
  getline(cin, title);

  int foundBookIndex = _inventory.findBookByTitle(title);

  if(foundBookIndex >= 0)
  {
      Book* foundBook = _inventory.getBookByIndex(foundBookIndex);

      // if checkedOut == false then we're checked in
      // if checkedOut == true then we're checked out

    if(!foundBook-> checkedOut == checkIn) //get the object at the point and look at the checked out property
    {
      cout << "Book already checked " + inOrOut << endl;
      return; //not break because we are not in a switch statement
    }

    if(checkIn)
    {
      _inventory.checkInBook(foundBook);
    }
    else {
      _inventory.checkOutBook(foundBook);
    }

    cout << "Success, book checked" + inOrOut + "!"<<endl;
  }
  else
  {
    cout << "Sorry! Your requested book was not found!"<<endl;
  }
}

void removeBook()
{
  cout << "What is the title of the book you want to add?" <<endl;
  string bookTitle;
  getline(cin, bookTitle); //use getline to get the full title
  _inventory.removeBook(bookTitle);
}

void displayCheckedOutBooks()
{
  for (int i = 0; i < _inventory.numberOfBooks(); i++) {
    if(_inventory.getBookByIndex(i)-> checkedOut)
    {
        cout << _inventory.getBookByIndex(i)-> Id << "\t" << _inventory.getBookByIndex(i)-> Title << "\t" << _inventory.getBookByIndex(i)-> Author << endl;
    }
  }
  cout << endl;
}


int main()
{
  while(true) {

    displayStartupmenu();

    int input;
    cin >> input;
    cin.ignore(); //To prevent getline from trying to get rest of cin

    switch (input)
    {
      case 0:
        cout << "Thank you for using our service!";
        return 0;
      case 1:
        addNewBook();
        break;
      case 2:
        listAllBooks();
        break;
      case 3:
        checkInOrOutBook(false); //checking out
        break;
      case 4:
        checkInOrOutBook(true); //checking in
        break;
      case 5:
        removeBook();
        break;
      case 6:
      displayCheckedOutBooks();
      break;
    }

  } //end of while loop

}
