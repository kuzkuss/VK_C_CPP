#ifndef TP_C_CPP_PROJECT_POSTS_LIB_INC_POSTS_ARRAY_H_
#define TP_C_CPP_PROJECT_POSTS_LIB_INC_POSTS_ARRAY_H_

#include "post.h"

typedef struct {
  post_t **data;
  size_t size;
  size_t capacity;
} posts_array_t;

return_code_t read_array(FILE *input_stream, posts_array_t **posts_array);
void free_array(posts_array_t *array);

#endif  // TP_C_CPP_PROJECT_POSTS_LIB_INC_POSTS_ARRAY_H_
