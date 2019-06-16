#include "4_Account.h"
#include <ctime>
#include "4_id_generator.hpp"

using namespace std;

Account::Account(std::string id, uint32_t password, std::string name,
                 std::string address, std::string bankName, time_t createTime)
    : id(id),
      password(password),
      name(name),
      address(address),
      bankName(bankName),
      createTime(createTime) {}

std::string Account::getID() { return id; }

std::string Account::getName() { return name; }

void Account::setName(std::string newName) {
  if (newName != "")
    name = newName;
  else
    cout << "Cannot assign empty name!" << endl;
}

std::string Account::getAddress() { return address; }

void Account::setAddress(std::string addr) {
  if (addr != "")
    address = addr;
  else
    cout << "Cannot assign empty address!" << endl;
}

bool Account::checkPassword(uint32_t pass) { return password == pass; }

void Account::display() {
  tm lt;

// Because default localtime function has security problem.
// MSVC compiler use localtime_s instead while GCC use localtime_r.
#ifdef _MSC_VER
  localtime_s(&lt, &createTime);
#else
  localtime_r(&createTime, &lt);
#endif

  cout << "-- Account info (" << id << ") --" << endl
       << "Name: " << name << endl
       << "Address: " << address << endl
       << "Bank: " << bankName << endl
       << "Create at: " << lt.tm_mday << "/" << lt.tm_mon << "/"
       << 1900 + lt.tm_year << " " << lt.tm_hour << ":" << lt.tm_min << ":"
       << lt.tm_sec << endl;
}

UserAccount::UserAccount(std::string id, uint32_t password, std::string name,
                         std::string address, std::string bankName,
                         time_t createTime, AccountType type, double balance,
                         time_t lastTimeWithdraw)
    : Account(id, password, name, address, bankName, createTime),
      type(type),
      balance(balance),
      lastTimeWithdraw(lastTimeWithdraw) {}

UserAccount UserAccount::Create() {
  auto id = GenerateID();
  int type;
  cout << "Creating User Account (" << id << ")" << endl
       << "Please enter your name: ";
  std::string name;
  cin >> name;
  cout << "Please enter your address: ";
  std::string addr;
  cin >> addr;
  cout << "Please enter bankName: ";
  std::string bankName;
  cin >> bankName;
  cout << "Please choose account type (0/1 for saving/current): ";
  cin >> type;

  cout << "Please enter password: ";
  uint32_t pass;

  // Password should have 6 digits.
enter:
  cin >> pass;
  if (pass < 100000 || pass > 999999) {
    cout << "Invalid format! Please enter again: ";
    goto enter;
  }

  return UserAccount(id, pass, name, addr, bankName, time(0), (AccountType)type,
                     0, NULL);
}

AccountType UserAccount::getType() { return type; }

double UserAccount::getBalance() { return balance; }

void UserAccount::deposit(double amount) {
  balance += amount;
  cout << "Success! Current balance: " << balance << endl;
}

void UserAccount::withdraw(double amount) {
  if (balance - amount >= 0) {
    balance -= amount;
    lastTimeWithdraw = time(0);
    cout << "Success! Current balance: " << balance << endl;
  } else
    cout << "Sorry, you don't have enough balance to pay!" << endl;
}

void UserAccount::transferTo(UserAccount& other, double amount) {
  if (balance - amount >= 0) {
    balance -= amount;
    other.balance += amount;
    cout << "Success! Current balance: " << balance << endl;
  } else
    cout << "Sorry, you don't have enough balance to pay!" << endl;
}

void UserAccount::display() {
  // Display basic account info first.
  Account::display();

  cout << "Type: " << (type == savingAccount ? "Saving" : "Current") << endl
       << "Balance: " << balance << endl;

  // LastTimeWithdraw will not be printed if user never withdraw.
  if (lastTimeWithdraw != NULL) {
    tm lt;

// Because default localtime function has security problem.
// MSVC compiler use localtime_s instead while GCC use localtime_r.
#ifdef _MSC_VER
    localtime_s(&lt, &lastTimeWithdraw);
#else
    localtime_r(&createTime, &lt);
#endif

    cout << "Last time withdraw: " << lt.tm_mday << "/" << lt.tm_mon << "/"
         << 1900 + lt.tm_year << " " << lt.tm_hour << ":" << lt.tm_min << ":"
         << lt.tm_sec << endl;
  }
}

AdminAccount::AdminAccount(std::string id, uint32_t password, std::string name,
                           std::string address, std::string bankName,
                           time_t createTime)
    : Account(id, password, name, address, bankName, createTime) {}

AdminAccount AdminAccount::Create() {
  auto id = GenerateID();
  cout << "Creating Admin Account (" << id << ")" << endl
       << "Please enter your name: ";
  std::string name;
  cin >> name;
  cout << "Please enter your address: ";
  std::string addr;
  cin >> addr;
  cout << "Please enter bankName: ";
  std::string bankName;
  cin >> bankName;

  cout << "Please enter password: ";
  uint32_t pass;

  // Password should have 6 digits.
enter:
  cin >> pass;
  if (pass < 100000 || pass > 999999) {
    cout << "Invalid format! Please enter again: ";
    goto enter;
  }

  return AdminAccount(id, pass, name, addr, bankName, time(0));
}

void AdminAccount::resetPasswordFor(UserAccount& uAccount) {
  cout << "-- Resetting password for account " << uAccount.getID() << " --"
       << endl
       << "Please enter new password: ";
  uint32_t newPassword;

  // Password should have 6 digits.
enter:
  cin >> newPassword;
  if (newPassword < 100000 || newPassword > 999999) {
    cout << "Invalid format! Please enter again: ";
    goto enter;
  }

  uAccount.password = newPassword;
}
