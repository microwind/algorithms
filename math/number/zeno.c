#include <stdio.h>
/**
 * zeno序列
 * output:
 * s = 1/2 + 1/4 + 1/8;
 * 2s = 1 + s;
 * s = 1;
 */
main() {
  double sum, term;
  sum  = 0.0;
  term = 0.8;
  while (sum != sum + term) {
       sum += term;
       printf("\n%g", sum);
       term /= 2;
  }
  printf("The sum of Zeno's series is %g\n", sum);
}
