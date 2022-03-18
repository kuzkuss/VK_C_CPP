#include "aircrafts_array.h"
#include "return_codes.h"

#define INPUT_PROMPT "Enter information about aircrafts. " \
                      "The end of the input is the key combination CTRL+D.\n\n" \
                      "Input format:\nbrand\nmodel\npurpose\ncrew size\nflight range\n\n"

static return_code_t aircrafts_process(void);

int main(void) { return aircrafts_process(); }

static return_code_t aircrafts_process(void) {
  aircrafts_array_t *aircrafts_array = NULL;
  printf("%s", INPUT_PROMPT);
  return_code_t rc = read_array(stdin, stdout, &aircrafts_array);
  if (rc != OK) {
    return rc;
  }

  sort_by_flight_range(aircrafts_array);
  group_by_brand(aircrafts_array);
  print_array(aircrafts_array, stdout);
  free_array(aircrafts_array);

  return OK;
}
