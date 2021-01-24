#include <iostream>

using namespace std;

int main()
{
    int number = 0, factor1 = 0, factor2 = 0, min = 0, temp_factor = 0;

    cout << "Enter a positive number: ";
    cin >> number;

    if (number <= 0) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        // Iterate till maximum posible value
        for (int i = 1; i <= number/2; i++) {
            // Check if number is divisible by i
            if(number % i == 0){
                cout << i << endl;
            }
        }
    }

    return 0;
}
