#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16  // 初始哈希表容量
#define LOAD_FACTOR 0.75      // 负载因子

// 哈希表节点结构
typedef struct SetNode {
    void *key;               // 存储的键（泛型指针）
    struct SetNode *next;    // 指向下一个节点（用于哈希冲突）
} SetNode;

// Set 结构体
typedef struct {
    SetNode **buckets;       // 哈希桶数组
    size_t capacity;         // 哈希表容量
    size_t size;             // 当前元素个数
    unsigned int (*hash_func)(void *key);  // 哈希函数
    int (*equals_func)(void *a, void *b);  // 比较函数
} Set;

// FNV-1a 哈希函数
unsigned int fnv_hash_func(void *key) {
    unsigned char *str = (unsigned char *)key;
    unsigned int hash = 2166136261u;
    while (*str) {
        hash ^= (unsigned int)(*str++);
        hash *= 16777619;
    }
    return hash;
}

// 默认比较函数（假设 key 是整数）
int default_equals_func(void *a, void *b) {
    return *(int *)a == *(int *)b;  // 比较值本身
}

// 创建 Set 并初始化
Set *set_create(size_t capacity, unsigned int (*hash_func)(void*), int (*equals_func)(void*, void*)) {
    Set *set = malloc(sizeof(Set));
    set->capacity = capacity;
    set->size = 0;
    set->buckets = calloc(set->capacity, sizeof(SetNode*));
    set->hash_func = hash_func ? hash_func : fnv_hash_func;
    set->equals_func = equals_func ? equals_func : default_equals_func;
    return set;
}

// 扩容 Set
void set_resize(Set *set) {
    size_t new_capacity = set->capacity * 2;
    SetNode **new_buckets = calloc(new_capacity, sizeof(SetNode*));

    // 重新哈希所有元素
    for (size_t i = 0; i < set->capacity; i++) {
        SetNode *node = set->buckets[i];
        while (node) {
            unsigned int index = set->hash_func(node->key) % new_capacity;
            SetNode *next_node = node->next;
            node->next = new_buckets[index];
            new_buckets[index] = node;
            node = next_node;
        }
    }

    // 释放旧的桶数组并更新容量
    free(set->buckets);
    set->buckets = new_buckets;
    set->capacity = new_capacity;
}

// 添加元素到 Set
void set_add(Set *set, void *key) {
    // 判断是否需要扩容
    if ((float)set->size / set->capacity > LOAD_FACTOR) {
        set_resize(set);  // 扩容
    }

    unsigned int index = set->hash_func(key) % set->capacity;
    SetNode *node = set->buckets[index];

    // 判断是否存在
    if (node) {
        printf("Exist node: index=%u key=%d value=%d\n", index, *(int *)key, *(int *)node->key);
    }

    // 查找桶中是否已经有相同的元素
    while (node) {
        // 如果找到了相同的元素，则返回
        if (set->equals_func(node->key, key)) {
            return;
        }
        node = node->next;
    }

    // 没有找到相同的元素，进行插入
    node = malloc(sizeof(SetNode));
    node->key = malloc(sizeof(int));  // 为 key 分配内存
    memcpy(node->key, key, sizeof(int));  // 深拷贝 key
    node->next = set->buckets[index];
    set->buckets[index] = node;
    set->size++;

    // 打印调试信息：打印插入后的 node
    printf("Adding node: index=%u key=%d value=%d\n", index, *(int *)key, *(int *)node->key);
}


// 检查元素是否在 Set 中
int set_contains(Set *set, void *key) {
    unsigned int index = set->hash_func(key) % set->capacity;
    SetNode *node = set->buckets[index];
    while (node) {
        if (set->equals_func(node->key, key)) return 1;
        node = node->next;
    }
    return 0;
}

// 从 Set 中删除元素
void set_remove(Set *set, void *key) {
    unsigned int index = set->hash_func(key) % set->capacity;
    SetNode *node = set->buckets[index], *prev = NULL;
    while (node) {
        if (set->equals_func(node->key, key)) {
            if (prev) prev->next = node->next;
            else set->buckets[index] = node->next;
            free(node);
            set->size--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

// 获取 Set 中的元素个数
size_t set_size(Set *set) {
    return set->size;
}

// 释放 Set 结构体的内存
void set_destroy(Set *set) {
    for (size_t i = 0; i < set->capacity; i++) {
        SetNode *node = set->buckets[i];
        while (node) {
            SetNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(set->buckets);
    free(set);
}

// 遍历 Set 并打印元素
void set_print(Set *set, void (*print_func)(void *)) {
    for (size_t i = 0; i < set->capacity; i++) {
        SetNode *node = set->buckets[i];
        while (node) {
            print_func(node->key);
            node = node->next;
        }
    }
    printf("\n");
}

// 打印整数的辅助函数
void print_int(void *key) {
    printf("%d ", *(int *)key);
}

int main() {
    // 创建一个 Set
    Set *set = set_create(INITIAL_CAPACITY, NULL, NULL);
    int values[] = {10, 20, 20, 30, 40, 40, 50};
    
    // 得到数组长度
    int len = sizeof(values) / sizeof(values[0]);

    // 添加元素
    for (int i = 0; i < len; i++) {
        set_add(set, &values[i]);
    }
    
    // 打印 Set 内容
    set_print(set, print_int);
    
    // 检查元素是否存在
    printf("Contains 30? %d\n", set_contains(set, &values[2]));
    
    // 删除元素
    set_remove(set, &values[2]);
    set_print(set, print_int);
    
    // 释放 Set
    set_destroy(set);
    return 0;
}

/*
jarry@MacBook-Pro set % gcc set.c
jarry@MacBook-Pro set % ./a.out 
Adding node: index=13 key=10 value=10
Adding node: index=3 key=20 value=20
Exist node: index=3 key=20 value=20
Adding node: index=1 key=30 value=30
Adding node: index=7 key=40 value=40
Exist node: index=7 key=40 value=40
Adding node: index=5 key=50 value=50
30 20 50 40 10 
Contains 30? 1
30 50 40 10 
*/
