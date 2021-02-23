#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Counter {
    /* data */
    unsigned int number;
    vector<unsigned int> lines;
};

const vector<string> explode(const string& s, const char& c)
{
    string buff { "" };
    vector<string> v;

    for (auto n : s) {
        if (n != c)
            buff += n;
        else if (n == c && buff != "") {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);

    return v;
}

int main()
{

    string input_filename = "";
    cout << "Input file: ";
    cin >> input_filename;
    // Open file to read values
    ifstream input_fileobject(input_filename);
    if (not input_fileobject) {
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        unsigned int line_counter = 1;
        string line;
        map<string, Counter> word_count;
        while (getline(input_fileobject, line)) {

            vector<string> v { explode(line, ' ') };
            pair<string, unsigned int> word;

            for (auto n : v) {
                word.first = n;
                word.second = line_counter;

                // Check if player exists
                if (word_count.find(word.first) != word_count.end()) {
                    // The word was found in the map.

                    if (word_count.at(word.first).lines.back() != word.second) {
                        word_count.at(word.first).number++;
                        word_count.at(word.first).lines.push_back(word.second);
                    }

                } else {
                    // The word was not found in the map.
                    // Insert word
                    word_count.insert({ word.first, { .number = 1, .lines = { word.second } } });
                }
            }
            line_counter++;
        }
        // Close file
        input_fileobject.close();
        // Create iterator to print word_count names and total points
        for (auto iter : word_count) {
            cout << iter.first << " " << iter.second.number << ": ";
            for (vector<unsigned int>::size_type i = 0; i < iter.second.lines.size(); i++) {
                if (i == 0) {
                    cout << iter.second.lines.at(i);
                } else {
                    cout << ", " << iter.second.lines.at(i);
                }
            }
            cout << endl;
        }
    }

    return 0;
}
