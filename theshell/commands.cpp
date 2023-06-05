//
// Created by Ricardo Prins on 5/31/23.
//

#include "commands.h"
#include <iostream>
#include <fstream>


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
// TODO: implement search by file size and modification date
int cmd_search(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Error: not enough arguments. Please provide a path and a file name/extension.\n";
        return 1;
    }

    const std::string& path = args[0];
    const std::string& file_to_search = args[1];

    try {
        if (!std::filesystem::exists(path)) {
            std::cerr << "Error: the path does not exist.\n";
            return 1;
        }

        std::filesystem::recursive_directory_iterator dir(path);
        std::filesystem::recursive_directory_iterator end;

        while (dir != end) {
            if (std::filesystem::is_regular_file(*dir)) {
                std::string file_name = dir->path().filename();
                if (file_name.find(file_to_search) != std::string::npos) {
                    std::cout << "Found: " << dir->path() << "\n";
                }
            }
            ++dir;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

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
};

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
        {"search", "search: Search for a file"},
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