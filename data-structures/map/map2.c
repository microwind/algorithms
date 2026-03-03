#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

// 键值对结构体
typedef struct
{
  char *key;
  int value;
} Entry;

// 哈希表结构体
typedef struct
{
  Entry *entries; // 存储键值对的数组
  int *indexMap;  // 键到索引的映射
  int size;       // 键值对的数量
  int capacity;   // 容量
} HashMap;

// 初始化 HashMap
void initHashMap(HashMap *map)
{
  map->size = 0;
  map->capacity = INITIAL_CAPACITY;
  map->entries = (Entry *)malloc(sizeof(Entry) * map->capacity);
  map->indexMap = (int *)malloc(sizeof(int) * map->capacity);
  for (int i = 0; i < map->capacity; i++)
  {
    map->indexMap[i] = -1;
  }
}

// 扩容
void resizeMap(HashMap *map)
{
  map->capacity *= 2;
  map->entries = (Entry *)realloc(map->entries, sizeof(Entry) * map->capacity);
  map->indexMap = (int *)realloc(map->indexMap, sizeof(int) * map->capacity);
}

// 插入键值对
void put(HashMap *map, const char *key, int value)
{
  // 查找键的索引
  for (int i = 0; i < map->size; i++)
  {
    if (strcmp(map->entries[i].key, key) == 0)
    {
      // 更新值
      map->entries[i].value = value;
      return;
    }
  }

  // 如果容量已满，扩容
  if (map->size >= map->capacity)
  {
    resizeMap(map);
  }

  // 插入新键值对
  map->entries[map->size].key = strdup(key);
  map->entries[map->size].value = value;
  map->indexMap[map->size] = map->size;
  map->size++;
}

// 查找键
int get(HashMap *map, const char *key)
{
  for (int i = 0; i < map->size; i++)
  {
    if (strcmp(map->entries[i].key, key) == 0)
    {
      return map->entries[i].value;
    }
  }
  return -1; // 未找到
}

// 删除键
void delete(HashMap *map, const char *key)
{
  for (int i = 0; i < map->size; i++)
  {
    if (strcmp(map->entries[i].key, key) == 0)
    {
      free(map->entries[i].key);
      for (int j = i; j < map->size - 1; j++)
      {
        map->entries[j] = map->entries[j + 1];
        map->indexMap[j] = map->indexMap[j + 1];
      }
      map->size--;
      return;
    }
  }
}

// 判断键是否存在
int has(HashMap *map, const char *key)
{
  for (int i = 0; i < map->size; i++)
  {
    if (strcmp(map->entries[i].key, key) == 0)
    {
      return 1;
    }
  }
  return 0;
}

// 获取键值对数量
int getSize(HashMap *map)
{
  return map->size;
}

// 清空所有数据
void clear(HashMap *map)
{
  for (int i = 0; i < map->size; i++)
  {
    free(map->entries[i].key);
  }
  free(map->entries);
  free(map->indexMap);
  map->size = 0;
}

// 遍历所有键值对
void forEach(HashMap *map, void (*callback)(int, const char *))
{
  for (int i = 0; i < map->size; i++)
  {
    callback(map->entries[i].value, map->entries[i].key);
  }
}

// 回调函数示例
void printEntry(int value, const char *key)
{
  printf("%s: %d\n", key, value);
}

// 测试
int main()
{
  HashMap map;
  initHashMap(&map);

  put(&map, "apple", 10);
  put(&map, "banana", 20);
  put(&map, "orange", 30);

  printf("apple: %d\n", get(&map, "apple"));
  printf("banana: %d\n", get(&map, "banana"));
  printf("grape: %d\n", get(&map, "grape"));

  delete (&map, "banana");
  printf("banana after delete: %d\n", get(&map, "banana"));

  forEach(&map, printEntry);

  clear(&map);
  return 0;
}

/*
jarry@MacBook-Pro map % gcc map2.c
jarry@MacBook-Pro map % ./a.out
apple: 10
banana: 20
grape: -1
banana after delete: -1
apple: 10
orange: 30
*/