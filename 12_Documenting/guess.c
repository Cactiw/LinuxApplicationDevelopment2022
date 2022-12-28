/*
 * @file This is the only file for this project
 */
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



/** Translate the given char into roman numerals.
 *
 * @param c - the char to translate
 * @return the roman numeral
 */
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

/** A function that translate the given roman numeral into an integer.
 *
 * @param s - String to convert
 * @return the integer
 */
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

/** Translate the given integer into roman numerals.
 *
 * @param num - the integer to translate
 * @return char* - the roman numeral
 */
char* int_to_roman(int num)
{
    char *roman = malloc(16);
    int i = 0;

    while (num >= 1000) {
        roman[i++] = 'M';
        num -= 1000;
    }
    while (num >= 900) {
        roman[i++] = 'C';
        roman[i++] = 'M';
        num -= 900;
    }
    while (num >= 500) {
        roman[i++] = 'D';
        num -= 500;
    }
    while (num >= 400) {
        roman[i++] = 'C';
        roman[i++] = 'D';
        num -= 400;
    }
    while (num >= 100) {
        roman[i++] = 'C';
        num -= 100;
    }
    while (num >= 90) {
        roman[i++] = 'X';
        roman[i++] = 'C';
        num -= 90;
    }
    while (num >= 50) {
        roman[i++] = 'L';
        num -= 50;
    }
    while (num >= 40) {
        roman[i++] = 'X';
        roman[i++] = 'L';
        num -= 40;
    }
    while (num >= 10) {
        roman[i++] = 'X';
        num -= 10;
    }
    while (num >= 9) {
        roman[i++] = 'I';
        roman[i++] = 'X';
        num -= 9;
    }
    while (num >= 5) {
        roman[i++] = 'V';
        num -= 5;
    }
    while (num >= 4) {
        roman[i++] = 'I';
        roman[i++] = 'V';
        num -= 4;
    }
    while (num >= 1) {
        roman[i++] = 'I';
        num -= 1;
    }
    roman[i] = '\0';
    return roman;
}

/** Return N if not use_roman, otherwise return the roman numeral for N.
 *
 * @param n - the integer to translate
 * @param use_roman - if true, translate to roman numeral
 * @return char* - the numeral
 */
char* get_number(int n, int use_roman) {
    char *number = malloc(16);
    if (use_roman) {
        number = int_to_roman(n);
    } else {
        sprintf(number, "%d", n);
    }
    return number;
}

/** Main guess function.
 *
 */
int main(int argc, char **argv) {
    bindtextdomain("guess", getenv("PWD"));
    setlocale(LC_ALL, "");
    textdomain("guess");

    int use_roman = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            printf(_("Usage: %s [options]\n"), argv[0]);
            printf(_("Options:\n"));
            printf(_("  -r\t\tUse roman numbers\n"));
            printf(_("  --help\t\tPrint this help message\n"));
            printf(_("  --version\t\tPrint version information\n"));
            return 0;
        } else if (strcmp(argv[1], "--version") == 0) {

            printf("%s version %s (built %s %s)\n", argv[0], "1.0", __DATE__, __TIME__);
            return 0;
        } else if (strcmp(argv[1], "-r") == 0) {
            use_roman = 1;
        }

    }

    char* answer = NULL;
    int guess;

    int l_border = MIN, r_border = MAX;
    while (r_border - 1 > l_border) {
        guess = (l_border + r_border) / 2;
        printf(_("Is your number greater than %s? (y/n) "), get_number(guess, use_roman));
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

    if (use_roman) {
        printf(_("Your number is %s\n"), int_to_roman(r_border));
    } else {
        printf(_("Your number is %d\n"), r_border);
    }
}