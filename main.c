#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int count_digits(unsigned long max_val) {
    int digits = 0;
    if (max_val == 0) return 1;
    
    /* log10(max_val) + 1 nos da el número de dígitos */
    digits = (int)(log10((double)max_val)) + 1;
    return digits;
}

int main(int argc, char const *argv[])
{
  // printf("%lu\n", ULONG_MAX);
  // printf("%lu\n", SIZE_T_MAX);
  // printf("unsigned long: %d dígitos\n", count_digits(ULONG_MAX));
  
  printf("%d\n", strlen("hello"));
  
  return 0;
}
