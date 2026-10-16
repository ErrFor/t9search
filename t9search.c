#include <stdio.h>

// Convert a character to its corresponding T9 digit representation
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

    return '\0';  // Character has no T9 representation
}

// Check if the T9 pattern matches any consecutive part of the text
int matches(const char text[], const char pattern[]) {
    
    // Try matching the pattern starting at each character
    for (int i = 0; text[i] != '\0'; i++) {
        int j = 0;

        // Compare consecutive characters through their T9 representations
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

// Read a line from stdin and check whether it fits in the buffer
int readLine(char str[], int size) {
    if (fgets(str, size, stdin) == NULL)
        return 0;  // EOF reached

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            return 1;  // Successfully read a line
        }
    }

    return -1;  // Line too long
}

// Validate that the name is non-empty and contains only printable ASCII characters
int validName(const char str[]) {
    if (str[0] == '\0')
        return 0;

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];

        if (c < 32 || c > 126)
            return 0;
    }

    return 1;
}

// Validate that the phone number is non-empty and contains digits with an optional leading '+'
int validPhone(const char str[]) {
    if (str[0] == '\0')
        return 0;

    int i = 0;

    if (str[0] == '+') {
        i = 1;

        if (str[i] == '\0')
            return 0;
    }

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {              
    char name[102];
    char phone[102];
    int found = 0;

    // Validate the number of command-line arguments
    if (argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    // Validate the search pattern
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
            fprintf(stderr, "Invalid argument length\n");
            return 1;
        }
    }

    // Process contacts until the end of input
    while (1) {
        int nameStatus = readLine(name, sizeof(name));

        if (nameStatus == 0)
            break;

        if (nameStatus == -1) {
            fprintf(stderr, "Input line too long\n");
            return 1;
        }

        int phoneStatus = readLine(phone, sizeof(phone));

        if (phoneStatus != 1) {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }

        // Validate both fields before processing the contact
        if (!validName(name) || !validPhone(phone)) {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }

        // Print all contacts or only those matching the pattern
        if (argc == 1) {
            fprintf(stdout, "%s, %s\n", name, phone);
        }else {
            if (matches(name, argv[1]) || matches(phone, argv[1])) {
                fprintf(stdout, "%s, %s\n", name, phone);
                found = 1;
            }
        }
    }

    // Report when no contacts match the search pattern
    if (argc == 2 && !found) {
        fprintf(stdout, "Not found\n");
    }

    return 0;
}