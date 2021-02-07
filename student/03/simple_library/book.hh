#ifndef BOOK_HH
#define BOOK_HH
#include <string>

#include "date.hh"

class Book
{
public:
    Book(std::string title, std::string author);
    void print() const;
    void loan(Date date);
    void renew();
    void give_back();
private:
    std::string title_;
    std::string author_;
    bool isLoaned_;
    Date loanDate_;
    Date returnDate_;
};

#endif // BOOK_HH
