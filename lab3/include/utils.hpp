#ifndef OS_LAB3_UTILS_HPP
#define OS_LAB3_UTILS_HPP

#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>

namespace gcc_ints {
    __extension__ typedef __int128 int128;

}

std::string intToString(gcc_ints::int128 num);

gcc_ints::int128 hex2dec(std::string hex);

void *calculateSum(void *numbers);

#endif