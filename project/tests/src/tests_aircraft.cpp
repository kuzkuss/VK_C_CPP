#include <gtest/gtest.h>

#define EPS 1e-07

extern "C" {
#include "aircraft.h"
}

TEST(readAircraft, incorrcectInputStream) {
  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(nullptr, stdout, &aircraft), INCORRECT_ARGS);
  EXPECT_EQ(aircraft, nullptr);
}

TEST(readAircraft, incorrcectOutputStream) {
  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(stdin, nullptr, &aircraft), INCORRECT_ARGS);
  EXPECT_EQ(aircraft, nullptr);
}

TEST(readAircraft, incorrcectArgumentAircraft) {
  EXPECT_EQ(read_aircraft(stdin, stdout, nullptr), INCORRECT_ARGS);
}

TEST(readAircraft, incorrectBrand) {
  char strAircraft[] = "\nModel\nPurpose\n10\n200";

  FILE *inputStream = fmemopen(strAircraft, sizeof(strAircraft), "r");
  ASSERT_NE(inputStream, nullptr);

  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(inputStream, stdout, &aircraft), INPUT_ERROR);
  EXPECT_EQ(aircraft, nullptr);

  fclose(inputStream);
}

TEST(readAircraft, incorrectModel) {
  char strAircraft[] = "Brand\n\nPurpose\n10\n200";

  FILE *inputStream = fmemopen(strAircraft, sizeof(strAircraft), "r");
  ASSERT_NE(inputStream, nullptr);

  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(inputStream, stdout, &aircraft), INPUT_ERROR);
  EXPECT_EQ(aircraft, nullptr);

  fclose(inputStream);
}

TEST(readAircraft, incorrectPurpose) {
  char strAircraft[] = "Brand\nModel\n\n10\n200";

  FILE *inputStream = fmemopen(strAircraft, sizeof(strAircraft), "r");
  ASSERT_NE(inputStream, nullptr);

  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(inputStream, stdout, &aircraft), INPUT_ERROR);
  EXPECT_EQ(aircraft, nullptr);

  fclose(inputStream);
}

TEST(readAircraft, incorrectCrewSize) {
  char strAircraft[] = "Brand\nModel\nPurpose\naaa\n200";

  FILE *inputStream = fmemopen(strAircraft, sizeof(strAircraft), "r");
  ASSERT_NE(inputStream, nullptr);

  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(inputStream, stdout, &aircraft), INPUT_ERROR);
  EXPECT_EQ(aircraft, nullptr);

  fclose(inputStream);
}

TEST(readAircraft, negativeCrewSize) {
  char strAircraft[] = "Brand\nModel\nPurpose\n-20\n200";

  FILE *inputStream = fmemopen(strAircraft, sizeof(strAircraft), "r");
  ASSERT_NE(inputStream, nullptr);

  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(inputStream, stdout, &aircraft), INPUT_ERROR);
  EXPECT_EQ(aircraft, nullptr);

  fclose(inputStream);
}

TEST(readAircraft, incorrectFlightRange) {
  char strAircraft[] = "Brand\nModel\nPurpose\n10\naa";

  FILE *inputStream = fmemopen(strAircraft, sizeof(strAircraft), "r");
  ASSERT_NE(inputStream, nullptr);

  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(inputStream, stdout, &aircraft), INPUT_ERROR);
  EXPECT_EQ(aircraft, nullptr);

  fclose(inputStream);
}

TEST(readAircraft, negativeFlightRange) {
  char strAircraft[] = "Brand\nModel\nPurpose\n10\n-100";

  FILE *inputStream = fmemopen(strAircraft, sizeof(strAircraft), "r");
  ASSERT_NE(inputStream, nullptr);

  aircraft_t *aircraft = nullptr;

  EXPECT_EQ(read_aircraft(inputStream, stdout, &aircraft), INPUT_ERROR);
  EXPECT_EQ(aircraft, nullptr);

  fclose(inputStream);
}

TEST(readAircraft, correctData) {
  char strAircraft[] = "Brand\nModel\nPurpose\n10\n2";

  FILE *inputStream = fmemopen(strAircraft, sizeof(strAircraft) - 1, "r");
  ASSERT_NE(inputStream, nullptr);

  aircraft_t *aircraft = nullptr;

  char brand[] = "Brand\n";
  char model[] = "Model\n";
  char purpose[] = "Purpose\n";

  aircraft_t expectedAircraft = {.brand = brand,
                                 .model = model,
                                 .purpose = purpose,
                                 .crew = 10,
                                 .flight_range = 2};

  EXPECT_EQ(read_aircraft(inputStream, stdout, &aircraft), OK);
  EXPECT_NE(aircraft, nullptr);

  EXPECT_STREQ(expectedAircraft.brand, aircraft->brand);
  EXPECT_STREQ(expectedAircraft.model, aircraft->model);
  EXPECT_STREQ(expectedAircraft.purpose, aircraft->purpose);
  EXPECT_EQ(expectedAircraft.crew, aircraft->crew);
  EXPECT_NEAR(expectedAircraft.flight_range, aircraft->flight_range, EPS);

  free_aircraft(aircraft);

  fclose(inputStream);
}
