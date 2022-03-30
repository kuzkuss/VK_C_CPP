#include "post_count.h"

return_code_t count_required_posts(posts_array_t *posts_array,
                                   int *number_req_posts) {
  if (!posts_array || !number_req_posts) {
    return INCORRECT_ARGS;
  }

  *number_req_posts = 0;
  for (size_t i = 0; i < posts_array->size; ++i) {
    if (check_post(posts_array->data[i])) {
      ++(*number_req_posts);
    }
  }
  return OK;
}
