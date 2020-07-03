/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

// 定义node结构体
struct Node
{
  int value;
  struct Node *left;
  struct Node *right;
};

// 创建新node
struct Node *create_node(int value)
{
  // 内存空间申请
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  // 赋值给value
  node->value = value;
  // 初始化左节点与右节点
  node->left = NULL;
  node->right = NULL;
  return node;
}

// 移除队列中某项，其余项往前移动
void remove_index(struct Node **queue, int len, int idx)
{
  for (int i = idx; i < len - 1; i++)
  {
    queue[i] = queue[i + 1];
  }
}

// 统计实际长度
int count_length(struct Node **queue, int len)
{
  for (int i = 0; i < len; i++)
  {
    if (queue[i] == NULL)
    {
      return i;
    }
  }
  return len;
}

// 根据-1标识来追加到数组中
void append_array(int *arr, int value, int len)
{
  for (int i = 0; i < len; i++)
  {
    if (arr[i] == -1)
    {
      // printf(" arr[%d]=%d", i, value);
      arr[i] = value;
      break;
    }
  }
}

// 1. 先序优先遍历DLR递归版
int *preOrderTraverse(struct Node *tree, int *result, int len)
{
  if (tree != NULL)
  {
    append_array(result, tree->value, len);
    preOrderTraverse(tree->left, result, len);
    preOrderTraverse(tree->right, result, len);
  }
  return result;
}

// 2.	中序优先遍历LDR递归版
int *inOrderTraverse(struct Node *tree, int *result, int len)
{
  if (tree != NULL)
  {
    inOrderTraverse(tree->left, result, len);
    append_array(result, tree->value, len);
    inOrderTraverse(tree->right, result, len);
  }
  return result;
}

// 3.	后序优先遍历LRD递归版
int *postOrderTraverse(struct Node *tree, int *result, int len)
{
  if (tree != NULL)
  {
    postOrderTraverse(tree->left, result, len);
    postOrderTraverse(tree->right, result, len);
    append_array(result, tree->value, len);
  }
  return result;
}

// 4. 广度优先(层级遍历)，自左往右，利用队列暂存数据
int *levelOrder(struct Node *tree, int *result, int len)
{
  int queue_len = len;
  struct Node **queue = (struct Node **)calloc(queue_len, sizeof(struct Node));
  for (int i = 0; i < queue_len; i++)
  {
    // initialize space or NULL
    // queue[i] = (struct Node *)malloc(sizeof(struct Node));
    queue[i] = NULL;
  }

  if (tree != NULL)
  {
    int idx = 0;
    int first = 0;
    queue[first] = tree;
    while (queue[first] != NULL)
    {
      tree = queue[first];
      append_array(result, tree->value, len);
      idx -= 1;
      // remove the first
      remove_index(queue, len, first);
      // printf("\r\n queue[first] != NULL is %d idx=%d", queue[first] != NULL, idx);

      // append substree to queue
      if (tree->left != NULL)
      {
        idx += 1;
        queue[idx] = tree->left;
      }
      if (tree->right != NULL)
      {
        idx += 1;
        queue[idx] = tree->right;
      }
    }
    free(queue);
  }
  return result;
}

// 5. 深度遍历(先序优先非递归版)
int *preOrderUnRecursive(struct Node *tree, int *result, int len)
{
  int queue_len = len;
  struct Node **queue = (struct Node **)calloc(queue_len, sizeof(struct Node));
  for (int i = 0; i < queue_len; i++)
  {
    queue[i] = NULL;
  }
  if (tree != NULL)
  {
    while (count_length(queue, queue_len) > 0 || tree != NULL)
    {
      int idx = count_length(queue, queue_len);
      if (tree != NULL)
      {
        append_array(result, tree->value, len);
        queue[idx] = tree;
        tree = tree->left;
      }
      else
      {
        tree = queue[idx - 1];
        queue[idx - 1] = NULL;
        tree = tree->right;
      }
    }
    free(queue);
  }
  return result;
}

// 6. 深度遍历(中序优先非递归版)
int *inOrderUnRecursive(struct Node *tree, int *result, int len)
{
  int queue_len = len;
  struct Node **queue = (struct Node **)calloc(queue_len, sizeof(struct Node));
  for (int i = 0; i < queue_len; i++)
  {
    queue[i] = NULL;
  }
  if (tree != NULL)
  {
    while (count_length(queue, queue_len) > 0 || tree != NULL)
    {
      int idx = count_length(queue, queue_len);
      if (tree != NULL)
      {
        queue[idx] = tree;
        tree = tree->left;
      }
      else
      {
        tree = queue[idx - 1];
        queue[idx - 1] = NULL;
        append_array(result, tree->value, len);
        tree = tree->right;
      }
    }
    free(queue);
  }
  return result;
}

// 7. 深度遍历(后序优先非递归版)
int *postOrderUnRecursive(struct Node *tree, int *result, int len)
{
  if (tree != NULL)
  {
    int queue_len = len;
    struct Node **queue = (struct Node **)calloc(queue_len, sizeof(struct Node));
    for (int i = 0; i < queue_len; i++)
    {
      queue[i] = NULL;
    }
    int idx;
    struct Node *item;
    queue[0] = tree;
    while (count_length(queue, queue_len) > 0)
    {
      // 先得到最后一项作为比较项
      idx = count_length(queue, queue_len);
      item = queue[idx - 1];
      // 把左子树按深度全部追加到queue
      if (item->left != NULL && tree != item->left && tree != item->right)
      {
        queue[idx] = item->left;
        // 把右子树追加到queue
      }
      else if (item->right != NULL && tree != item->right)
      {
        queue[idx] = item->right;
      }
      else
      {
        // 左子树到最底层节点，开始打印left与right
        append_array(result, queue[idx - 1]->value, len);
        queue[idx - 1] = NULL;
        //  指向上一个节点，直到queue为空，也就是遍历至根节点
        tree = item;
      }
    }
    free(queue);
  }
  return result;
}

void printArray(int *arr, int len)
{
  printf("{ ");
  for (int i = 0; i < len; i++)
  {
    printf("%d", arr[i]);
    if (i < len - 1)
    {
      printf(", ");
    }
  }
  printf(" }");
}

int main()
{
  // 二叉树数据
  /*
    tree imaging:
                 1
            /         \
          2              3
        /   \          /   \
      4      5        6     7
           /   \          /    \
          8     9        10    11
        /   \
      12    13
    */

  /* 构造树 */
  struct Node *tree = create_node(1);
  tree->left = create_node(2);
  tree->right = create_node(3);
  struct Node *node2 = tree->left;
  struct Node *node3 = tree->right;
  node2->left = create_node(4);
  node2->right = create_node(5);
  node3->left = create_node(6);
  node3->right = create_node(7);
  struct Node *node5 = node2->right;
  node5->left = create_node(8);
  node5->right = create_node(9);
  struct Node *node7 = node3->right;
  node7->left = create_node(10);
  node7->right = create_node(11);
  struct Node *node8 = node5->left;
  node8->left = create_node(12);
  node8->right = create_node(13);

  /* test start */
  printf("test start:");
  double startTime = clock();
  int len = 13;
  // 申请空间且默认赋值为-1
  int *result = malloc(len * sizeof(int));
  memset(result, -1, len * sizeof(int));
  printf("\r\n origin result = ");
  printArray(result, len);
  // 1.
  result = preOrderTraverse(tree, result, len);
  printf("\r\n 1. preOrderTraverse: ");
  printArray(result, len);
  // { 1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11 }

  // 2.
  memset(result, -1, len * sizeof(int));
  result = inOrderTraverse(tree, result, len);
  printf("\r\n 2. inOrderTraverse: ");
  printArray(result, len);
  // { 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11 }

  // 3.
  memset(result, -1, len * sizeof(int));
  result = postOrderTraverse(tree, result, len);
  printf("\r\n 3. postOrderTraverse: ");
  printArray(result, len);
  // { 4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1 }

  // 4.
  memset(result, -1, len * sizeof(int));
  result = levelOrder(tree, result, len);
  printf("\r\n 4. levelOrder: ");
  printArray(result, len);
  // { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }

  // 5.
  memset(result, -1, len * sizeof(int));
  result = preOrderUnRecursive(tree, result, len);
  printf("\r\n 5. preOrderUnRecursive: ");
  printArray(result, len);
  // { 1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11 }

  // 6.
  memset(result, -1, len * sizeof(int));
  result = inOrderUnRecursive(tree, result, len);
  printf("\r\n 6. inOrderUnRecursive: ");
  printArray(result, len);
  // { 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11 }

  // 7.
  memset(result, -1, len * sizeof(int));
  result = postOrderUnRecursive(tree, result, len);
  printf("\r\n 7. postOrderUnRecursive: ");
  printArray(result, len);
  // { 4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1 }

  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

  free(result);
}

/**
jarry@jarrys-MacBook-Pro binarytree % gcc -v
jarry@jarrys-MacBook-Pro binarytree % gcc binary_tree.c
jarry@jarrys-MacBook-Pro binarytree % ./a.out
test start: 
 origin result = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
 1. preOrderTraverse: { 1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11 }
 2. inOrderTraverse: { 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11 }
 3. postOrderTraverse: { 4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1 }
 4. levelOrder: { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }
 5. preOrderUnRecursive: { 1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11 }
 6. inOrderUnRecursive: { 4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11 }
 7. postOrderUnRecursive: { 4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1 }
time: 0.100000 ms.%  
*/