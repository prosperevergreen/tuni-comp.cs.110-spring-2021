#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

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

void record_save(std::string id1, std::string id2, std::map<std::string, std::vector<std::string>>& record_book)
{
    if (record_book.find(id1) != record_book.end()) {
        record_book.at(id1).push_back(id2);
    } else {
        record_book.insert({ id1, { id2 } });
    }
}

void record_print(std::string id, std::map<std::string, std::vector<std::string>>& record_book, std::string indent = "")
{
    // Print the current id and its indentation
    std::cout << indent << id << std::endl;

    // Check if id has a sub network
    if (record_book.find(id) != record_book.end()) {
        indent += "..";
        for (auto sub_id : record_book.at(id)) {
            record_print(sub_id, record_book, indent);
        }
    }
}

unsigned int record_count(std::string id, std::map<std::string, std::vector<std::string>>& record_book, unsigned int count = 0)
{
    // Check if id has a sub network
    if (record_book.find(id) != record_book.end()) {
        for (auto sub_id : record_book.at(id)) {
            count += record_count(sub_id, record_book, 1 );
        }
        return count;
    }
    return count;
}


unsigned int max_depth_count(std::string id, std::map<std::string, std::vector<std::string>>& record_book, unsigned int depth = 0)
{
    // Check if id has a sub network
    if (record_book.find(id) != record_book.end()) {
        ++depth;
        unsigned int max = 0;
        for (auto sub_id : record_book.at(id)) {
            unsigned int prev_depth = max_depth_count(sub_id, record_book, depth);
            max = prev_depth > max ? prev_depth : max;
        }
        return max;
    }
    return depth + 1;
}



int main()
{
    // TODO: Implement the datastructure here

    std::map<std::string, std::vector<std::string>> netword_record;

    while (true) {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if (command == "S" or command == "s") {
            if (parts.size() != 3) {
                std::cout << "Erroneous parameters!" << std::endl
                          << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            record_save(id1, id2, netword_record);

        } else if (command == "P" or command == "p") {
            if (parts.size() != 2) {
                std::cout << "Erroneous parameters!" << std::endl
                          << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            record_print(id, netword_record);

        } else if (command == "C" or command == "c") {
            if (parts.size() != 2) {
                std::cout << "Erroneous parameters!" << std::endl
                          << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << record_count(id, netword_record) << std::endl;

        } else if (command == "D" or command == "d") {
            if (parts.size() != 2) {
                std::cout << "Erroneous parameters!" << std::endl
                          << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << max_depth_count(id, netword_record) << std::endl;

        } else if (command == "Q" or command == "q") {
            return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl
                      << HELP_TEXT;
        }
    }
}
