#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------

    // Add your implementation here

    if (a_word.front() != a_word.back() && a_word.length() > 1)
        return false;
    else if (a_word.length() <= 1)
        return true;
    else {
        a_word.pop_back();
        a_word.erase(a_word.begin());
        return palindrome_ckeck(a_word);
    }
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if (palindrome_recursive(word)) {
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
