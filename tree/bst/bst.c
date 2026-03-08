/*
 * 树算法 - 二叉搜索树实现 (Binary Search Tree)
 * 有序二叉树，左子树 < 根节点 < 右子树
 * 用于快速查找、插入、删除
 */

#include <stdio.h>
#include <stdlib.h>

// BST节点结构
typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

/**
 * 创建新节点
 */
BSTNode* create_bst_node(int data) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * 插入节点到BST
 */
BSTNode* bst_insert(BSTNode* root, int data) {
    // 如果树为空，创建新节点
    if (root == NULL) {
        return create_bst_node(data);
    }
    
    // 递归插入到左子树或右子树
    if (data < root->data) {
        root->left = bst_insert(root->left, data);
    } else if (data > root->data) {
        root->right = bst_insert(root->right, data);
    }
    // 如果data等于root->data，不做任何操作（避免重复）
    
    return root;
}

/**
 * 查找节点
 */
BSTNode* bst_search(BSTNode* root, int data) {
    // 如果树为空或找到目标节点
    if (root == NULL || root->data == data) {
        return root;
    }
    
    // 递归查找左子树或右子树
    if (data < root->data) {
        return bst_search(root->left, data);
    } else {
        return bst_search(root->right, data);
    }
}

/**
 * 找到最小值节点（最左节点）
 */
BSTNode* find_min(BSTNode* root) {
    if (root == NULL) {
        return NULL;
    }
    
    while (root->left != NULL) {
        root = root->left;
    }
    
    return root;
}

/**
 * 找到最大值节点（最右节点）
 */
BSTNode* find_max(BSTNode* root) {
    if (root == NULL) {
        return NULL;
    }
    
    while (root->right != NULL) {
        root = root->right;
    }
    
    return root;
}

/**
 * 删除节点
 */
BSTNode* bst_delete(BSTNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    // 查找要删除的节点
    if (data < root->data) {
        root->left = bst_delete(root->left, data);
    } else if (data > root->data) {
        root->right = bst_delete(root->right, data);
    } else {
        // 找到要删除的节点
        
        // 情况1: 节点只有一个子节点或没有子节点
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // 情况2: 节点有两个子节点
        // 找到右子树的最小值节点（中序后继）
        BSTNode* temp = find_min(root->right);
        
        // 用中序后继的值替换当前节点的值
        root->data = temp->data;
        
        // 删除右子树中的中序后继节点
        root->right = bst_delete(root->right, temp->data);
    }
    
    return root;
}

/**
 * 中序遍历（左-根-右）：输出有序序列
 */
void inorder_traversal(BSTNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

/**
 * 前序遍历（根-左-右）
 */
void preorder_traversal(BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

/**
 * 后序遍历（左-右-根）
 */
void postorder_traversal(BSTNode* root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

/**
 * 计算树的高度
 */
int tree_height(BSTNode* root) {
    if (root == NULL) {
        return 0;
    }
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

/**
 * 计算节点总数
 */
int tree_size(BSTNode* root) {
    if (root == NULL) {
        return 0;
    }
    
    return 1 + tree_size(root->left) + tree_size(root->right);
}

/**
 * 检查是否为有效的BST
 */
int is_valid_bst(BSTNode* root, int min_val, int max_val) {
    if (root == NULL) {
        return 1;
    }
    
    // 当前节点的值必须在有效范围内
    if (root->data <= min_val || root->data >= max_val) {
        return 0;
    }
    
    // 递归检查左右子树
    return is_valid_bst(root->left, min_val, root->data) &&
           is_valid_bst(root->right, root->data, max_val);
}

/**
 * 打印树的结构（简化版）
 */
void print_tree_structure(BSTNode* root, int space) {
    if (root == NULL) {
        return;
    }
    
    // 增加缩进
    space += 5;
    
    // 先打印右子树
    print_tree_structure(root->right, space);
    
    // 打印当前节点
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    // 打印左子树
    print_tree_structure(root->left, space);
}

/**
 * 释放树的内存
 */
void free_tree(BSTNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

/**
 * 演示BST操作
 */
void bst_operations_demo() {
    printf("\nBST操作演示:\n");
    
    BSTNode* root = NULL;
    int data[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(data) / sizeof(data[0]);
    
    // 插入节点
    printf("  插入节点: ");
    for (int i = 0; i < n; i++) {
        root = bst_insert(root, data[i]);
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // 打印树结构
    printf("  树结构:\n");
    print_tree_structure(root, 0);
    
    // 遍历
    printf("\n  中序遍历（有序）: ");
    inorder_traversal(root);
    printf("\n");
    
    printf("  前序遍历: ");
    preorder_traversal(root);
    printf("\n");
    
    printf("  后序遍历: ");
    postorder_traversal(root);
    printf("\n");
    
    // 查找测试
    int search_values[] = {40, 55, 80};
    int search_count = sizeof(search_values) / sizeof(search_values[0]);
    
    printf("\n  查找测试:\n");
    for (int i = 0; i < search_count; i++) {
        BSTNode* result = bst_search(root, search_values[i]);
        printf("    查找 %d: %s\n", search_values[i], 
               result ? "找到" : "未找到");
    }
    
    // 删除测试
    int delete_values[] = {20, 30, 50};
    int delete_count = sizeof(delete_values) / sizeof(delete_values[0]);
    
    printf("\n  删除测试:\n");
    for (int i = 0; i < delete_count; i++) {
        printf("    删除 %d 后的中序遍历: ", delete_values[i]);
        root = bst_delete(root, delete_values[i]);
        inorder_traversal(root);
        printf("\n");
    }
    
    // 树的统计信息
    printf("\n  树的统计信息:\n");
    printf("    高度: %d\n", tree_height(root));
    printf("    节点数: %d\n", tree_size(root));
    printf("    有效性: %s\n", 
           is_valid_bst(root, INT_MIN, INT_MAX) ? "有效BST" : "无效BST");
}

/**
 * 性能测试
 */
void performance_test() {
    printf("\n性能测试:\n");
    
    BSTNode* root = NULL;
    int test_size = 1000;
    
    // 插入测试
    printf("  插入 %d 个元素...\n", test_size);
    for (int i = 0; i < test_size; i++) {
        root = bst_insert(root, rand() % 10000);
    }
    
    printf("    树高度: %d\n", tree_height(root));
    printf("    节点数: %d\n", tree_size(root));
    
    // 查找测试
    printf("  查找测试...\n");
    int found_count = 0;
    for (int i = 0; i < 100; i++) {
        int target = rand() % 10000;
        if (bst_search(root, target) != NULL) {
            found_count++;
        }
    }
    printf("    100次随机查找，找到 %d 个\n", found_count);
    
    free_tree(root);
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("二叉搜索树实现 (Binary Search Tree)\n");
    printf("==================================================\n");
    
    // 基本操作演示
    bst_operations_demo();
    
    // 性能测试
    performance_test();
    
    printf("\n应用场景:\n");
    printf("  • 快速查找数据\n");
    printf("  • 动态集合维护\n");
    printf("  • 有序数据存储\n");
    printf("  • 范围查询\n");
    printf("  • 数据库索引\n");
    printf("  • 集合和映射的实现\n");
    
    printf("\n复杂度分析:\n");
    printf("  • 平均情况:\n");
    printf("    - 查找: O(log n)\n");
    printf("    - 插入: O(log n)\n");
    printf("    - 删除: O(log n)\n");
    printf("  • 最坏情况（退化为链表）:\n");
    printf("    - 查找: O(n)\n");
    printf("    - 插入: O(n)\n");
    printf("    - 删除: O(n)\n");
    printf("  • 空间复杂度: O(n)\n");
    
    printf("\n改进版本:\n");
    printf("  • AVL树：自平衡，保证O(log n)\n");
    printf("  • 红黑树：自平衡，保证O(log n)\n");
    printf("  • B树：多路搜索树，适合磁盘存储\n");
    
    return 0;
}
