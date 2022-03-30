#define _GNU_SOURCE

#include "posts_array.h"

#include <stdlib.h>
#include <unistd.h>

#define INIT_SIZE 8
#define STEP 2

static posts_array_t *create_array(void);
static return_code_t append(posts_array_t *array, post_t *new_element);

return_code_t read_array(FILE *input_stream, posts_array_t **posts_array) {
  if (!input_stream || !posts_array) {
    return INCORRECT_ARGS;
  }

  return_code_t rc = OK;

  *posts_array = create_array();
  if (!(*posts_array)) {
    return ALLOCATION_ERROR;
  }

  post_t *post = NULL;
  while (!(rc = read_post(input_stream, &post))) {
    rc = append(*posts_array, post);
    if (rc != OK) {
      break;
    }
    post = NULL;
  }

  if (feof(input_stream) && rc == INPUT_ERROR) {
    rc = OK;
  }

  if ((*posts_array)->size == 0) {
    rc = INPUT_ERROR;
  }

  if (rc != OK) {
    free(post);
    free_array(*posts_array);
  }

  return rc;
}

static posts_array_t *create_array(void) {
  long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
  if (l1dcls == -1) {
    l1dcls = sizeof(void *);
  }

  posts_array_t *array = calloc(1, sizeof(posts_array_t));

  int rc = posix_memalign((void **)&array->data, l1dcls,
                          INIT_SIZE * sizeof(post_t *));
  if (rc != OK) {
    array->data = malloc(INIT_SIZE * sizeof(post_t *));
    if (!array->data) {
      free(array);
      return NULL;
    }
  }

  array->size = 0;
  array->capacity = INIT_SIZE;

  return array;
}

static return_code_t append(posts_array_t *array, post_t *new_element) {
  if (!array || !new_element) {
    return INCORRECT_ARGS;
  }

  if (array->size >= array->capacity) {
    post_t **tmp =
        realloc(array->data, array->capacity * sizeof(post_t *) * STEP);
    if (!tmp) {
      return ALLOCATION_ERROR;
    }

    array->data = tmp;
    array->capacity *= STEP;
  }

  array->data[array->size] = new_element;
  ++array->size;

  return OK;
}

void free_array(posts_array_t *array) {
  if (!array) {
    return;
  }

  for (size_t i = 0; i < array->size; ++i) {
    free(array->data[i]);
  }
  free(array->data);
  free(array);
}
