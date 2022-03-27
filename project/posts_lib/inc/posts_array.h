#ifndef PROJECT_POSTS_LIB_postS_ARRAY_H_
#define PROJECT_POSTS_LIB_postS_ARRAY_H_

#include "post.h"

typedef struct {
  post_t **data;
  size_t size;
  size_t capacity;
} posts_array_t;

return_code_t read_array(FILE *input_stream, posts_array_t **posts_array);
void free_array(posts_array_t *array);

#endif  // PROJECT_POSTS_LIB_postS_ARRAY_H_
