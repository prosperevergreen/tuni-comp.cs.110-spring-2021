/* Rasse2
 *
 * Desc:
 * This program can be used to manage a tram system.
 * There are possiblilities of adding routes through
 * file, or manually. Also, searches can be conducted
 * on the information got about the tram network for
 * navigation or other purposes.
 *
 * Program author
 * Name: Prosper Evergreen
 * Student number: 050542738
 * UserID: hsprev
 * E-Mail: prosper.evergreen@tuni.fi
 *
 * */

#include <fstream>
#include <iostream>
#include <locale> // std::locale, std::toupper
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Stop {
    string stop;
    float distance;
};

struct Multi_Word {
    string word;
    string::size_type next_index;
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
const string LINES_INTRO = "All tramlines in alphabetical order:";
const string STOPS_INTRO = "All stops in alphabetical order:";

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

/**
 * Sorts by distance function for a vector of Stops
 *
 * @param i First compare value
 * @param j Second compare value
 *
 * @return boolean of i < j
*/
bool sort_by_distance(Stop i, Stop j) { return (i.distance < j.distance); }

/**
 * Checks if stop or distance is already in the line
 *
 * @param line_stops Vector of stops of a line to be searched
 * @param stop Stop to be searched for in the line
 * @param distance Distance to be searched for in the line
 * @param pos Position of the stop in the line Vector to be searched
 *
 * @return Boolean of whether any match was found or not
*/
Stops::size_type has_stop_distance(Stops& line_stops, string stop, float distance = -1, Stops::size_type pos = 0)
{
    // return false if stops have exhausted
    if (pos == line_stops.size()) {
        return -1;
    }

    // return true if stops or distance is matched
    if (line_stops.at(pos).stop == stop || line_stops.at(pos).distance == distance) {
        return pos;
    }

    // Test next stop
    return has_stop_distance(line_stops, stop, distance, pos + 1);
}

/**
 * Add a new route to tram routes
 *
 * @param tram_way Tram routes
 * @param line Line name to be added to the tram routee
 * @param stop Stop name to be added to the line
 * @param distance Distance of stop from line start
 *
 * @return Successfulness of the insertion
*/
bool add_tram_route(Line& tram_way, string line, string stop, float distance = 0)
{
    // Check if line exist
    if (tram_way.find(line) != tram_way.end()) {
        // Check if stop or distance in line exist
        if (has_stop_distance(tram_way.at(line), stop, distance) > -1) {
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
    return true;
}

/**
 * Print all the lines in the tram network
 *
 * @param tram_way Tram routes
 * @param iter Poiter to a signle line in tram route
 *
*/
void print_lines(Line& tram_way, Line::iterator iter)
{
    if (iter == tram_way.end()) {
        return;
    }

    cout << iter->first << endl;
    print_lines(tram_way, ++iter);
}

/**
 * Extracts a line/stop name as a sigle or multiple words from command line e.g name or
 *
 * @param command_parts Vector of string consisting of the command contents separated by space
 * @param start_point start index of the word to be extracted
 *
 * @return Extracted word and index of the possible next word
*/
Multi_Word get_word_or_words(std::vector<std::string>& command_parts, std::vector<std::string>::size_type start_point)
{
    // Get word from command
    std::string full_word = command_parts.at(start_point);

    // Get start position in comand of word
    std::vector<std::string>::size_type next_index = start_point;

    // Move next word position
    next_index++;

    // Check if work starts with " sign
    if (full_word.at(0) == '"') {
        bool isEnd = false;
        std::vector<std::string>::size_type temp_index = start_point;
        string temp_word = "";
        while (!isEnd) {
            // Append word at command_parts index to temp_word
            if (temp_index == start_point) {
                temp_word += command_parts.at(temp_index);
            } else {
                temp_word += " " + command_parts.at(temp_index);
            }
            // Check if word end i.e end of word is " sign and terminate loop
            if (temp_word.at(temp_word.size() - 1) == '"')
                isEnd = true;
            // Go to next word in command
            temp_index++;
        }

        // Set next word location
        next_index = temp_index;

        // set full word as sub string of temp word removing the leading and trailing quotes
        full_word = temp_word.substr(1, temp_word.size() - 2);
    }

    return { .word = full_word, .next_index = next_index };
}

/**
 * Prints the stops in the given line vector
 *
 * @param stops Vector of stops of a line to be printed
 * @param index Position of the stop in the line Vector to be printed
 *
*/
void print_stop(Stops& stops, Stops::size_type index = 0)
{

    if (index == stops.size()) {
        return;
    }

    cout << " - " << stops.at(index).stop << " : " << stops.at(index).distance << endl;

    print_stop(stops, ++index);
}

bool has_line(Line& tram_way, string line)
{
    // Check if line exist
    if (tram_way.find(line) != tram_way.end()) {
        return true;
    } else {
        return false;
    }
}

/**
 * Prints the stops of the given line
 *
 * @param tram_way Tram routes
 * @param line Line name to be printed
 *
*/
void print_line(Line& tram_way, string line)
{
    // Check if line exist
    if (has_line(tram_way, line)) {
        cout << "Line " << line << " goes through these stops in the order they are listed:" << endl;
        print_stop(tram_way.at(line));
    } else {
        cout << BAD_LINE << endl;
    }
}

void get_stops(set<string>& stops_acc, Stops& stops)
{
    for (Stops::iterator stop = stops.begin(); stop != stops.end(); ++stop) {
        if (stops_acc.find(stop->stop) != stops_acc.end()) {
            continue;
        } else {
            stops_acc.insert(stop->stop);
        }
    }
}

void print_lines(Line& tram_way, string stop)
{
    set<string> lines_acc;

    for (Line::iterator line = tram_way.begin(); line != tram_way.end(); ++line) {
        if (has_stop_distance(line->second, stop) > -1)
            lines_acc.insert(line->first);
    }

    if (lines_acc.size() == 0) {
        cout << BAD_STOP << endl;
    } else {
        cout << "Stop " << stop << " can be found on the following lines:" << endl;

        for (set<string>::iterator line_name = lines_acc.begin(); line_name != lines_acc.end(); ++line_name) {
            cout << " - " << *line_name << endl;
        }
    }
}

void print_all_stops(Line& tram_way)
{
    set<string> stops_acc;

    for (Line::iterator line = tram_way.begin(); line != tram_way.end(); ++line) {
        get_stops(stops_acc, line->second);
    }

    cout << STOPS_INTRO << endl;

    for (set<string>::iterator stop_name = stops_acc.begin(); stop_name != stops_acc.end(); ++stop_name) {
        cout << *stop_name << endl;
    }
}

string str_toupper(string word)
{
    string word_uppercase = "";
    std::locale loc;
    for (std::string::size_type i = 0; i < word.length(); ++i)
        word_uppercase += std::toupper(word[i], loc);
    return word_uppercase;
}

float calc_distance(Stops& stops, Stops::size_type startIndex, Stops::size_type stopIndex)
{
    return abs(stops.at(startIndex).distance - stops.at(stopIndex).distance);;
}

void print_distance(Line& tram_way, string line, string stop1, string stop2)
{
    if (!has_line(tram_way, line)) {
        cout << BAD_LINE << endl;
        return;
    }

    Stops stops = tram_way.at(line);
    Stops::size_type index1 = has_stop_distance(stops, stop1);
    Stops::size_type index2 = has_stop_distance(stops, stop2);

    if (index1 * index2 < 0) {
        cout << BAD_STOP << endl;
        return;
    }

    float distance = calc_distance(stops, index1, index2);

    cout << "Distance between "<< stop1 <<" and "<< stop2 <<" is "<< distance << endl;
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
        input_fileobject.close();
    }
    cin.ignore();
    while (true) {
        std::string command_line = "";
        std::cout << "tramway> ";
        getline(std::cin, command_line);
        std::vector<std::string> parts = split(command_line, ' ', true);
        std::string command = str_toupper(parts.at(0));

        if (command == "LINES") {

            cout << LINES_INTRO << endl;
            print_lines(tram_way, tram_way.begin());

        } else if (command == "LINE" && parts.size() > 1) {

            std::string line = get_word_or_words(parts, 1).word;
            print_line(tram_way, line);

        } else if (command == "STOPS") {

            print_all_stops(tram_way);

        } else if (command == "STOP" && parts.size() > 1) {

            std::string stop = get_word_or_words(parts, 1).word;
            print_lines(tram_way, stop);

        } else if (command == "DISTANCE" && parts.size() > 3) {
            Multi_Word line = get_word_or_words(parts, 1);
            Multi_Word stop1 = get_word_or_words(parts, line.next_index);
            Multi_Word stop2 = get_word_or_words(parts, stop1.next_index);
            print_distance(tram_way, line.word, stop1.word, stop2.word);

        } else if (command == "ADDLINE" && parts.size() > 1) {
            std::string line = parts.at(1);
            // TODO: Implement the command here!

        } else if (command == "ADDSTOP" && parts.size() > 1) {
            std::string stop = parts.at(1);
            // TODO: Implement the command here!

        } else if (command == "REMOVE" && parts.size() > 1) {
            std::string stop = parts.at(1);
            // TODO: Implement the command here!

        } else if (command == "QUIT") {
            return EXIT_SUCCESS;
        } else {
            std::cout << BAD_COMMAND << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
