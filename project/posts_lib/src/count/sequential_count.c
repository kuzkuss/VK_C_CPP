#include <stdbool.h>
#include <time.h>

#include "posts_array.h"

#define REQUIRED_BOUND 4.0
#define QUARTER 3
#define MONTHS 12
#define MAX_DIFF_YEARS 1

#define START_OF_MONTHS 1
#define START_OF_YEARS 1900

static bool check_grade(const post_t *post);
static date_t get_current_date(void);
static bool check_date(const post_t *post);

int count_required_posts(posts_array_t *posts_array) {
    int counter = 0;
    for (size_t i = 0; i < posts_array->size; ++i) {
        if (check_grade(posts_array->data[i]) && check_date(posts_array->data[i])) {
            ++counter;
        }
    }
    return counter;
}

static bool check_grade(const post_t *post) {
    return post->avg_grade.kind_avg_grade == CORRECT_AVG_GRADE && !(post->avg_grade.average_grade < REQUIRED_BOUND);
}

static date_t get_current_date(void) {
    time_t cur_time = time(NULL);
    struct tm *cur_date = localtime(&cur_time);
    date_t date = { 0 };
    date.day = cur_date->tm_mday;
    date.month = cur_date->tm_mon + START_OF_MONTHS;
    date.year = cur_date->tm_year + START_OF_YEARS;
    return date;
}

static bool check_date(const post_t *post) {
    date_t today = get_current_date();
    if (post->date.year == today.year && (today.month - post->date.month <= QUARTER)) {
        if (today.month - post->date.month == QUARTER && post->date.day < today.day) {
            return false;
        }
        return true;
    }
    if (today.year - post->date.year == MAX_DIFF_YEARS && (today.month + MONTHS - post->date.month <= QUARTER)) {
        if (today.month + MONTHS - post->date.month == QUARTER && post->date.day < today.day) {
            return false;
        }
        return true;
    }
    return false;
}

