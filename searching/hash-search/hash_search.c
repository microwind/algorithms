/*
 * 哈希查找 - Hash Search
 * 使用哈希表实现O(1)查找
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// 哈希表节点
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// 哈希表
typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

// 哈希函数
int hash(int key) {
    return key % TABLE_SIZE;
}

// 创建哈希表
HashTable* create_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

// 插入键值对
void insert(HashTable* table, int key, int value) {
    int index = hash(key);
    
    // 检查是否已存在
    Node* current = table->buckets[index];
    while (current) {
        if (current->key == key) {
            current->value = value;  // 更新值
            return;
        }
        current = current->next;
    }
    
    // 创建新节点
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

// 哈希查找
int search(HashTable* table, int key, int* found) {
    int index = hash(key);
    Node* current = table->buckets[index];
    
    while (current) {
        if (current->key == key) {
            *found = 1;
            return current->value;
        }
        current = current->next;
    }
    
    *found = 0;
    return -1;
}

// 显示哈希表
void display(HashTable* table) {
    printf("哈希表内容:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("  桶 %d: ", i);
        Node* current = table->buckets[i];
        if (!current) {
            printf("空");
        }
        while (current) {
            printf("(%d:%d)", current->key, current->value);
            if (current->next) printf(" -> ");
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable* table = create_table();
    
    printf("哈希查找演示:\n\n");
    
    // 插入数据
    int keys[] = {5, 15, 25, 35, 45, 55};
    int values[] = {100, 200, 300, 400, 500, 600};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    printf("插入数据:\n");
    for (int i = 0; i < n; i++) {
        insert(table, keys[i], values[i]);
        printf("  key=%d, value=%d, hash=%d\n", keys[i], values[i], hash(keys[i]));
    }
    
    printf("\n");
    display(table);
    
    // 查找测试
    printf("\n查找测试:\n");
    int search_keys[] = {25, 45, 100};
    
    for (int i = 0; i < 3; i++) {
        int found;
        int value = search(table, search_keys[i], &found);
        
        if (found) {
            printf("  查找 %d: 找到，value=%d\n", search_keys[i], value);
        } else {
            printf("  查找 %d: 未找到\n", search_keys[i]);
        }
    }
    
    printf("\n性能分析:\n");
    printf("  • 平均时间复杂度: O(1)\n");
    printf("  • 最坏时间复杂度: O(n)（所有键冲突）\n");
    printf("  • 空间复杂度: O(n)\n");
    
    return 0;
}
