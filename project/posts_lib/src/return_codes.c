#include "return_codes.h"

#include <stdio.h>

#define INCORRECT_ARGS_MSG "Invalid arguments in the function."
#define INPUT_ERROR_MSG "Input error: incorrect data."
#define ALLOCATION_ERROR_MSG "Memory allocation error."
#define FILE_ERROR_MSG "File opening error."
#define KEY_ERROR_MSG \
  "Invalid command line arguments. Use \"--help\" for more information."
#define PARALLEL_ERROR_MSG "Error while executing parallel algorithm."

void check_error(int rc) {
  switch (rc) {
    case INCORRECT_ARGS:
      fprintf(stderr, "%s\n", INCORRECT_ARGS_MSG);
      break;
    case INPUT_ERROR:
      fprintf(stderr, "%s\n", INPUT_ERROR_MSG);
      break;
    case ALLOCATION_ERROR:
      fprintf(stderr, "%s\n", ALLOCATION_ERROR_MSG);
      break;
    case FILE_ERROR:
      fprintf(stderr, "%s\n", FILE_ERROR_MSG);
      break;
    case KEY_ERROR:
      fprintf(stderr, "%s\n", KEY_ERROR_MSG);
      break;
    case PARALLEL_ERROR:
      fprintf(stderr, "%s\n", PARALLEL_ERROR_MSG);
      break;
  }
}
