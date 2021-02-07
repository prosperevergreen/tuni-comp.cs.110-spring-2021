#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    unsigned int seed;
    char option = 'c';

    cout << "Enter a seed value: ";
    cin >> seed;

    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(lower, upper);


    while (option != 'q') {

        if(option == 'c'){
            cout << "Your drawn random number is " << distr(gen) << endl;
        }
        cout << "Press c to continue or q to quit: ";
        cin >> option;
    }


}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if (lower_bound >= upper_bound) {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
