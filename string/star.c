#include <stdio.h>
#include <stdlib.h>
/**
 * output:
 * 
 *   *
 *   **
 *   ***
 *   ****
 *   *****
 *   ******
 *   *******
 *   ********
 *   *********
 *   **********

 *   --apart line--
 *            *
 *           ***
 *          *****
 *         *******
 *        *********
 *       ***********
 *      *************
 *     ***************
 *    *****************
 *   *******************
 */
int main()
{

    //#define line 8;
    int line;
    line = 10;
    int i, j;
    j = 0;
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            //printf("* %d & %d  ", i, j);
            printf("*");
            if (i == j)
                break; // or for( j = 0; j < i; j++)
        }

        printf("\n");
    }

    printf("\n--apart line--\n");

    line = 10 * 2;
    int curLine, space;
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            if (i % 2 == 0)
            {
                curLine = i + 1;              // 取模后实际行号为双数，当前行数也就是星号个数
                space = (line - curLine) / 2; // 两边的空格数

                //printf("(%d%d )", space, curLine);
                if (j < space || j >= curLine + space)
                {
                    // 当前列小于当前空格数则表示左侧的空格数
                    // 大于等于当前显示的个数(行数就是个数)加左边的空格数，即是右侧的空格
                    printf(" ");
                }
                else
                {
                    printf("*");
                }
            }
        }
        if (i % 2 == 0)
            printf("\n");
    }

    getchar();
    return 0;
}