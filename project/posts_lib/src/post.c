#define _GNU_SOURCE

#include "post.h"

#include <stdlib.h>
#include <time.h>

#define REQUIRED_BOUND 4.0
#define QUARTER 3
#define MONTHS 12
#define MAX_DIFF_YEARS 1

#define START_OF_MONTHS 1
#define START_OF_YEARS 1900

#define NUM_FIELDS 7

#define SCANF_FORMAT_STR "%d%f%zu%hhu.%hhu.%hd%d"

typedef enum { NO_GRADES, MIN_GRADE = 1, MAX_GRADE = 5 } values_grade_t;

typedef enum { MIN_DAY = 1, MAX_DAY = 31 } limits_day_t;

typedef enum { MIN_MONTH = 1, MAX_MONTH = 12 } limits_month_t;

static post_t *create_post(size_t votes, float grade, int last_grade, int id,
                           const date_t *date);
static bool check_grade(const post_t *post);
static date_t get_current_date(void);
static bool check_date(const post_t *post);

return_code_t read_post(FILE *input_stream, post_t **p_post) {
  if (!input_stream || !p_post) {
    return INCORRECT_ARGS;
  }

  size_t votes = 0;
  float grade = 0.0;
  int last_grade = 0;
  int id = 0;
  date_t date = {0};

  if (fscanf(input_stream, SCANF_FORMAT_STR, &id, &grade, &votes, &date.day,
             &date.month, &date.year, &last_grade) != NUM_FIELDS) {
    return INPUT_ERROR;
  }

  if (id < 0 || grade < NO_GRADES || grade > MAX_GRADE ||
      (grade < MIN_GRADE && grade > NO_GRADES)) {
    return INPUT_ERROR;
  }

  if (date.day < MIN_DAY || date.day > MAX_DAY || date.month < MIN_MONTH ||
      date.month > MAX_MONTH || date.year < 0 || last_grade < MIN_GRADE ||
      last_grade > MAX_GRADE) {
    return INPUT_ERROR;
  }

  *p_post = create_post(votes, grade, last_grade, id, &date);
  if (!(*p_post)) {
    return ALLOCATION_ERROR;
  }

  return OK;
}

static post_t *create_post(size_t votes, float grade, int last_grade, int id,
                           const date_t *date) {
  if (!date || grade < NO_GRADES || grade > MAX_GRADE ||
      (grade < MIN_GRADE && grade > NO_GRADES) || last_grade < MIN_GRADE ||
      last_grade > MAX_GRADE || id < 0) {
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

bool check_post(const post_t *post) {
  if (!post) {
    return false;
  }

  return check_grade(post) && check_date(post);
}

static bool check_grade(const post_t *post) {
  if (!post) {
    return false;
  }

  return post->avg_grade.kind_avg_grade == CORRECT_AVG_GRADE &&
         !(post->avg_grade.average_grade < REQUIRED_BOUND);
}

static date_t get_current_date(void) {
  time_t cur_time = time(NULL);
  struct tm cur_date = {0};
  localtime_r(&cur_time, &cur_date);
  date_t date = {0};
  date.day = cur_date.tm_mday;
  date.month = cur_date.tm_mon + START_OF_MONTHS;
  date.year = cur_date.tm_year + START_OF_YEARS;
  return date;
}

static bool check_date(const post_t *post) {
  if (!post) {
    return false;
  }

  date_t today = get_current_date();
  if (post->date.year == today.year &&
      (today.month - post->date.month <= QUARTER)) {
    if (today.month - post->date.month == QUARTER &&
        post->date.day < today.day) {
      return false;
    }
    return true;
  }
  if (today.year - post->date.year == MAX_DIFF_YEARS &&
      (today.month + MONTHS - post->date.month <= QUARTER)) {
    if (today.month + MONTHS - post->date.month == QUARTER &&
        post->date.day < today.day) {
      return false;
    }
    return true;
  }
  return false;
}
