#include "utils.hpp"

int count()
{
    int numsSum = 0;
    int num = 0;
    while (std::cin >> num) {
        numsSum += num;
    }
    return numsSum;
}