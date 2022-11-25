#include "average.hpp"

int Average(const char* Filename, std::istream &ThreadsMemory, std::ostream &out) {
    std::ifstream file(Filename);
    int threadsLimit;
    int nMemorySize;

    __int128 globalSum = 0;
    std::vector<pthread_t> threads;

    ThreadsMemory >> threadsLimit >> nMemorySize;

    if (nMemorySize < 16)
    {
        std::cout << "Not enough memory to read the 128 bit number" << std::endl;
        return EXIT_FAILURE;
    }

    nMemorySize /= 16;
    std::vector<__int128> threadPart;

    int nNumbers = 0;
    while (!file.eof()) {

        while (!file.eof() && threadPart.size() < nMemorySize) {
            std::string s;
            file >> s;
            threadPart.push_back(hex2dec(s));
        }

        nNumbers += threadPart.size();

        if (threads.size() == threadsLimit) {
            for (pthread_t &thread: threads) {
                __int128 *sum;
                pthread_join(thread, (void **) &sum);
                globalSum += *sum;
                free(sum);
            }
            threads.clear();
        }

        pthread_t thread;
        auto *threadPartCopy = new std::vector<__int128>(threadPart);
        pthread_create(&thread, nullptr, calculateSum, threadPartCopy);
        threads.push_back(thread);

        threadPart.clear();
    }

    for (pthread_t &thread: threads) {
        __int128 *sum;
        pthread_join(thread, (void **) &sum);
        globalSum += *sum;
        free(sum);
    }

    __int128 average = globalSum / nNumbers;
    out << intToString(average) << std::endl;

    file.close();
    return EXIT_FAILURE;
}