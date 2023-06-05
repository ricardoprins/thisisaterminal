//
// Created by Ricardo Prins on 5/31/23.
//

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "commands.h"


void parse_input(const std::string& input, std::string& command, std::vector<std::string>& arguments) {
    std::stringstream ss(input);
    std::string word;

    // Get the command.
    if (ss >> word) {
        command = word;
    }

    // Get the arguments.
    while (ss >> word) {
        arguments.push_back(word);
    }
}


int main() {
    std::cout << R"(
 _______  __   __  _______  _______  __   __  _______  ___      ___
|       ||  | |  ||       ||       ||  | |  ||       ||   |    |   |
|_     _||  |_|  ||    ___||  _____||  |_|  ||    ___||   |    |   |
  |   |  |       ||   |___ | |_____ |       ||   |___ |   |    |   |
  |   |  |       ||    ___||_____  ||       ||    ___||   |___ |   |___
  |   |  |   _   ||   |___  _____| ||   _   ||   |___ |       ||       |
  |___|  |__| |__||_______||_______||__| |__||_______||_______||_______|
)" << '\n';

    std::cout << "Insert your command here or type 'help' for help\n";

    std::string input;
    std::string command;
    std::vector<std::string> arguments;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        parse_input(input, command, arguments);

        if (command == "exit") {
            break;
        }

        int result = execute_command(command, arguments);
        if (result != 0) {
            std::cout << "Command execution failed with error code: " << result << '\n';
        }

        command.clear();
        arguments.clear();
    }

    return 0;
}
