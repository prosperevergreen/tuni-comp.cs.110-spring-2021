#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;


// word counter type
struct Counter {
    unsigned int number;
    vector<unsigned int> lines;
};


// function to split a string by a given delimiter
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
    // Check if file exists
    if (not input_fileobject) {
        // File does not exist
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        // File exists

        // File line tracker
        unsigned int curr_line = 1;
        string line;

        // Word counter and line tracker
        map<string, Counter> word_count;

        // Read file line by line
        while (getline(input_fileobject, line)) {
            // Create vector and init with with words separated by delimiter in this case ' '
            vector<string> v { explode(line, ' ') };


            string word = "";
            for (auto n : v) {
                word = n;
                // Check if player exists
                if (word_count.find(word) != word_count.end()) {
                    // The word was found in the map.
                    // Check if word has been added for line
                    if (word_count.at(word).lines.back() != curr_line) {
                        // Word not add
                        // Add word
                        word_count.at(word).number++;
                        word_count.at(word).lines.push_back(curr_line);
                    }

                } else {
                    // The word was not found in the map.
                    // Insert new word
                    word_count.insert({ word, { .number = 1, .lines = { curr_line } } });
                }
            }
            curr_line++;
        }
        // Close file
        input_fileobject.close();

        // Create iterator to print word, total number of appearanc and lines of appearance
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
