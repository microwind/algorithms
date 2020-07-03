#include <stdio.h>
#include <stdlib.h>

int main()
{
  int max = 10;
  for (int i = 1; i < max; i++)
  {
    printf("\r\n ");
    for (int j = 1; j < max; j++)
    {
      if (j <= i)
      {
        printf("%d * %d = %d  ", i, j, i * j);
      }
    }
  }
  printf("\r\n The follow multiple you need to know. \r\n");
  for (int i = 10; i < 17; i++)
  {
    printf(" %d * %d = %d  ", i, i, i * i);
  }
  return 0;
}