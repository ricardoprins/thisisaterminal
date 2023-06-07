//
// Created by Ricardo Prins on 5/31/23.
//
// TODO:
// 4. Menu System:
//- Implement a menu system that allows the user to select the desired file operation from a list of options.
//- Ensure that the menu system is easy to navigate and provides a clear understanding of available choices.

#include <vector>
#include <string>
#include <map>
#include <functional>

#ifndef THISISATERMINAL_COMMANDS_H
#define THISISATERMINAL_COMMANDS_H


int cmd_makefile(const std::vector<std::string>& args);
int cmd_readfile(const std::vector<std::string>& args);
int cmd_writefile(const std::vector<std::string>& args);
int cmd_deletefile(const std::vector<std::string>& args);
int cmd_renamefile(const std::vector<std::string>& args);
int cmd_movefile(const std::vector<std::string>& args);
int cmd_copyfile(const std::vector<std::string>& args);
int cmd_mkdir(const std::vector<std::string>& args);
int cmd_search(const std::vector<std::string>& args);
int cmd_help(const std::vector<std::string>& args);
int cmd_fileinfo(const std::vector<std::string>& args);

int execute_command(const std::string& command, const std::vector<std::string>& arguments);

extern std::map<std::string, std::function<int(const std::vector<std::string>&)>> command_dispatcher;
void parse_input(const std::string& input, std::string& command, std::vector<std::string>& arguments);


#endif //THISISATERMINAL_COMMANDS_H
