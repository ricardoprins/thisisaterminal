#include "gtest/gtest.h"
#include "commands.h"
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

// makefile test
TEST(CommandTest, TestMakeFile) {
    std::vector<std::string> args = {"testfile"};
    ASSERT_EQ(0, cmd_makefile(args));
    ASSERT_TRUE(fs::exists("testfile"));
    fs::remove("testfile"); // cleanup
}

// readfile test
TEST(CommandTest, TestReadFile) {
    std::ofstream testfile("testfile");
    testfile << "hello";
    testfile.close();

    std::vector<std::string> args = {"testfile"};
    ASSERT_EQ(0, cmd_readfile(args));
    fs::remove("testfile"); // cleanup
}

// writefile test
TEST(CommandTest, TestWriteFile) {
    std::vector<std::string> args = {"testfile", "hello"};
    ASSERT_EQ(0, cmd_writefile(args));
    ASSERT_TRUE(fs::exists("testfile"));

    std::ifstream testfile("testfile");
    std::string content;
    std::getline(testfile, content);
    ASSERT_EQ("hello", content);

    fs::remove("testfile"); // cleanup
}

// deletefile test
TEST(CommandTest, TestDeleteFile) {
    std::ofstream testfile("testfile");
    testfile << "hello";
    testfile.close();

    std::vector<std::string> args = {"testfile"};
    ASSERT_EQ(0, cmd_deletefile(args));
    ASSERT_FALSE(fs::exists("testfile")); // file should no longer exist
}

// renamefile test
TEST(CommandTest, TestRenameFile) {
    std::ofstream testfile("testfile");
    testfile << "hello";
    testfile.close();

    std::vector<std::string> args = {"testfile", "newfile"};
    ASSERT_EQ(0, cmd_renamefile(args));
    ASSERT_TRUE(fs::exists("newfile"));
    ASSERT_FALSE(fs::exists("testfile"));

    fs::remove("newfile"); // cleanup
}

// TODO: movefile test
// TODO: copyfile test
// TODO: search test

// mkdir test
TEST(CommandTest, TestCreateDirectory) {
    std::vector<std::string> args = {"testdir"};
    ASSERT_EQ(0, cmd_mkdir(args));
    ASSERT_TRUE(fs::exists("testdir"));
    ASSERT_TRUE(fs::is_directory("testdir"));

    fs::remove_all("testdir"); // cleanup
}

// help test
TEST(CommandTest, TestHelp) {
    // No arguments needed for help command
    std::vector<std::string> args = {};
    ASSERT_EQ(0, cmd_help(args));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
