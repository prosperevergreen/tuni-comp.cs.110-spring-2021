#include <fstream> // Notice the required library for file handling
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string input_filename = "";
    cout << "Input file: ";
    cin >> input_filename;
    string output_filename = "";
    cout << "Output file: ";
    cin >> output_filename;

    ifstream input_fileobject(input_filename);
    ofstream output_fileobject(output_filename);
    if (not input_fileobject) {
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string line;
        unsigned int counter = 0;
        while (getline(input_fileobject, line)) {
            output_fileobject << counter << " " << line << endl;
        }
        input_fileobject.close();
        output_fileobject.close();
    }
}
