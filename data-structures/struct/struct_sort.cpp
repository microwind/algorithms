/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体排序 - 贪心算法购书问题 - C++实现
 */

#include <stdio.h>
#include <algorithm>
#include <stdlib.h>

int TOTAL_MONEY = 1000;

struct Book
{
  int id;
  char title[50];
  double price;
  int count;
};

Book books[] = {
    {1, "语文", 4.0, 33},
    {2, "英语", 2.5, 45},
    {3, "数学", 6.6, 26},
    {4, "物理", 3.7, 83},
    {5, "化学", 5.2, 51},
    {6, "历史", 4.1, 63},
    {7, "化学", 3.7, 15},
    {8, "政治", 2.3, 76},
    {9, "生物", 4.8, 62},
    {10, "音乐", 6.2, 34}};

int compare(Book one, Book two)
{
  return one.price < two.price;
}

int isOverTotal(int number)
{
  return TOTAL_MONEY < number;
}

void insertSort(Book books[], int len)
{
  for (int i = 0; i < len; i++)
  {
    int j = i;
    Book current = books[i];
    while (j-- > 0 && current.price < books[j].price)
    {
      books[j + 1] = books[j];
    }
    books[j + 1] = current;
  }
}

void printBooks(Book books[], int len)
{
  printf("顺序 原序号 名称 价格 数量\n");
  for (int i = 0; i < len; i++)
  {
    printf("%d)   %d     %s  %.1f  %d\n", i, books[i].id, books[i].title, books[i].price, books[i].count);
  }
}

int main()
{
  int booksLen = sizeof(books) / sizeof(books[0]);
  printf("std::sort 排序 \n");
  std::sort(books, books + booksLen, compare);

  printf("按价格排序后:\n");
  printBooks(books, booksLen);

  int buyCount = 0;
  int currentCost = 0;
  printf("== 开始购买计算 ==:\n");
  for (int i = 0; i < booksLen; i++)
  {
    Book book = books[i];
    currentCost += book.price * book.count;
    buyCount += book.count;
    printf("%d) 购买了: %d本%s, 单价:%.2f。", i + 1, book.count, book.title, book.price);
    printf("%s %d %s %d\n", " 当前购买总数：", buyCount, " 总花费：", currentCost);
    if (isOverTotal(currentCost))
    {
      printf("购买到 %s 时超出了金额。需要从最近购买项里面逐个移除以符合预算。\n", book.title);

      for (int j = 0; j < book.count; j++)
      {
        currentCost -= book.price;
        printf("\n减掉1本%s, 减去%.1f", book.title, book.price);
        buyCount--;
        if (!(isOverTotal(currentCost)))
        {
          printf("\n符合金额要求了, %s 只能买 %d 本。\n", book.title, book.count - j);
          break;
        }
      }

      break;
    }
  }
  printf("%s %d %s %d\n", "您最大购买总数：", buyCount, " 总花费：", currentCost);
}

/**
jarry@jarrys-mbp struct % gcc struct_sort.cpp
jarry@jarrys-mbp struct % ./a.out 
std::sort 排序 
按价格排序后:
顺序 原序号 名称 价格 数量
0)   8     政治  2.3  76
1)   2     英语  2.5  45
2)   4     物理  3.7  83
3)   7     化学  3.7  15
4)   1     语文  4.0  33
5)   6     历史  4.1  63
6)   9     生物  4.8  62
7)   5     化学  5.2  51
8)   10     音乐  6.2  34
9)   3     数学  6.6  26
== 开始购买计算 ==:
1) 购买了: 76本政治, 单价:2.30。 当前购买总数： 76  总花费： 174
2) 购买了: 45本英语, 单价:2.50。 当前购买总数： 121  总花费： 286
3) 购买了: 83本物理, 单价:3.70。 当前购买总数： 204  总花费： 593
4) 购买了: 15本化学, 单价:3.70。 当前购买总数： 219  总花费： 648
5) 购买了: 33本语文, 单价:4.00。 当前购买总数： 252  总花费： 780
6) 购买了: 63本历史, 单价:4.10。 当前购买总数： 315  总花费： 1038
购买到 历史 时超出了金额。需要从最近购买项里面逐个移除以符合预算。

减掉1本历史, 减去4.1
减掉1本历史, 减去4.1
减掉1本历史, 减去4.1
减掉1本历史, 减去4.1
减掉1本历史, 减去4.1
减掉1本历史, 减去4.1
减掉1本历史, 减去4.1
减掉1本历史, 减去4.1
符合金额要求了, 历史 只能买 56 本。
您最大购买总数： 307  总花费： 998
*/