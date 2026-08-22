CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGETS = test_string_utils test_matrix_ops random_generator test_vector test_linked_list test_sort_search test_stack test_queue test_bst test_heap test_hash_table test_graph test_electricity_charge electricity_calculator

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

test_stack: stack.c test_stack.c
	$(CC) $(CFLAGS) stack.c test_stack.c -o test_stack

test_queue: queue.c test_queue.c
	$(CC) $(CFLAGS) queue.c test_queue.c -o test_queue

test_bst: bst.c test_bst.c
	$(CC) $(CFLAGS) bst.c test_bst.c -o test_bst

test_heap: heap.c test_heap.c
	$(CC) $(CFLAGS) heap.c test_heap.c -o test_heap

test_hash_table: hash_table.c test_hash_table.c
	$(CC) $(CFLAGS) hash_table.c test_hash_table.c -o test_hash_table

test_graph: graph.c test_graph.c graph.h
	$(CC) $(CFLAGS) graph.c test_graph.c -o test_graph

test_electricity_charge: electricity_charge.c test_electricity_charge.c electricity_charge.h
	$(CC) $(CFLAGS) electricity_charge.c test_electricity_charge.c -o test_electricity_charge -lm

electricity_calculator: electricity_charge.c electricity_calculator.c electricity_charge.h
	$(CC) $(CFLAGS) electricity_charge.c electricity_calculator.c -o electricity_calculator -lm

test: all
	@echo "Running all test programs..."
	./test_string_utils
	./test_matrix_ops
	./random_generator
	./test_vector
	./test_linked_list
	./test_sort_search
	./test_stack
	./test_queue
	./test_bst
	./test_heap
	./test_hash_table
	./test_graph
	./test_electricity_charge

clean:
	rm -f $(TARGETS) *.o

.PHONY: all test clean
