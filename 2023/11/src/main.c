#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_utils.h"

struct line {
    char *text;
    struct line *next;
};

void free_lines(struct line* head) {
    while (head != NULL) {
        struct line* temp = head;
        head = head->next;
        free(temp->text);
        free(temp);
    }
}

#define for_each(line, head) \
    for (line = head; line != NULL; line = line->next)

struct line* parse_lines(char *lines) {
    struct line* head = NULL;
    struct line* current = NULL;
    struct line* prev = NULL;

    while(*lines != '\0') {
        current = malloc(sizeof(struct line));
        if (current == NULL) {
            free_lines(head);
            return NULL;
        }
        current->next = NULL;

        if (prev == NULL) {
            head = current;
        } else {
            prev->next = current;
        }

        size_t j = 0;
        while (lines[j] != '\n' && lines[j] != '\0') {
            ++j;
        }

        current->text = malloc(sizeof(char) * (j + 1));
        if (current->text == NULL) {
            free_lines(head);
            return NULL;
        }
        memcpy(current->text, lines, j);
        current->text[j] = '\0';

        lines += j + 1;

        prev = current;
    }

    return head;
}

int is_all_dots(char *buffer) {
    for (size_t i = 0; i < strlen(buffer); ++i) {
        if (buffer[i] != '.') {
            return 0;
        }
    }
    return 1;
}

void add_dot_line(struct line *line) {
    struct line *new_line = malloc(sizeof(struct line));

    size_t size = strlen(line->text);

    new_line->text = malloc(size + 1);
    new_line->next = line->next;
    line->next = new_line;

    if (new_line->text == NULL) {
        return;
    }
    memset(new_line->text, '.', size);
    new_line->text[size] = '\0';
}

int main(int argc, char **argv) {
    char *file_buffer;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int fd = read_file_to_string(argv[1], &file_buffer);
    if (fd == -1) {
        fprintf(stderr, "Error reading file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    struct line *first_line = parse_lines(file_buffer);

    struct line *e;

    for_each(e, first_line) {
        if (is_all_dots(e->text)) {
            add_dot_line(e);
            e = e->next; // skip 1 iteration
        }
    }

    for_each(e, first_line) {
        printf("Line: %s\n", e->text);
    }

    return EXIT_SUCCESS;
}
