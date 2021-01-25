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
    int total_num = 0, drawn_num = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> total_num;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_num;

    if (total_num * drawn_num < 0) {
        cout << "The number of balls must be a positive number." << endl;
    } else if (drawn_num > total_num) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    } else {
        cout << "The probability of guessing all " << drawn_num << " balls correctly is 1/" << calculate_lottery(total_num, drawn_num) << endl;
    }
    return 0;
}
