/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 二叉树数据结构 - C实现
 */

#include <stdio.h>
#include <stdlib.h>

// 节点结构体：值、左子节点、右子节点
typedef struct Node
{
  int value;
  struct Node *left;
  struct Node *right;
} Node;

Node *createNode(int value)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// 前序遍历：根 -> 左 -> 右
void preorderTraversal(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  printf("%d ", root->value); // 访问根
  preorderTraversal(root->left); // 遍历左子树
  preorderTraversal(root->right); // 遍历右子树
}

// 中序遍历：左 -> 根 -> 右
void inorderTraversal(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  inorderTraversal(root->left); // 遍历左子树
  printf("%d ", root->value); // 访问根
  inorderTraversal(root->right); // 遍历右子树
}

// 后序遍历：左 -> 右 -> 根
void postorderTraversal(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  postorderTraversal(root->left); // 遍历左子树
  postorderTraversal(root->right); // 遍历右子树
  printf("%d ", root->value); // 访问根
}

int main()
{
  // 构建示例二叉树
  //        1
  //       / \
  //      2   3
  //     / \   /
  //    4   5 6
  Node *root = createNode(1);
  root->left = createNode(2);
  root->right = createNode(3);
  root->left->left = createNode(4);
  root->left->right = createNode(5);
  root->right->left = createNode(6);

  // 输出三种遍历结果
  printf("前序遍历：");
  preorderTraversal(root);
  printf("\n");

  printf("中序遍历：");
  inorderTraversal(root);
  printf("\n");

  printf("后序遍历：");
  postorderTraversal(root);
  printf("\n");

  return 0;
}

/*
jarry@MacBook-Pro tree % gcc tree.c
jarry@MacBook-Pro tree % ./a.out
前序遍历：1 2 4 5 3 6
中序遍历：4 2 5 1 6 3
后序遍历：4 5 2 6 3 1
*/