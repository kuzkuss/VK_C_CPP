#ifndef PROJECT_POSTS_LIB_INC_POST_H_
#define PROJECT_POSTS_LIB_INC_POST_H_

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

#include "return_codes.h"

typedef struct {
  u_int8_t day;
  u_int8_t month;
  u_int16_t year;
} date_t;

typedef struct {
  unsigned int id;
  unsigned int votes;
  float avg_grade;
  bool is_correct_avg_grade;
  u_int8_t last_grade;
  date_t date;
} post_t;

return_code_t read_post(FILE *input_stream, post_t **p_post);
bool check_post(const post_t *post);

#endif  // PROJECT_POSTS_LIB_INC_POST_H_
