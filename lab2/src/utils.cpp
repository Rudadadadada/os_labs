#include "utils.hpp"

int count()
{
    int nums_sum = 0;
    int num = 0;
    while (std::cin >> num) {
        nums_sum += num;
    }
    return nums_sum;
}