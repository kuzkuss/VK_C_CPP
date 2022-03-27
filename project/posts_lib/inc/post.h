#ifndef PROJECT_POSTS_LIB_POST_H_
#define PROJECT_POSTS_LIB_POST_H_

#include <stdio.h>

#include "return_codes.h"

typedef struct {
  unsigned char day;
  unsigned char month;
  short year;
} date_t;

typedef enum {
  ZERO_GRADES,
  CORRECT_AVG_GRADE
} kind_avg_grade_t;

typedef struct {
  kind_avg_grade_t kind_avg_grade;
  union {
    float average_grade;
    int no_grade;
  };
} avg_grade_t;

typedef struct {
  size_t votes;
  avg_grade_t avg_grade;
  int last_grade;
  int id;
  date_t date;
} post_t;

return_code_t read_post(FILE *input_stream, post_t **p_post);

#endif  // PROJECT_POSTS_LIB_POST_H_
