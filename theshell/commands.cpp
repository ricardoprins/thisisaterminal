//
// Created by Ricardo Prins on 5/31/23.
//

#if defined(_WIN32) || defined(_WIN64)
#define localtime_r(_Time, _Tm) localtime_s(_Tm, _Time)
#endif

#include "commands.h"
#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>

// Helper function for time point conversion
std::chrono::system_clock::time_point from_file_time(std::filesystem::file_time_type file_time) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(file_time - std::filesystem::file_time_type::clock::now()
                                                        + system_clock::now());
    return sctp;
}

// Helper function to convert a time_point to a string
std::string to_string(std::chrono::system_clock::time_point tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm tm{};
    localtime_r(&t, &tm);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Makes a new file
int cmd_makefile(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "You must provide a file name.\n";
        return 1;
    }

    std::ofstream file(args[0]);

    if (!file) {
        std::cout << "Failed to create file: " << args[0] << '\n';
        return 1;
    }

    file.close();
    return 0;
}

// Reads a file
int cmd_readfile(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "You must provide a file name.\n";
        return 1;
    }

    std::ifstream file(args[0]);
    if (!file) {
        std::cout << "Failed to open file: " << args[0] << '\n';
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
    return 0;
}

// Writes into an existing file
int cmd_writefile(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "You must provide a file name and the content to write.\n";
        return 1;
    }

    std::ofstream file(args[0]);
    if (!file) {
        std::cout << "Failed to open file: " << args[0] << '\n';
        return 1;
    }

    file << args[1];
    file.close();
    return 0;
}

// Deletes an existing file
int cmd_deletefile(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "You must provide a file name.\n";
        return 1;
    }

    std::filesystem::path file_path(args[0]);
    if (std::filesystem::exists(file_path)) {
        std::filesystem::remove(file_path);
        return 0;
    } else {
        std::cout << "File doesn't exist: " << args[0] << '\n';
        return 1;
    }
}


// Renames an existing file
int cmd_renamefile(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "You must provide the existing file name and the new file name.\n";
        return 1;
    }

    std::filesystem::path old_path(args[0]);
    std::filesystem::path new_path(args[1]);

    if (std::filesystem::exists(old_path)) {
        std::filesystem::rename(old_path, new_path);
        return 0;
    } else {
        std::cout << "File doesn't exist: " << args[0] << '\n';
        return 1;
    }
}

// Moves an existing file into a different folder
int cmd_movefile(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "You must provide the existing file name and the destination directory.\n";
        return 1;
    }

    std::filesystem::path old_path(args[0]);
    std::filesystem::path new_path(args[1]);

    if (std::filesystem::exists(old_path)) {
        std::filesystem::rename(old_path, new_path / old_path.filename());
        return 0;
    } else {
        std::cout << "File doesn't exist: " << args[0] << '\n';
        return 1;
    }
}

// Copies an existing file into a specified destination (or into same folder as default)
int cmd_copyfile(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "You must provide the source file name and the destination directory.\n";
        return 1;
    }

    std::filesystem::path source_path(args[0]);
    std::filesystem::path destination_path(args[1]);

    if (std::filesystem::exists(source_path)) {
        std::filesystem::copy(source_path, destination_path / source_path.filename());
        return 0;
    } else {
        std::cout << "Source file doesn't exist: " << args[0] << '\n';
        return 1;
    }
}

// Makes a new directory
int cmd_mkdir(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "You must provide a directory name.\n";
        return 1;
    }

    std::filesystem::path dir_path(args[0]);

    if (std::filesystem::create_directory(dir_path)) {
        return 0;
    } else {
        std::cout << "Failed to create directory: " << args[0] << '\n';
        return 1;
    }
}

// Searches for a file
int cmd_search(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Search: missing operands\n";
        return 1;
    }

    const std::string& searchType = args[0];
    const std::string& target = args[1];

    std::cout << "Searching for " << target << "...\n";

    for (auto& dir : std::filesystem::recursive_directory_iterator(std::filesystem::current_path())) {
        // Search by filename or extension
        if ((searchType == "name" && dir.path().filename() == target) ||
            (searchType == "ext" && dir.path().extension() == target)) {
            std::cout << "Found: " << dir.path() << "\n";
        }
            // Search by size
        else if (searchType == "size" && args.size() == 4) {
            std::uintmax_t size = std::filesystem::file_size(dir.path());
            std::uintmax_t target_size = std::stoull(target);
            const std::string& op = args[2];
            if ((op == "<" && size < target_size)
                || (op == ">" && size > target_size)
                || (op == "=" && size == target_size)) {
                std::cout << "Found: " << dir.path() << "\n";
            }
        }
        // TODO: Search by modification date
    }

    return 0;
}

std::map<std::string, std::string> help_messages = {
        {"makefile", "makefile <filename> : Create a new file"},
        {"readfile", "readfile <filename> : Read a file"},
        {"writefile", "writefile <filename> : Write to an existing file"},
        {"deletefile", "deletefile <filename> : Delete a file"},
        {"renamefile", "renamefile <old_filename> <new_filename> : Rename a file"},
        {"movefile", "movefile <filename> <destination> : Move a file to a new location"},
        {"copyfile", "copyfile <filename> <destination> : Copy a file"},
        {"mkdir", "mkdir <directory_name> : Create a new directory"},
        {"help", "help : Display this help message"},
        {"search", "search <search type> <parameter>: Search for a file"},
        {"fileinfo", "fileinfo <filename>: Displays file information"}
};

// Help function for the commands
int cmd_help(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Available commands:\n";
        for (const auto& [command, description] : help_messages) {
            std::cout << description << "\n";
        }
    } else {
        const auto& it = help_messages.find(args[0]);
        if (it != help_messages.end()) {
            std::cout << it->second << "\n";
        } else {
            std::cerr << "Error: command not found: " << args[0] << "\n";
            return 1;
        }
    }
    return 0;
}

// Displays file information
int cmd_fileinfo(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "fileinfo: missing operand\n";
        return 1;
    }

    std::filesystem::path filepath(args[0]);
    if (!std::filesystem::exists(filepath)) {
        std::cerr << "fileinfo: " << filepath << ": No such file or directory\n";
        return 1;
    }

    std::cout << "Information for " << filepath << ":\n";
    std::cout << "Size: " << std::filesystem::file_size(filepath) << " bytes\n";
    std::cout << "Extension: " << filepath.extension() << "\n";

    auto creation_time = std::filesystem::last_write_time(filepath);
    std::chrono::system_clock::time_point tp_creation = from_file_time(creation_time);
    std::cout << "Last modification date: " << to_string(tp_creation) << "\n";

    return 0;
}


std::map<std::string, std::function<int(const std::vector<std::string>&)>> command_dispatcher = {
        {"makefile", cmd_makefile},
        {"readfile", cmd_readfile},
        {"writefile", cmd_writefile},
        {"deletefile", cmd_deletefile},
        {"renamefile", cmd_renamefile},
        {"movefile", cmd_movefile},
        {"copyfile", cmd_copyfile},
        {"mkdir", cmd_mkdir},
        {"help", cmd_help},
        {"search", cmd_search},
        {"fileinfo", cmd_fileinfo},
};

// Command executor
int execute_command(const std::string& command, const std::vector<std::string>& arguments){
    auto cmd_iterator = command_dispatcher.find(command);

    if (cmd_iterator == command_dispatcher.end()) {
        std::cout << "Unknown command: " << command << '\n';
        return 1;
    } else {
        return cmd_iterator->second(arguments);
    }
}