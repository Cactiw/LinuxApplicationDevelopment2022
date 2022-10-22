#include "stdio.h"
#include "stdlib.h"


int main(int argc, char** argv) {
    int N, M = 0, S = 1;
    switch (argc) {
        case 1:
            printf("This is help for range.c program!\n");
            break;
        case 4:
            S = atoi(argv[3]);
            // no break
        case 3:
            M = atoi(argv[2]);
            // no break
        case 2:
            N = atoi(argv[1]);
            for (int i = M; i < N; i += S) {
                printf("%d\n", i);
            }
        default:
            break;
    }
}
