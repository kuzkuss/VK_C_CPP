#include <stdio.h>

typedef struct {
  char day;
  char month;
  short year;
} date_t;

typedef enum {
  NO_GRADES,
  CORRECT_AVG_GRADE
} kind_avg_grade_t;

typedef struct {
  kind_avg_grade_t kind_avg_grade;
  union {
    float average_grade;
    int no_grade;
  };
} avg_grade_t;

typedef struct {
  size_t votes;
  avg_grade_t avg_grade;
  date_t date;
  int last_grade;
  int id;
} post_t;

typedef struct {
  int id;
  int id1;
  int id2;
  int id3;
  int id4;
  int id5;
  int id6;
  int id7;
  int id8;
} post2_t;

int main(void) {
    printf("%ld %ld %ld %ld %ld", sizeof(date_t), sizeof(avg_grade_t), sizeof(post_t), sizeof(kind_avg_grade_t), sizeof(post2_t));

    return 0;
}

