#include <iostream>
using namespace std;

int main() {
    int* dyn_variable_address = nullptr;
    dyn_variable_address = new int(7);
    cout << "Address: " << dyn_variable_address << endl;
    cout << "Start:   " << *dyn_variable_address << endl;
    *dyn_variable_address = *dyn_variable_address * 4;
    cout << "End:     " << *dyn_variable_address << endl;
    delete dyn_variable_address;
    return EXIT_SUCCESS;
}