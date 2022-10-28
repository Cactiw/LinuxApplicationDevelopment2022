#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "regex.h"


void error_handler(int res, regex_t regex) {
    size_t error_message_len = regerror(res, &regex, NULL, 0);
    char *error_buf = calloc(error_message_len, sizeof(*error_buf));
    regerror(res, &regex, error_buf, error_message_len);
    fprintf(stderr, "%s\n", error_buf);
    free(error_buf);
    regfree(&regex);

}

void sub(char* regStr, char* sub, char* str) {
    regex_t regex;
    int res = regcomp(&regex, regStr, 0);
    if (res) {
        fprintf(stderr, "Can not compile regex!");
        error_handler(res, regex);
        return;
    }
    regmatch_t regmatch[1];
    res = regexec(&regex, str, 1, regmatch, 0);
    if (res == REG_NOMATCH) {
        // Ничего не нашлось, просто выйти
        printf("%s\n", str);
        return;
    }
    if (res) {
        error_handler(res, regex);
        return;
        // Ошибка, обрабатываем
    }
    const unsigned long long endLength = strlen(str) - regmatch[0].rm_eo;
    char* beginning = malloc((regmatch[0].rm_so + 1) * sizeof(char));
    char* end = malloc(endLength + 2 * sizeof(char));
    strncpy(beginning, str, regmatch[0].rm_so);
    strncpy(end, str + regmatch[0].rm_eo, endLength);
    printf("%s%s%s\n", beginning, sub, end);

    free(beginning);
    free(end);
    regfree(&regex);
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "Not enough arguments!");
        return 1;
    }
    sub(argv[1], argv[2], argv[3]);
}
