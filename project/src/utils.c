#define _GNU_SOURCE

#include "utils.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "post_count.h"

#define FORMAT_STR_OPTIONS "hf:"
#define GETOPT_LONG_ERR -1

#define HELP_MSG                                                             \
  "Usage:\n   app [options]\nParameters:\n   --help    show this help "      \
  "(optional parameter)\n"                                                   \
  "--filename <filepath>    to specify the path to the data file (required " \
  "parameter)\n"

#define SHORT_OPTION_FILE 'f'
#define LONG_OPTION_FILE "filename"

#define SHORT_OPTION_HELP 'h'
#define LONG_OPTION_HELP "help"

#define MIN_ARGS 2

static void help(void);

return_code_t run_process(int argc, char *argv[]) {
  if (!argv) {
    return INCORRECT_ARGS;
  }

  char *filename = NULL;
  return_code_t rc = parse_args(argc, argv, &filename);
  if (rc == CALL_HELP) {
    return OK;
  }

  if (rc != OK) {
    return rc;
  }

  int res = 0;
  rc = posts_process(filename, &res);

  free(filename);

  if (rc == OK) {
    printf("Result: %d\n", res);
  }

  return rc;
}

return_code_t posts_process(const char *filename, int *res) {
  if (!filename) {
    return INCORRECT_ARGS;
  }

  FILE *input_file = fopen(filename, "r");
  if (!input_file) {
    return FILE_ERROR;
  }

  posts_array_t *posts_array = NULL;

  return_code_t rc = read_array(input_file, &posts_array);

  fclose(input_file);

  if (rc != OK) {
    return rc;
  }

  rc = count_required_posts(posts_array, res);

  free_array(posts_array);

  return rc;
}

return_code_t parse_args(int argc, char *argv[], char **filename) {
  if (argc < MIN_ARGS || !argv || !filename) {
    return KEY_ERROR;
  }

  int opt = 0;
  int opt_idx = 0;

  struct option options[] = {
      {LONG_OPTION_HELP, no_argument, NULL, SHORT_OPTION_HELP},
      {LONG_OPTION_FILE, required_argument, NULL, SHORT_OPTION_FILE},
      {NULL, 0, NULL, 0}};

  return_code_t rc = OK;
  while (rc == OK && (opt = getopt_long(argc, argv, FORMAT_STR_OPTIONS, options,
                                        &opt_idx)) != GETOPT_LONG_ERR) {
    switch (opt) {
      case SHORT_OPTION_FILE:
        free(*filename);
        *filename = strdup(optarg);
        if (!(*filename)) {
          rc = ALLOCATION_ERROR;
        }
        break;
      case SHORT_OPTION_HELP:
        help();
        rc = CALL_HELP;
        break;
      default:
        help();
        rc = KEY_ERROR;
        break;
    }
  }

  if (rc != OK) {
    free(*filename);
    return rc;
  }

  if (optind < argc) {
    free(*filename);
    return KEY_ERROR;
  }

  return OK;
}

static void help(void) { printf("%s", HELP_MSG); }
