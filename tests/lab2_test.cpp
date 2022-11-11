#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>

#include "parent.hpp"

namespace fs = std::filesystem;

TEST(FirstLabTests, SimpleTest) {
const char* fileWithInput = "input.txt";
const char* fileWithOutput = "output.txt";
const char* fileWithNums = "nums.txt";

constexpr int inputSize = 4;

std::array<const char*, inputSize> input = {
        "1 2 3 4",
        "0 3 2",
        "5 6 5",
        "1337"
};

std::array<int, inputSize> expectedOutput = {
        1368
};

    {
        auto inFile = std::ofstream(fileWithInput);

        inFile << fileWithNums << '\n';
    }

    {
        auto inFile = std::ofstream(fileWithNums);

        for(const auto& line : input) {
            inFile << line << '\n';
        }
    }

    auto inFile = std::ifstream(fileWithInput);
    {
        auto outFile = std::ofstream(fileWithOutput);
        Parent(getenv("child"), inFile, outFile);
    }

    auto outFile = std::ifstream(fileWithOutput);
    int res;
    outFile >> res;

    EXPECT_EQ(res, expectedOutput[0]);

    auto removeIfExists = [](const char* path) {
        if(fs::exists(path)) {
            fs::remove(path);
        }
    };

    removeIfExists(fileWithInput);
    removeIfExists(fileWithOutput);
}