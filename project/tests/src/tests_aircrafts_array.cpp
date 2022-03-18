#include <gtest/gtest.h>

#define EPS 1e-07

extern "C" {
#include "aircrafts_array.h"
}

TEST(readAircraftsArray, incorrcectInputStream) {
  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(nullptr, stdout, &aircraftsArray), INCORRECT_ARGS);
  EXPECT_EQ(aircraftsArray, nullptr);
}

TEST(readAircraftsArray, incorrcectOutputStream) {
  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(stdin, nullptr, &aircraftsArray), INCORRECT_ARGS);
  EXPECT_EQ(aircraftsArray, nullptr);
}

TEST(readAircraftsArray, incorrcectArgumentAircraft) {
  EXPECT_EQ(read_array(stdin, stdout, nullptr), INCORRECT_ARGS);
}

TEST(readAircraftsArray, emptyData) {
  char strAircrafts[] = "";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts), "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readAircraftsArray, incorrectBrand) {
  char strAircrafts[] = "\nModel\nPurpose\n10\n200\n";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts), "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readAircraftsArray, incorrectModel) {
  char strAircrafts[] = "Brand\n\nPurpose\n10\n200";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts), "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readAircraftsArray, incorrectPurpose) {
  char strAircrafts[] = "Brand\nModel\n\n10\n200";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts), "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readAircraftsArray, incorrectCrewSize) {
  char strAircrafts[] = "Brand\nModel\nPurpose\naaa\n200";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts), "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readAircraftsArray, negativeCrewSize) {
  char strAircrafts[] = "Brand\nModel\nPurpose\n-20\n200";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts), "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readAircraftsArray, incorrectFlightRange) {
  char strAircrafts[] = "Brand\nModel\nPurpose\n10\naa";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts), "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readAircraftsArray, negativeFlightRange) {
  char strAircrafts[] = "Brand\nModel\nPurpose\n10\n-100";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts), "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), INPUT_ERROR);

  fclose(inputStream);
}

TEST(readAircraftsArray, correctDataOneRecord) {
  char strAircrafts[] = "Brand\nModel\nPurpose\n10\n2";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts) - 1, "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t aircraft = {.brand = brand,
                         .model = model,
                         .purpose = purpose,
                         .crew = 10,
                         .flight_range = 2};

  aircraft_t *data[] = {&aircraft};

  aircrafts_array_t expectedArray = {.data = data, .size = 1, .capacity = 1};

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), OK);
  EXPECT_NE(aircraftsArray, nullptr);

  EXPECT_EQ(expectedArray.size, aircraftsArray->size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray->capacity);

  for (size_t i = 0; i < aircraftsArray->size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray->data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray->data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray->data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray->data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray->data[i]->flight_range, EPS);
  }

  free_array(aircraftsArray);
  fclose(inputStream);
}

TEST(readAircraftsArray, correctDataSeveralRecords) {
  char strAircrafts[] =
      "Brand\nModel\nPurpose\n10\n200\nBrand\nModel\nPurpose\n10\n200";

  FILE *inputStream = fmemopen(strAircrafts, sizeof(strAircrafts) - 1, "r");
  ASSERT_NE(inputStream, nullptr);

  aircrafts_array_t *aircraftsArray = nullptr;

  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t firstAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 200};

  aircraft_t secondAircraft = firstAircraft;

  aircraft_t *data[] = {&firstAircraft, &secondAircraft};

  aircrafts_array_t expectedArray = {.data = data, .size = 2, .capacity = 2};

  EXPECT_EQ(read_array(inputStream, stdout, &aircraftsArray), OK);
  EXPECT_NE(aircraftsArray, nullptr);

  EXPECT_EQ(expectedArray.size, aircraftsArray->size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray->capacity);

  for (size_t i = 0; i < aircraftsArray->size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray->data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray->data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray->data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray->data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray->data[i]->flight_range, EPS);
  }

  free_array(aircraftsArray);
  fclose(inputStream);
}

TEST(sortByFlightRange, incorrectArg) {
  aircrafts_array_t *aircraftsArray = nullptr;
  sort_by_flight_range(aircraftsArray);

  EXPECT_EQ(aircraftsArray, nullptr);
}

TEST(sortByFlightRange, allValuesEqual) {
  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t firstAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 200};

  aircraft_t secondAircraft = {.brand = brand,
                               .model = model,
                               .purpose = purpose,
                               .crew = 20,
                               .flight_range = 200};

  aircraft_t thirdAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 30,
                              .flight_range = 200};

  aircraft_t *data[] = {&firstAircraft, &secondAircraft, &thirdAircraft};

  aircrafts_array_t aircraftsArray = {.data = data, .size = 3, .capacity = 4};

  aircrafts_array_t expectedArray = {.data = data, .size = 3, .capacity = 4};

  sort_by_flight_range(&aircraftsArray);

  EXPECT_EQ(expectedArray.size, aircraftsArray.size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray.capacity);

  for (size_t i = 0; i < aircraftsArray.size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray.data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray.data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray.data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray.data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray.data[i]->flight_range, EPS);
  }
}

TEST(sortByFlightRange, allValuesDifferent) {
  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t firstAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 200};

  aircraft_t secondAircraft = {.brand = brand,
                               .model = model,
                               .purpose = purpose,
                               .crew = 20,
                               .flight_range = 100};

  aircraft_t thirdAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 30,
                              .flight_range = 300};

  aircraft_t *data[] = {&firstAircraft, &secondAircraft, &thirdAircraft};

  aircrafts_array_t aircraftsArray = {.data = data, .size = 3, .capacity = 4};

  aircraft_t *expectedData[] = {&secondAircraft, &firstAircraft,
                                &thirdAircraft};

  aircrafts_array_t expectedArray = {
      .data = expectedData, .size = 3, .capacity = 4};

  sort_by_flight_range(&aircraftsArray);

  EXPECT_EQ(expectedArray.size, aircraftsArray.size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray.capacity);

  for (size_t i = 0; i < aircraftsArray.size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray.data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray.data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray.data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray.data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray.data[i]->flight_range, EPS);
  }
}

TEST(sortByFlightRange, severalValuesEqual) {
  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t firstAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 200};

  aircraft_t secondAircraft = {.brand = brand,
                               .model = model,
                               .purpose = purpose,
                               .crew = 20,
                               .flight_range = 200};

  aircraft_t thirdAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 30,
                              .flight_range = 300};

  aircraft_t fourthAircraft = {.brand = brand,
                               .model = model,
                               .purpose = purpose,
                               .crew = 30,
                               .flight_range = 100};

  aircraft_t *data[] = {&firstAircraft, &secondAircraft, &thirdAircraft,
                        &fourthAircraft};

  aircrafts_array_t aircraftsArray = {.data = data, .size = 4, .capacity = 4};

  aircraft_t *expectedData[] = {&fourthAircraft, &firstAircraft,
                                &secondAircraft, &thirdAircraft};

  aircrafts_array_t expectedArray = {
      .data = expectedData, .size = 4, .capacity = 4};

  sort_by_flight_range(&aircraftsArray);

  EXPECT_EQ(expectedArray.size, aircraftsArray.size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray.capacity);

  for (size_t i = 0; i < aircraftsArray.size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray.data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray.data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray.data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray.data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray.data[i]->flight_range, EPS);
  }
}

TEST(sortByFlightRange, valuesSortedInDescending) {
  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t firstAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 300};

  aircraft_t secondAircraft = {.brand = brand,
                               .model = model,
                               .purpose = purpose,
                               .crew = 20,
                               .flight_range = 200};

  aircraft_t thirdAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 30,
                              .flight_range = 100};

  aircraft_t *data[] = {&firstAircraft, &secondAircraft, &thirdAircraft};

  aircrafts_array_t aircraftsArray = {.data = data, .size = 3, .capacity = 4};

  aircraft_t *expectedData[] = {&thirdAircraft, &secondAircraft,
                                &firstAircraft};

  aircrafts_array_t expectedArray = {
      .data = expectedData, .size = 3, .capacity = 4};

  sort_by_flight_range(&aircraftsArray);

  EXPECT_EQ(expectedArray.size, aircraftsArray.size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray.capacity);

  for (size_t i = 0; i < aircraftsArray.size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray.data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray.data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray.data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray.data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray.data[i]->flight_range, EPS);
  }
}

TEST(sortByFlightRange, allValuesDouble) {
  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t firstAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 128.2};

  aircraft_t secondAircraft = {.brand = brand,
                               .model = model,
                               .purpose = purpose,
                               .crew = 20,
                               .flight_range = 101.1};

  aircraft_t thirdAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 30,
                              .flight_range = 203.778};

  aircraft_t *data[] = {&firstAircraft, &secondAircraft, &thirdAircraft};

  aircrafts_array_t aircraftsArray = {.data = data, .size = 3, .capacity = 4};

  aircraft_t *expectedData[] = {&secondAircraft, &firstAircraft,
                                &thirdAircraft};

  aircrafts_array_t expectedArray = {
      .data = expectedData, .size = 3, .capacity = 4};

  sort_by_flight_range(&aircraftsArray);

  EXPECT_EQ(expectedArray.size, aircraftsArray.size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray.capacity);

  for (size_t i = 0; i < aircraftsArray.size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray.data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray.data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray.data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray.data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray.data[i]->flight_range, EPS);
  }
}

TEST(groupByBrand, incorrectArg) {
  aircrafts_array_t *aircraftsArray = nullptr;
  group_by_brand(aircraftsArray);

  EXPECT_EQ(aircraftsArray, nullptr);
}

TEST(groupByBrand, allBrandsEqual) {
  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t firstAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 300};

  aircraft_t secondAircraft = {.brand = brand,
                               .model = model,
                               .purpose = purpose,
                               .crew = 20,
                               .flight_range = 200};

  aircraft_t thirdAircraft = {.brand = brand,
                              .model = model,
                              .purpose = purpose,
                              .crew = 30,
                              .flight_range = 100};

  aircraft_t *data[] = {&firstAircraft, &secondAircraft, &thirdAircraft};

  aircrafts_array_t aircraftsArray = {.data = data, .size = 3, .capacity = 4};

  aircrafts_array_t expectedArray = {.data = data, .size = 3, .capacity = 4};

  group_by_brand(&aircraftsArray);

  EXPECT_EQ(expectedArray.size, aircraftsArray.size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray.capacity);

  for (size_t i = 0; i < aircraftsArray.size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray.data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray.data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray.data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray.data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray.data[i]->flight_range, EPS);
  }
}

TEST(groupByBrand, brandsInOrder) {
  char brand1[] = "Brand1\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  char brand2[] = "Brand2\n";

  aircraft_t firstAircraft = {.brand = brand1,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 300};

  aircraft_t secondAircraft = {.brand = brand1,
                               .model = model,
                               .purpose = purpose,
                               .crew = 20,
                               .flight_range = 200};

  aircraft_t thirdAircraft = {.brand = brand2,
                              .model = model,
                              .purpose = purpose,
                              .crew = 30,
                              .flight_range = 100};

  aircraft_t fourthAircraft = {.brand = brand2,
                               .model = model,
                               .purpose = purpose,
                               .crew = 30,
                               .flight_range = 100};

  aircraft_t *data[] = {&firstAircraft, &secondAircraft, &thirdAircraft,
                        &fourthAircraft};

  aircrafts_array_t aircraftsArray = {.data = data, .size = 4, .capacity = 4};

  aircrafts_array_t expectedArray = {.data = data, .size = 4, .capacity = 4};

  group_by_brand(&aircraftsArray);

  EXPECT_EQ(expectedArray.size, aircraftsArray.size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray.capacity);

  for (size_t i = 0; i < aircraftsArray.size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray.data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray.data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray.data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray.data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray.data[i]->flight_range, EPS);
  }
}

TEST(groupByBrand, brandsMixed) {
  char brand1[] = "Brand1\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  char brand2[] = "Brand2\n";

  aircraft_t firstAircraft = {.brand = brand1,
                              .model = model,
                              .purpose = purpose,
                              .crew = 10,
                              .flight_range = 300};

  aircraft_t secondAircraft = {.brand = brand2,
                               .model = model,
                               .purpose = purpose,
                               .crew = 20,
                               .flight_range = 200};

  aircraft_t thirdAircraft = {.brand = brand1,
                              .model = model,
                              .purpose = purpose,
                              .crew = 30,
                              .flight_range = 100};

  aircraft_t fourthAircraft = {.brand = brand2,
                               .model = model,
                               .purpose = purpose,
                               .crew = 30,
                               .flight_range = 100};

  aircraft_t *data[] = {&firstAircraft, &thirdAircraft, &secondAircraft,
                        &fourthAircraft};

  aircrafts_array_t aircraftsArray = {.data = data, .size = 4, .capacity = 4};

  aircrafts_array_t expectedArray = {.data = data, .size = 4, .capacity = 4};

  group_by_brand(&aircraftsArray);

  EXPECT_EQ(expectedArray.size, aircraftsArray.size);
  EXPECT_EQ(expectedArray.capacity, aircraftsArray.capacity);

  for (size_t i = 0; i < aircraftsArray.size; ++i) {
    EXPECT_STREQ(expectedArray.data[i]->brand, aircraftsArray.data[i]->brand);
    EXPECT_STREQ(expectedArray.data[i]->model, aircraftsArray.data[i]->model);
    EXPECT_STREQ(expectedArray.data[i]->purpose,
                 aircraftsArray.data[i]->purpose);
    EXPECT_EQ(expectedArray.data[i]->crew, aircraftsArray.data[i]->crew);
    EXPECT_NEAR(expectedArray.data[i]->flight_range,
                aircraftsArray.data[i]->flight_range, EPS);
  }
}
