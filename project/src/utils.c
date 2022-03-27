#define _GNU_SOURCE

#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "count.h"
#include "utils.h"

#define FORMAT_STR_OPTIONS "hf:"
#define GETOPT_LONG_ERR -1

#define HELP_MSG "Usage:\n   app [options]\nParameters:\n   --help    show this help (optional parameter)\n\
   --filename <filepath>    to specify the path to the data file (required parameter)\n"

#define SHORT_OPTION_FILE 'f'
#define LONG_OPTION_FILE "filename"

#define SHORT_OPTION_HELP 'h'
#define LONG_OPTION_HELP "help"

#define MIN_ARGS 2

static void help(void);

return_code_t posts_process(int argc, char *argv[])
{
    char *filename = NULL;
    return_code_t rc = parse_args(argc, argv, &filename);
    if (rc == CALL_HELP) {
        return OK;
    }

    if (rc == KEY_ERROR) {
        return rc;
    }

  posts_array_t *posts_array = NULL;

  FILE *input_file = fopen(filename, "r");
  if (!input_file) {
      return FILE_ERROR;
  }

  rc = read_array(input_file, &posts_array);
  if (rc != OK) {
    return rc;
  }

  int res = count_required_posts(posts_array);

  printf("Result: %d", res);

  free(filename);
  free_array(posts_array);

  return OK;
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
    {NULL, 0, NULL, 0}
  };

  return_code_t rc = OK;
  while ((opt = getopt_long(argc, argv, FORMAT_STR_OPTIONS, options, &opt_idx)) != GETOPT_LONG_ERR)
  {
    switch (opt)
    {
      case SHORT_OPTION_FILE:
        *filename = strdup(optarg);
        if (!(*filename)) {
          return ALLOCATION_ERROR;
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

static void help(void) {
    printf(HELP_MSG);
}

