/**
 * using struct for sorting
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

struct Node
{
  int data;
  struct Node *next;
};

void bucket_sort(int arr[], int len);
struct Node *insertion_sort(struct Node *list);
void print(int arr[], int len);
void print_buckets(struct Node *list);

/**
 * 桶排序，通过strut结构提来当做桶，与普通数组排序一样
 */
void bucket_sort(int arr[], int len)
{
  int max_value = arr[0];
  int min_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max_value)
      max_value = arr[i];
    if (arr[i] < min_value)
      min_value = arr[i];
  }
  if (max_value < 1)
    max_value = 2;
  if (min_value < 1)
    min_value = 1;
  int i, j;
  struct Node **buckets;

  //  设置每个桶的大小
  int bucket_size = (max_value - min_value) / min_value + 1;
  // 一共多少个桶
  int bucket_number = (max_value - min_value) / bucket_size + 1;
  // 申请内存空间
  buckets = (struct Node **)malloc(sizeof(struct Node *) * bucket_number);

  // 初始化空的桶
  for (i = 0; i < bucket_number; ++i)
  {
    buckets[i] = NULL;
  }

  // 给桶内填充数据
  for (i = 0; i < len; ++i)
  {
    struct Node *current;
    int pos = (arr[i] - min_value) / bucket_size;
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    current->next = buckets[pos];
    buckets[pos] = current;
  }

  // 打印全部桶
  for (i = 0; i < bucket_number; i++)
  {
    printf("Bucket[%d]:", i);
    print_buckets(buckets[i]);
    printf("\n");
  }

  // 给每个桶按插入排序
  for (i = 0; i < bucket_number; ++i)
  {
    buckets[i] = insertion_sort(buckets[i]);
  }

  printf("-------------\n");
  printf("排序之后\n");
  for (i = 0; i < bucket_number; i++)
  {
    printf("Bucket[%d]: ", i);
    print_buckets(buckets[i]);
    printf("\n");
  }

  // 再将数据取出给数组
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

  return;
}

// 针对桶的插入排序
struct Node *insertion_sort(struct Node *list)
{
  struct Node *k, *node_list;
  if (list == 0 || list->next == 0)
  {
    return list;
  }

  node_list = list;
  k = list->next;
  node_list->next = 0;
  while (k != 0)
  {
    struct Node *ptr;
    if (node_list->data > k->data)
    {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = node_list;
      node_list = tmp;
      continue;
    }

    for (ptr = node_list; ptr->next != 0; ptr = ptr->next)
    {
      if (ptr->next->data > k->data)
        break;
    }

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
      ptr->next = k;
      k = k->next;
      ptr->next->next = 0;
      continue;
    }
  }
  return node_list;
}

void print(int arr[], int len)
{
  for (int i = 0; i < len; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// 打印全部桶
void print_buckets(struct Node *list)
{
  struct Node *cur = list;
  while (cur)
  {
    printf("%d ", cur->data);
    cur = cur->next;
  }
}

// Test
int main(void) {
  int arr[7] = {42, 32, 33, 52, 37, 47, 51};
  int arr2[12] = {2, 11, -9, 30, -15, 13, -2, 3, 4, 90, 0, 120};
  int arr3[5] = {9, -1, -2, 0, 4};
  int len = sizeof(arr) / sizeof(arr[0]);

  printf("arr1: ");
  print(arr, len);
  printf("-------------\n");

  bucket_sort(arr, len);
  printf("-------------\n");
  printf("Sorted arr1: ");
  print(arr, len);

  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("arr2: ");
  print(arr2, len2);
  printf("-------------\n");

  bucket_sort(arr2, len2);
  printf("-------------\n");
  printf("Sorted arr2: ");
  print(arr2, len2);

  int len3 = sizeof(arr3) / sizeof(arr3[0]);
  printf("arr3: ");
  print(arr3, len3);
  printf("-------------\n");

  bucket_sort(arr3, len3);
  printf("-------------\n");
  printf("Sorted arr3: ");
  print(arr3, len3);

  return 0;
}