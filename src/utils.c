#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Fetches input from stdin
 */
char* input(char *msg, size_t size) {
    char *buffer = (char *)malloc(size);

    if (buffer == NULL) {
        free(buffer);
        return NULL;
    }

    printf("%s", msg);

    if (fgets(buffer, (int) size, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

/**
 * Clears the current console stream
 */
void clear_console() {
    printf("\033[2J");

    #ifdef _WIN32
        system("cls"); // NOLINT
    #else
        system("clear"); // NOLINT
    #endif
}