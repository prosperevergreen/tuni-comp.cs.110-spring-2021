#include <iostream>

int main()
{
    int count = 0, guess = 1;

    std::cout << "How many numbers would you like to have? ";
    std::cin >> count;

    while (count >= guess)
    {
        if (guess % 3 == 0)
        {
            std::cout << "zip" << std::endl;
        }
        else
        {
            std::cout << guess << std::endl;
        }
        guess++;
    }
}
