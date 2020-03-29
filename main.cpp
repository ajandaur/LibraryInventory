#include <iostream>
#include "book.h"
#include "inventory.h"
#include <string>

using namespace std;

Inventory _inventory;

int main()
{
  while(true) {
    cout << "Please input which option you desire." <<endl;
    cout << "1. Add a book" <<endl;
    cout << "2. List all books" <<endl;
    cout << "3. Check out book" <<endl;
    cout << "4. Check in book" <<endl;
    cout << "0. Exit Library Inventory" <<endl;

    int input;
    cin >> input;
    cin.ignore(); //To prevent getline from trying to get rest of cin

    switch (input)
    {
      case 0:
        cout << "Thank you for using our service!";
        return 0;

      case 1:
      {
        cout << "What is the title of the book you want to add?" <<endl;
        string bookTitle;
        getline(cin, bookTitle); //use getline to get the full title

        cout << "What is the author of the book?"<<endl;
        string bookAuthor;
        getline(cin, bookAuthor); //use getline to get the full title

        int id = _inventory.Books.size() + 1;
        //temporary solution, problem when removing books

        Book newBook(id, bookTitle, bookAuthor);

        _inventory.addBook(newBook);
        break;
      }

      case 2:

        cout << "\nID\tTitle\tAuthor\n";
        for (int i = 0; i < _inventory.Books.size(); i++)
        {
          cout << _inventory.Books[i].Id << "\t" << _inventory.Books[i].Title << "\t" << _inventory.Books[i].Author << endl;
        }
        cout << endl;
        break;
      case 3:
      {
        cout << "Enter the title of the book you would like to check out: ";
        string title;
        getline(cin, title);
        Book foundBook;
        if(_inventory.findBookByTitle(title, foundBook))
        {
          if(foundBook.checkedOut)
          {
            cout << "Book already checked in!"<< endl;
            break;
          }

          _inventory.checkOutBook(foundBook);
          cout << "Success, book checked out!"<<endl;
        }
        else
        {
          cout << "Sorry! Your requested book was not found!"<<endl;
        }
        break;
      }
      case 4:
      {
        cout << "Enter the title of the book you would like to check in: ";
        string title;
        getline(cin, title);
        Book foundBook;
        if(_inventory.findBookByTitle(title, foundBook))
        {
          if(!foundBook.checkedOut)
          {
            cout << "Book already checked in!"<< endl;
            break;
          }
          _inventory.checkInBook(foundBook);
          cout << "Success, book checked in!"<<endl;
        }
        else
        {
          cout << "Sorry! Your requested book was not found!"<<endl;
        }
        break;
      }
      default:
        cout << "Invalid selection. Try again" << endl;
        break;
    }

  } //run forever until we tell it to break

}
