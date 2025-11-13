////八、完整示例：银行账户管理系统
//#include <iostream>
//#include <string>
//#include <vector>
//#include <memory>
//#include <stdexcept>
//
//// 前向声明
//class Transaction;
//
//// 账户基类
//class Account {
//protected:
//    std::string accountNumber;
//    std::string ownerName;
//    double balance;
//    std::vector<Transaction> transactions;
//
//    static int accountCount;
//
//public:
//    Account(const std::string& number, const std::string& owner, double initialBalance = 0.0)
//        : accountNumber(number), ownerName(owner), balance(initialBalance) {
//        ++accountCount;
//    }
//
//    virtual ~Account() {
//        --accountCount;
//    }
//
//    // 纯虚函数 - 使Account成为抽象类
//    virtual void displayDetails() const = 0;
//
//    // 虚函数 - 可以被派生类重写
//    virtual bool withdraw(double amount) {
//        if (amount <= 0) {
//            std::cout << "Invalid withdrawal amount" << std::endl;
//            return false;
//        }
//
//        if (amount > balance) {
//            std::cout << "Insufficient funds" << std::endl;
//            return false;
//        }
//
//        balance -= amount;
//        addTransaction("Withdrawal", -amount);
//        return true;
//    }
//
//    virtual void deposit(double amount) {
//        if (amount <= 0) {
//            std::cout << "Invalid deposit amount" << std::endl;
//            return;
//        }
//
//        balance += amount;
//        addTransaction("Deposit", amount);
//    }
//
//    double getBalance() const {
//        return balance;
//    }
//
//    std::string getAccountNumber() const {
//        return accountNumber;
//    }
//
//    std::string getOwnerName() const {
//        return ownerName;
//    }
//
//    void addTransaction(const std::string& type, double amount);
//
//    void displayTransactions() const;
//
//    static int getAccountCount() {
//        return accountCount;
//    }
//
//    // 友元函数
//    friend void transferFunds(Account& from, Account& to, double amount);
//};
//
//// 静态成员初始化
//int Account::accountCount = 0;
//
//// 交易类
//class Transaction {
//private:
//    std::string date;
//    std::string type;
//    double amount;
//
//public:
//    Transaction(const std::string& type, double amount)
//        : type(type), amount(amount) {
//        // 获取当前日期（简化版）
//        date = "2023-05-20"; // 实际应用中应使用真实日期
//    }
//
//    void display() const {
//        std::cout << "Date: " << date << ", Type: " << type
//            << ", Amount: " << amount << std::endl;
//    }
//};
//
//// 实现Account类中依赖于Transaction的方法
//void Account::addTransaction(const std::string& type, double amount) {
//    transactions.push_back(Transaction(type, amount));
//}
//
//void Account::displayTransactions() const {
//    std::cout << "Transaction History for Account " << accountNumber << ":" << std::endl;
//    for (const auto& transaction : transactions) {
//        transaction.display();
//    }
//}
//
//// 储蓄账户类
//class SavingsAccount : public Account {
//private:
//    double interestRate;
//
//public:
//    SavingsAccount(const std::string& number, const std::string& owner,
//        double initialBalance = 0.0, double rate = 0.01)
//        : Account(number, owner, initialBalance), interestRate(rate) {
//    }
//
//    void displayDetails() const override {
//        std::cout << "Savings Account Details:" << std::endl;
//        std::cout << "Account Number: " << accountNumber << std::endl;
//        std::cout << "Owner: " << ownerName << std::endl;
//        std::cout << "Balance: $" << balance << std::endl;
//        std::cout << "Interest Rate: " << (interestRate * 100) << "%" << std::endl;
//    }
//
//    void addInterest() {
//        double interest = balance * interestRate;
//        balance += interest;
//        addTransaction("Interest", interest);
//        std::cout << "Added interest: $" << interest << std::endl;
//    }
//};
//
//// 支票账户类
//class CheckingAccount : public Account {
//private:
//    double overdraftLimit;
//
//public:
//    CheckingAccount(const std::string& number, const std::string& owner,
//        double initialBalance = 0.0, double limit = 100.0)
//        : Account(number, owner, initialBalance), overdraftLimit(limit) {
//    }
//
//    void displayDetails() const override {
//        std::cout << "Checking Account Details:" << std::endl;
//        std::cout << "Account Number: " << accountNumber << std::endl;
//        std::cout << "Owner: " << ownerName << std::endl;
//        std::cout << "Balance: $" << balance << std::endl;
//        std::cout << "Overdraft Limit: $" << overdraftLimit << std::endl;
//    }
//
//    // 重写withdraw方法以支持透支
//    bool withdraw(double amount) override {
//        if (amount <= 0) {
//            std::cout << "Invalid withdrawal amount" << std::endl;
//            return false;
//        }
//
//        if (amount > (balance + overdraftLimit)) {
//            std::cout << "Exceeds overdraft limit" << std::endl;
//            return false;
//        }
//
//        balance -= amount;
//        addTransaction("Withdrawal", -amount);
//
//        if (balance < 0) {
//            std::cout << "Account overdrawn by $" << -balance << std::endl;
//        }
//
//        return true;
//    }
//};
//
//// 信用卡账户类
//class CreditAccount : public Account {
//private:
//    double creditLimit;
//    double interestRate;
//
//public:
//    CreditAccount(const std::string& number, const std::string& owner,
//        double initialBalance = 0.0, double limit = 1000.0, double rate = 0.02)
//        : Account(number, owner, initialBalance), creditLimit(limit), interestRate(rate) {
//    }
//
//    void displayDetails() const override {
//        std::cout << "Credit Account Details:" << std::endl;
//        std::cout << "Account Number: " << accountNumber << std::endl;
//        std::cout << "Owner: " << ownerName << std::endl;
//        std::cout << "Balance: $" << balance << std::endl;
//        std::cout << "Credit Limit: $" << creditLimit << std::endl;
//        std::cout << "Interest Rate: " << (interestRate * 100) << "%" << std::endl;
//    }
//
//    // 重写withdraw方法以支持信用额度
//    bool withdraw(double amount) override {
//        if (amount <= 0) {
//            std::cout << "Invalid withdrawal amount" << std::endl;
//            return false;
//        }
//
//        if (balance - amount < -creditLimit) {
//            std::cout << "Exceeds credit limit" << std::endl;
//            return false;
//        }
//
//        balance -= amount;
//        addTransaction("Purchase", -amount);
//        return true;
//    }
//
//    // 支付信用卡账单
//    void makePayment(double amount) {
//        if (amount <= 0) {
//            std::cout << "Invalid payment amount" << std::endl;
//            return;
//        }
//
//        balance += amount;
//        addTransaction("Payment", amount);
//    }
//
//    // 计算利息（对负余额）
//    void calculateInterest() {
//        if (balance < 0) {
//            double interest = -balance * interestRate;
//            balance -= interest;
//            addTransaction("Interest Charge", -interest);
//            std::cout << "Interest charged: $" << interest << std::endl;
//        }
//    }
//};
//
//// 友元函数实现
//void transferFunds(Account& from, Account& to, double amount) {
//    if (from.withdraw(amount)) {
//        to.deposit(amount);
//        std::cout << "Transferred $" << amount << " from account "
//            << from.accountNumber << " to account " << to.accountNumber << std::endl;
//    }
//    else {
//        std::cout << "Transfer failed" << std::endl;
//    }
//}
//
//// 银行类
//class Bank {
//private:
//    std::string name;
//    std::vector<std::shared_ptr<Account>> accounts;
//
//public:
//    Bank(const std::string& bankName) : name(bankName) {}
//
//    void addAccount(std::shared_ptr<Account> account) {
//        accounts.push_back(account);
//    }
//
//    void displayAllAccounts() const {
//        std::cout << "Accounts at " << name << " Bank:" << std::endl;
//        for (const auto& account : accounts) {
//            account->displayDetails();
//            std::cout << "------------------------" << std::endl;
//        }
//    }
//
//    std::shared_ptr<Account> findAccount(const std::string& accountNumber) {
//        for (auto& account : accounts) {
//            if (account->getAccountNumber() == accountNumber) {
//                return account;
//            }
//        }
//        return nullptr;
//    }
//};
//
//// 主函数
//int main() {
//    Bank bank("MyBank");
//
//    // 创建不同类型的账户
//    auto savings = std::make_shared<SavingsAccount>("S123", "John Doe", 1000.0, 0.02);
//    auto checking = std::make_shared<CheckingAccount>("C456", "Jane Smith", 2000.0, 500.0);
//    auto credit = std::make_shared<CreditAccount>("CC789", "Bob Johnson", 0.0, 2000.0, 0.015);
//
//    // 添加账户到银行
//    bank.addAccount(savings);
//    bank.addAccount(checking);
//    bank.addAccount(credit);
//
//    // 显示所有账户
//    bank.displayAllAccounts();
//
//    // 执行一些交易
//    std::cout << "\nPerforming transactions...\n" << std::endl;
//
//    savings->deposit(500.0);
//    checking->withdraw(1000.0);
//    credit->withdraw(1500.0);
//
//    // 转账
//    transferFunds(*checking, *savings, 300.0);
//
//    // 添加利息
//    savings->addInterest();
//    credit->calculateInterest();
//
//    // 显示交易历史
//    std::cout << "\nTransaction History:\n" << std::endl;
//    savings->displayTransactions();
//    std::cout << std::endl;
//    checking->displayTransactions();
//    std::cout << std::endl;
//    credit->displayTransactions();
//
//    // 再次显示所有账户
//    std::cout << "\nUpdated Account Details:\n" << std::endl;
//    bank.displayAllAccounts();
//
//    // 显示账户总数
//    std::cout << "Total number of accounts: " << Account::getAccountCount() << std::endl;
//
//    return 0;
//}