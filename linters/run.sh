#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cppcheck"
check_log "cppcheck ../project --enable=all --inconclusive --error-exitcode=1 -I ../project/posts_lib/inc -I ../project/inc --suppress=missingIncludeSystem --suppress=unmatchedSuppression" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy ../project/posts_lib/src/*.c ../project/src/*.c ../project/inc/*.h ../project/posts_lib/inc/*.h -warnings-as-errors=* -extra-arg=-std=c99 -- -I../project/inc -I../project/posts_lib/inc" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint ../project/posts_lib/src/*.c ../project/src/*.c ../project/inc/*.h ../project/posts_lib/inc/*.h ../project/tests/src/*.cpp ../project/tests/*.cpp" "Can't open for reading"

print_header "RUN clang-format"
check_log "clang-format ../project/posts_lib/src/*.c ../project/src/*.c ../project/inc/*.h ../project/posts_lib/inc/*.h ../project/tests/src/*.cpp ../project/tests/*.cpp -dry-run -Werror -style=Google" "Error (?:reading|while processing)"

print_header "SUCCESS"
