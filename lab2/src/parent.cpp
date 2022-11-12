#include <sys/wait.h>
#include <fcntl.h>

#include "parent.hpp"


int Parent(const char *pathToChild, std::istream &in, std::ostream &out) {
    int fd[2];
    if (pipe(fd) == -1) {
        std::cout << "Pipe open error" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string filename;
    in >> filename;

    int pid = fork();
    if (pid == -1) {
        std::cout << "Fork error" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        close(fd[0]);
        int descriptorOfFile = open(filename.c_str(), O_RDONLY);
        if (descriptorOfFile == -1) {
            std::cout << "File open error" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (dup2(descriptorOfFile, STDIN_FILENO) == -1) {
            std::cout << "Error changing stdin" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            std::cout << "Error changing stdout" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (execl(pathToChild, "", nullptr) == -1) {
            std::cout << "Error executing child process" << std::endl;
            exit(EXIT_FAILURE);
        }
    } else {
        close(fd[1]);
        wait(nullptr);
        int NumsSum;

        if (dup2(fd[0], STDIN_FILENO) == -1) {
            std::cout << "Error changing stdin" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cin >> NumsSum;
        out << NumsSum;

        close(fd[0]);
    }
    return EXIT_SUCCESS;
}
