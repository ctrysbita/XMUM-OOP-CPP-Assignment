#include <algorithm>
#include <iostream>
#include <vector>
#include "4_Account.h"

using namespace std;

/**
 * @brief Display user menu untill user log out.
 *
 * @param users All users
 * @param currentUser Current logged-in user.
 */
void UserMenu(vector<UserAccount> &users, UserAccount &currentUser) {
umenu:
  cout << endl
       << "-- User Menu - " << currentUser.getName() << " --" << endl
       << " 1 - Deposit" << endl
       << " 2 - Withdraw" << endl
       << " 3 - Transfer" << endl
       << " 4 - Account info" << endl
       << " 5 - Log out" << endl;
  uint8_t choice;
  cin.clear();  // Clear cin cache to prevent reading unexpected char to choice.
  cin >> choice;
  switch (choice) {
    case '1': {
      cout << "Please enter amount:";
      double amount;
      cin >> amount;
      currentUser.deposit(amount);
      goto umenu;
    }

    case '2': {
      cout << "Please enter amount (Maximum " << currentUser.getBalance()
           << "):";
      double amount;
      cin >> amount;
      currentUser.withdraw(amount);
      goto umenu;
    }

    case '3': {
      cout << "Please receiver: ";
      std::string target;
      cin >> target;
      cout << "Please enter amount (Maximum " << currentUser.getBalance()
           << "):";
      double amount;
      cin >> amount;
      for (auto &user : users)
        if (user.getID() == target) {
          currentUser.transferTo(user, amount);
          break;
        }
      goto umenu;
    }

    case '4':
      currentUser.display();
      goto umenu;

    case '5':
      return;

    default:
      goto umenu;
  }
}

/**
 * @brief Display admin menu untill log out.
 *
 * @param users All users
 * @param currentUser Current logged-in admin.
 */
void AdminMenu(vector<UserAccount> &users, AdminAccount &currentAdmin) {
amenu:
  cout << endl
       << "-- Admin Menu - " << currentAdmin.getName() << " --" << endl
       << " 1 - Add user" << endl
       << " 2 - Reset password" << endl
       << " 3 - Delete user" << endl
       << " 4 - Log out" << endl;
  uint8_t choice;
  cin.clear();  // Clear cin cache to prevent reading unexpected char to choice.
  cin >> choice;
  switch (choice) {
    case '1':
      users.push_back(UserAccount::Create());
      goto amenu;

    case '2': {
      cout << "Please the user id to reset: ";
      std::string target;
      cin >> target;
      for (auto &user : users)
        if (user.getID() == target) {
          currentAdmin.resetPasswordFor(user);
          break;
        }
      goto amenu;
    }

    case '3': {
      cout << "Please the user id to delete: ";
      std::string target;
      cin >> target;

      auto it = users.begin();
      for (; it != users.end(); it++)
        if ((*it).getID() == target) break;
      if (it != users.end()) users.erase(it);
      goto amenu;
    }

    case '4':
      return;

    default:
      goto amenu;
  }
}

int main4() {
  vector<UserAccount> users;    // All users.
  vector<AdminAccount> admins;  // All admins.

// Display main menu untill exit.
main:
  cout << "-- Main Menu --" << endl
       << " 1 - User login" << endl
       << " 2 - Admin login" << endl
       << " 3 - Create admin" << endl
       << " 4 - List all accounts" << endl
       << " 5 - Exit" << endl
       << "Select your choice: ";
  uint8_t choice;
  cin.clear();  // Clear cin cache to prevent reading unexpected char to choice.
  cin >> choice;
  switch (choice) {
    case '1': {
      string id;
      uint32_t password;
      cout << "Please enter your account number: ";
      cin >> id;
      cout << "Please enter your password: ";
      cin >> password;
      for (auto &user : users)
        if (user.getID() == id && user.checkPassword(password)) {
          UserMenu(users, user);
          goto main;
        }
      cout << "User not found or wrong password! Please try again!" << endl;
      goto main;
    }

    case '2': {
      string id;
      uint32_t password;
      cout << "Please enter your account number: ";
      cin >> id;
      cout << "Please enter your password: ";
      cin >> password;
      for (auto &admin : admins)
        if (admin.getID() == id && admin.checkPassword(password)) {
          AdminMenu(users, admin);
          goto main;
        }
      cout << "User not found or wrong password! Please try again!" << endl;
      goto main;
    }

    case '3':
      admins.push_back(AdminAccount::Create());
      goto main;

    case '4': {
      cout << endl << "-- All Users --" << endl;
      for (auto user : users) user.display();
      cout << "-- All Admins --" << endl;
      for (auto admin : admins) admin.display();
      cout << endl;
      goto main;
    }

    case '5':
      exit(0);
      break;

    default:
      goto main;
  }

  return 0;
}