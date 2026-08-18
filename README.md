# C Programming

A collection of C programs written while learning and practicing C.

## Programs & Modules

| File / Module | Description |
|---------------|-------------|
| `day1.c` | Getting started with C basics |
| `constants.c` | Working with constants |
| `trail.c` | Practice / trial program |
| `valparai.c` | Valparai e-pass management system |
| `hostel_booking.c` | Hostel 2 room booking system for 1st year students |
| `triangle_pattern.c` | Star triangle patterns (right-angled, pyramid, inverted, hollow, diamond) |
| `calculator.c` | Interactive calculator (+, -, *, /, %) with input validation |
| `electricity_calculator.c` | **CLI App**: Interactive electricity charge calculator for Domestic, Commercial, Industrial, Agricultural categories |
| `test_electricity_charge.c` | **Test Suite**: Multi-tier slab rate, tax, fuel surcharge, and prompt discount unit tests (`electricity_charge.c/h`) |
| `test_string_utils.c` | **Test Suite**: String manipulation unit tests (`string_utils.c/h`) |
| `test_matrix_ops.c` | **Test Suite**: Matrix and array operations unit tests (`matrix_ops.c/h`) |
| `random_generator.c` | **Toolkit**: Random numbers, dice roller, password/token generator, and stats |
| `test_vector.c` | **Test Suite**: Dynamic resizing array / vector structure (`vector.c/h`) |
| `test_linked_list.c` | **Test Suite**: Singly linked list operations & in-place reversal (`linked_list.c/h`) |
| `test_sort_search.c` | **Test Suite**: Quick Sort, Merge Sort, Binary Search & verification (`sort_search.c/h`) |
| `test_stack.c` | **Test Suite**: Dynamic Stack LIFO data structure (`stack.c/h`) |
| `test_queue.c` | **Test Suite**: Circular Queue FIFO data structure (`queue.c/h`) |
| `test_bst.c` | **Test Suite**: Binary Search Tree structure and operations (`bst.c/h`) |
| `test_heap.c` | **Test Suite**: Min-Heap Priority Queue structure and operations (`heap.c/h`) |
| `test_hash_table.c` | **Test Suite**: Hash Table key-value store (`hash_table.c/h`) |

## How to compile and run

### Individual Programs
```bash
gcc electricity_charge.c electricity_calculator.c -o electricity_calculator -lm
./electricity_calculator
```

### Running Test Programs
To compile and execute all test programs using the Makefile:
```bash
make test
```
