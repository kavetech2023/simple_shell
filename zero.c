#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf("simple_shell> "); // Display the prompt
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n"); // Handle end of file (Ctrl+D)
            break;
        }

        // Remove the trailing newline character
        input[strlen(input) - 1] = '\0';

        // Execute the command using the system function
        int result = system(input);

        if (result == -1) {
            perror("system"); // Handle execution error
        } else {
            if (WIFEXITED(result)) {
                if (WEXITSTATUS(result) != 0) {
                    fprintf(stderr, "Error: Command not found or failed\n");
                }
            } else {
                fprintf(stderr, "Error: Command did not terminate normally\n");
            }
        }
    }

    return 0;
}

