int aoc_file_to_string(char* filename, char** buffer);

// #ifdef AOC_IMPLEMENTATION

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define AOC_LOG_ERROR(fmt, ...)                                              \
    fprintf(                                                                 \
        stderr, "ERROR %s:%d (%s): " fmt "\n", __FILE__, __LINE__, __func__, \
        ##__VA_ARGS__)

int aoc_file_to_string(char* filename, char** buffer)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        AOC_LOG_ERROR("open");
        return -1;
    }
    off_t file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    *buffer = (char*)malloc(file_size + 1);
    memset(*buffer, 0, file_size + 1);

    int bytes_read = read(fd, *buffer, file_size);
    if (bytes_read == -1) {
        AOC_LOG_ERROR("read");
        return -1;
    }
    (*buffer)[bytes_read - 1] = '\0';

    return fd;
}

// #endif // AOC_IMPLEMENTATION
