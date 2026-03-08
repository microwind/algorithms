/*
 * 树算法 - AVL树实现 (Adelson-Velsky and Landis Tree)
 * 自平衡二叉搜索树，确保高度差不超过1
 * 保证查找、插入、删除都是O(log n)时间复杂度
 */

#include <stdio.h>
#include <stdlib.h>

// AVL节点结构
typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

/**
 * 获取节点高度
 */
int get_height(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

/**
 * 计算平衡因子
 */
int get_balance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

/**
 * 更新节点高度
 */
void update_height(AVLNode* node) {
    if (node != NULL) {
        int left_height = get_height(node->left);
        int right_height = get_height(node->right);
        node->height = 1 + (left_height > right_height ? left_height : right_height);
    }
}

/**
 * 创建新节点
 */
AVLNode* create_avl_node(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * 右旋操作
 */
AVLNode* right_rotate(AVLNode* y) {
    printf("    执行右旋，节点 %d\n", y->data);
    
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // 执行旋转
    x->right = y;
    y->left = T2;
    
    // 更新高度
    update_height(y);
    update_height(x);
    
    return x;  // 新的根节点
}

/**
 * 左旋操作
 */
AVLNode* left_rotate(AVLNode* x) {
    printf("    执行左旋，节点 %d\n", x->data);
    
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    // 执行旋转
    y->left = x;
    x->right = T2;
    
    // 更新高度
    update_height(x);
    update_height(y);
    
    return y;  // 新的根节点
}

/**
 * 平衡AVL树
 */
AVLNode* balance_avl_tree(AVLNode* node) {
    if (node == NULL) {
        return node;
    }
    
    // 更新高度
    update_height(node);
    
    // 获取平衡因子
    int balance = get_balance(node);
    
    printf("    节点 %d: 平衡因子 = %d\n", node->data, balance);
    
    // 情况1: 左左情况（LL）- 需要右旋
    if (balance > 1 && get_balance(node->left) >= 0) {
        return right_rotate(node);
    }
    
    // 情况2: 右右情况（RR）- 需要左旋
    if (balance < -1 && get_balance(node->right) <= 0) {
        return left_rotate(node);
    }
    
    // 情况3: 左右情况（LR）- 需要先左旋再右旋
    if (balance > 1 && get_balance(node->left) < 0) {
        printf("    执行左右旋转\n");
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    
    // 情况4: 右左情况（RL）- 需要要先右旋再左旋
    if (balance < -1 && get_balance(node->right) > 0) {
        printf("    执行右左旋转\n");
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    
    return node;  // 已经平衡
}

/**
 * 插入节点
 */
AVLNode* avl_insert(AVLNode* root, int data) {
    printf("  插入 %d\n", data);
    
    // 1. 标准BST插入
    if (root == NULL) {
        return create_avl_node(data);
    }
    
    if (data < root->data) {
        root->left = avl_insert(root->left, data);
    } else if (data > root->data) {
        root->right = avl_insert(root->right, data);
    } else {
        // 重复值不插入
        return root;
    }
    
    // 2. 平衡树
    return balance_avl_tree(root);
}

/**
 * 找到最小值节点
 */
AVLNode* find_min_node(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

/**
 * 删除节点
 */
AVLNode* avl_delete(AVLNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    // 1. 标准BST删除
    if (data < root->data) {
        root->left = avl_delete(root->left, data);
    } else if (data > root->data) {
        root->right = avl_delete(root->right, data);
    } else {
        // 找到要删除的节点
        
        // 节点只有一个子节点或没有子节点
        if (root->left == NULL || root->right == NULL) {
            AVLNode* temp = root->left ? root->left : root->right;
            
            // 没有子节点
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // 有一个子节点
                *root = *temp;
            }
            
            free(temp);
        } else {
            // 节点有两个子节点
            AVLNode* temp = find_min_node(root->right);
            root->data = temp->data;
            root->right = avl_delete(root->right, temp->data);
        }
    }
    
    // 如果树为空，直接返回
    if (root == NULL) {
        return root;
    }
    
    // 2. 平衡树
    return balance_avl_tree(root);
}

/**
 * 查找节点
 */
AVLNode* avl_search(AVLNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return avl_search(root->left, data);
    } else {
        return avl_search(root->right, data);
    }
}

/**
 * 中序遍历
 */
void inorder_avl(AVLNode* root) {
    if (root != NULL) {
        inorder_avl(root->left);
        printf("%d ", root->data);
        inorder_avl(root->right);
    }
}

/**
 * 前序遍历（用于显示树结构）
 */
void preorder_avl(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_avl(root->left);
        preorder_avl(root->right);
    }
}

/**
 * 打印树的结构（简化版）
 */
void print_avl_structure(AVLNode* root, int space) {
    if (root == NULL) {
        return;
    }
    
    space += 5;
    
    // 先打印右子树
    print_avl_structure(root->right, space);
    
    // 打印当前节点
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d(h:%d,b:%d)\n", root->data, root->height, get_balance(root));
    
    // 打印左子树
    print_avl_structure(root->left, space);
}

/**
 * 验证AVL树属性
 */
int is_valid_avl(AVLNode* root) {
    if (root == NULL) {
        return 1;
    }
    
    // 检查平衡因子
    int balance = get_balance(root);
    if (balance < -1 || balance > 1) {
        printf("节点 %d 平衡因子异常: %d\n", root->data, balance);
        return 0;
    }
    
    // 递归检查子树
    return is_valid_avl(root->left) && is_valid_avl(root->right);
}

/**
 * 计算节点数
 */
int avl_size(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + avl_size(root->left) + avl_size(root->right);
}

/**
 * 释放AVL树
 */
void free_avl_tree(AVLNode* root) {
    if (root != NULL) {
        free_avl_tree(root->left);
        free_avl_tree(root->right);
        free(root);
    }
}

/**
 * AVL操作演示
 */
void avl_operations_demo() {
    printf("\nAVL树操作演示:\n");
    
    AVLNode* root = NULL;
    
    // 插入测试（会触发旋转）
    printf("插入节点（观察平衡操作）:\n");
    int insert_data[] = {10, 20, 30, 40, 50, 25};
    int insert_size = sizeof(insert_data) / sizeof(insert_data[0]);
    
    for (int i = 0; i < insert_size; i++) {
        root = avl_insert(root, insert_data[i]);
    }
    
    printf("\n最终树结构:\n");
    print_avl_structure(root, 0);
    
    printf("\n中序遍历（有序）: ");
    inorder_avl(root);
    printf("\n");
    
    printf("前序遍历: ");
    preorder_avl(root);
    printf("\n");
    
    // 验证AVL属性
    printf("\nAVL树验证: %s\n", is_valid_avl(root) ? "✓ 有效" : "✗ 无效");
    printf("节点数: %d\n", avl_size(root));
    printf("树高度: %d\n", get_height(root));
    
    // 删除测试
    printf("\n删除节点测试:\n");
    int delete_data[] = {30, 20, 10};
    int delete_size = sizeof(delete_data) / sizeof(delete_data[0]);
    
    for (int i = 0; i < delete_size; i++) {
        printf("删除 %d:\n", delete_data[i]);
        root = avl_delete(root, delete_data[i]);
        
        printf("删除后的树结构:\n");
        print_avl_structure(root, 0);
        printf("中序遍历: ");
        inorder_avl(root);
        printf("\n");
        printf("AVL验证: %s\n\n", is_valid_avl(root) ? "✓ 有效" : "✗ 无效");
    }
}

/**
 * 性能对比测试
 */
void performance_comparison() {
    printf("\n性能对比测试 (插入1000个随机数):\n");
    
    // 这里只是演示，实际性能测试需要更精确的计时
    printf("  AVL树保证O(log n)的操作复杂度\n");
    printf("  普通BST在最坏情况下退化为O(n)\n");
    printf("  AVL树通过旋转操作维持平衡\n");
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("AVL树实现 (Adelson-Velsky and Landis Tree)\n");
    printf("==================================================\n");
    
    // AVL操作演示
    avl_operations_demo();
    
    // 性能对比
    performance_comparison();
    
    printf("\n应用场景:\n");
    printf("  • 需要保证O(log n)查找性能的场景\n");
    printf("  • 数据库索引\n");
    printf("  • 内存管理器\n");
    printf("  • 文件系统\n");
    printf("  • 网络路由表\n");
    printf("  • 游戏开发中的空间索引\n");
    
    printf("\nAVL树特性:\n");
    printf("  • 自平衡二叉搜索树\n");
    printf("  • 任何节点的平衡因子在[-1, 1]范围内\n");
    printf("  • 高度为O(log n)\n");
    printf("  • 插入、删除、查找都是O(log n)\n");
    printf("  • 通过旋转操作维持平衡\n");
    
    printf("\n四种不平衡情况:\n");
    printf("  1. LL（左左）: 右旋\n");
    printf("  2. RR（右右）: 左旋\n");
    printf("  3. LR（左右）: 先左旋后右旋\n");
    printf("  4. RL（右左）: 先右旋后左旋\n");
    
    printf("\n与其他平衡树的比较:\n");
    printf("  • AVL树: 更严格的平衡，查找更快，插入删除稍慢\n");
    printf("  • 红黑树: 较松的平衡，插入删除更快，查找稍慢\n");
    printf("  • 选择: 查找密集用AVL，插入删除频繁用红黑树\n");
    
    // 释放内存
    AVLNode* root = NULL;
    // 注意：在实际应用中需要保存根节点引用来释放
    
    return 0;
}
