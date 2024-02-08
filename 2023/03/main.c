#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int read_file_to_string(const char *filename, char **buffer) {
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


int main(int argc, char *argv[])
{
    const char* input_file = argv[1];
    char* input = NULL;

    read_file_to_string(input_file, &input);

    printf("%s\n", input);

    int line_length = 0;

    for (size_t i = 0; i < strlen(input); i++) {
        if (input[i] == '\n') {
            if (line_length == 0) {
                line_length = i;
            }
        }
    }

    return 0;
}
