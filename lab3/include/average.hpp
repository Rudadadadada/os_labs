#ifndef OS_LAB3_AVERAGE_H
#define OS_LAB3_AVERAGE_H

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <vector>
#include "utils.hpp"

int Average(const char* Filename, std::istream &ThreadsMemory, std::ostream &out);

#endif