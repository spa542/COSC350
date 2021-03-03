#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int str_to_int(char* num) {
    // Subtract the ASCII 0 from each digit and then multiply by each
    // decimal place to get out number back
    int i, result = 0;
    for (i = 0; num[i] != '\0'; i++) {
        result = result * 10 + num[i] - '0';
    }
    return result;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        puts("*** Invalid # of arguments ***");
        return 1;
    }

    int i;
    int tmp, result = 0;
    for (i = 0; i < argc; i++) {
        tmp = str_to_int(argv[i]);
        if (tmp % 2 != 0) {
            result += tmp;
        }
    }

    printf("The sum of odd arguments is %d\n", result);

    return 0;
}
