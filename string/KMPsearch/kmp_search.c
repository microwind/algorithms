#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
}

// 创建部分匹配表
void makePMT(const char *pattern, int patternLen, int **pmt)
{
    *pmt = (int *)malloc(patternLen * sizeof(int));
    if (*pmt == NULL)
    {
        perror("malloc failed");
        exit(1);
    }

    for (int i = 0; i < patternLen; i++)
    {
        int pmtValue = 0;

        // 遍历前缀和后缀
        for (int j = 0; j < i; j++)
        {
            char prefix[j + 2];
            char postfix[j + 2];

            strncpy(prefix, pattern, j + 1);
            prefix[j + 1] = '\0';

            strncpy(postfix, pattern + (i - j), j + 1);
            postfix[j + 1] = '\0';

            if (strcmp(prefix, postfix) == 0 && j + 1 > pmtValue)
            {
                pmtValue = j + 1;
            }
        }

        (*pmt)[i] = pmtValue;
    }
    printArray(*pmt, patternLen);
}

// 创建 KMP 部分匹配表
void makePMT2(const char *pattern, int patternLen, int **pmt)
{
    *pmt = (int *)malloc(patternLen * sizeof(int));
    if (*pmt == NULL)
    {
        perror("malloc failed");
        exit(1);
    }

    int pmtValue = 0;
    (*pmt)[0] = 0;

    for (int i = 1; i < patternLen; i++)
    {
        while (pmtValue > 0 && pattern[i] != pattern[pmtValue])
        {
            pmtValue = (*pmt)[pmtValue - 1];
        }

        if (pattern[i] == pattern[pmtValue])
        {
            pmtValue++;
        }

        (*pmt)[i] = pmtValue;
    }
    printArray(*pmt, patternLen);
}

// KMP 搜索
void kmpSearch(const char *pattern, int patternLen, const char *text, int textLen, int **matches, int *matchCount)
{
    int *pmt = NULL;
    // makePMT(pattern, patternLen, &pmt);
    makePMT2(pattern, patternLen, &pmt);

    int j = 0;       // 模式串的索引
    *matchCount = 0; // 匹配计数

    for (int i = 0; i < textLen; i++)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            j = pmt[j - 1];
        }

        if (text[i] == pattern[j])
        {
            j++;
        }

        if (j == patternLen)
        {
            *matches = realloc(*matches, (*matchCount + 1) * sizeof(int));
            if (*matches == NULL)
            {
                perror("realloc failed");
                exit(1);
            }

            (*matches)[*matchCount] = i - j + 1;
            (*matchCount)++;

            j = pmt[j - 1]; // 回退以继续查找
        }
    }

    free(pmt); // 释放部分匹配表
}

int main()
{
    const char *pattern = "ABCABAB";
    const char *text1 = "AAABABCABABCDABABCABAB";
    const char *text2 = "ABAAABABCABABCDABABCABAB";

    printf("%s%s\n", "pattern:", pattern);
    printf("%s%s\n", "text1:", text1);
    printf("%s%s\n", "text2:", text2);

    int *matches = NULL; // 动态分配内存
    int matchCount = 0;

    kmpSearch(pattern, strlen(pattern), text1, strlen(text1), &matches, &matchCount);
    printf("匹配结果 1：");
    printArray(matches, matchCount);
    printf("\n");

    free(matches); // 释放分配的内存
    matches = NULL;

    /** 分割线 ***/

    matchCount = 0;

    kmpSearch(pattern, strlen(pattern), text2, strlen(text2), &matches, &matchCount);
    printf("匹配结果 2：");
    printArray(matches, matchCount);
    printf("\n");

    free(matches); // 释放分配的内存

    return 0;
}