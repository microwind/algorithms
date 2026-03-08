/*
 * 树遍历 - Tree Traversal
 * 实现二叉树的前序、中序、后序遍历（递归和迭代）
 */
#include <stdio.h>
#include <stdlib.h>

// 二叉树节点
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 创建新节点
TreeNode* create_node(int val) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 前序遍历 - 递归
void preorder_recursive(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->val);  // 访问根
    preorder_recursive(root->left);   // 遍历左子树
    preorder_recursive(root->right);  // 遍历右子树
}

// 中序遍历 - 递归
void inorder_recursive(TreeNode* root) {
    if (root == NULL) return;
    inorder_recursive(root->left);      // 遍历左子树
    printf("%d ", root->val);  // 访问根
    inorder_recursive(root->right); // 遍历右子树
}

// 后序遍历 - 递归
void postorder_recursive(TreeNode* root) {
    if (root == NULL) return;
    postorder_recursive(root->left);  // 遍历左子树
    postorder_recursive(root->right); // 遍历右子树
    printf("%d ", root->val);  // 访问根
}

// 释放树内存
void free_tree(TreeNode* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    // 构建示例树
    //       1
    //      / \
    //     2   3
    //    / \  /
    //   4   5 6
    
    TreeNode* root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    root->right->left = create_node(6);
    
    printf("树遍历演示:\n\n");
    
    printf("树结构:\n");
    printf("      1\n");
    printf("     / \\\n");
    printf("    2   3\n");
    printf("   / \\  /\n");
    printf("  4   5 6\n\n");
    
    printf("前序遍历 (根-左-右): ");
    preorder_recursive(root);
    printf("\n");
    
    printf("中序遍历 (左-根-右): ");
    inorder_recursive(root);
    printf("\n");
    
    printf("后序遍历 (左-右-根): ");
    postorder_recursive(root);
    printf("\n");
    
    printf("\n遍历特点:\n");
    printf("  前序: 根节点最先访问\n");
    printf("  中序: BST中序遍历得到有序序列\n");
    printf("  后序: 适合删除树（先删除子节点）\n");
    
    free_tree(root);
    return 0;
}
