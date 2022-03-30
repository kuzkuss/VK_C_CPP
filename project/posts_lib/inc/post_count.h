#ifndef TP_C_CPP_PROJECT_POSTS_LIB_INC_POST_COUNT_H_
#define TP_C_CPP_PROJECT_POSTS_LIB_INC_POST_COUNT_H_

#include "posts_array.h"
#include "return_codes.h"

return_code_t count_required_posts(posts_array_t *posts_array,
                                   int *number_req_posts);

#endif  // TP_C_CPP_PROJECT_POSTS_LIB_INC_POST_COUNT_H_
