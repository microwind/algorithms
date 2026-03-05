/*
 * 使用回溯算法生成组合（C 语言版）
 *
 * 算法说明：
 *   生成从 1 到 n 中选取 k 个元素的所有组合，即 C(n, k)。
 *   使用回溯系统地探索所有选择：
 *     - 每一步只考虑 >= 当前起点的元素，防止生成重复组合。
 *     - 当已选元素数量达到 k 时，将当前组合记录到结果中。
 *
 * 时间复杂度：O(C(n,k) * k)，其中 C(n,k) 为组合总数
 * 空间复杂度：O(k)，用于递归栈深度和当前组合缓冲区
 *
 * 示例：
 *   combine(4, 2) 返回：
 *   [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 单个组合：保存元素数组及其长度 */
typedef struct
{
    int *data;
    int size;
} Combination;

/* 组合结果集：动态数组，存储所有组合 */
typedef struct
{
    Combination *combos; /* 组合数组 */
    int count;           /* 当前已存储的组合数量 */
    int capacity;        /* 动态数组当前容量 */
} CombinationResult;

/*
 * add_combination - 将一个组合追加到结果集
 *
 * 若容量不足则自动扩容（容量翻倍）。
 * 每个组合深拷贝一份独立的数据，与调用方的缓冲区解耦。
 *
 * 参数：
 *   result  - 目标结果集
 *   arr     - 当前组合的元素数组
 *   k       - 组合中元素的个数
 */
void add_combination(CombinationResult *result, int *arr, int k)
{
    /* 容量不足时扩容 */
    if (result->count >= result->capacity)
    {
        result->capacity *= 2;
        result->combos = (Combination *)realloc(
            result->combos, result->capacity * sizeof(Combination));
    }

    /* 深拷贝当前组合 */
    result->combos[result->count].data = (int *)malloc(k * sizeof(int));
    memcpy(result->combos[result->count].data, arr, k * sizeof(int));
    result->combos[result->count].size = k;
    result->count++;
}

/*
 * backtrack - 回溯核心函数
 *
 * 递归地在 [start, n] 范围内选取元素，构建长度为 k 的组合。
 * 每次递归只向后选（num+1 起），保证组合有序且不重复。
 *
 * 参数：
 *   n           - 元素上界（1 到 n）
 *   k           - 目标组合长度
 *   start       - 本层可选的最小元素值
 *   current     - 当前已选元素的缓冲区（复用，不额外分配）
 *   current_len - 当前已选元素的数量
 *   result      - 结果集
 */
void backtrack(int n, int k, int start, int *current, int current_len,
               CombinationResult *result)
{
    /* 终止条件：已选够 k 个元素，记录本次组合 */
    if (current_len == k)
    {
        add_combination(result, current, k);
        return;
    }

    /* 枚举本层的每个候选元素 */
    for (int num = start; num <= n; num++)
    {
        /* 做选择：将 num 放入当前位置 */
        current[current_len] = num;

        /* 递归：继续选下一个元素，起点为 num+1（保证不重复） */
        backtrack(n, k, num + 1, current, current_len + 1, result);

        /* 撤销选择：下一次循环覆盖 current[current_len]，无需显式清除 */
    }
}

/*
 * combine - 生成 C(n, k) 的所有组合
 *
 * 参数：
 *   n - 元素的总数（取值范围 1 到 n）
 *   k - 每个组合的大小
 *
 * 返回：
 *   指向 CombinationResult 的指针，调用方负责调用 free_result() 释放内存。
 */
CombinationResult *combine(int n, int k)
{
    /* 初始化结果集 */
    CombinationResult *result = (CombinationResult *)malloc(sizeof(CombinationResult));
    result->capacity = 1000;
    result->combos = (Combination *)malloc(result->capacity * sizeof(Combination));
    result->count = 0;

    /* 分配复用缓冲区，回溯过程中原地修改 */
    int *current = (int *)malloc(k * sizeof(int));
    backtrack(n, k, 1, current, 0, result);
    free(current);

    return result;
}

/*
 * free_result - 释放组合结果集占用的所有内存
 *
 * 参数：
 *   result - 由 combine() 返回的结果集指针
 */
void free_result(CombinationResult *result)
{
    for (int i = 0; i < result->count; i++)
    {
        free(result->combos[i].data);
    }
    free(result->combos);
    free(result);
}

/*
 * print_combination - 打印单个组合，格式为 [a, b, c]
 *
 * 参数：
 *   combo - 指向单个 Combination 的指针
 */
void print_combination(Combination *combo)
{
    printf("[");
    for (int i = 0; i < combo->size; i++)
    {
        printf("%d", combo->data[i]);
        if (i < combo->size - 1)
            printf(", ");
    }
    printf("]");
}

/* ===== 测试入口 ===== */
int main()
{
    printf("=== 组合回溯算法测试 ===\n\n");

    /* 测试用例 1：从 4 个元素中选 2 个，期望 C(4,2)=6 种 */
    printf("测试 1：combine(4, 2)\n");
    CombinationResult *result1 = combine(4, 2);
    printf("结果（共 %d 种）：\n", result1->count);
    for (int i = 0; i < result1->count; i++)
    {
        printf("  ");
        print_combination(&result1->combos[i]);
        printf("\n");
    }
    free_result(result1);
    printf("\n");

    /* 测试用例 2：从 3 个元素中选 1 个，期望 C(3,1)=3 种 */
    printf("测试 2：combine(3, 1)\n");
    CombinationResult *result2 = combine(3, 1);
    printf("结果（共 %d 种）：\n", result2->count);
    for (int i = 0; i < result2->count; i++)
    {
        printf("  ");
        print_combination(&result2->combos[i]);
        printf("\n");
    }
    free_result(result2);
    printf("\n");

    /* 测试用例 3：从 3 个元素中选 3 个，期望 C(3,3)=1 种 */
    printf("测试 3：combine(3, 3)\n");
    CombinationResult *result3 = combine(3, 3);
    printf("结果（共 %d 种）：\n", result3->count);
    for (int i = 0; i < result3->count; i++)
    {
        printf("  ");
        print_combination(&result3->combos[i]);
        printf("\n");
    }
    free_result(result3);
    printf("\n");

    /* 测试用例 4：从 5 个元素中选 3 个，期望 C(5,3)=10 种 */
    printf("测试 4：combine(5, 3)\n");
    CombinationResult *result4 = combine(5, 3);
    printf("结果（共 %d 种）：\n", result4->count);
    for (int i = 0; i < result4->count; i++)
    {
        printf("  ");
        print_combination(&result4->combos[i]);
        printf("\n");
    }
    free_result(result4);
    printf("\n");

    /* 测试用例 5：从 6 个元素中选 2 个，期望 C(6,2)=15 种 */
    printf("测试 5：combine(6, 2)\n");
    CombinationResult *result5 = combine(6, 2);
    printf("结果（共 %d 种）：\n", result5->count);
    for (int i = 0; i < result5->count; i++)
    {
        printf("  ");
        print_combination(&result5->combos[i]);
        printf("\n");
    }
    free_result(result5);

    return 0;
}

/**
jarry@Mac combination % ./a.out
=== 组合回溯算法测试 ===

测试 1：combine(4, 2)
结果（共 6 种）：
  [1, 2]
  [1, 3]
  [1, 4]
  [2, 3]
  [2, 4]
  [3, 4]

测试 2：combine(3, 1)
结果（共 3 种）：
  [1]
  [2]
  [3]

测试 3：combine(3, 3)
结果（共 1 种）：
  [1, 2, 3]

测试 4：combine(5, 3)
结果（共 10 种）：
  [1, 2, 3]
  [1, 2, 4]
  [1, 2, 5]
  [1, 3, 4]
  [1, 3, 5]
  [1, 4, 5]
  [2, 3, 4]
  [2, 3, 5]
  [2, 4, 5]
  [3, 4, 5]

测试 5：combine(6, 2)
结果（共 15 种）：
  [1, 2]
  [1, 3]
  [1, 4]
  [1, 5]
  [1, 6]
  [2, 3]
  [2, 4]
  [2, 5]
  [2, 6]
  [3, 4]
  [3, 5]
  [3, 6]
  [4, 5]
  [4, 6]
  [5, 6]
 */