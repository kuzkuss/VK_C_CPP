import random
import sys

HELP_MSG = ("Usage:\n   app output_file [num_records]\n")
LARGE_NUM = 10000000
REQ_NUM_ARGS = 2
EXTN_NUM_ARGS = 3

MIN_GRADE = 1
MAX_GRADE = 5

MIN_VOTES = 1
MAX_VOTES = 1000

MIN_DAY = 1
MAX_DAY = 31

MIN_MONTH = 1
MAX_MONTH = 12

MIN_YEAR = 1
MAX_YEAR = 2022

PRECISION = 2

if len(sys.argv) < REQ_NUM_ARGS:
    print(HELP_MSG)
    exit(1)

amount_records = LARGE_NUM

if len(sys.argv) == EXTN_NUM_ARGS:
    amount_records = int(sys.argv[REQ_NUM_ARGS])

data = []
for i in range(amount_records):
    avg_grade = round(random.uniform(MIN_GRADE, MAX_GRADE), PRECISION)
    votes = random.randint(MIN_VOTES, MAX_VOTES)
    day = random.randint(MIN_DAY, MAX_DAY)
    month = random.randint(MIN_MONTH, MAX_MONTH)
    year = random.randint(MIN_YEAR, MAX_YEAR)
    last_grade = random.randint(MIN_GRADE, MAX_GRADE)
    data.append(" ".join([str(j) for j in [i + 1, avg_grade, votes]]) + 
                " " + ".".join([str(j) for j in [day, month, year]]) + " " + str(last_grade))


file = open(sys.argv[1], 'w')

for record in data:
    file.write(record + '\n')

file.close()

