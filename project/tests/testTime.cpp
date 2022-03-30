#include <iostream>
#include <chrono>

extern "C" {
#include "utils.h"
#include "post_count.h"
}

#define ERROR_TIME_MSG "Error during time measurement.\n"
#define REPEATS 100

return_code_t time_measure(int argc, char *argv[]) {
    if (!(*argv)) {
        return INCORRECT_ARGS;
    }

    char *filename = NULL;
    return_code_t rc = parse_args(argc, argv, &filename);
    if (rc == CALL_HELP) {
        return OK;
    }

    if (rc != OK) {
        return rc;
    }

    size_t sum_duraction = 0;
    rc = OK;
    for (size_t i = 0; i < REPEATS; ++i) {
        int res = 0;
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        rc = posts_process(filename, &res);
        sum_duraction += std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::high_resolution_clock::now() - start).count();

        if (rc != OK) {
            break;
        }
    }
    if (rc != OK) {
        return rc;
    }

    std::cout << "Average time of work is: " << sum_duraction / float(REPEATS) << "ms\n";

    free(filename);
    return OK;
}

int main(int argc, char *argv[]) {
    return_code_t rc = time_measure(argc, argv);
    if (rc != OK) {
        printf("%s", ERROR_TIME_MSG);
    }
    return rc;
}