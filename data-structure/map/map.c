#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义Map结构体
typedef struct Map {
    char **keys;  // 存储key的数组
    int *values;  // 存储value的数组
    int size;     // 元素数量
} Map;

// 初始化Map
void map_init(Map *map) {
    map->keys = NULL;
    map->values = NULL;
    map->size = 0;
}

// 向Map中插入元素
void map_put(Map *map, char *key, int value) {
    // 查找是否已经存在该key
    for (int i = 0; i < map->size; i++) {
        if (strcmp(map->keys[i], key) == 0) {
            // 如果已经存在，则更新对应的value
            map->values[i] = value;
            return;
        }
    }
    // 如果不存在，则在末尾插入新元素
    map->keys = (char **)realloc(map->keys, sizeof(char *) * (map->size + 1));
    map->values = (int *)realloc(map->values, sizeof(int) * (map->size + 1));
    map->keys[map->size] = strdup(key);
    map->values[map->size] = value;
    map->size++;
}

// 从Map中删除元素
void map_remove(Map *map, char *key) {
    int i;
    for (i = 0; i < map->size; i++) {
        if (strcmp(map->keys[i], key) == 0) {
            // 找到对应的key后，将它和末尾元素互换，然后删除末尾元素
            free(map->keys[i]);
            map->keys[i] = map->keys[map->size - 1];
            map->values[i] = map->values[map->size - 1];
            map->keys = (char **)realloc(map->keys, sizeof(char *) * (map->size - 1));
            map->values = (int *)realloc(map->values, sizeof(int) * (map->size - 1));
            map->size--;
            return;
        }
    }
}

// 从Map中查找元素
int map_get(Map *map, char *key) {
    int i;
    for (i = 0; i < map->size; i++) {
        if (strcmp(map->keys[i], key) == 0) {
            return map->values[i];
        }
    }
    return -1;
}

// 清空Map
void map_clear(Map *map) {
    int i;
    for (i = 0; i < map->size; i++) {
        free(map->keys[i]);
    }
    free(map->keys);
    free(map->values);
    map->size = 0;
}

/* Test */

// 测试Map的函数
int main() {
    Map map;
    map_init(&map);
    map_put(&map, "apple", 1);
    map_put(&map, "banana", 2);
    map_put(&map, "cat", 3);
    printf("apple: %d\n", map_get(&map, "apple"));
    printf("banana: %d\n", map_get(&map, "banana"));
    printf("cat: %d\n", map_get(&map, "cat"));
    return 0;
}

// result


