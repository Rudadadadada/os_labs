#include "average.hpp"

int main() {
    AverageMultiThread("input.txt", std::cin, std::cout);
    AverageSingleThread("input.txt", std::cin, std::cout);
    return EXIT_FAILURE;
}