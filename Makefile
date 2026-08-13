CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGETS = test_string_utils test_matrix_ops random_generator test_vector test_linked_list test_sort_search

all: $(TARGETS)

test_string_utils: string_utils.c test_string_utils.c
	$(CC) $(CFLAGS) string_utils.c test_string_utils.c -o test_string_utils

test_matrix_ops: matrix_ops.c test_matrix_ops.c
	$(CC) $(CFLAGS) matrix_ops.c test_matrix_ops.c -o test_matrix_ops

random_generator: random_generator.c random_generator.h
	$(CC) $(CFLAGS) random_generator.c -o random_generator -lm

test_vector: vector.c test_vector.c
	$(CC) $(CFLAGS) vector.c test_vector.c -o test_vector

test_linked_list: linked_list.c test_linked_list.c
	$(CC) $(CFLAGS) linked_list.c test_linked_list.c -o test_linked_list

test_sort_search: sort_search.c test_sort_search.c
	$(CC) $(CFLAGS) sort_search.c test_sort_search.c -o test_sort_search

test: all
	@echo "Running all test programs..."
	./test_string_utils
	./test_matrix_ops
	./random_generator
	./test_vector
	./test_linked_list
	./test_sort_search

clean:
	rm -f $(TARGETS) *.o

.PHONY: all test clean
