#pragma once
#include <string>

/**
 * @brief Type for user account.
 */
enum AccountType { savingAccount, currentAccount };

/**
 * @brief Base abstract class for accounts.
 * Should use UserAccount and AdminAccount instead.
 */
class Account {
 private:
  /**
   * @brief Unique account ID.
   * Currently use 4 hex numbers.
   * Should be replaced with UUID if in production.
   */
  std::string id;

  uint32_t password;
  std::string name;
  std::string address;
  std::string bankName;
  time_t createTime;

 protected:
  /**
   * @brief Construct Account from raw.
   */
  Account(std::string id, uint32_t password, std::string name,
          std::string address, std::string bankName, time_t createTime);

 public:
  std::string getID();
  std::string getName();
  void setName(std::string newName);
  std::string getAddress();
  void setAddress(std::string addr);

  /**
   * @brief Check if password is right.
   * @return Checking result.
   */
  bool checkPassword(uint32_t pass);

  /**
   * @brief Print Account information.
   */
  virtual void display();

  // Friend class for AdminAccount to reset password.
  friend class AdminAccount;
};

/**
 * @brief Account for normal users.
 */
class UserAccount : public Account {
 private:
  AccountType type;
  double balance;

  /**
   * @brief Last withdraw time. (NULL if never withdraw)
   */
  time_t lastTimeWithdraw;

 protected:
  /**
   * @brief Construct UserAccount from raw.
   */
  UserAccount(std::string id, uint32_t password, std::string name,
              std::string address, std::string bankName, time_t createTime,
              AccountType type, double balance, time_t lastTimeWithdraw);

 public:
  /**
   * @brief Create a UserAccount.
   * Will ask user to input neccessary information.
   */
  static UserAccount Create();

  AccountType getType();
  double getBalance();

  void deposit(double amount);
  void withdraw(double amount);
  void transferTo(UserAccount &other, double amount);
  void display();
};

/**
 * @brief Account for admins.
 */
class AdminAccount : public Account {
 protected:
  /**
   * @brief Construct AdminAccount from raw.
   */
  AdminAccount(std::string id, uint32_t password, std::string name,
               std::string address, std::string bankName, time_t createTime);

 public:
  /**
   * @brief Create a AdminAccount.
   * Will ask user to input neccessary information.
   */
  static AdminAccount Create();

  /**
   * @brief Reset password for UserAccount.
   * @param uAccount The UserAccount to reset password.
   */
  void resetPasswordFor(UserAccount &uAccount);
};
