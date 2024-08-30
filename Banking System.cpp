
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>  
class BankAccount {
protected:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

public:
    BankAccount(std::string accNum, std::string accHolder, double bal)
        : accountNumber(accNum), accountHolderName(accHolder), balance(bal) {}

    virtual ~BankAccount() {}

    
    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    
    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient funds or invalid amount.\n";
        }
    }

   
    virtual double getBalance() const {
        return balance;
    }

   
    virtual void displayAccountInfo() const {
        std::cout << "Account Number: " << accountNumber << "\n"
                  << "Account Holder: " << accountHolderName << "\n"
                  << "Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    }
};


class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(std::string accNum, std::string accHolder, double bal, double intRate)
        : BankAccount(accNum, accHolder, bal), interestRate(intRate) {}

    void calculateInterest() {
        double interest = (balance * interestRate) / 100;
        deposit(interest);
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        std::cout << "Interest Rate: " << interestRate << "%\n";
    }
};


class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(std::string accNum, std::string accHolder, double bal, double overdraft)
        : BankAccount(accNum, accHolder, bal), overdraftLimit(overdraft) {}

    void withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
        } else {
            std::cout << "Withdrawal exceeds overdraft limit or invalid amount.\n";
        }
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        std::cout << "Overdraft Limit: $" << std::fixed << std::setprecision(2) << overdraftLimit << "\n";
    }
};


class FixedDepositAccount : public BankAccount {
private:
    int term; 

public:
    FixedDepositAccount(std::string accNum, std::string accHolder, double bal, int duration)
        : BankAccount(accNum, accHolder, bal), term(duration) {}

    void deposit(double amount) override {
        std::cout << "Deposits are not allowed in Fixed Deposit accounts.\n";
    }

    void withdraw(double amount) override {
        std::cout << "Withdrawals are not allowed in Fixed Deposit accounts.\n";
    }

    void calculateInterest() {
        // Assuming a fixed interest rate for simplicity
        double interestRate = 5.0;
        double interest = (balance * interestRate * term) / 100;
        deposit(interest);
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        std::cout << "Term: " << term << " months\n";
    }
};


void menu() {
    std::vector<std::shared_ptr<BankAccount>> accounts;
    int choice;
    do {
        std::cout << "\nBank Account Menu:\n"
                  << "1. Create Savings Account\n"
                  << "2. Create Checking Account\n"
                  << "3. Create Fixed Deposit Account\n"
                  << "4. Display All Accounts\n"
                  << "5. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        std::cin.ignore(); 

        switch (choice) {
            case 1: {
                std::string accNum, accHolder;
                double bal, intRate;
                std::cout << "Enter account number: ";
                std::getline(std::cin, accNum);
                std::cout << "Enter account holder name: ";
                std::getline(std::cin, accHolder);
                std::cout << "Enter balance: ";
                std::cin >> bal;
                std::cout << "Enter interest rate: ";
                std::cin >> intRate;
                accounts.push_back(std::make_shared<SavingsAccount>(accNum, accHolder, bal, intRate));
                break;
            }
            case 2: {
                std::string accNum, accHolder;
                double bal, overdraft;
                std::cout << "Enter account number: ";
                std::getline(std::cin, accNum);
                std::cout << "Enter account holder name: ";
                std::getline(std::cin, accHolder);
                std::cout << "Enter balance: ";
                std::cin >> bal;
                std::cout << "Enter overdraft limit: ";
                std::cin >> overdraft;
                accounts.push_back(std::make_shared<CheckingAccount>(accNum, accHolder, bal, overdraft));
                break;
            }
            case 3: {
                std::string accNum, accHolder;
                double bal;
                int duration;
                std::cout << "Enter account number: ";
                std::getline(std::cin, accNum);
                std::cout << "Enter account holder name: ";
                std::getline(std::cin, accHolder);
                std::cout << "Enter balance: ";
                std::cin >> bal;
                std::cout << "Enter term (months): ";
                std::cin >> duration;
                accounts.push_back(std::make_shared<FixedDepositAccount>(accNum, accHolder, bal, duration));
                break;
            }
            case 4:
                for (const auto& acc : accounts) {
                    acc->displayAccountInfo();
                    std::cout << "\n";
                }
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
