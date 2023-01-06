#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <memory>

#include "average.hpp"

namespace fs = std::filesystem;

TEST(ThirdLabTests, SimpleTest) {
    const char *fileWithInput = "input.txt";
    const char *fileWithOutput = "output.txt";
    const char *fileWithTM = "tm.txt";

    constexpr int nTests = 3;

    std::vector<const char *> tm0 = {
            "3 80"
    };

    std::vector<const char *> input0 = {
            "00000000000000000000000000000001",
            "00000000000000000000000000000002",
            "00000000000000000000000000000003",
            "00000000000000000000000000000004",
            "00000000000000000000000000000005"
    };

    std::vector<const char *> expectedOutput0 = {
            "3"
    };

    std::vector<const char *> tm1 = {
            "5 16"
    };

    std::vector<const char *> input1 = {
            "0000000000000000000000000000000A",
            "0000000000000000000000000000000B",
            "0000000000000000000000000000000C",
            "0000000000000000000000000000000D",
            "0000000000000000000000000000000E"
    };

    std::vector<const char *> expectedOutput1 = {
            "12"
    };

    std::vector<const char *> tm2 = {
            "1 80"
    };

    std::vector<const char *> input2 = {
            "00000000000000008b38a67f4692599c",
            "0000000000000000fcbe4a81bbe7dbe9",
    };

    std::vector<const char *> expectedOutput2 = {
            "14122013549869733888"
    };

    std::vector<std::vector<const char *>> input = {input0, input1, input2};
    std::vector<std::vector<const char *>> expectedOutput = {expectedOutput0, expectedOutput1, expectedOutput2};
    std::vector<std::vector<const char *>> tm = {tm0, tm1, tm2};


    for (int test = 0; test < nTests; ++test)
    {

        std::vector<const char *> curTest = input[test];
        std::vector<const char *> curExpectedOutput = expectedOutput[test];
        std::vector<const char *> curTM = tm[test];


        {
        auto inFile = std::ofstream(fileWithInput);

        for (int i = 0; i < (int)curTest.size() - 1; ++i) {
            inFile << curTest[i] << '\n';
        }
        inFile << curTest[curTest.size() - 1];
        }

        {
            auto inFileTM = std::ofstream(fileWithTM);

            for (const auto &line: curTM) {
                inFileTM << line << '\n';
            }
        }

        auto inFile = std::ifstream(fileWithInput);
        {
            auto inFileTM = std::ifstream(fileWithTM);
            auto outFile = std::ofstream(fileWithOutput);
            AverageSingleThread(fileWithInput, inFileTM, outFile);
        }

        auto outFile = std::ifstream(fileWithOutput);
        std::string res;
        outFile >> res;

        EXPECT_EQ(res, curExpectedOutput[0]);

        auto removeIfExists = [](const char* path) {
            if(fs::exists(path)) {
                fs::remove(path);
            }
        };

        removeIfExists(fileWithInput);
        removeIfExists(fileWithOutput);
        removeIfExists(fileWithTM);
    }
}