
#include "rhash.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "errno.h"

#ifdef HAVE_LIBREADLINE
#include "readline/readline.h"
#endif

int main() {
    char *str = NULL;
    rhash_library_init();
#ifdef HAVE_LIBREADLINE
    str = readline("rhash> ");
#else
    size_t size;
    printf("rhash> ");
    getline(&str, &size, stdin);
#endif
    fflush(stdout);
    while (str != NULL) {
//        printf("Parsing\n");
//        fflush(stdout);
        char* alg_name = strtok(str, " ");
        char* inputStr = strtok(strtok(NULL, " "), "\n");
//        printf("Got inputStr: %s\n", inputStr);
//        printf("Got alg_name: %s\n", alg_name);

        int output_mode = islower(alg_name[0]) ? RHPR_HEX : RHPR_UPPERCASE;
        for(int i = 0; alg_name[i]; i++){
            alg_name[i] = tolower(alg_name[i]);
        }
//        printf("alg_name after lower: %s\n", alg_name);
//        fprintf(stderr, "starting rhash\n");

        int alg = -1;
        if (!strcmp(alg_name, "md5")) {
            alg = RHASH_MD5;
        } else if (!strcmp(alg_name, "sha1")) {
            alg = RHASH_SHA1;
        } else if (!strcmp(alg_name, "tth")) {
            alg = RHASH_TTH;
        }
        if (alg == -1) {
            fprintf(stderr, "Unknown algorithm: %s", alg_name);
#ifdef HAVE_LIBREADLINE
            str = readline("rhash> ");
#else
            printf("rhash> ");
            getline(&str, &size, stdin);
#endif
            continue;
        }
        char is_file = inputStr[0] != '\"';
        unsigned char result[128];
        int res;
        fflush(stdout);
        if (is_file) {
//            printf("Parsing file: %s\n", inputStr);
            res = rhash_file(alg, inputStr, result);
        } else {
//            printf("Parsing line: %s\n", inputStr);
            res = rhash_msg(alg, inputStr, strlen(inputStr), result);
        }
        if (res < 0) {
            fprintf(stderr, "RHash error: %s\n", strerror(errno));
        } else {
            char output[128];
            rhash_print_bytes(output, result, rhash_get_digest_size(alg), output_mode);
            puts(output);
        }

#ifdef HAVE_LIBREADLINE
        str = readline("rhash> ");
#else
        printf("rhash> ");
        getline(&str, &size, stdin);
#endif
    }

}
