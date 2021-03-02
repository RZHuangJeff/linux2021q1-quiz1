#ifndef QUIZ1_PRNG_H
#define QUIZ1_PRNG_H

#include <stdint.h>

/*
 * Init psuedorandom number generator with seed.
 */
void prng_set_seed(uint32_t seed);

/*
 * Generate a random number.
 */
uint32_t prng_gen_number();

#endif // QUIZ1_PRNG_H