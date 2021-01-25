#include <iostream>

using namespace std;

int main()
{
    int max_int_cube = 1290, number = 0, cube = 0;

    cout << "Enter a number: ";
    cin >> number;

    if (number < 0) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        cube = number * number * number;

        if (number > max_int_cube) {
            cout << "Error! The cube of " << number << " is not " << cube << "." << endl;
        } else {
            cout << "The cube of " << number << " is " << cube << "." << endl;
        }
    }

    return EXIT_SUCCESS;
}
