#include <iostream>

using namespace std;

int main()
{
    int max_int = INT_MAX, number = 0, cube = 0;

    cout << "Enter a number: ";
    cin >> number;

    if (number < 0) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        cube = number * number * number;

        if (number > 1290) {
            cout << "Error! The cube of " << number << " is not " << cube << "." << endl;
        } else {
            cout << "The cube of " << number << " is " << cube << "." << endl;
        }
    }

    return 0;
}
