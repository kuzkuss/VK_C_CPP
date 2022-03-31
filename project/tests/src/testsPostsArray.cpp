#include <gtest/gtest.h>

#define EPS 1e-07

extern "C" {
#include "posts_array.h"
}

TEST(readPostsArray, incorrcectInputStream) {
  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(nullptr, &postsArray), INCORRECT_ARGS);
  EXPECT_EQ(postsArray, nullptr);
}

TEST(readPostsArray, incorrcectArgumentpost) {
  EXPECT_EQ(read_array(stdin, nullptr), INCORRECT_ARGS);
}

TEST(readPostsArray, emptyData) {
  char strPosts[] = "";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, incorrectId) {
  char strPosts[] = "aaa 4.2 128 02.03.2022 5";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, negativeId) {
  char strPosts[] = "-1 4.2 128 02.03.2022 5";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, incorrectAverageGrade) {
  char strPosts[] = "1 aaa 128 02.03.2022 4";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, negativeAverageGrade) {
  char strPosts[] = "1 -3.2 128 02.03.2022 4";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, tooBigAverageGrade) {
  char strPosts[] = "1 6.1 128 02.03.2022 4";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, tooSmallAverageGrade) {
  char strPosts[] = "1 0.2 128 02.03.2022 4";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, incorrectVotes) {
  char strPosts[] = "1 2.3 aaa 02.03.2022 4";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, incorrectDateDay) {
  char strPosts[] = "1 4.2 128 aaa.03.2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, tooSmallDateDay) {
  char strPosts[] = "1 4.2 128 00.03.2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, tooBigDateDay) {
  char strPosts[] = "1 4.2 128 41.03.2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, incorrectDateMonth) {
  char strPosts[] = "1 4.2 128 02.aaa.2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, tooSmallDateMonth) {
  char strPosts[] = "1 4.2 128 02.-2.2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, tooBigDateMonth) {
  char strPosts[] = "1 4.2 128 02.21.2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, incorrectDateYear) {
  char strPosts[] = "1 4.2 128 02.03.aaa 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, incorrectLastGrade) {
  char strPosts[] = "1 4.2 128 02.03.2022 aaa";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, tooSmallLastGrade) {
  char strPosts[] = "1 4.2 128 02.03.2022 -2";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, tooBigLastGrade) {
  char strPosts[] = "1 4.2 128 02.03.2022 10";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, incorrectDateFormat) {
  char strPosts[] = "1 4.2 128 02/03/2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts), "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, &postsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readPostsArray, correctDataOneRecord) {
  char strPosts[] = "1 4.2 128 02.03.2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts) - 1, "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  date_t date = {.day = 2, .month = 3, .year = 2022};

  post_t post = {.id = 1,
                 .votes = 128,
                 .avg_grade = 4.2,
                 .is_correct_avg_grade = true,
                 .last_grade = 3,
                 .date = date};

  post_t *data[] = {&post};

  posts_array_t expectedArray = {.data = data, .size = 1, .capacity = 8};

  EXPECT_EQ(read_array(inputStream, &postsArray), OK);
  ASSERT_NE(postsArray, nullptr);

  EXPECT_EQ(expectedArray.size, postsArray->size);
  EXPECT_EQ(expectedArray.capacity, postsArray->capacity);

  for (size_t i = 0; i < postsArray->size; ++i) {
    EXPECT_EQ(expectedArray.data[i]->id, postsArray->data[i]->id);
    EXPECT_EQ(expectedArray.data[i]->votes, postsArray->data[i]->votes);
    EXPECT_NEAR(expectedArray.data[i]->avg_grade,
                postsArray->data[i]->avg_grade, EPS);
    EXPECT_EQ(expectedArray.data[i]->is_correct_avg_grade,
              postsArray->data[i]->is_correct_avg_grade);
    EXPECT_EQ(expectedArray.data[i]->last_grade,
              postsArray->data[i]->last_grade);
    EXPECT_EQ(expectedArray.data[i]->date.day, postsArray->data[i]->date.day);
    EXPECT_EQ(expectedArray.data[i]->date.month,
              postsArray->data[i]->date.month);
    EXPECT_EQ(expectedArray.data[i]->date.year, postsArray->data[i]->date.year);
  }

  free_array(postsArray);
  fclose(inputStream);
}

TEST(readPostsArray, correctDataOneRecordNoGrades) {
  char strPosts[] = "1 0 0 02.03.2022 1";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts) - 1, "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  date_t date = {.day = 2, .month = 3, .year = 2022};

  post_t post = {.id = 1,
                 .votes = 0,
                 .avg_grade = 0.f,
                 .is_correct_avg_grade = false,
                 .last_grade = 1,
                 .date = date};

  post_t *data[] = {&post};

  posts_array_t expectedArray = {.data = data, .size = 1, .capacity = 8};

  EXPECT_EQ(read_array(inputStream, &postsArray), OK);
  ASSERT_NE(postsArray, nullptr);

  EXPECT_EQ(expectedArray.size, postsArray->size);
  EXPECT_EQ(expectedArray.capacity, postsArray->capacity);

  for (size_t i = 0; i < postsArray->size; ++i) {
    EXPECT_EQ(expectedArray.data[i]->id, postsArray->data[i]->id);
    EXPECT_EQ(expectedArray.data[i]->votes, postsArray->data[i]->votes);
    EXPECT_NEAR(expectedArray.data[i]->avg_grade,
                postsArray->data[i]->avg_grade, EPS);
    EXPECT_EQ(expectedArray.data[i]->is_correct_avg_grade,
              postsArray->data[i]->is_correct_avg_grade);
    EXPECT_EQ(expectedArray.data[i]->last_grade,
              postsArray->data[i]->last_grade);
    EXPECT_EQ(expectedArray.data[i]->date.day, postsArray->data[i]->date.day);
    EXPECT_EQ(expectedArray.data[i]->date.month,
              postsArray->data[i]->date.month);
    EXPECT_EQ(expectedArray.data[i]->date.year, postsArray->data[i]->date.year);
  }

  free_array(postsArray);
  fclose(inputStream);
}

TEST(readPostsArray, correctDataSeveralRecords) {
  char strPosts[] = "1 4.2 128 02.03.2022 3\n1 4.2 128 02.03.2022 3";

  FILE *inputStream = fmemopen(strPosts, sizeof(strPosts) - 1, "r");
  ASSERT_NE(inputStream, nullptr);

  posts_array_t *postsArray = nullptr;

  date_t date = {.day = 2, .month = 3, .year = 2022};

  post_t firstPost = {.id = 1,
                      .votes = 128,
                      .avg_grade = 4.2,
                      .is_correct_avg_grade = true,
                      .last_grade = 3,
                      .date = date};

  post_t secondPost = firstPost;

  post_t *data[] = {&firstPost, &secondPost};

  posts_array_t expectedArray = {.data = data, .size = 2, .capacity = 8};

  EXPECT_EQ(read_array(inputStream, &postsArray), OK);
  ASSERT_NE(postsArray, nullptr);

  EXPECT_EQ(expectedArray.size, postsArray->size);
  EXPECT_EQ(expectedArray.capacity, postsArray->capacity);

  for (size_t i = 0; i < postsArray->size; ++i) {
    EXPECT_EQ(expectedArray.data[i]->id, postsArray->data[i]->id);
    EXPECT_EQ(expectedArray.data[i]->votes, postsArray->data[i]->votes);
    EXPECT_NEAR(expectedArray.data[i]->avg_grade,
                postsArray->data[i]->avg_grade, EPS);
    EXPECT_EQ(expectedArray.data[i]->is_correct_avg_grade,
              postsArray->data[i]->is_correct_avg_grade);
    EXPECT_EQ(expectedArray.data[i]->last_grade,
              postsArray->data[i]->last_grade);
    EXPECT_EQ(expectedArray.data[i]->date.day, postsArray->data[i]->date.day);
    EXPECT_EQ(expectedArray.data[i]->date.month,
              postsArray->data[i]->date.month);
    EXPECT_EQ(expectedArray.data[i]->date.year, postsArray->data[i]->date.year);
  }

  free_array(postsArray);
  fclose(inputStream);
}
