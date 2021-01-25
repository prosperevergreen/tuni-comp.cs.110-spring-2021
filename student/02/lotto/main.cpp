#include <iostream>

using namespace std;

unsigned long int factorial(int num)
{
    if (num <= 1) {
        return 1;
    } else {
        return num * factorial(num - 1);
    }
}

unsigned long int calculate_lottery(int total_balls, int drawn_balls)
{
    unsigned long int divisor = factorial(total_balls),
                      dividend1 = factorial(total_balls - drawn_balls),
                      dividend2 = factorial(drawn_balls);

    return divisor / (dividend1 * dividend2);
}

int main()
{
    int number;
    cout << "Enter the total number of lottery balls: ";
    cin >> number;
    cout << factorial(number) << endl;
    return 0;
}
