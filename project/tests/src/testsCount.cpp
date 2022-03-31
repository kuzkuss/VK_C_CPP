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
  date_t firstDate = {.day = 2, .month = 3, .year = 2020};

  date_t secondDate = {.day = 2, .month = 3, .year = 2022};

  post_t firstPost = {.id = 1,
                      .votes = 128,
                      .avg_grade = 4.2,
                      .is_correct_avg_grade = true,
                      .last_grade = 3,
                      .date = firstDate};

  post_t secondPost = {.id = 1,
                       .votes = 128,
                       .avg_grade = 3.1,
                       .is_correct_avg_grade = true,
                       .last_grade = 3,
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
  date_t firstDate = {.day = 2, .month = 3, .year = 2022};
  date_t secondDate = {.day = 2, .month = 3, .year = 2022};

  post_t firstPost = {.id = 1,
                      .votes = 128,
                      .avg_grade = 4.2,
                      .is_correct_avg_grade = true,
                      .last_grade = 3,
                      .date = firstDate};

  post_t secondPost = {.id = 1,
                       .votes = 128,
                       .avg_grade = 3.1,
                       .is_correct_avg_grade = true,
                       .last_grade = 3,
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
  date_t firstDate = {.day = 2, .month = 3, .year = 2020};

  date_t secondDate = {.day = 2, .month = 3, .year = 2022};

  post_t firstPost = {.id = 1,
                      .votes = 128,
                      .avg_grade = 4.2,
                      .is_correct_avg_grade = true,
                      .last_grade = 3,
                      .date = firstDate};

  post_t secondPost = {.id = 1,
                       .votes = 128,
                       .avg_grade = 4.3,
                       .is_correct_avg_grade = true,
                       .last_grade = 3,
                       .date = secondDate};

  post_t thirdPost = secondPost;
  post_t fourthPost = secondPost;

  post_t *data[] = {&firstPost, &thirdPost, &secondPost, &fourthPost};

  posts_array_t postsArray = {.data = data, .size = 4, .capacity = 8};

  int result = 0;

  EXPECT_EQ(count_required_posts(&postsArray, &result), OK);
  EXPECT_EQ(result, 3);
}
