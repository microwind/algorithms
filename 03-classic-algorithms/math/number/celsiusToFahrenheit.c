#include <stdio.h>
#include <stdlib.h>

#define lowerLimit 0
#define upperLimit 100
#define stepSize 5
double celsiusTofahrenheit(double c);
int fahrenheitTocelsius(int f);
/**
 * output:
 * 
 * Celsius to Fahrenheit table
 *  0  |  32
 *  5  |  41
 *  10  |  50
 *  15  |  59
 *  20  |  68
 *  25  |  77
 *  30  |  86
 *  35  |  95
 */
int main()
{
    printf("Celsius to Fahrenheit table\n");
    int c;
    c = lowerLimit;
    while (c <= upperLimit)
    {
        printf("%3d  | %3g", c, celsiusTofahrenheit(c));
        c += stepSize;
        printf("\n");
    }

    int number;
    printf("Fahrenheit to Celsius. please input some number: ");
    scanf("%d", &number);
    printf("%d  | %d", number, fahrenheitTocelsius(number));

    getchar();
    return 0;
}
/**
 * C = 5(F - 32) /  9
 * C/5 = (F - 32) / 9
 * 9 * C/5 = F - 32
 * 9 * C/5 + 32 = F
 */
double celsiusTofahrenheit(double c)
{
    return 9.0 / 5.0 * c + 32;
}

/**
 * F = 9 / 5 * C + 32
 * 
 * F - 32 = 9 / 5 * C
 * (F - 32) * 5 = 9C
 * (F - 32) * 5 / 9 = C
 */
int fahrenheitTocelsius(int f)
{
    return 5 * (f - 32) / 9;
}
