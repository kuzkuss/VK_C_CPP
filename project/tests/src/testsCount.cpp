#include <gtest/gtest.h>

extern "C" {
#include "post_count.h"
}

TEST(countRequiredPosts, incorrectPointerArray) {
  int result = 0;
  EXPECT_EQ(count_required_posts(nullptr, &result), INCORRECT_ARGS);
}

TEST(countRequiredPosts, incorrectPointerResult) {
  posts_array_t postsArray = {0};
  EXPECT_EQ(count_required_posts(&postsArray, nullptr), INCORRECT_ARGS);
}

TEST(countRequiredPosts, noRequiredPosts) {
  avg_grade_t firstAvgGrade = {.kind_avg_grade = CORRECT_AVG_GRADE,
                               .average_grade = 4.2};

  date_t firstDate = {.day = 2, .month = 3, .year = 2020};

  avg_grade_t secondAvgGrade = {.kind_avg_grade = CORRECT_AVG_GRADE,
                                .average_grade = 3.1};

  date_t secondDate = {.day = 2, .month = 3, .year = 2022};

  post_t firstPost = {.votes = 128,
                      .avg_grade = firstAvgGrade,
                      .last_grade = 3,
                      .id = 1,
                      .date = firstDate};

  post_t secondPost = {.votes = 128,
                       .avg_grade = secondAvgGrade,
                       .last_grade = 3,
                       .id = 1,
                       .date = secondDate};

  post_t thirdPost = firstPost;
  post_t fourthPost = secondPost;

  post_t *data[] = {&firstPost, &thirdPost, &secondPost, &fourthPost};

  posts_array_t postsArray = {.data = data, .size = 4, .capacity = 8};

  int result = 0;

  EXPECT_EQ(count_required_posts(&postsArray, &result), OK);
  EXPECT_EQ(result, 0);
}

TEST(countRequiredPosts, oneRequiredPost) {
  avg_grade_t firstAvgGrade = {.kind_avg_grade = CORRECT_AVG_GRADE,
                               .average_grade = 4.2};

  date_t firstDate = {.day = 2, .month = 3, .year = 2022};

  avg_grade_t secondAvgGrade = {.kind_avg_grade = CORRECT_AVG_GRADE,
                                .average_grade = 3.1};

  date_t secondDate = {.day = 2, .month = 3, .year = 2022};

  post_t firstPost = {.votes = 128,
                      .avg_grade = firstAvgGrade,
                      .last_grade = 3,
                      .id = 1,
                      .date = firstDate};

  post_t secondPost = {.votes = 128,
                       .avg_grade = secondAvgGrade,
                       .last_grade = 3,
                       .id = 1,
                       .date = secondDate};

  post_t thirdPost = secondPost;
  post_t fourthPost = secondPost;

  post_t *data[] = {&firstPost, &thirdPost, &secondPost, &fourthPost};

  posts_array_t postsArray = {.data = data, .size = 4, .capacity = 8};

  int result = 0;

  EXPECT_EQ(count_required_posts(&postsArray, &result), OK);
  EXPECT_EQ(result, 1);
}

TEST(countRequiredPosts, severalRequiredPosts) {
  avg_grade_t firstAvgGrade = {.kind_avg_grade = CORRECT_AVG_GRADE,
                               .average_grade = 4.2};

  date_t firstDate = {.day = 2, .month = 3, .year = 2020};

  avg_grade_t secondAvgGrade = {.kind_avg_grade = CORRECT_AVG_GRADE,
                                .average_grade = 4.3};

  date_t secondDate = {.day = 2, .month = 3, .year = 2022};

  post_t firstPost = {.votes = 128,
                      .avg_grade = firstAvgGrade,
                      .last_grade = 3,
                      .id = 1,
                      .date = firstDate};

  post_t secondPost = {.votes = 128,
                       .avg_grade = secondAvgGrade,
                       .last_grade = 3,
                       .id = 1,
                       .date = secondDate};

  post_t thirdPost = secondPost;
  post_t fourthPost = secondPost;

  post_t *data[] = {&firstPost, &thirdPost, &secondPost, &fourthPost};

  posts_array_t postsArray = {.data = data, .size = 4, .capacity = 8};

  int result = 0;

  EXPECT_EQ(count_required_posts(&postsArray, &result), OK);
  EXPECT_EQ(result, 3);
}
