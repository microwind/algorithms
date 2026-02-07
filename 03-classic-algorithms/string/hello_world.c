#include <stdio.h>
//#include<string.h>
#include <stddef.h>
/**
 * output:
 * Hello, World 0 ,  Welcome to here. Hello, World 1 ,  Welcome to here. Hello, World 2 ,  ..
 * 
 */
typedef char *string;

int main()
{
    int i;
    char *str;
    str = "Hello, World";

    string word = " Welcome to here. ";
    for (i = 0; i < 10; i++)
    {
        printf("%s %d , %s", str, i, word);
    }
    return 0;
}