#include <gtest/gtest.h>
#include <stdbool.h>

#define EPS 1e-07

extern "C" {
#include "post.h"
}

TEST(readPost, incorrcectInputStream) {
  post_t *post = nullptr;

  EXPECT_EQ(read_post(nullptr, &post), INCORRECT_ARGS);
  EXPECT_EQ(post, nullptr);
}

TEST(readPost, incorrcectArgumentPost) {
  EXPECT_EQ(read_post(stdin, nullptr), INCORRECT_ARGS);
}

TEST(readPost, incorrectId) {
  char strPost[] = "aaa 4.2 128 02.03.2022 5";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, negativeId) {
  char strPost[] = "-1 4.2 128 02.03.2022 5";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, incorrectAverageGrade) {
  char strPost[] = "1 aaa 128 02.03.2022 4";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, negativeAverageGrade) {
  char strPost[] = "1 -3.2 128 02.03.2022 4";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, tooBigAverageGrade) {
  char strPost[] = "1 6.1 128 02.03.2022 4";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, tooSmallAverageGrade) {
  char strPost[] = "1 0.2 128 02.03.2022 4";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, incorrectVotes) {
  char strPost[] = "1 2.3 aaa 02.03.2022 4";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, negativeVotes) {
  char strPost[] = "1 2.3 -2 02.03.2022 4";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, incorrectDateDay) {
  char strPost[] = "1 4.2 128 aaa.03.2022 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, tooSmallDateDay) {
  char strPost[] = "1 4.2 128 00.03.2022 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, tooBigDateDay) {
  char strPost[] = "1 4.2 128 41.03.2022 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, incorrectDateMonth) {
  char strPost[] = "1 4.2 128 02.aaa.2022 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, tooSmallDateMonth) {
  char strPost[] = "1 4.2 128 02.-2.2022 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, tooBigDateMonth) {
  char strPost[] = "1 4.2 128 02.21.2022 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, incorrectDateYear) {
  char strPost[] = "1 4.2 128 02.03.aaa 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, incorrectLastGrade) {
  char strPost[] = "1 4.2 128 02.03.2022 aaa";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, tooSmallLastGrade) {
  char strPost[] = "1 4.2 128 02.03.2022 -2";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, tooBigLastGrade) {
  char strPost[] = "1 4.2 128 02.03.2022 10";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, incorrectDateFormat) {
  char strPost[] = "1 4.2 128 02/03/2022 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost), "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  EXPECT_EQ(read_post(inputStream, &post), INPUT_ERROR);
  EXPECT_EQ(post, nullptr);

  fclose(inputStream);
}

TEST(readPost, correctData) {
  char strPost[] = "1 4.2 128 02.03.2022 3";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost) - 1, "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  date_t date = {.day = 2, .month = 3, .year = 2022};

  post_t expectedPost = {.id = 1,
                         .votes = 128,
                         .avg_grade = 4.2,
                         .is_correct_avg_grade = true,
                         .last_grade = 3,
                         .date = date};

  EXPECT_EQ(read_post(inputStream, &post), OK);
  ASSERT_NE(post, nullptr);

  EXPECT_EQ(expectedPost.id, post->id);
  EXPECT_EQ(expectedPost.votes, post->votes);
  EXPECT_NEAR(expectedPost.avg_grade, post->avg_grade, EPS);
  EXPECT_EQ(expectedPost.is_correct_avg_grade, post->is_correct_avg_grade);
  EXPECT_EQ(expectedPost.last_grade, post->last_grade);
  EXPECT_EQ(expectedPost.date.day, post->date.day);
  EXPECT_EQ(expectedPost.date.month, post->date.month);
  EXPECT_EQ(expectedPost.date.year, post->date.year);

  free(post);

  fclose(inputStream);
}

TEST(readPost, correctDataNoGrades) {
  char strPost[] = "1 0 0 02.03.2022 1";

  FILE *inputStream = fmemopen(strPost, sizeof(strPost) - 1, "r");
  ASSERT_NE(inputStream, nullptr);

  post_t *post = nullptr;

  date_t date = {.day = 2, .month = 3, .year = 2022};

  post_t expectedPost = {.id = 1,
                         .votes = 0,
                         .avg_grade = 0.f,
                         .is_correct_avg_grade = false,
                         .last_grade = 1,
                         .date = date};

  EXPECT_EQ(read_post(inputStream, &post), OK);
  ASSERT_NE(post, nullptr);

  EXPECT_EQ(expectedPost.id, post->id);
  EXPECT_EQ(expectedPost.votes, post->votes);
  EXPECT_NEAR(expectedPost.avg_grade, post->avg_grade, EPS);
  EXPECT_EQ(expectedPost.is_correct_avg_grade, post->is_correct_avg_grade);
  EXPECT_EQ(expectedPost.last_grade, post->last_grade);
  EXPECT_EQ(expectedPost.date.day, post->date.day);
  EXPECT_EQ(expectedPost.date.month, post->date.month);
  EXPECT_EQ(expectedPost.date.year, post->date.year);

  free(post);

  fclose(inputStream);
}

TEST(checkPost, validOnlyAvgGradeDiffYears) {
  date_t date = {.day = 17, .month = 6, .year = 2021};

  post_t post = {.id = 1,
                 .votes = 27,
                 .avg_grade = 4.5,
                 .is_correct_avg_grade = true,
                 .last_grade = 5,
                 .date = date};

  EXPECT_EQ(check_post(&post), false);
}

TEST(checkPost, validOnlyDateCorrectAvg) {
  date_t date = {.day = 2, .month = 2, .year = 2022};

  post_t post = {.id = 1,
                 .votes = 27,
                 .avg_grade = 3.1,
                 .is_correct_avg_grade = true,
                 .last_grade = 5,
                 .date = date};

  EXPECT_EQ(check_post(&post), false);
}

TEST(checkPost, validOnlyDateZeroAvg) {
  date_t date = {.day = 2, .month = 2, .year = 2022};

  post_t post = {.id = 1,
                 .votes = 0,
                 .avg_grade = 0.f,
                 .is_correct_avg_grade = false,
                 .last_grade = 1,
                 .date = date};

  EXPECT_EQ(check_post(&post), false);
}

TEST(checkPost, invalidDateAndAvgGrade) {
  date_t date = {.day = 17, .month = 6, .year = 2020};

  post_t post = {.id = 1,
                 .votes = 0,
                 .avg_grade = 0.f,
                 .is_correct_avg_grade = false,
                 .last_grade = 1,
                 .date = date};

  EXPECT_EQ(check_post(&post), false);
}

TEST(checkPost, validAvgGradeAndDateEqualYears) {
  date_t date = {.day = 2, .month = 2, .year = 2022};

  post_t post = {.id = 1,
                 .votes = 27,
                 .avg_grade = 4.0,
                 .is_correct_avg_grade = true,
                 .last_grade = 5,
                 .date = date};

  EXPECT_EQ(check_post(&post), true);
}

TEST(checkPost, validAvgGradeAndDateDiffYears) {
  date_t date = {.day = 31, .month = 12, .year = 2021};

  post_t post = {.id = 1,
                 .votes = 27,
                 .avg_grade = 4.5,
                 .is_correct_avg_grade = true,
                 .last_grade = 5,
                 .date = date};

  EXPECT_EQ(check_post(&post), true);
}
