#include <stdio.h>

int main() {
    char str[100];
    int i = 0;
    printf("Enter string: ");
    scanf("%s", str);

    while (str[i] == 'a') {
        i++;
    }


    if (str[i] == 'b' && str[i+1] == 'b' && str[i+2] == '\0') {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}