#include "aircrafts_array.h"

#include <stdlib.h>
#include <string.h>

#include "aircraft.h"

#define INIT_SIZE 1
#define STEP 2

static aircrafts_array_t *create_array(void);
static return_code_t append(aircrafts_array_t *array, aircraft_t *new_element);
static void shift(aircraft_t **array, size_t start, size_t end);

return_code_t read_array(FILE *input_stream, FILE *output_stream,
                         aircrafts_array_t **aircrafts_array) {
  if (!input_stream || !output_stream || !aircrafts_array) {
    return INCORRECT_ARGS;
  }

  return_code_t rc = OK;

  *aircrafts_array = create_array();
  if (!(*aircrafts_array)) {
    return ALLOCATION_ERROR;
  }

  aircraft_t *aircraft = NULL;
  while (!feof(input_stream)) {
    aircraft = NULL;
    if ((*aircrafts_array)->size != 0) {
      fgetc(input_stream);
    }
    rc = read_aircraft(input_stream, output_stream, &aircraft);
    if (rc != OK) {
      break;
    }
    rc = append(*aircrafts_array, aircraft);
    if (rc != OK) {
      break;
    }
  }

  if ((*aircrafts_array)->size == 0) {
    rc = INPUT_ERROR;
  }

  if (rc != OK) {
    free_aircraft(aircraft);
    free_array(*aircrafts_array);
  }

  return rc;
}

static aircrafts_array_t *create_array(void) {
  aircrafts_array_t *array = malloc(sizeof(aircrafts_array_t));

  if (!array) {
    return NULL;
  }

  array->data = malloc(INIT_SIZE * sizeof(aircraft_t *));
  if (!array->data) {
    free(array);
    return NULL;
  }

  array->size = 0;
  array->capacity = INIT_SIZE;

  return array;
}

static return_code_t append(aircrafts_array_t *array, aircraft_t *new_element) {
  if (!array || !new_element) {
    return INCORRECT_ARGS;
  }

  if (array->size >= array->capacity) {
    aircraft_t **tmp =
        realloc(array->data, array->capacity * sizeof(aircraft_t *) * STEP);
    if (!tmp) {
      return ALLOCATION_ERROR;
    }

    array->data = tmp;
    array->capacity *= STEP;
  }

  array->data[array->size] = new_element;
  ++array->size;

  return OK;
}

void free_array(aircrafts_array_t *array) {
  if (!array) {
    return;
  }

  for (size_t i = 0; i < array->size; ++i) {
    free_aircraft(array->data[i]);
  }
  free(array->data);
  free(array);
}

void print_array(const aircrafts_array_t *array, FILE *output_stream) {
  if (!array || !output_stream) {
    return;
  }

  for (size_t i = 0; i < array->size; ++i) {
    print_aircraft(array->data[i], output_stream);
  }
}

void sort_by_flight_range(aircrafts_array_t *array) {
  if (!array) {
    return;
  }

  for (size_t i = 1; i < array->size; ++i) {
    aircraft_t *cur = array->data[i];
    int j = i - 1;
    for (; j >= 0 && cur->flight_range < array->data[j]->flight_range; --j) {
      array->data[j + 1] = array->data[j];
    }
    array->data[j + 1] = cur;
  }
}

static void shift(aircraft_t **array, size_t start, size_t end) {
  if (!array) {
    return;
  }

  for (size_t i = start; i > end; --i) {
    array[i] = array[i - 1];
  }
}

void group_by_brand(aircrafts_array_t *array) {
  if (!array) {
    return;
  }

  for (size_t i = 0; i < array->size - 1;) {
    size_t count = 0;
    for (size_t j = i + 1; j < array->size; ++j) {
      if (strcmp(array->data[i]->brand, array->data[j]->brand) == 0) {
        ++count;
        if (i + count == j) {
          continue;
        }

        aircraft_t *tmp = array->data[j];
        shift(array->data, j, i + count);
        array->data[i + count] = tmp;
      }
    }
    i += count + 1;
  }
}
