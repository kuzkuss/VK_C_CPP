#ifndef PROJECT_INC_UTILS_H_
#define PROJECT_INC_UTILS_H_

#include "return_codes.h"

return_code_t run_process(int argc, char *argv[]);
return_code_t posts_process(const char *filename, int *res);
return_code_t parse_args(int argc, char *argv[], char **filename);

#endif  // PROJECT_INC_UTILS_H_
