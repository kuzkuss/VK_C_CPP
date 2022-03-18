#define _GNU_SOURCE

#include "aircraft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "return_codes.h"

#define GETLINE_ERROR -1
#define EPS 1e-07

#define EOL_N '\n'
#define EOL_R '\r'

static aircraft_t *create_aircraft(char *brand, char *model, char *purpose,
                                   int crew, double flight_range);

return_code_t read_aircraft(FILE *input_stream, FILE *output_stream,
                            aircraft_t **p_aircraft) {
  if (!input_stream || !output_stream || !p_aircraft) {
    return INCORRECT_ARGS;
  }

  char *brand = NULL;
  char *model = NULL;
  char *purpose = NULL;
  int crew = 0;
  double flight_range = 0.0;

  size_t n = 0;
  if (getline(&brand, &n, input_stream) == GETLINE_ERROR || brand[0] == EOL_N ||
      brand[0] == EOL_R) {
    free(brand);
    return INPUT_ERROR;
  }

  n = 0;
  if (getline(&model, &n, input_stream) == GETLINE_ERROR || model[0] == EOL_N ||
      model[0] == EOL_R) {
    free(brand);
    free(model);
    return INPUT_ERROR;
  }

  n = 0;
  if (getline(&purpose, &n, input_stream) == GETLINE_ERROR ||
      purpose[0] == EOL_N || purpose[0] == EOL_R) {
    free(brand);
    free(model);
    free(purpose);
    return INPUT_ERROR;
  }

  return_code_t rc = OK;
  if (fscanf(input_stream, "%d", &crew) == 1 && crew > 0) {

    if (fscanf(input_stream, "%lf", &flight_range) == 1 && flight_range > 0.0) {
      *p_aircraft = create_aircraft(brand, model, purpose, crew, flight_range);
      if (!(*p_aircraft)) {
        rc = ALLOCATION_ERROR;
      }
    } else {
      rc = INPUT_ERROR;
    }
  } else {
    rc = INPUT_ERROR;
  }

  if (rc != OK) {
    free(brand);
    free(model);
    free(purpose);
  }

  return rc;
}

static aircraft_t *create_aircraft(char *brand, char *model, char *purpose,
                                   int crew, double flight_range) {
  if (!brand || !model || !purpose || crew <= 0 || flight_range <= EPS) {
    return NULL;
  }

  aircraft_t *aircraft = malloc(sizeof(aircraft_t));
  if (aircraft) {
    aircraft->brand = brand;
    aircraft->model = model;
    aircraft->purpose = purpose;
    aircraft->crew = crew;
    aircraft->flight_range = flight_range;
  }

  return aircraft;
}

void free_aircraft(aircraft_t *aircraft) {
  if (!aircraft) {
    return;
  }
  free(aircraft->brand);
  free(aircraft->model);
  free(aircraft->purpose);
  free(aircraft);
}

void print_aircraft(const aircraft_t *aircraft, FILE *output_stream) {
  if (!aircraft || !output_stream || !aircraft->brand || !aircraft->model ||
      !aircraft->purpose) {
    return;
  }

  fprintf(output_stream, "\nBrand: %s", aircraft->brand);
  fprintf(output_stream, "Model: %s", aircraft->model);
  fprintf(output_stream, "Purpose: %s", aircraft->purpose);
  fprintf(output_stream, "Crew size: %zu\n", aircraft->crew);
  fprintf(output_stream, "Flight range: %lf\n", aircraft->flight_range);
}
