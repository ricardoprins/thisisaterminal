//
// Created by Ricardo Prins on 5/31/23.
//

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "commands.h"
#include "replxx.hxx"

using Replxx = replxx::Replxx;

// A list of all available commands for usage with code completion, hinting, and syntax highlighting.
const std::vector<std::string> commands = {
        "makefile",
        "readfile",
        "writefile",
        "deletefile",
        "renamefile",
        "movefile",
        "copyfile",
        "mkdir",
        "help",
        "search",
        "fileinfo",
};

// Completion generation callback
std::vector<replxx::Replxx::Completion> completionHook(const std::string& context, [[maybe_unused]] int index) {
    std::vector<replxx::Replxx::Completion> completions;
    for (const auto& cmd : commands) {
        if (cmd.find(context) == 0) {
            completions.emplace_back(cmd);
        }
    }
    return completions;
}

// Hint generation callback
std::vector<std::string> hintHook(const std::string& context, [[maybe_unused]] int index, replxx::Replxx::Color& color) {
    std::vector<std::string> hints;
    for (const auto& cmd : commands) {
        if (cmd.size() > context.size() && cmd.substr(0, context.size()) == context) {
            color = replxx::Replxx::Color::YELLOW; // set the hint text color
            hints.push_back(cmd.substr(context.size())); // add the hint text
        }
    }
    return hints; // return the generated hints
}



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

    Replxx rx;
    rx.install_window_change_handler();

    rx.set_completion_callback(completionHook);
    rx.set_hint_callback(hintHook);

    std::string input;
    std::string command;
    std::vector<std::string> arguments;

    while (true) {
        char const* cinput = rx.input( "> " );
        if (cinput == nullptr) {
            printf("\n");
            break;
        }
        input = cinput;

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
