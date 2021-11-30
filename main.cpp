#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "book.h"
#include "inventory.h"
#include "CheckInOutResult.h"
#include "User.h"


using namespace std;

Inventory _inventory;
vector<User> _users;
User _loggedInUser;

Role GetRoleFromIntVal(int roleVal)
{
  Role outRole;

  if(roleVal == 0)
  {
    outRole = Role::Admin;
  } else if (roleVal == 1)
  {
    outRole = Role::Employee;
  } else
  {
    outRole = Role::Member;
  }
  return outRole;
}


void LoadUsers()
{
  ifstream in("users.txt");

  string lineData[3];
  //lineData[0] = username
  //lineData[1] = role int val
  //lineData[2] = password


  string userLine;
  while(getline(in, userLine))
  {
  size_t index = userLine.find('|');
  lineData[0] = userLine.substr(0, index);
  lineData[1] = userLine.substr(index+1, '|');
  size_t index2 = userLine.find("password:");
  lineData[2] = userLine.substr(index2 +1);

  User loadedUser;
  loadedUser.Username = lineData[0];
  loadedUser.Role = GetRoleFromIntVal(stoi(lineData[1]));
  loadedUser.Password = lineData[2];

  _users.push_back(loadedUser);
  }
}

int GetIntValFromRole(Role role)
{
  int roleVal = -1; //default value
  if(role == Role::Admin)
  {
    roleVal = 0;
  } else if (role == Role::Employee)
  {
    roleVal = 1;
  } else if (role == Role::Member)
  {
    roleVal = 2;
  }
  return roleVal;
}

void CreateAccount ()
{

  User newUser;

  cout << "First name:" <<endl;
  string firstName;
  getline(cin, firstName);

  cout << "Last name:" <<endl;
  string lastName;
  getline(cin, lastName);

  cout << "Username: " <<endl;
  getline(cin, newUser.Username);

  cout << "Password: " <<endl;
  getline(cin, newUser.Password);

  cout << "Choose a role:" <<endl;
  cout << "1. Admin" <<endl;
  cout << "2. Employee" <<endl;
  cout << "3. Member" <<endl;

  int roleOption;
  cin >> roleOption;
  cin.ignore();

  if(roleOption == 1)
  {
    newUser.Role = Role::Admin;
  } else if (roleOption == 2)
  {
    newUser.Role = Role::Employee;
  } else
  {
    newUser.Role = Role::Member;
  }

  //anmol|0|password:

  _users.push_back(newUser);

  ofstream o("users.txt", ios_base::app); //apend to users.txt
  o << newUser.Username << "|" << GetIntValFromRole(newUser.Role) << "|" << "password:" << newUser.Password << endl;
  o.close();
}

void Login()
{
  cout << "Please input which option you desire." <<endl;
  cout << "1. Log in" <<endl;
  cout << "2. Create an account" <<endl;

  int option;
  cin >> option;
  cin.ignore();

  if(option == 2)
  {
    CreateAccount ();
  }
  while(true){
  cout << "Enter username: ";
  string username;
  getline(cin, username);
  cout << "Enter password: ";
  string password;
  getline(cin, password);

  User user;
  user.Username = username;
  user.Password = password;

  vector<User>::iterator it = find(_users.begin(), _users.end(), user);
    //if user is found
    if(it != _users.end())
    {
      _loggedInUser = _users[it - _users.begin()];
      break;
    } else //if user not found, try again
    {
      cout << "Incorrect username or password, try again.." << endl;
    }
  }
}

void displayStartupmenu()
{
  cout << endl;
  cout << "Please input which option you desire." <<endl;

  cout << "1. List all books" <<endl;
  cout << "2. Check out book" <<endl;
  cout << "3. Check in book" <<endl;

  if(_loggedInUser.Role == Role::Employee || _loggedInUser.Role == Role::Admin)
  {
    cout << "4. Add a book" <<endl;
    cout << "5. Remove book from library" <<endl;
    cout << "6. List all checked out books" << endl;
  }
  cout << "9. Log out" << endl;
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


  Book newBook(bookTitle, bookAuthor);

  _inventory.addBook(newBook);
}

void listAllBooks()
{
  _inventory.DisplayAllBooks();
}

void checkInOrOutBook(bool checkOut)
{
  string inOrOut;
  if(checkOut)
    {
      inOrOut = "out";
    }
  else
    {
      inOrOut = "in";
    }
  cout << "Enter the title of the book you would like to check " + inOrOut + ": ";
  string title;
  getline(cin, title);

  CheckInOrOutResult result = _inventory.checkInOrOutBook(title, checkOut);

  if(result == CheckInOrOutResult::BookNotFound)
  {
    cout << "Book not found";
  }
  else if(result == CheckInOrOutResult::Success)
  {
    cout << "Book checked " + inOrOut<<endl;
  }
  else if(result == CheckInOrOutResult::AlreadyCheckedIn || result == CheckInOrOutResult::AlreadyCheckedOut)
  {
    cout << "Book already checked " + inOrOut << endl;
  }
  else
  {
    cout << "Book failed checking " + inOrOut << endl;
  }
}

void removeBook()
{
  cout << "What is the title of the book you want to remove?" <<endl;
  string bookTitle;
  getline(cin, bookTitle); //use getline to get the full title
  _inventory.removeBook(bookTitle);
}

void displayCheckedOutBooks()
{
  _inventory.DisplayCheckedOutBooks();
}

int main()
{
  LoadUsers();

  while(true)
  {
  Login();

  _inventory.LoadBooks();
  bool isLoggedIn = true;

  while(isLoggedIn) {

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
        listAllBooks();
        break;
      case 2:
        checkInOrOutBook(true); //checking out
        break;
      case 3:
        checkInOrOutBook(false); //checking in
        break;
      case 4:
        addNewBook();
        break;
      case 5:
        removeBook();
        break;
      case 6:
        displayCheckedOutBooks();
      break;
      case 9:
        isLoggedIn = false;
        break;
      default:
        cout << "Invalid Selection. Input valid number.." << endl;
        break;
      }
    }
  } //end of while loop when user logs out
}
