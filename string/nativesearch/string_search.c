/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

int find(char* str, char* text)
{
  int text_len = strlen(text);
  int str_len = strlen(str);
  // 两个循环，外层是被查找文本，内循环是查找字符串
  for (int i = 0; i < text_len; i++)
  {
    int j = 0;
    for (; j < str_len; j++)
    {
      // 当遇到不有不相等时，跳出从文本下一个字符开始比较
      if (str[j] != text[i + j])
      {
        break;
      }
    }
    // 如果查找字符串全部比较完成表示成功匹配
    if (j == str_len)
    {
      return i;
    }
  }

  // 如果文本全部比较完还是没有查找到，则返回-1
  return -1;
}

int find2(char* str, char* text)
{
  int text_len = strlen(text);
  int str_len = strlen(str);
  // 两个循环，外层是被查找文本，内循环是查找字符串
  for (int i = 0, l = text_len - str_len + 1; i < l; i++)
  {
    int j = 0;
    for (; j < str_len; j++)
    {
      // 循环长度优化+剩余字符优化
      // 如果被查找的长度比要查找的还少，则可以返回-1
      if (text_len - i < str_len - j)
      {
        // console.log('less length', i, j)
        return -1;
      }
      // 当遇到不有不相等时，跳出从文本下一个字符开始比较
      if (str[j] != text[i + j])
      {
        break;
      }
    }
    // 如果查找字符串全部比较完成表示成功匹配
    if (j == str_len)
    {
      return i;
    }
  }

  // 如果文本全部比较完还是没有查找到，则返回-1
  return -1;
}

int main()
{
  /* find test */
  float startTime = clock();
  printf("find start");
  char str1[] = "ABC";
  char text1[] = "AABABC";
  int result = find(str1, text1);       // 3
  printf("\nfind('ABC', 'AABABC'), %d", result);

  char str2[] = "AAB";
  char text2[] = "AAAABC";
  result = find(str2, text2);;          // 2
  printf("\nfind('AAB', 'AAAABC'), %d", result);

  char str3[] = "ABC";
  char text3[] = "AABAC";
  result = find(str3, text3);;          // -1
  printf("\nfind('ABC', 'AABAC'), %d", result);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\nfind end\n");

  /* find2 test */

  startTime = clock();
  printf("find2 start");
  result = find2(str1, text1);           // 3
  printf("\nfind('ABC', 'AABABC'), %d", result);

  result = find2(str2, text2);;          // 2
  printf("\nfind('AAB', 'AAAABC'), %d", result);

  result = find2(str3, text3);;          // -1
  printf("\nfind('ABC', 'AABAC'), %d", result);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\nfind2 end\n");
}

/**
jarry@jarrys-MacBook-Pro nativesearch % gcc string_search.c -o string_search
jarry@jarrys-MacBook-Pro nativesearch % ./string_search                     
find start
find('ABC', 'AABABC'), 3
find('AAB', 'AAAABC'), 2
find('ABC', 'AABAC'), -1
time: 0.041000 ms.
find end
find2 start
find('ABC', 'AABABC'), 3
find('AAB', 'AAAABC'), 2
find('ABC', 'AABAC'), -1
time: 0.006000 ms.
find2 end
*/