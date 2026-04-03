/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 桶排序结构体版本 - 使用链表结构作为桶实现
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 创建链表桶数组
 * 4. 将元素分配到对应桶中
 * 5. 对每个桶进行插入排序
 * 6. 合并所有桶的元素
 * 
 * 特点：
 * - 结构体桶：使用链表结构作为桶
 * - 动态内存：动态分配桶内存
 * - 链表操作：使用链表插入排序
 * - 内存管理：需要手动释放内存
 * 
 * @param {int[]} arr - 待排序的数字数组
 * @param {int} len - 数组长度
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

/**
 * 链表节点结构
 * 用于构建桶的链表结构
 */
struct Node
{
  int data;
  struct Node *next;
};

// 函数声明
void bucket_sort(int arr[], int len);
struct Node *insertion_sort(struct Node *list);
void print(int arr[], int len);
void print_buckets(struct Node *list);

/**
 * 桶排序主函数 - 使用结构体链表作为桶
 * 
 * 算法步骤：
 * 1. 计算数组最大值和最小值
 * 2. 根据数据范围计算桶的大小和数量
 * 3. 创建链表桶数组
 * 4. 将元素分配到对应桶中
 * 5. 对每个桶进行插入排序
 * 6. 合并所有桶的元素
 * 
 * @param {int[]} arr - 待排序的数字数组
 * @param {int} len - 数组长度
 */
void bucket_sort(int arr[], int len)
{
  // 第一步：计算数组最大值和最小值
  int max_value = arr[0];
  int min_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max_value)
      max_value = arr[i];
    if (arr[i] < min_value)
      min_value = arr[i];
  }
  
  // 边界处理：确保最大最小值的有效范围
  if (max_value < 1)
    max_value = 2;
  if (min_value < 1)
    min_value = 1;
  
  int i, j;
  struct Node **buckets;

  // 第二步：计算桶的大小和数量
  // 设置每个桶的大小
  int bucket_size = (max_value - min_value) / min_value + 1;
  // 一共多少个桶
  int bucket_number = (max_value - min_value) / bucket_size + 1;
  // 第三步：创建并初始化桶
  // 申请内存空间
  buckets = (struct Node **)malloc(sizeof(struct Node *) * bucket_number);

  // 初始化空的桶
  for (i = 0; i < bucket_number; ++i)
  {
    buckets[i] = NULL;
  }

  // 第四步：将元素分配到对应桶中
  for (i = 0; i < len; ++i)
  {
    struct Node *current;
    // 计算元素应该放入的桶索引
    int pos = (arr[i] - min_value) / bucket_size;
    // 创建新节点
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    // 头插法插入到桶中
    current->next = buckets[pos];
    buckets[pos] = current;
  }

  // 第五步：打印排序前的桶状态（调试用）
  for (i = 0; i < bucket_number; i++)
  {
    printf("Bucket[%d]:", i);
    print_buckets(buckets[i]);
    printf("\n");
  }

  // 第六步：对每个桶进行插入排序
  for (i = 0; i < bucket_number; ++i)
  {
    buckets[i] = insertion_sort(buckets[i]);
  }

  // 第七步：打印排序后的桶状态（调试用）
  printf("-------------\n");
  printf("排序之后\n");
  for (i = 0; i < bucket_number; i++)
  {
    printf("Bucket[%d]: ", i);
    print_buckets(buckets[i]);
    printf("\n");
  }

  // 第八步：将排序后的数据合并到原数组
  for (j = 0, i = 0; i < bucket_number; ++i)
  {
    struct Node *node;
    node = buckets[i];
    while (node)
    {
      arr[j++] = node->data;
      node = node->next;
    }
  }

  // 第九步：释放内存
  // 释放所有桶中的节点
  for (i = 0; i < bucket_number; ++i)
  {
    struct Node *node = buckets[i];
    while (node)
    {
      struct Node *temp = node;
      node = node->next;
      free(temp);
    }
  }
  // 释放桶数组
  free(buckets);

  return;
}

/**
 * 链表插入排序 - 对单个桶进行排序
 * 
 * 算法步骤：
 * 1. 检查链表是否为空或只有一个节点
 * 2. 将链表分为已排序部分和未排序部分
 * 3. 逐个将未排序节点插入到已排序部分的正确位置
 * 
 * @param {struct Node*} list - 待排序的链表头节点
 * @returns {struct Node*} 排序后的链表头节点
 */
struct Node *insertion_sort(struct Node *list)
{
  struct Node *k, *node_list;
  
  // 边界检查：空链表或单节点链表无需排序
  if (list == 0 || list->next == 0)
  {
    return list;
  }

  // 初始化：node_list为已排序部分，k为未排序部分
  node_list = list;
  k = list->next;
  node_list->next = 0;
  
  // 插入排序主循环
  while (k != 0)
  {
    struct Node *ptr;
    
    // 如果新节点应该插入到头部
    if (node_list->data > k->data)
    {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = node_list;
      node_list = tmp;
      continue;
    }

    // 在已排序部分中找到合适的插入位置
    for (ptr = node_list; ptr->next != 0; ptr = ptr->next)
    {
      if (ptr->next->data > k->data)
        break;
    }

    // 找到插入位置并插入节点
    if (ptr->next != 0)
    {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = ptr->next;
      ptr->next = tmp;
      continue;
    }
    else
    {
      // 插入到链表末尾
      ptr->next = k;
      k = k->next;
      ptr->next->next = 0;
      continue;
    }
  }
  return node_list;
}

/**
 * 打印数组 - 输出数组内容
 * 
 * @param {int[]} arr - 待打印的数组
 * @param {int} len - 数组长度
 */
void print(int arr[], int len)
{
  for (int i = 0; i < len; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

/**
 * 打印桶内容 - 输出链表桶中的所有元素
 * 
 * @param {struct Node*} list - 链表桶的头节点
 */
void print_buckets(struct Node *list)
{
  struct Node *cur = list;
  while (cur)
  {
    printf("%d ", cur->data);
    cur = cur->next;
  }
}

/**
 * 主函数 - 测试桶排序算法
 * 
 * 测试用例：
 * 1. 基本数组测试
 * 2. 包含负数的数组测试
 * 3. 混合数据测试
 */
int main(void) {
  // 测试数据1：基本数组
  int arr[7] = {42, 32, 33, 52, 37, 47, 51};
  // 测试数据2：包含负数的数组
  int arr2[12] = {2, 11, -9, 30, -15, 13, -2, 3, 4, 90, 0, 120};
  // 测试数据3：混合数据
  int arr3[5] = {9, -1, -2, 0, 4};

  printf("-------------\n");
  printf("原始数据arr1: ");
  int len = sizeof(arr) / sizeof(arr[0]);
  print(arr, len);
  bucket_sort(arr, len);
  printf("Sorted arr1: ");
  print(arr, len);
  
  printf("-------------\n");
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("原始数据arr2: ");
  print(arr2, len2);
  bucket_sort(arr2, len2);
  printf("Sorted arr2: ");
  print(arr2, len2);

  printf("-------------\n");
  int len3 = sizeof(arr3) / sizeof(arr3[0]);
  printf("原始数据arr3: ");
  print(arr3, len3);
  bucket_sort(arr3, len3);
  printf("Sorted arr3: ");
  print(arr3, len3);

  return 0;
}

/* 打印结果
jarry@Mac bucketsort % gcc bucket_struct_sort.c -o bucket_struct_sort && ./bucket_struct_sort
-------------
原始数据arr1: 42 32 33 52 37 47 51 
Bucket[0]:32 
Bucket[1]:33 
Bucket[2]:
Bucket[3]:
Bucket[4]:
Bucket[5]:37 
Bucket[6]:
Bucket[7]:
Bucket[8]:
Bucket[9]:
Bucket[10]:42 
Bucket[11]:
Bucket[12]:
Bucket[13]:
Bucket[14]:
Bucket[15]:47 
Bucket[16]:
Bucket[17]:
Bucket[18]:
Bucket[19]:51 
Bucket[20]:52 
-------------
排序之后
Bucket[0]: 32 
Bucket[1]: 33 
Bucket[2]: 
Bucket[3]: 
Bucket[4]: 
Bucket[5]: 37 
Bucket[6]: 
Bucket[7]: 
Bucket[8]: 
Bucket[9]: 
Bucket[10]: 42 
Bucket[11]: 
Bucket[12]: 
Bucket[13]: 
Bucket[14]: 
Bucket[15]: 47 
Bucket[16]: 
Bucket[17]: 
Bucket[18]: 
Bucket[19]: 51 
Bucket[20]: 52 
Sorted arr1: 32 33 37 42 47 51 52 
-------------
原始数据arr2: 2 11 -9 30 -15 13 -2 3 4 90 0 120 
Bucket[0]:120 0 90 4 3 -2 13 -15 30 -9 11 2 
-------------
排序之后
Bucket[0]: -15 -9 -2 0 2 3 4 11 13 30 90 120 
Sorted arr2: -15 -9 -2 0 2 3 4 11 13 30 90 120 
-------------
原始数据arr3: 9 -1 -2 0 4 
Bucket[0]:4 0 -2 -1 9 
-------------
排序之后
Bucket[0]: -2 -1 0 4 9 
Sorted arr3: -2 -1 0 4 9 
*/