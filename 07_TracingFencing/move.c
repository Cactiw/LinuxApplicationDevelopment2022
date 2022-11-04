
#include "stdlib.h"
#include "stdio.h"
#include "errno.h"

void on_error(FILE* input, FILE* output) {
    if (input != NULL) {
        fclose(input);
    }
    if (output != NULL) {
        fclose(output);
    }


}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Not enough arguments!\n");
        on_error(NULL, NULL);
        return 1;
    }
    FILE* input = fopen(argv[1], "r");
    if (errno || input == NULL) {
        on_error(input, NULL);
        fprintf(stderr, "Can not open input file\n");
        return 2;
    }

    FILE* output = fopen(argv[2], "w");
    if (errno || output == NULL) {
        on_error(input, output);
        fprintf(stderr, "Can not open output file\n");
        return 2;
    }
    char chr;
    while ((chr = fgetc(input)) != EOF) {
        if (errno) {
        on_error(input, output);
            fprintf(stderr, "Can not read from file!");
            return 3;
        }
        fputc(chr, output);
        if (errno) {
        on_error(input, output);
            fprintf(stderr, "Can not write to file!");
            return 4;
        }
    }
    if (errno) {
        on_error(input, output);
        fprintf(stderr, "Can not read from file!");
        return 3;
    }
    fclose(output);
    if (errno) {
        on_error(input, output);
        fprintf(stderr, "Can not close output file!");
        return 5;
    }
    fclose(input);
    if (errno) {
        on_error(input, output);
        fprintf(stderr, "Can not close input file!");
        return 6;
    }

    // Everything OK, delete old file
    remove(argv[1]);
    return 0;
}
