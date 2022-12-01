#include "utils.hpp"

std::string intToString(gcc_ints::int128 num) {
    std::string result;
    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num *= -1;
    }
    while (num > 0) {
        result += (num % 10) + '0';
        num /= 10;
    }
    if (isNegative) {
        result += '-';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

gcc_ints::int128 hex2dec(std::string hex) {
    gcc_ints::int128 result = 0;
    for (int i = 0; i < (int)hex.length(); i++) {
        if (hex[i] >= 48 && hex[i] <= 57) {
            result += (hex[i] - 48) * pow(16, hex.length() - i - 1);
        } else if (hex[i] >= 65 && hex[i] <= 70) {
            result += (hex[i] - 55) * pow(16, hex.length() - i - 1);
        } else if (hex[i] >= 97 && hex[i] <= 102) {
            result += (hex[i] - 87) * pow(16, hex.length() - i - 1);
        }
    }
    return result;
}

void *calculateSum(void *numbers) {
    auto *numbersVector = (std::vector<gcc_ints::int128> *) numbers;
    auto *sum = new gcc_ints::int128(0);
    *sum = std::accumulate(numbersVector->begin(), numbersVector->end(), *sum);
    free(numbers);
    return sum;
}