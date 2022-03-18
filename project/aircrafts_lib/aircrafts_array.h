#ifndef TP_C_CPP_PROJECT_AIRCRAFTS_LIB_AIRCRAFTS_ARRAY_H_
#define TP_C_CPP_PROJECT_AIRCRAFTS_LIB_AIRCRAFTS_ARRAY_H_

#include "aircraft.h"

typedef struct {
  aircraft_t **data;
  size_t size;
  size_t capacity;
} aircrafts_array_t;

return_code_t read_array(FILE *input_stream, FILE *output_stream,
                         aircrafts_array_t **aircrafts_array);
void free_array(aircrafts_array_t *array);
void print_array(const aircrafts_array_t *array, FILE *output_stream);
void sort_by_flight_range(aircrafts_array_t *array);
void group_by_brand(aircrafts_array_t *array);

#endif  // TP_C_CPP_PROJECT_AIRCRAFTS_LIB_AIRCRAFTS_ARRAY_H_
