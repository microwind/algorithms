#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

// 定义结构体 List
typedef struct {
    int *data;
    int size;
    int capacity;
} List;

// 初始化 List
List* createList() {
    List* list = (List*)malloc(sizeof(List));
    list->capacity = INITIAL_CAPACITY;
    list->data = (int*)malloc(list->capacity * sizeof(int));
    list->size = 0;
    return list;
}

// 扩展 List 容量
void resizeList(List* list, int newCapacity) {
    // 只在新容量大于当前容量时才扩展
    if (newCapacity > list->capacity) {
        list->capacity = newCapacity;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
    }
}

// 添加元素
void addElement(List* list, int value) {
    // 如果当前元素个数等于容量，扩展数组
    if (list->size == list->capacity) {
        resizeList(list, list->capacity * 2);  // 容量翻倍
    }
    list->data[list->size] = value;
    list->size++;
}

// 删除最后一个元素
void removeElement(List* list) {
    if (list->size > 0) {
        list->size--;
    }
}

// 获取指定索引的元素
int getElement(List* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of range\n");
        exit(1);
    }
    return list->data[index];
}

// 打印所有元素
void printList(List* list) {
    printf("List: ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// 获取 List 的大小
int getSize(List* list) {
    return list->size;
}

// 获取 List 的容量
int getCapacity(List* list) {
    return list->capacity;
}

// 释放 List 内存
void freeList(List* list) {
    free(list->data);
    free(list);
}

int main() {
    // 创建 List
    List* list = createList();

    // 添加元素
    addElement(list, 10);
    addElement(list, 20);
    addElement(list, 30);
    addElement(list, 40);

    // 打印列表
    printList(list);  // 输出：List: 10 20 30 40

    // 获取元素
    printf("Element at index 2: %d\n", getElement(list, 2));  // 输出：Element at index 2: 30

    // 删除最后一个元素
    removeElement(list);
    printList(list);  // 输出：List: 10 20 30

    // 获取大小和容量
    printf("Size: %d\n", getSize(list));  // 输出：Size: 3
    printf("Capacity: %d\n", getCapacity(list));  // 输出：Capacity: 10

    // 调整容量
    resizeList(list, 20);  // 设置新的容量为 20
    printf("New Capacity: %d\n", getCapacity(list));  // 输出：New Capacity: 20

    // 释放内存
    freeList(list);

    return 0;
}

/*
jarry@MacBook-Pro list % gcc list.c
jarry@MacBook-Pro list % ./a.out   
List: 10 20 30 40 
Element at index 2: 30
List: 10 20 30 
Size: 3
Capacity: 10
New Capacity: 20
*/