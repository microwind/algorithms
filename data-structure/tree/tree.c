#include <stdio.h>
#include <stdlib.h>

// 定义树的节点结构
typedef struct Node
{
  int value;          // 节点值
  struct Node *left;  // 左子节点
  struct Node *right; // 右子节点
} Node;

// 创建新节点
Node *createNode(int value)
{
  Node *newNode = (Node *)malloc(sizeof(Node)); // 分配内存
  newNode->value = value;                       // 设置节点值
  newNode->left = NULL;                         // 初始化左子节点为空
  newNode->right = NULL;                        // 初始化右子节点为空
  return newNode;                               // 返回新创建的节点
}

// 前序遍历：根 -> 左 -> 右
void preorderTraversal(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  printf("%d ", root->value);     // 访问根节点
  preorderTraversal(root->left);  // 递归访问左子树
  preorderTraversal(root->right); // 递归访问右子树
}

// 中序遍历：左 -> 根 -> 右
void inorderTraversal(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  inorderTraversal(root->left);  // 递归访问左子树
  printf("%d ", root->value);    // 访问根节点
  inorderTraversal(root->right); // 递归访问右子树
}

// 后序遍历：左 -> 右 -> 根
void postorderTraversal(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  postorderTraversal(root->left);  // 递归访问左子树
  postorderTraversal(root->right); // 递归访问右子树
  printf("%d ", root->value);      // 访问根节点
}

// 主函数，展示树的结构和遍历
int main()
{
  // 创建树
  /*
        1
       / \
      2   3
     / \   /
    4   5 6
  */
  Node *root = createNode(1);        // 根节点
  root->left = createNode(2);        // 根的左子节点
  root->right = createNode(3);       // 根的右子节点
  root->left->left = createNode(4);  // 节点2的左子节点
  root->left->right = createNode(5); // 节点2的右子节点
  root->right->left = createNode(6); // 节点3的左子节点

  // 输出树的遍历结果
  printf("前序遍历：");
  preorderTraversal(root); // 1 2 4 5 3 6
  printf("\n");

  printf("中序遍历：");
  inorderTraversal(root); // 4 2 5 1 6 3
  printf("\n");

  printf("后序遍历：");
  postorderTraversal(root); // 4 5 2 6 3 1
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