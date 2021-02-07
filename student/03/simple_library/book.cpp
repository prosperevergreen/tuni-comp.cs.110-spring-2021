#include "book.hh"
#include <iostream>
#include <string.h>

Book::Book(std::string title, std::string author)
    : title_(title)
    , author_(author)
    , isLoaned_(false)
{
}

void Book::print() const
{
    std::cout << title_ << " : " << author_ << std::endl;

    if (!isLoaned_) {
        std::cout << "- available" << std::endl;
        return;
    }


    std::cout << "- loaned: ";
    loanDate_.print();
    std::cout << "- to be returned: ";
    returnDate_.print();
}

void Book::loan(Date date)
{
    if (isLoaned_) {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }
    isLoaned_ = true;
    loanDate_ = date;
    date.advance(28);
    returnDate_ = date;
}

void Book::renew()
{
    if (!isLoaned_) {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
        return;
    }
    returnDate_.advance(28);
}

void Book::give_back(){
    isLoaned_ = false;
}

