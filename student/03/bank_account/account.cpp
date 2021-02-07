#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit)
    : owner_(owner)
    , has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if (running_number_ < 10) {
        suffix.append("0");
    } else if (running_number_ > 99) {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::save_money(unsigned int amount)
{
    balance_ += amount;
}

void Account::set_credit_limit(int limit)
{
    if (has_credit_ != true) {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
        return;
    }
    credit_limit_ = -limit;
}

int Account::take_money(unsigned int amount)
{
    if ((balance_ - static_cast<int>(amount)) < credit_limit_) {
        std::cout << "Cannot take money: " << (has_credit_ ? "credit limit overflow" : "balance underflow") << std::endl;
        return -1;
    }

    balance_ -= amount;
    std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
    return amount;
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}

bool Account::transfer_to(Account& user, unsigned int amount)
{
    int transferAmount = take_money(amount);
    if (transferAmount == -1) {
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        return false;
    }

    user.save_money(transferAmount);
    return true;
}
