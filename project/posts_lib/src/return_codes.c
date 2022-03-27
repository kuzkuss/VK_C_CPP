#include <stdio.h>

#include "return_codes.h"

#define INCORRECT_ARGS_MSG "Invalid arguments in the function."
#define INPUT_ERROR_MSG "Input error: incorrect data."
#define ALLOCATION_ERROR_MSG "Memory allocation error."
#define FILE_ERROR_MSG "File opening error."
#define KEY_ERROR_MSG "Invalid command line arguments. Use \"--help\" for more information."

void check_error(int rc) {
    if (rc == INCORRECT_ARGS) {
        fprintf(stderr, "%s\n", INCORRECT_ARGS_MSG);
    }
    else if (rc == INPUT_ERROR) {
        fprintf(stderr, "%s\n", INPUT_ERROR_MSG);
    }
    else if (rc == ALLOCATION_ERROR) {
        fprintf(stderr, "%s\n", ALLOCATION_ERROR_MSG);
    }
    else if (rc == FILE_ERROR) {
        fprintf(stderr, "%s\n", FILE_ERROR_MSG);
    }
    else {
        fprintf(stderr, "%s\n", KEY_ERROR_MSG);
    }
}