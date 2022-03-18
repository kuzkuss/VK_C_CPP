#ifndef PROJECT_AIRCRAFTS_LIB_AIRCRAFT_H_
#define PROJECT_AIRCRAFTS_LIB_AIRCRAFT_H_

#include <stdio.h>

#include "return_codes.h"

typedef struct {
  char *brand;
  char *model;
  char *purpose;
  size_t crew;
  double flight_range;
} aircraft_t;

void free_aircraft(aircraft_t *aircraft);
return_code_t read_aircraft(FILE *input_stream, FILE *output_stream,
                            aircraft_t **p_aircraft);
void print_aircraft(const aircraft_t *aircraft, FILE *output_stream);

#endif  // PROJECT_AIRCRAFTS_LIB_AIRCRAFT_H_
