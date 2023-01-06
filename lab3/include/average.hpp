#ifndef OS_LAB3_AVERAGE_H
#define OS_LAB3_AVERAGE_H

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <vector>
#include "utils.hpp"
#include <ctime>

int AverageMultiThread(const char* Filename, std::istream &ThreadsMemory, std::ostream &out);

int AverageSingleThread(const char* Filename, std::istream &ThreadsMemory, std::ostream &out);

#endif