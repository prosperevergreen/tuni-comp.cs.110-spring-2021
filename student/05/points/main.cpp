#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

int main()
{

    string input_filename = "";
    cout << "Input file: ";
    cin >> input_filename;

    ifstream input_fileobject(input_filename);
    if (not input_fileobject) {
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string line;
        map<string, unsigned int> players;
        while (getline(input_fileobject, line)) {

            string delim = ":";

            string::size_type location = 0;
            location = line.find(delim);
            string name = line.substr(0, location);
            unsigned int point = stoi(line.substr(location + 1));
            pair<string, unsigned int> player(name, point);
            cout << name << endl;

            // Check if player exists
            if (players.find(player.first) != players.end()) {
                // The player was found in the map.
                players.at(player.first) += player.second;
            } else {
                // The player was not found in the map.
                // Insert player
                players.insert(player);
            }
        }
        // Close file
        input_fileobject.close();
        // Create iterator to print players names and total points
        map<string, unsigned int>::iterator iter;
        iter = players.begin();
        cout << "Final scores:" << endl;
        while (iter != players.end()) {
            cout << iter->first << ": " << iter->second << endl;
            ++iter;
        }
    }

    return 0;
}
