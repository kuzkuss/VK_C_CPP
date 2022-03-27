#include "utils.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  return_code_t rc = posts_process(argc, argv);
  if (rc != OK) {
    check_error(rc);
  }
  return rc;
}

