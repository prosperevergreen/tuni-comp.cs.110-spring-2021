#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Stop {
    string stop;
    float distance;
};

using Stops = vector<Stop>;
using Line = map<std::string, Stops>;

const std::string FILE_NAME = "Give a name for input file: ";
const std::string BAD_FILE = "Error: File could not be read.";
const std::string BAD_FILE_CONTENT = "Error: Invalid format in file.";
const std::string BAD_COMMAND = "Error: Invalid input.";
const std::string BAD_STOP = "Error: Stop could not be found.";
const std::string BAD_LINE = "Error: Line could not be found.";
const std::string DUPLICATE_LINE_STOP = "Error: Stop/line already exists.";
const string REMOVED_STOP = "Stop was removed from all lines.";

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout << "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------"
              << std::endl;
}

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while (tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if (not(ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if (not(ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}

bool sort_by_distance(Stop i, Stop j) { return (i.distance < j.distance); }

bool has_stop_distance(Stops& line_stops, string stop, float distance, Stops::size_type pos = 0)
{
    // return false if stops have exhausted
    if (pos == line_stops.size()) {
        return false;
    }

    // return true if stops or distance is matched
    if (line_stops.at(pos).stop == stop || line_stops.at(pos).distance == distance) {
        return true;
    }

    // Test next stop
    return has_stop_distance(line_stops, stop, distance, pos + 1);
}

bool add_tram_route(Line& tram_way, string line, string stop, float distance = 0)
{
    // Check if line exist
    if (tram_way.find(line) != tram_way.end()) {
        // Check if stop or distance in line exist
        if (has_stop_distance(tram_way.at(line), stop, distance)) {
            return false;
        } else {
            // Add new stop
            tram_way.at(line).push_back({ .stop = stop, .distance = distance });
            // sort stops
            sort(tram_way.at(line).begin(), tram_way.at(line).end(), sort_by_distance);
        }

    } else {
        // The line was not found in the map.
        // Create line and insert new stop
        Stop new_stop = { .stop = stop, .distance = distance };
        Stops new_stop_vector = { new_stop };
        tram_way.insert({ line, new_stop_vector });
    }
    //check if stop in line exist
    //check if distance in stop exist
    return true;
}

// Short and sweet main.
int main()
{
    print_rasse();

    // TODO: Implement the datastructure here

    Line tram_way;
    vector<string> tram_stops;

    string input_filename = "";
    cout << FILE_NAME;
    cin >> input_filename;

    // Open file to read values
    ifstream input_fileobject(input_filename);

    // Check if file exists
    if (not input_fileobject) {
        // File does not exist
        cout << BAD_FILE << endl;
        return EXIT_FAILURE;
    } else {
        // File exists
        string file_line = "";
        // Read file line by line
        while (getline(input_fileobject, file_line)) {
            std::vector<std::string> parts = split(file_line, ';', true);
            bool did_add = false;
            if (parts.size() < 2) {
                // File content has bad format
                input_fileobject.close();
                cout << BAD_FILE_CONTENT << endl;
                return EXIT_FAILURE;
            } else if (parts.size() == 2) {
                did_add = add_tram_route(tram_way, parts.at(0), parts.at(1));
            } else {
                did_add = add_tram_route(tram_way, parts.at(0), parts.at(1), stof(parts.at(2)));
            }

            if (!did_add) {
                input_fileobject.close();
                cout << DUPLICATE_LINE_STOP << endl;
                return EXIT_FAILURE;
            }
        }
        // Close file
         cout << "All added" << endl;
        input_fileobject.close();
    }

   
    return EXIT_SUCCESS;
}
