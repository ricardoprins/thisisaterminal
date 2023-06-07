//
// Created by Ricardo Prins on 5/31/23.
//
// TODO: add coverage for fileinfo, help, search

#include "commands.h"
#include <gtest/gtest.h>
#include <fstream>

TEST(CommandsTest, TestMakefile) {
    std::vector<std::string> args = {"testfile.txt"};
    int result = cmd_makefile(args);
    ASSERT_EQ(result, 0);
    ASSERT_TRUE(std::filesystem::exists("testfile.txt"));
}

TEST(CommandsTest, TestReadfile) {
    std::vector<std::string> args = {"testfile.txt"};

    // First ensure the file exists and has content
    std::ofstream ofs(args[0]);
    ofs << "test content";
    ofs.close();

    // Now test reading it
    int result = cmd_readfile(args);
    ASSERT_EQ(result, 0);
}

TEST(CommandsTest, TestWritefile) {
    std::vector<std::string> args = {"testfile.txt", "Hello, World!"};

    // First ensure the file exists
    cmd_makefile({args[0]});

    // Now test writing to it
    int result = cmd_writefile(args);
    ASSERT_EQ(result, 0);

    // Check if the contents are written correctly
    std::ifstream ifs(args[0]);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    ASSERT_EQ(content, "Hello, World!");
}

TEST(CommandsTest, TestDeletefile) {
    std::vector<std::string> args = {"testfile.txt"};

    // First ensure the file exists
    cmd_makefile(args);

    // Now test deleting it
    int result = cmd_deletefile(args);
    ASSERT_EQ(result, 0);
    ASSERT_FALSE(std::filesystem::exists("testfile.txt"));
}

TEST(CommandsTest, TestRenamefile) {
    std::vector<std::string> args = {"testfile.txt", "renamedfile.txt"};

    // Ensure the file exists
    cmd_makefile({args[0]});

    // Now test renaming it
    int result = cmd_renamefile(args);
    ASSERT_EQ(result, 0);
    ASSERT_TRUE(std::filesystem::exists("renamedfile.txt"));
    ASSERT_FALSE(std::filesystem::exists("testfile.txt"));
}

TEST(CommandsTest, TestMovefile) {
    std::vector<std::string> args = {"renamedfile.txt", "./testdir"};

    // Ensure the file exists and the directory where to move
    cmd_makefile({args[0]});
    cmd_mkdir({args[1]});

    // Now test moving it
    int result = cmd_movefile(args);
    ASSERT_EQ(result, 0);
    ASSERT_TRUE(std::filesystem::exists("./testdir/renamedfile.txt"));
    ASSERT_FALSE(std::filesystem::exists("renamedfile.txt"));
}

TEST(CommandsTest, TestCopyfile) {
    std::vector<std::string> args = {"./testdir/renamedfile.txt", "."};

    // Ensure the file exists
    cmd_makefile(args);

    // Now test copying it
    int result = cmd_copyfile(args);
    ASSERT_EQ(result, 0);
    ASSERT_TRUE(std::filesystem::exists("renamedfile.txt"));
    ASSERT_TRUE(std::filesystem::exists("./testdir/renamedfile.txt"));
}

TEST(CommandsTest, TestMkdir) {
    std::vector<std::string> args = {"testdir2"};

    // Test making a directory
    int result = cmd_mkdir(args);
    ASSERT_EQ(result, 0);
    ASSERT_TRUE(std::filesystem::exists("testdir2"));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
