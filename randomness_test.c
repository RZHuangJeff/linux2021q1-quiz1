#include <stdio.h>
#include <string.h>
#include <time.h>

#include "prng.h"

#define ROUND 5
#define SAMPLE 10000000

int main() {
  uint32_t seed = time(NULL);
  uint32_t n, count[32] = {0};

  for (int i = 1; i <= ROUND; i++) {
    prng_set_seed(seed);

    memset(count, 0, sizeof(uint32_t) * 32);

    for (int j = 0; j < SAMPLE; j++) {
      n = prng_gen_number();

      for (char b = 0; b < 32; b++)
        if (n & (1 << b))
          count[b]++;
    }

    printf("0/1 ratio of ROUND %d with seed %u:\n", i, seed);
    for (int j = 0; j < 32; j++)
      printf("%lf ", (SAMPLE - count[j])/(double)count[j]);
    printf("\n");

    seed = prng_gen_number();
  }
}