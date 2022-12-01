#include "average.hpp"
#include <chrono>

namespace gcc_ints {
    __extension__ typedef __int128 int128;

}

int AverageMultiThread(const char* Filename, std::istream &ThreadsMemory, std::ostream &out) {
    std::ifstream file(Filename);
    int threadsLimit;
    int nMemorySize;

    gcc_ints::int128 globalSum = 0;
    std::vector<pthread_t> threads;

    ThreadsMemory >> threadsLimit >> nMemorySize;


    auto start = std::chrono::high_resolution_clock::now();
    if (nMemorySize < 16)
    {
        std::cout << "Not enough memory to read the 128 bit number" << std::endl;
        return EXIT_FAILURE;
    }

    nMemorySize /= 16;
    std::vector<gcc_ints::int128> threadPart;

    int nNumbers = 0;
    while (!file.eof()) {

        while (!file.eof() && (int)threadPart.size() < nMemorySize) {
            std::string s;
            file >> s;
            threadPart.push_back(hex2dec(s));
        }

        nNumbers += (int)threadPart.size();

        if ((int)threads.size() == threadsLimit) {
            for (pthread_t &thread: threads) {
                gcc_ints::int128 *sum;
                pthread_join(thread, (void **) &sum);
                globalSum += *sum;
                free(sum);
            }
            threads.clear();
        }

        pthread_t thread;
        auto *threadPartCopy = new std::vector<gcc_ints::int128>(threadPart);
        pthread_create(&thread, nullptr, calculateSum, threadPartCopy);
        threads.push_back(thread);

        threadPart.clear();
    }

    for (pthread_t &thread: threads) {
        gcc_ints::int128 *sum;
        pthread_join(thread, (void **) &sum);
        globalSum += *sum;
        free(sum);
    }

    gcc_ints::int128 average = globalSum / nNumbers;
    out << intToString(average) << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " microseconds" << std::endl;
    file.close();
    return 0;
}

int AverageSingleThread(const char* Filename, std::istream &ThreadsMemory, std::ostream &out)
{
    std::ifstream file(Filename);
    int threadsLimit;
    int nMemorySize;

    gcc_ints::int128 globalSum = 0;
    std::vector<pthread_t> threads;

    ThreadsMemory >> threadsLimit >> nMemorySize;

    auto start = std::chrono::high_resolution_clock::now();
    if (nMemorySize < 16)
    {
        std::cout << "Not enough memory to read the 128 bit number" << std::endl;
        return EXIT_FAILURE;
    }

    nMemorySize /= 16;
    std::vector<gcc_ints::int128> threadPart;

    int nNumbers = 0;
    while (!file.eof()) {

        while (!file.eof() && (int)threadPart.size() < nMemorySize) {
            std::string s;
            file >> s;
            threadPart.push_back(hex2dec(s));
        }

        nNumbers += (int)threadPart.size();

        gcc_ints::int128 sum = std::accumulate(threadPart.begin(), threadPart.end(), (gcc_ints::int128) 0);
        globalSum += sum;

        threadPart.clear();
    }

    gcc_ints::int128 average = globalSum / nNumbers;
    out << intToString(average) << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " microseconds" << std::endl;
    file.close();
    return 0;
}
