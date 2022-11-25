#ifndef OS_LAB3_UTILS_HPP
#define OS_LAB3_UTILS_HPP

#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>

std::string intToString(__int128 num);

__int128 hex2dec(std::string hex);

void *calculateSum(void *numbers);

#endif