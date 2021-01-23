#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    // Write your code here

    float temperature = 0, fahrenheit = 0, celsius = 0;

    cin >> temperature;

    fahrenheit = (temperature * 1.8) + 32;
    celsius = (temperature - 32)/1.8;

    cout << temperature << " degrees Celsius is " << fahrenheit <<" degrees Fahrenheit" << endl;
    cout << temperature << " degrees in Fahrenheit is " << celsius <<" degrees Celsius" << endl;

    return 0;
}
