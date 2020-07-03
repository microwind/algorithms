#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef char *string;
string monthName(int month);

/**
 * output:
 * Oct. 1, 2001
 */
int main()
{
    int month, day, year;
    month = 10;
    day = 1;
    year = 2001;
    printf("%s %d, %d\n", monthName(month), day, year);
    return 0;
}
string monthName(int month)
{
    switch (month)
    {
    case 1:
        return ("Jan.");
    case 2:
        return ("Feb.");
    case 3:
        return ("Mar.");
    case 4:
        return ("Apr.");
    case 5:
        return ("May");
    case 6:
        return ("Jun.");
    case 7:
        return ("Jul.");
    case 8:
        return ("Aug.");
    case 9:
        return ("Sep.");
    case 10:
        return ("Oct.");
    case 11:
        return ("Nov.");
    case 12:
        return ("Dec.");
    default:
        return ("Illegal month");
    }
}