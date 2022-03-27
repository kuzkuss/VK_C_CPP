#define _GNU_SOURCE

#include "post.h"

#include <stdio.h>
#include <stdlib.h>

#include "return_codes.h"

typedef enum {
  NO_GRADES,
  MIN_GRADE = 1,
  MAX_GRADE = 5
} values_grade_t;

typedef enum {
  MIN_DAY = 1,
  MAX_DAY = 31
} limits_day_t;

typedef enum {
  MIN_MONTH = 1,
  MAX_MONTH = 12
} limits_month_t;

static post_t *create_post(size_t votes, float grade, int last_grade, int id, const date_t *date);

return_code_t read_post(FILE *input_stream, post_t **p_post) {
  if (!input_stream || !p_post) {
    return INCORRECT_ARGS;
  }

  size_t votes = 0;
  float grade = 0.0;
  int last_grade = 0;
  int id = 0;
  date_t date = { 0 };

  if (fscanf(input_stream, "%d%f%zu%hhu.%hhu.%hd%d", &id, &grade, &votes, &date.day, &date.month, &date.year, &last_grade) != 7) {
    return INPUT_ERROR;
  }

  if (id < 0 || grade < NO_GRADES || grade > MAX_GRADE || (grade < MIN_GRADE && grade > NO_GRADES)) {
    return INPUT_ERROR;
  }
  
  if (date.day < MIN_DAY || date.day > MAX_DAY || date.month < MIN_MONTH || date.month > MAX_MONTH || date.year < 0 || 
                                                                    last_grade < MIN_GRADE || last_grade > MAX_GRADE) {
    return INPUT_ERROR;
  }

  *p_post = create_post(votes, grade, last_grade, id, &date);
  if (!(*p_post)) {
    return ALLOCATION_ERROR;
  }

  return OK;
}

static post_t *create_post(size_t votes, float grade, int last_grade, int id, const date_t *date) {
  if (!date || grade < NO_GRADES || grade > MAX_GRADE || (grade < MIN_GRADE && grade > NO_GRADES) 
                                        || last_grade < MIN_GRADE || last_grade > MAX_GRADE || id < 0) {
    return NULL;
  }

  post_t *post = malloc(sizeof(post_t));
  if (post) {
    post->votes = votes;
    if (grade < MIN_GRADE) {
      post->avg_grade.no_grade = NO_GRADES;
      post->avg_grade.kind_avg_grade = ZERO_GRADES;
    } else {
      post->avg_grade.average_grade = grade;
      post->avg_grade.kind_avg_grade = CORRECT_AVG_GRADE;
    }
    post->last_grade = last_grade;
    post->id = id;
    post->date = *date;
  }

  return post;
}
