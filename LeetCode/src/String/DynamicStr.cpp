#include <cstdio>
#include <cstdlib>
#include <cstring>

const int basic = 4;

char* scan(char *str) {
    if (str == NULL) {
        str = (char*)malloc(basic * sizeof(char));
    }
    int length = basic;
    int index = 0;
    while (scanf("%c", (str + index)) != EOF) {
        index++;
        if (str[index - 1] == '\n') {
            break;
        }
        if (index >= length) {
            length = length << 1;
            str = (char*)realloc(str, length);
        }
    }
    str[index] = '\0';
    return str;
}


int main(int argc, char* argv[]) {
    char *str = 0;
    str = scan(str);
    printf("str length: %lu\n", strlen(str));
    printf("%s\n", str);
    free(str);
    return 0;
}