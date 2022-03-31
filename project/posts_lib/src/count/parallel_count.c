#define _GNU_SOURCE

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include "post_count.h"

#define SYSCONF_ERROR -1
#define WAITPID_ERROR -1
#define KILL_ERROR -1
#define FORK_ERROR -1

#define CHILD 0

static void kill_processes(size_t num_processes, const pid_t *processes);

static return_code_t exit_processes(size_t num_processes,
                                    const pid_t *processes);

static return_code_t create_processes_array(long *num_processes,
                                            pid_t **processes,
                                            size_t size_array);

static int *get_shared_memory(void);

static return_code_t cur_count_posts(size_t start, size_t offset,
                                     post_t **const posts_array,
                                     int *shared_res);

static return_code_t generate_processes(const posts_array_t *posts_array,
                                        int *shared_res, size_t num_processes,
                                        pid_t *processes);

return_code_t count_required_posts(posts_array_t *posts_array,
                                   int *number_req_posts) {
  if (!posts_array || !number_req_posts) {
    return INCORRECT_ARGS;
  }

  long num_processes = 0;
  pid_t *processes = NULL;
  return_code_t rc =
      create_processes_array(&num_processes, &processes, posts_array->size);
  if (rc != OK) {
    return rc;
  }

  int *shared_result = get_shared_memory();
  if (!shared_result) {
    free(processes);
    return PARALLEL_ERROR;
  }

  *shared_result = 0;

  rc = generate_processes(posts_array, shared_result, num_processes, processes);
  if (rc != OK) {
    free(processes);
    return rc;
  }

  rc = exit_processes(num_processes, processes);
  if (rc != OK) {
    free(processes);
    return rc;
  }

  free(processes);

  *number_req_posts = *shared_result;

  if (munmap(shared_result, sizeof(int)) != OK) {
    return PARALLEL_ERROR;
  }

  return rc;
}

static void kill_processes(size_t num_processes, const pid_t *processes) {
  if (!processes) {
    return;
  }

  for (size_t i = 0; i < num_processes; ++i) {
    kill(processes[i], SIGKILL);
  }
}

static return_code_t exit_processes(size_t num_processes,
                                    const pid_t *processes) {
  if (!processes) {
    return INCORRECT_ARGS;
  }

  int status = 0;
  return_code_t rc = OK;
  for (size_t i = 0; i < num_processes; ++i) {
    pid_t pid = waitpid(processes[i], &status, WUNTRACED);
    if (pid == WAITPID_ERROR || status != OK) {
      rc = status ? status : PARALLEL_ERROR;
    }
  }
  return rc;
}

static return_code_t create_processes_array(long *num_processes,
                                            pid_t **processes,
                                            size_t size_array) {
  if (!num_processes || !processes) {
    return INCORRECT_ARGS;
  }

  *num_processes = sysconf(_SC_NPROCESSORS_ONLN);
  if (*num_processes == SYSCONF_ERROR) {
    return PARALLEL_ERROR;
  }

  if ((size_t)*num_processes > size_array) {
    *num_processes = size_array;
  }

  *processes = calloc(*num_processes, sizeof(pid_t));
  if (!(*processes)) {
    return ALLOCATION_ERROR;
  }

  return OK;
}

static int *get_shared_memory(void) {
  int *shared_num_posts = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (shared_num_posts == MAP_FAILED) {
    return NULL;
  }

  return shared_num_posts;
}

static return_code_t cur_count_posts(size_t start, size_t offset,
                                     post_t **const posts_array,
                                     int *shared_res) {
  if (!shared_res || !posts_array) {
    return INCORRECT_ARGS;
  }

  size_t end = start + offset;
  for (size_t i = start; i < end; ++i) {
    if (check_post(posts_array[i])) {
      ++(*shared_res);
    }
  }

  return OK;
}

static return_code_t generate_processes(const posts_array_t *posts_array,
                                        int *shared_res, size_t num_processes,
                                        pid_t *processes) {
  if (!posts_array || !shared_res || !processes) {
    return INCORRECT_ARGS;
  }

  size_t cur_num_posts =
      posts_array->size / num_processes + posts_array->size % num_processes;
  size_t start = 0;

  return_code_t rc = OK;

  for (size_t i = 0; !rc && i < num_processes; ++i) {
    pid_t child = fork();
    switch (child) {
      case FORK_ERROR:
        kill_processes(i, processes);
        rc = PARALLEL_ERROR;
        break;
      case CHILD:
        rc = cur_count_posts(start, cur_num_posts, posts_array->data,
                             shared_res);
        exit(rc);
      default:
        processes[i] = child;
        start += cur_num_posts;
    }
    if (i == 0 && child == CHILD) {
      cur_num_posts -= posts_array->size % num_processes;
    }
  }

  return rc;
}
