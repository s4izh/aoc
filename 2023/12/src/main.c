#include "aoc.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    char* input;
    aoc_file_to_string(argv[1], &input);

    printf("%s\n", input);

}
