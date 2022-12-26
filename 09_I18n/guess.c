
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