#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10
#define LOAD_FACTOR 0.75

// 哈希表的元素结构体
typedef struct Entry {
    char *key;
    int value;
    struct Entry *next; // 用于链表解决冲突
} Entry;

// 哈希表结构体
typedef struct {
    Entry **table;    // 哈希表数组
    int size;         // 哈希表中存储的元素数量
    int capacity;     // 哈希表的容量
} HashMap;

// 哈希函数（使用简单的字符串哈希函数）
unsigned int hash(const char *key, int capacity) {
    unsigned int hashValue = 0;
    while (*key) {
        hashValue = (hashValue * 31) + *key;
        key++;
    }
    return hashValue % capacity;
}

// 初始化 HashMap
void initHashMap(HashMap *map) {
    map->size = 0;
    map->capacity = INITIAL_CAPACITY;
    map->table = (Entry **)malloc(sizeof(Entry *) * map->capacity);
    for (int i = 0; i < map->capacity; i++) {
        map->table[i] = NULL;
    }
}

// 重新分配容量，扩容 HashMap
void resizeMap(HashMap *map) {
    int newCapacity = map->capacity * 2;
    Entry **newTable = (Entry **)malloc(sizeof(Entry *) * newCapacity);

    // 初始化新表
    for (int i = 0; i < newCapacity; i++) {
        newTable[i] = NULL;
    }

    // 迁移原表数据到新表
    for (int i = 0; i < map->capacity; i++) {
        Entry *entry = map->table[i];
        while (entry) {
            int newIndex = hash(entry->key, newCapacity);
            Entry *newEntry = (Entry *)malloc(sizeof(Entry));
            newEntry->key = strdup(entry->key);
            newEntry->value = entry->value;
            newEntry->next = newTable[newIndex];
            newTable[newIndex] = newEntry;

            entry = entry->next;
        }
    }

    // 释放原表并更新哈希表
    for (int i = 0; i < map->capacity; i++) {
        Entry *entry = map->table[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(map->table);
    map->table = newTable;
    map->capacity = newCapacity;
}

// 插入键值对（如果存在则更新）
void put(HashMap *map, const char *key, int value) {
    // 判断是否需要扩容
    if ((float)map->size / map->capacity > LOAD_FACTOR) {
        resizeMap(map);
    }

    int index = hash(key, map->capacity);
    Entry *entry = map->table[index];

    // 遍历链表，检查是否已经存在相同的键
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;  // 更新值
            return;
        }
        entry = entry->next;
    }

    // 如果没有找到相同的键，插入新键值对
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    newEntry->key = strdup(key);
    newEntry->value = value;
    newEntry->next = map->table[index];
    map->table[index] = newEntry;
    map->size++;
}

// 查找键
int get(HashMap *map, const char *key) {
    int index = hash(key, map->capacity);
    Entry *entry = map->table[index];

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return -1;  // 返回 -1 表示未找到
}

// 删除键
void delete(HashMap *map, const char *key) {
    int index = hash(key, map->capacity);
    Entry *entry = map->table[index];
    Entry *prev = NULL;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->table[index] = entry->next;
            }
            free(entry->key);
            free(entry);
            map->size--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// 释放哈希表
void freeHashMap(HashMap *map) {
    for (int i = 0; i < map->capacity; i++) {
        Entry *entry = map->table[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(map->table);
}

// 测试
int main() {
    HashMap map;
    initHashMap(&map);

    put(&map, "apple", 10);
    put(&map, "banana", 20);
    put(&map, "orange", 30);

    printf("apple: %d\n", get(&map, "apple"));
    printf("banana: %d\n", get(&map, "banana"));
    printf("grape: %d (not found)\n", get(&map, "grape"));

    delete(&map, "banana");
    printf("banana after delete: %d\n", get(&map, "banana"));

    freeHashMap(&map);
    return 0;
}

/*
jarry@MacBook-Pro hash % gcc hash_map.c
jarry@MacBook-Pro hash % ./a.out 
apple: 10
banana: 20
grape: -1 (not found)
banana after delete: -1
*/