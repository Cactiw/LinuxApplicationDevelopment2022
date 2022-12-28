
#include <libgen.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libintl.h>

#define _(STRING) gettext(STRING)

enum {
    MIN = 1,
    MAX = 100
};


int roman_to_integer(char c)
{
    switch(c) {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0;
    }
}

int roman_to_int (char *s)
{
    int i, int_num = roman_to_integer(s[0]);

    for (i = 1; s[i] != '\0'; i++) {
        int prev_num = roman_to_integer(s[i - 1]);
        int cur_num = roman_to_integer(s[i]);
        if (prev_num < cur_num) {
            int_num = int_num - prev_num + (cur_num - prev_num);
        } else {
            int_num += cur_num;
        }
    }
    return int_num;
}

int main() {
    bindtextdomain("guess", getenv("PWD"));
    setlocale(LC_ALL, "");
    textdomain("guess");

    char* answer = NULL;
    int guess;

    int l_border = MIN, r_border = MAX;
    while (r_border - 1 > l_border) {
        guess = (l_border + r_border) / 2;
        printf(_("Is your number greater than %d? (y/n) "), guess);
        while (1) {
            scanf("%ms", &answer);
            if (strcmp(answer, _("y")) == 0) {
                l_border = guess;
                break;
            } else if (strcmp(answer, _("n")) == 0) {
                r_border = guess;
                break;
            } else {
                printf(_("Invalid answer\n"));
                return 1;
            }
        }
    }
    printf(_("Your number is %d\n"), r_border);
}