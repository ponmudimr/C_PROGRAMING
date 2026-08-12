CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGETS = test_string_utils test_matrix_ops random_generator

all: $(TARGETS)

test_string_utils: string_utils.c test_string_utils.c
	$(CC) $(CFLAGS) string_utils.c test_string_utils.c -o test_string_utils

test_matrix_ops: matrix_ops.c test_matrix_ops.c
	$(CC) $(CFLAGS) matrix_ops.c test_matrix_ops.c -o test_matrix_ops

random_generator: random_generator.c random_generator.h
	$(CC) $(CFLAGS) random_generator.c -o random_generator -lm

test: all
	@echo "Running all test programs..."
	./test_string_utils
	./test_matrix_ops
	./random_generator


clean:
	rm -f $(TARGETS) *.o

.PHONY: all test clean
