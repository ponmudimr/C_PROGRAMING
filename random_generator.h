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

/* Generate a random password string of specified length into buffer */
void generate_random_password(char *buffer, size_t length, int include_symbols);

/* Generate a random hexadecimal token string of specified length */
void generate_hex_token(char *buffer, size_t length);

#endif /* RANDOM_GENERATOR_H */

