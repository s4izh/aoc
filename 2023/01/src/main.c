#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define _cleanup_(x) __attribute__((__cleanup__(x)))
#define _cleanup_buffer_ _cleanup_(free_buffer)

void free_buffer(char **buffer) {
    if (*buffer)
        free(*buffer);
}

int read_file(char *filename, char **buffer) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    off_t file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    *buffer = (char*) malloc(file_size + 1);
    memset(*buffer, 0, file_size + 1);

    printf("file_size: %ld\n", file_size);

    int bytes_read = read(fd, *buffer, file_size);
    if (bytes_read == -1) {
        perror("read");
        return -1;
    }
    /* *buffer[bytes_read] = '\0'; */

    return fd;
}

int is_digit(char d) {
    return d >= '0' && d <= '9';
}

#define NO_SOLUTION -1
#define PARTIAL_SOLUTION 10
#define PARTIAL_SOLUTION_MOVE_1 11

int str_digit(char *str) {
    int number = NO_SOLUTION;
    int str_len = strlen(str);
    int i = str_len;

    if (strncmp(str, "zero", i) == 0) {
        if (i == 4) {
            number = 0;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "one", i) == 0) {
        if (i == 3) {
            number = 1;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "two", i) == 0) {
        if (i == 3) {
            number = 2;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "three", i) == 0) {
        if (i == 5) {
            number = 3;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "four", i) == 0) {
        if (i == 4) {
            number = 4;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "five", i) == 0) {
        if (i == 4) {
            number = 5;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "six", i) == 0) {
        if (i == 3) {
            number = 6;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "seven", i) == 0) {
        if (i == 5) {
            number = 7;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "eight", i) == 0) {
        if (i == 5) {
            number = 8;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    if (strncmp(str, "nine", i) == 0) {
        if (i == 4) {
            number = 9;
        }
        else if (i == str_len)
            number = PARTIAL_SOLUTION;
    }
    return number;
}

int part1(char *buffer) {
    int total = 0;
    int first = -1;
    int last = -1;
    int line = 0;
    while (*buffer != '\0') {
        while (*buffer != '\n') {
            if (is_digit(*buffer)) {
                if (first == -1) {
                    first = *buffer - '0';
                    last = first;
                } else {
                    last = *buffer - '0';
                }
            }
            buffer++;
        }
        int line_result = (first * 10 + last);
        total += line_result;
        first = -1;
        last = -1;
        line++;
        buffer++;
    }
    return total;
}

int letter_table[10] = {
    4, 3, 3, 5, 4, 4, 3, 5, 5, 4
};

void first_and_last_in_line(char* line, int* first, int* last) {
    *first = -1;
    *last = -1;

    int num = -1;

    for (int i = 0; i < strlen(line); ++i) {
        if (is_digit(line[i])) {
            if (*first == -1) {
                *first = line[i] - '0';
                *last = *first;
            } else {
                *last = line[i] - '0';
            }
            continue;
        }
        if (strncmp(&line[i], "zero", 4) == 0) num = 0;
        if (strncmp(&line[i], "one", 3) == 0) num = 1;
        if (strncmp(&line[i], "two", 3) == 0) num = 2;
        if (strncmp(&line[i], "three", 5) == 0) num = 3;
        if (strncmp(&line[i], "four", 4) == 0) num = 4;
        if (strncmp(&line[i], "five", 4) == 0) num = 5;
        if (strncmp(&line[i], "six", 3) == 0) num = 6;
        if (strncmp(&line[i], "seven", 5) == 0) num = 7;
        if (strncmp(&line[i], "eight", 5) == 0) num = 8;
        if (strncmp(&line[i], "nine", 4) == 0) num = 9;


        if (num != -1) {
            if (*first == -1) {
                *first = num;
                *last = num;
            } else {
                *last = num;
            }
        }
        num = -1;
    }
}

int part2(char *buffer) {
    int total = 0;
    int first = -1;
    int last = -1;
    int line = 0;
    char str_num[32];
    memset(str_num, 0, sizeof(str_num));

    char line_buffer[128];
    memset(line_buffer, 0, sizeof(line_buffer));

    int buff_i = 0;

    while (*buffer != '\0') {
        while (*buffer != '\n') {
            line_buffer[buff_i] = *buffer;
            buff_i++;
            buffer++;
        }

        first_and_last_in_line(line_buffer, &first, &last);
        /* printf("\n"); */

        int line_result = first * 10 + last;
        total += line_result;
        /* printf("line[%d] line_result: %d\n", line, line_result); */

        memset(line_buffer, 0, sizeof(line_buffer));
        buff_i = 0;
        buffer++;
        line++;
    }

    // esto estaba a nada de funcionar

    /* while (*buffer != '\0') { */
    /*     while (*buffer != '\n') { */
    /*         // part 1 adding a digit */
    /*         if (is_digit(*buffer)) { */
    /*             if (first == -1) { */
    /*                 first = *buffer - '0'; */
    /*                 last = first; */
    /*             } else { */
    /*                 last = *buffer - '0'; */
    /*             } */
    /*             memset(str_num, 0, sizeof(str_num)); */
    /*             buff_i = 0; */
    /*         } */

    /*         // part 2 adding a word as a digit */
    /*         str_num[buff_i] = *buffer; */
    /*         str_num[buff_i + 1] = '\0'; */
    /*         /1* printf("- buff_i: %d\n", buff_i); *1/ */
    /*         /1* printf("- buffer: %c\n", *buffer); *1/ */
    /*         /1* printf("- str_num: %s\n", str_num); *1/ */
    /*         int num = str_digit(str_num); */
    /*         /1* printf("- num: %d\n", num); *1/ */

    /*         if (num == NO_SOLUTION) { */
    /*             str_num[0] = str_num[buff_i]; */
    /*             str_num[1] = '\0'; */
    /*             num = str_digit(str_num); */
    /*             if (num == NO_SOLUTION) { */
    /*                 memset(str_num, 0, sizeof(str_num)); */
    /*                 buff_i = 0; */
    /*             } */
    /*             else if (num != PARTIAL_SOLUTION) { */
    /*                 if (first == -1) { */
    /*                     first = num; */
    /*                     last = first; */
    /*                 } else { */
    /*                     last = num; */
    /*                 } */
    /*                 memset(str_num, 0, sizeof(str_num)); */
    /*                 buff_i = 0; */
    /*             } */
    /*         } */
    /*         else if (num != PARTIAL_SOLUTION) { */
    /*             if (first == -1) { */
    /*                 first = num; */
    /*                 last = first; */
    /*             } else { */
    /*                 last = num; */
    /*             } */
    /*             memset(str_num, 0, sizeof(str_num)); */
    /*             buff_i = 0; */
    /*         } */
    /*         else { */
    /*             buff_i++; */
    /*         } */
    /*         buffer++; */
    /*     } */



    /*     int line_result = (first * 10 + last); */
    /*     total += line_result; */

    /*     printf("line[%d]: line_result: %d, total: %d, ", line, line_result, total); */
    /*     printf("first: %d, last: %d\n", first, last); */

    /*     first = -1; */
    /*     last = -1; */
    /*     line++; */
    /*     buffer++; */

    /*     // clear str_num buffer */
    /*     memset(str_num, 0, sizeof(str_num)); */
    /*     buff_i = 0; */
    /* } */

    return total;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *buffer;
    int fd = read_file(argv[1], &buffer);
    if (fd == -1) {
        return EXIT_FAILURE;
    }

    int result;

    result = part1(buffer);
    if (result != 142 && result != 198 && result != 55816) {
        printf("part1 failed, got: %d, expected: %d, or: %d, or: %d\n", result, 142, 198, 55816);
    } else {
        printf("part1 success, got: %d\n", result);
    }

    result = part2(buffer);
    if (result != 281 && result != 54980) {
        printf("part2 failed, got: %d, expected: %d or %d\n", result, 281, 54980);
    } else {
        printf("part2 success, got: %d\n", result);
    }

    return EXIT_SUCCESS;
}
