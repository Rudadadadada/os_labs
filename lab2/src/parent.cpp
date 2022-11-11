#include <sys/wait.h>
#include <fcntl.h>

#include "parent.hpp"


int Parent(const char *path_to_child, std::istream &in, std::ostream &out) {
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

        int descriptor_of_file = open(filename.c_str(), O_RDONLY);

        if (descriptor_of_file == -1) {
            std::cout << "File open error" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (dup2(descriptor_of_file, STDIN_FILENO) == -1) {
            std::cout << "Error changing stdin" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            std::cout << "Error changing stdout" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (execl(path_to_child, "", nullptr) == -1) {
            std::cout << "Error executing child process" << std::endl;
            exit(EXIT_FAILURE);
        }
    } else {
        close(fd[1]);
        wait(nullptr);
        int nums_sum;

        if (dup2(fd[0], STDIN_FILENO) == -1) {
            std::cout << "Error changing stdin" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cin >> nums_sum;
        out << nums_sum;

        close(fd[0]);
    }
    return EXIT_SUCCESS;
}
