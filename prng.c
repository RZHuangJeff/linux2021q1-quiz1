#include "prng.h"

#include <stdbool.h>

#define W 32
#define N 624
#define M 397
#define R 31

#define U 11
#define S 7
#define T 15
#define L 18

#define _a 0x9908b0df
#define _b 0x9d2c5680
#define _c 0xefc60000

#define U_MASK 0x80000000 /* Get upper W - R bit(s) */
#define L_MASK 0x7fffffff /* Get lower R bit(s) */

static uint32_t x[N];
static int xi = N + 1;
static bool been_set = false;

void prng_set_seed(uint32_t seed) {
  /* Since seed = 0 will make all initial buffer to zero,
     which will cause numbers being generaged be zero. */
  x[0] = (!seed ? 1 : seed) & 0xffffffff;
  for (xi = 1; xi < N; xi++)
    x[xi] = (69069 * x[xi - 1]) & 0xffffffff;

  been_set = true;
}

uint32_t prng_gen_number() {
  if (!been_set)
    prng_set_seed(1);

  uint32_t y;
  int k;
  /* Generate N numbers at one time */
  if (xi == N) {
    for (k = 0; k < N - M; k++) {
      y = (x[k] & U_MASK) | (x[k + 1] & L_MASK);
      x[k] = x[k + M] ^ (y >> 1) ^ ((y & 0x1) ? _a : 0);
    }

    for (; k < N - 1; k++) {
      y = (x[k] & U_MASK) | (x[k + 1] & L_MASK);
      x[k] = x[k - N + M] ^ (y >> 1) ^ ((y & 0x1) ? _a : 0);
    }

    y = (x[N - 1] & U_MASK) | (x[0] & L_MASK);
    x[N - 1] = x[M - 1] ^ (y >> 1) ^ ((y & 0x1) ? _a : 0);

    xi = 0;
  }

  y = x[xi++];
  y ^= (y >> U);
  y ^= (y << S) & _b;
  y ^= (y << T) & _c;
  y ^= (y >> L);

  return y;
}