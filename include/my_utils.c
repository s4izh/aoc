#include "my_utils.h"

int read_file_to_string(char *filename, char **buffer) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    off_t file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    *buffer = (char*) malloc(file_size + 1);
    memset(*buffer, 0, file_size + 1);

    int bytes_read = read(fd, *buffer, file_size);
    if (bytes_read == -1) {
        perror("read");
        return -1;
    }
    (*buffer)[bytes_read - 1] = '\0';

    return fd;
}
