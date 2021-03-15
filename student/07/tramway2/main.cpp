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

// using namespace std;

struct Stop {
    std::string stop;
    float distance;
};

struct Multi_Word {
    std::string word;
    std::string::size_type next_index;
};

using Stops = std::vector<Stop>;
using Line = std::map<std::string, Stops>;

const std::string FILE_NAME = "Give a name for input file: ";
const std::string BAD_FILE = "Error: File could not be read.";
const std::string BAD_FILE_CONTENT = "Error: Invalid format in file.";
const std::string BAD_COMMAND = "Error: Invalid input.";
const std::string BAD_STOP = "Error: Stop could not be found.";
const std::string BAD_LINE = "Error: Line could not be found.";
const std::string DUPLICATE_LINE_STOP = "Error: Stop/line already exists.";
const std::string REMOVED_STOP = "Stop was removed from all lines.";
const std::string LINES_INTRO = "All tramlines in alphabetical order:";
const std::string STOPS_INTRO = "All stops in alphabetical order:";
const std::string LINE_ADDED = "Line was added.";
const std::string STOP_ADDED = "Stop was added.";
const std::string STOP_REMOVED = "Stop was removed from all lines";

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
 * Returns the index of a stop in the stop vector
 *
 * @param line_stops Vector of stops of a line to be searched
 * @param stop Stop to be searched for in the line
 * @param distance Distance to be searched for in the line
 * @param pos Position of the stop in the line Vector to be searched
 *
 * @return return the index of the match or -1
*/
Stops::size_type get_stop_position(Stops& line_stops, std::string stop, Stops::size_type pos = 0)
{
    // return false if stops have exhausted
    if (pos == line_stops.size()) {
        return -1;
    }

    // return true if stops is matched
    if (line_stops.at(pos).stop == stop) {
        return pos;
    }

    // Test next stop
    return get_stop_position(line_stops, stop, ++pos);
}

/**
 * Checks if a stop is in the tram line or not
 *
 * @param stops Vector of stopss
 * @param stop_name Name of stop to be searched
 *
 * @return true if found else false
*/
bool has_stop_distance(Stops& stops, std::string stop_name, float distance = -1)
{
    for (Stops::iterator currStop = stops.begin(); currStop != stops.end(); ++currStop) {
        if (currStop->stop == stop_name || currStop->distance == distance) {
            return true;
        }
    }
    return false;
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
bool add_tram_route(Line& tram_way, std::string line, std::string stop, float distance = 0)
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
            std::sort(tram_way.at(line).begin(), tram_way.at(line).end(), sort_by_distance);
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
 * Print the line name of current iter
 *
 * @param tram_way Tram routes
 * @param iter Poiter to a signle line in tram route
 *
*/
void print_line(Line& tram_way, Line::iterator iter)
{
    if (iter == tram_way.end()) {
        return;
    }

    std::cout << iter->first << std::endl;
    print_line(tram_way, ++iter);
}

/**
 * Print all the lines in the tram network
 *
 * @param tram_way Tram routes
 *
*/
void print_all_lines(Line& tram_way)
{
    std::cout << LINES_INTRO << std::endl;
    print_line(tram_way, tram_way.begin());
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
        std::string temp_word = "";
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
 * Prints a stop in a given line position
 *
 * @param stops Vector of stops of a line to be printed
 * @param index Position of the stop in the line Vector to be printed
 *
*/
void print_line_stop(Stops& stops, Stops::size_type index = 0)
{

    if (index == stops.size()) {
        return;
    }

    std::cout << " - " << stops.at(index).stop << " : " << stops.at(index).distance << std::endl;

    print_line_stop(stops, ++index);
}

/**
 * Checks if a line is in the tram route or not
 *
 * @param tram_way Tram routes
 * @param line Line name to be printed
 *
 * @return true if found else false
*/
bool has_line(Line& tram_way, std::string line)
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
void print_line_stops(Line& tram_way, std::string line)
{
    // Check if line exist
    if (has_line(tram_way, line)) {
        std::cout << "Line " << line << " goes through these stops in the order they are listed:" << std::endl;
        print_line_stop(tram_way.at(line));
    } else {
        std::cout << BAD_LINE << std::endl;
    }
}

/**
 * Adds the stops to a set
 *
 * @param stops_acc ref of Accumulated stop set to be added new stops
 * @param stops Vector of stops of a line to be searched
 *
*/
void add_stops(std::set<std::string>& stops_acc, Stops& stops)
{
    for (Stops::iterator stop = stops.begin(); stop != stops.end(); ++stop) {
        // Continue if stop is already in the set else add
        if (stops_acc.find(stop->stop) != stops_acc.end()) {
            continue;
        } else {
            stops_acc.insert(stop->stop);
        }
    }
}

/**
 * Print the lines of a given stop
 *
 * @param tram_way Tram routes
 * @param stop Name of the stop to find it's lines
 *
*/
void print_stop_lines(Line& tram_way, std::string stop)
{
    std::set<std::string> lines_acc;

    for (Line::iterator line = tram_way.begin(); line != tram_way.end(); ++line) {
        // Add line if stop is in line stops
        if (has_stop_distance(line->second, stop))
            lines_acc.insert(line->first);
    }

    if (lines_acc.size() == 0) {
        std::cout << BAD_STOP << std::endl;
    } else {
        std::cout << "Stop " << stop << " can be found on the following lines:" << std::endl;

        for (std::set<std::string>::iterator line_name = lines_acc.begin(); line_name != lines_acc.end(); ++line_name) {
            std::cout << " - " << *line_name << std::endl;
        }
    }
}

/**
 * Print all the stops of the tram network
 *
 * @param tram_way Tram routes
 *
*/
void print_all_stops(Line& tram_way)
{
    std::set<std::string> stops_acc;

    for (Line::iterator line = tram_way.begin(); line != tram_way.end(); ++line) {
        add_stops(stops_acc, line->second);
    }

    std::cout << STOPS_INTRO << std::endl;

    for (std::set<std::string>::iterator stop_name = stops_acc.begin(); stop_name != stops_acc.end(); ++stop_name) {
        std::cout << *stop_name << std::endl;
    }
}

/**
 * Convert a string to upper case
 *
 * @param word String to be converted
 * 
 * @return String in upper case
*/
std::string str_to_upper(std::string word)
{
    std::string word_uppercase = "";
    std::locale loc;
    for (std::string::size_type i = 0; i < word.length(); ++i)
        word_uppercase += std::toupper(word[i], loc);
    return word_uppercase;
}

/**
 * Calculate the absolute distance between two stops
 * 
 * @param stops Vector of stops to be searched
 * @param startIndex index of the start position
 * @param stopIndex index of the stop position
 * 
 * @return the distance between the stops
*/
float calc_distance(Stops& stops, Stops::size_type startIndex, Stops::size_type stopIndex)
{
    return abs(stops.at(startIndex).distance - stops.at(stopIndex).distance);
}

/**
 * Prints the absolute distance between two stops
 *
 * @param tram_way Tram routes
 * @param line Name of the line to be used
 * @param stop1 Name of the stop to be used
 * @param stop2 Name of the line to be used
 * 
*/
void print_distance(Line& tram_way, std::string line, std::string stop1, std::string stop2)
{
    if (!has_line(tram_way, line)) {
        std::cout << BAD_LINE << std::endl;
        return;
    }

    Stops stops = tram_way.at(line);
    Stops::size_type index1 = get_stop_position(stops, stop1);
    Stops::size_type index2 = get_stop_position(stops, stop2);

    if (index1 < 0 || index2 < 0) {
        std::cout << BAD_STOP << std::endl;
        return;
    }

    float distance = calc_distance(stops, index1, index2);

    std::cout << "Distance between " << stop1 << " and " << stop2 << " is " << distance << std::endl;
}

/**
 * Add a new line with no stops to tram ways
 *
 * @param tram_way Tram routes
 * @param line Name of the line to be used
 * 
 * @return Successfulness of the operation
*/
bool add_line(Line& tram_way, std::string line_name)
{
    // Check if line exist
    if (tram_way.find(line_name) != tram_way.end()) {
        return false;
    } else {
        // The line was not found in the map.
        // Create new line
        tram_way.insert({ line_name, {} });
        return true;
    }
}

/**
 * Remove stop from all lines in tram ways
 *
 * @param tram_way Tram routes
 * @param stop_name Name of the stop to be removed
 * 
 * @return Successfulness of the operation
*/
bool remove_stop(Line& tram_way, std::string stop_name)
{
    bool found_stop = false;

    for (Line::iterator line = tram_way.begin(); line != tram_way.end(); ++line) {
        // Removes stop if line has stop in it
        if (has_stop_distance(line->second, stop_name)) {
            Stops::size_type pos = get_stop_position(line->second, stop_name);
            line->second.erase(line->second.begin() + pos);
            found_stop = true;
        }
    }

    return found_stop;
}

// Short and sweet main.
int main()
{
    print_rasse();

    // TODO: Implement the datastructure here

    Line tram_way;
    std::vector<std::string> tram_stops;

    std::string input_filename = "";
    std::cout << FILE_NAME;
    std::cin >> input_filename;

    // Open file to read values
    std::ifstream input_fileobject(input_filename);

    // Check if file exists
    if (not input_fileobject) {
        // File does not exist
        std::cout << BAD_FILE << std::endl;
        return EXIT_FAILURE;
    } else {
        // File exists
        std::string file_line = "";
        // Read file line by line
        while (getline(input_fileobject, file_line)) {
            std::vector<std::string> parts = split(file_line, ';', true);
            bool did_add = false;
            if (parts.size() < 2) {
                // File content has bad format
                input_fileobject.close();
                std::cout << BAD_FILE_CONTENT << std::endl;
                return EXIT_FAILURE;
            } else if (parts.size() == 2) {
                did_add = add_tram_route(tram_way, parts.at(0), parts.at(1));
            } else {
                did_add = add_tram_route(tram_way, parts.at(0), parts.at(1), stof(parts.at(2)));
            }

            if (!did_add) {
                input_fileobject.close();
                std::cout << DUPLICATE_LINE_STOP << std::endl;
                return EXIT_FAILURE;
            }
        }
        // Close file
        input_fileobject.close();
    }

    std::cin.ignore();

    while (true) {

        std::string command_line = "";
        std::cout << "tramway> ";

        // Read command line input
        getline(std::cin, command_line);

        // Split command into words
        std::vector<std::string> parts = split(command_line, ' ', true);

        // Get command action word
        std::string command = str_to_upper(parts.at(0));

        // Compare command action word
        if (command == "LINES") {

            print_all_lines(tram_way);

        } else if (command == "LINE" && parts.size() >= 2) {

            std::string line = get_word_or_words(parts, 1).word;
            print_line_stops(tram_way, line);

        } else if (command == "STOPS") {

            print_all_stops(tram_way);

        } else if (command == "STOP" && parts.size() >= 2) {

            std::string stop = get_word_or_words(parts, 1).word;
            print_stop_lines(tram_way, stop);

        } else if (command == "DISTANCE" && parts.size() >= 4) {

            Multi_Word line = get_word_or_words(parts, 1);
            Multi_Word stop1 = get_word_or_words(parts, line.next_index);
            Multi_Word stop2 = get_word_or_words(parts, stop1.next_index);
            print_distance(tram_way, line.word, stop1.word, stop2.word);

        } else if (command == "ADDLINE" && parts.size() >= 2) {

            std::string line = get_word_or_words(parts, 1).word;
            bool did_add = add_line(tram_way, line);

            if (did_add) {
                std::cout << LINE_ADDED << std::endl;
            } else {
                std::cout << DUPLICATE_LINE_STOP << std::endl;
            }
            // TODO: Implement the command here!

        } else if (command == "ADDSTOP" && parts.size() >= 4) {
            Multi_Word line = get_word_or_words(parts, 1);
            Multi_Word stop = get_word_or_words(parts, line.next_index);
            Multi_Word distance = get_word_or_words(parts, stop.next_index);

            bool did_add = add_tram_route(tram_way, line.word, stop.word, stof(distance.word));

            if (did_add) {
                std::cout << STOP_ADDED << std::endl;
            } else {
                std::cout << DUPLICATE_LINE_STOP << std::endl;
            }

        } else if (command == "REMOVE" && parts.size() >= 2) {

            std::string stop = get_word_or_words(parts, 1).word;
            bool did_remove = remove_stop(tram_way, stop);

            if (did_remove) {
                std::cout << STOP_REMOVED << std::endl;
            } else {
                std::cout << BAD_STOP << std::endl;
            }

        } else if (command == "QUIT") {
            return EXIT_SUCCESS;
        } else {
            std::cout << BAD_COMMAND << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
