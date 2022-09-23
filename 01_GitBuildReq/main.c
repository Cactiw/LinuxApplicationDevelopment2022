#include "stdio.h"
#include "string.h"

#define BUF_SIZE 1024

int main() {
    char str[BUF_SIZE];
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\r\n")] = 0;
    printf("Hello, %s!\n", str);
}
