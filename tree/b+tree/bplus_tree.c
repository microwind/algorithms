/*
 * B+树 - 多路搜索树简单实现
 * 支持高效的范围查询
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 3  // B+树的阶数

// B+树节点结构
typedef struct BPlusNode {
    int keys[2 * ORDER - 1];
    struct BPlusNode* children[2 * ORDER];
    struct BPlusNode* next;  // 叶节点链表指针
    int num_keys;
    bool is_leaf;
} BPlusNode;

// 创建新节点
BPlusNode* create_node(bool is_leaf) {
    BPlusNode* node = (BPlusNode*)malloc(sizeof(BPlusNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->next = NULL;
    
    for (int i = 0; i < 2 * ORDER; i++) {
        node->children[i] = NULL;
    }
    
    return node;
}

// 查找应该包含key的叶节点
BPlusNode* find_leaf(BPlusNode* root, int key) {
    if (root->is_leaf) {
        return root;
    }
    
    int i = 0;
    while (i < root->num_keys && key > root->keys[i]) {
        i++;
    }
    
    return find_leaf(root->children[i], key);
}

// 在叶节点中搜索
bool search(BPlusNode* root, int key) {
    BPlusNode* leaf = find_leaf(root, key);
    
    for (int i = 0; i < leaf->num_keys; i++) {
        if (leaf->keys[i] == key) {
            return true;
        }
    }
    
    return false;
}

// 分裂子节点
void split_child(BPlusNode* parent, int i, BPlusNode* child) {
    BPlusNode* new_child = create_node(child->is_leaf);
    int mid = ORDER - 1;
    
    // 复制后半部分键到新节点
    new_child->num_keys = ORDER - 1;
    for (int j = 0; j < ORDER - 1; j++) {
        new_child->keys[j] = child->keys[j + mid + 1];
    }
    
    // 如果不是叶节点，复制子节点指针
    if (!child->is_leaf) {
        for (int j = 0; j < ORDER; j++) {
            new_child->children[j] = child->children[j + mid + 1];
        }
    } else {
        new_child->next = child->next;
        child->next = new_child;
    }
    
    child->num_keys = mid;
    
    // 在父节点中插入中间键
    for (int j = parent->num_keys; j > i; j--) {
        parent->keys[j] = parent->keys[j - 1];
        parent->children[j + 1] = parent->children[j];
    }
    
    parent->keys[i] = child->keys[mid];
    parent->children[i + 1] = new_child;
    parent->num_keys++;
}

// 在非满节点中插入
void insert_non_full(BPlusNode* node, int key) {
    if (node->is_leaf) {
        // 叶节点直接插入
        int i = node->num_keys - 1;
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // 内部节点
        int i = node->num_keys - 1;
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        
        if (node->children[i]->num_keys == 2 * ORDER - 1) {
            split_child(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        
        insert_non_full(node->children[i], key);
    }
}

// 插入键值
BPlusNode* insert(BPlusNode* root, int key) {
    if (root->num_keys == 2 * ORDER - 1) {
        BPlusNode* new_root = create_node(false);
        new_root->children[0] = root;
        split_child(new_root, 0, root);
        insert_non_full(new_root, key);
        return new_root;
    } else {
        insert_non_full(root, key);
        return root;
    }
}

// 中序遍历
void traverse(BPlusNode* node) {
    if (node->is_leaf) {
        for (int i = 0; i < node->num_keys; i++) {
            printf("%d ", node->keys[i]);
        }
    } else {
        for (int i = 0; i < node->num_keys; i++) {
            traverse(node->children[i]);
            printf("%d ", node->keys[i]);
        }
        traverse(node->children[node->num_keys]);
    }
}

// 释放树内存
void free_tree(BPlusNode* node) {
    if (node == NULL) return;
    
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            free_tree(node->children[i]);
        }
    }
    
    free(node);
}

int main() {
    printf("B+树演示 (阶数=%d)\n\n", ORDER);
    
    BPlusNode* root = create_node(true);
    
    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(values) / sizeof(values[0]);
    
    printf("插入数据: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert(root, values[i]);
    }
    printf("\n\n");
    
    printf("中序遍历结果: ");
    traverse(root);
    printf("\n\n");
    
    // 搜索测试
    printf("搜索测试:\n");
    int test_keys[] = {6, 15, 30};
    for (int i = 0; i < 3; i++) {
        bool found = search(root, test_keys[i]);
        printf("  查找 %d: %s\n", test_keys[i], found ? "找到" : "未找到");
    }
    
    printf("\nB+树特点:\n");
    printf("  • 所有数据在叶节点\n");
    printf("  • 叶节点形成有序链表\n");
    printf("  • 适合范围查询和磁盘存储\n");
    
    free_tree(root);
    return 0;
}
