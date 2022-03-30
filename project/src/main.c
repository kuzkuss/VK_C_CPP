#include "utils.h"

int main(int argc, char *argv[]) {
  return_code_t rc = run_process(argc, argv);
  if (rc != OK) {
    check_error(rc);
  }
  return rc;
}
