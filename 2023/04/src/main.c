#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define SCRATCH_SIZE 512
#define SOLUTION_SIZE SCRATCH_SIZE

int error_exit(char* error_msg) {
    perror(error_msg);
    exit(1);
}

void usage(char* exec_name) {
    printf("Usage: %s <filename>", exec_name);
    exit(1);
}

void print_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(",");
    }
    printf("]\n");
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int* arr, int low, int high) {
    printf("partition args: %d, %d\n", low, high);
    int pivot = arr[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            ++i;
        }
    }
    swap(&arr[i], &arr[high]);

    return i;
}

void quicksort_rec(int* arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quicksort_rec(arr, low, p - 1);
        quicksort_rec(arr, p + 1, high);
    }
}

void quicksort(int* array, int size) {
    quicksort_rec(array, 0, size - 1);
}

static int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int check_part1(int* left, int left_index, int* right, int right_index) {
    int total_score = 0;

    qsort(left, left_index, sizeof(int), cmp);
    qsort(right, right_index, sizeof(int), cmp);

    /* print_array(left, left_index); */
    /* print_array(right, right_index); */

    for (int i = 0; i < left_index; ++i) {
        for (int j = 0; j < right_index; ++j) {
            /* printf("comparing left[%d](%d) to right[%d](%d)\n", i, left[i], j, right[j]); */
            if (left[i] == right[j]) {
                if (total_score == 0)
                    total_score = 1;
                else
                    total_score *= 2;
            }
        }
    }

    return total_score;
}

int read_file_to_string(char* filename, char** buffer)
{
    int ret = -1;

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        error_exit("open");
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char* tmp = (char*) malloc(file_size + 1);

    ret = read(fd, tmp, file_size);
    if (ret < file_size) {
        error_exit("read");
    }

    tmp[file_size] = '\0';

    *buffer = tmp;

    return file_size;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        usage(argv[0]);
    }

    char* buffer;
    int file_size = read_file_to_string(argv[1], &buffer);
    int skipped_colon = 0;

    char* line = strtok_r(buffer, "\n", &buffer);
    int total_sum = 0;

    while (line != NULL) {
        while (*line != ':' && !skipped_colon && *line != '\0') {
            ++line;
        }
        if (*line == ':') {
            ++line;
            skipped_colon = 1;
        }

        int left[SCRATCH_SIZE];
        int right[SOLUTION_SIZE];
        int left_full = 0;
        int right_full = 0;
        int left_index = 0;
        int right_index = 0;

        char* side = strtok_r(line, "|", &line);
        while (side != NULL) {
            char* num = strtok_r(side, " ", &side);
            while (num != NULL) {
                if (!left_full) {
                    left[left_index] = atoi(num);
                    ++left_index;
                }
                else {
                    right[right_index] = atoi(num);
                    ++right_index;
                }
                num = strtok_r(NULL, " ", &side);
            }
            left_full = 1;
            side = strtok_r(NULL, "|", &line);
        }
        total_sum += check_part1(left, left_index, right, right_index);

        line = strtok_r(NULL, "\n", &buffer);
        skipped_colon = 0;
    }
    printf("%d\n", total_sum);
}
