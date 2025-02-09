#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10 // 初始容量

// Map 结构体
typedef struct
{
    char *key;
    int value;
} Entry;

typedef struct
{
    Entry *entries;
    int size;
    int capacity;
} Map;

// 初始化 Map
void initMap(Map *map)
{
    map->size = 0;
    map->capacity = INITIAL_CAPACITY;
    map->entries = (Entry *)malloc(map->capacity * sizeof(Entry));
}

// 重新分配容量
void resizeMap(Map *map, int newCapacity)
{
    map->capacity = newCapacity;
    map->entries = (Entry *)realloc(map->entries, map->capacity * sizeof(Entry));
}

// 插入键值对（如果存在则更新）
void put(Map *map, const char *key, int value)
{
    for (int i = 0; i < map->size; i++)
    {
        if (strcmp(map->entries[i].key, key) == 0)
        {
            map->entries[i].value = value; // 更新值
            return;
        }
    }
    if (map->size >= map->capacity)
    {
        resizeMap(map, map->capacity * 2);
    }
    map->entries[map->size].key = strdup(key);
    map->entries[map->size].value = value;
    map->size++;
}

// 查找键
int get(Map *map, const char *key, int *found)
{
    for (int i = 0; i < map->size; i++)
    {
        if (strcmp(map->entries[i].key, key) == 0)
        {
            *found = 1;
            return map->entries[i].value;
        }
    }
    *found = 0;
    return -1; // 未找到
}

// 删除键
void delete(Map *map, const char *key)
{
    for (int i = 0; i < map->size; i++)
    {
        if (strcmp(map->entries[i].key, key) == 0)
        {
            free(map->entries[i].key);
            for (int j = i; j < map->size - 1; j++)
            {
                map->entries[j] = map->entries[j + 1];
            }
            map->size--;
            return;
        }
    }
}

// 释放 Map
void freeMap(Map *map)
{
    for (int i = 0; i < map->size; i++)
    {
        free(map->entries[i].key);
    }
    free(map->entries);
}

// 测试
int main()
{
    Map map;
    initMap(&map);

    put(&map, "apple", 10);
    put(&map, "banana", 20);
    put(&map, "orange", 30);

    int found;
    printf("apple: %d\n", get(&map, "apple", &found));
    printf("banana: %d\n", get(&map, "banana", &found));
    printf("grape: %d (not found)\n", get(&map, "grape", &found));

    delete (&map, "banana");
    printf("banana after delete: %d\n", get(&map, "banana", &found));

    freeMap(&map);
    return 0;
}

/*
jarry@MacBook-Pro map % gcc map.c
jarry@MacBook-Pro map % ./a.out
apple: 10
banana: 20
grape: -1 (not found)
banana after delete: -1
*/
