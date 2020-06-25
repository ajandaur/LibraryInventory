#include "book.h"
#include<string>

using namespace std;

Book::Book() {}

Book::Book(string title, string author): Title(title), Author(author), checkedOut(false) {}
//takes in parameters

void Book::CheckInOrOut(bool checkOut)
{
    checkedOut = checkOut;
  }

void Book::DisplayBook()
{
    cout << Id << "\t" << Title << "\t" << Author << endl;
  }

bool Book::IsCheckedOut()
{
    return checkedOut;
  }

std::string Book::GetBookFileData()
{
    return std::to_string(Id) + "|" + Title + "|" + Author + "|" + (checkedOut ? "1" : "0");
  }
