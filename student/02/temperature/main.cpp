#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    // Write your code here

    float temperature = 0, fahrenheit = 0;

    cin >> temperature;

    fahrenheit = (temperature * 1.8) + 32;

    cout << temperature << " degrees Celsius is " << fahrenheit <<" degrees Fahrenheit" << endl;


    return 0;
}
