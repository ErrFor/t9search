#include <stdio.h>

char charToDigit(char c) {
    if(c >= '0' && c <= '9')
        return c;

    if((c >= 'a' && c <= 'c') || (c >= 'A' && c <= 'C'))
        return '2';

    if((c >= 'd' && c <= 'f') || (c >= 'D' && c <= 'F'))
        return '3';

    if((c >= 'g' && c <= 'i') || (c >= 'G' && c <= 'I'))
        return '4';

    if((c >= 'j' && c <= 'l') || (c >= 'J' && c <= 'L'))
        return '5';

    if((c >= 'm' && c <= 'o') || (c >= 'M' && c <= 'O'))
        return '6';

    if((c >= 'p' && c <= 's') || (c >= 'P' && c <= 'S'))
        return '7';

    if((c >= 't' && c <= 'v') || (c >= 'T' && c <= 'V'))
        return '8';

    if((c >= 'w' && c <= 'z') || (c >= 'W' && c <= 'Z'))
        return '9';

    if (c == '+')
        return '0';

    return '\0';
}

int matches(const char text[], const char pattern[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        int j = 0;

        while (pattern[j] != '\0' && text[i + j] != '\0') {

            if (charToDigit(text[i + j]) != pattern[j])
                break;

            j++;
        }

        if (pattern[j] == '\0')
            return 1;
    }

    return 0;
}

int readLine(char str[], int size) {
    if (fgets(str, size, stdin) == NULL)
        return 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            return 1;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    char name[102];
    char phone[102];
    int found = 0;

    if (argc > 2) {
        fprintf(stderr, "Invalid argument\n");
        return 1;
    }

    if (argc == 2) {
        int length = 0;

        while (argv[1][length] != '\0') {
            if (argv[1][length] < '0' || argv[1][length] > '9') {
                fprintf(stderr, "Invalid argument\n");
                return 1;
            }

            length++;
        }

        if (length == 0 || length > 100) {
            fprintf(stderr, "Invalid argument\n");
            return 1;
        }
    }

    while (1) {
        int nameStatus = readLine(name, sizeof(name));

        if (nameStatus == 0)
            break;

        if (nameStatus == -1) {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }

        int phoneStatus = readLine(phone, sizeof(phone));

        if (phoneStatus != 1) {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }

        if (argc == 1) {
            fprintf(stdout, "%s, %s\n", name, phone);
        }else {
            if (matches(name, argv[1]) || matches(phone, argv[1])) {
                fprintf(stdout, "%s, %s\n", name, phone);
                found = 1;
            }
        }
    }

    if (argc == 2 && !found) {
        fprintf(stdout, "Not found\n");
    }

    return 0;
}