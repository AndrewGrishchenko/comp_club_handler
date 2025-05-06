#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "ClubManager.h"

namespace fs = std::filesystem;

class ClubManagerTest : public ::testing::Test {
protected:
    const std::string validInputFile = "test_input.txt";
    const std::string errorInputFile1 = "test_error_input1.txt";
    const std::string errorInputFile2 = "test_error_input2.txt";
    const std::string errorInputFile3 = "test_error_input3.txt";

    void SetUp() override {
        std::ofstream(validInputFile) <<
            "3\n"
            "09:00 19:00\n"
            "10\n"
            "09:48 1 client1\n";

        std::ofstream(errorInputFile1) <<
            "3 4\n"
            "09:00 19:00\n"
            "10\n"
            "09:48 1 client1 2\n";

        std::ofstream(errorInputFile2) <<
            "3\n"
            "09:00\n"
            "10\n"
            "09:48 1 client1 2\n";

        std::ofstream(errorInputFile3) <<
            "3\n"
            "09:00 19:00\n"
            "abc\n"
            "09:48 1 client1 2\n";
    }

    void TearDown() override {
        fs::remove(validInputFile);
        fs::remove(errorInputFile1);
        fs::remove(errorInputFile2);
        fs::remove(errorInputFile3);
    }
};

TEST_F(ClubManagerTest, ProcessWithoutErrors) {
    ClubManager manager("test_input.txt");
    ASSERT_TRUE(manager.process());
}

TEST_F(ClubManagerTest, ProcessWithErrorCase1) {
    ClubManager manager("test_error_input1.txt");
    ASSERT_FALSE(manager.process());
}

TEST_F(ClubManagerTest, ProcessWithErrorCase2) {
    ClubManager manager("test_error_input2.txt");
    ASSERT_FALSE(manager.process());
}

TEST_F(ClubManagerTest, ProcessWithErrorCase3) {
    ClubManager manager("test_error_input3.txt");
    ASSERT_FALSE(manager.process());
}