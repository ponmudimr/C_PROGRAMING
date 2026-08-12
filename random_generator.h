#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <stddef.h>

/* Initialize the random number generator seed */
void init_random(void);

/* Generate a random integer between min and max inclusive */
int get_random_int(int min, int max);

/* Generate a random double between min and max */
double get_random_double(double min, double max);

/* Roll n dice with the specified number of sides, returns sum */
int roll_dice(int count, int sides);

#endif /* RANDOM_GENERATOR_H */
