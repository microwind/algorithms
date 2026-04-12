/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  本文件实现通用单向链表数据结构，提供完整的链表CRUD操作。
 *  解决的问题：
 *  1. 动态数据存储 - 无需预先分配固定大小的内存空间
 *  2. 高效插入删除 - 头部操作O(1)，无需像数组那样移动元素
 *  3. 灵活内存管理 - 按需分配/释放节点内存
 *  
 *  提供的功能：
 *  - insertHead/insertTail: 在头部/尾部插入节点
 *  - deleteNode: 删除指定数据的节点
 *  - findNode: 查找节点
 *  - printList: 打印链表内容
 *  - freeList: 释放链表内存（防止内存泄漏）
 *  
 *  适用场景：需要频繁插入删除、数据量动态变化、无需随机访问的场景
 */

#include <stdio.h>
#include <stdlib.h>

// 节点结构体：包含数据和指向下一个节点的指针
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 链表结构体：管理整个链表的头节点和大小
typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

// 创建链表：分配内存并初始化空链表
LinkedList* createList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;     // 初始为空链表，头节点为NULL
    list->size = 0;        // 初始节点数为0
    return list;
}

// 在头部插入：时间复杂度 O(1)
void insertHead(LinkedList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));  // 分配新节点内存
    newNode->data = data;      // 设置节点数据
    newNode->next = list->head; // 新节点的next指向当前头节点
    list->head = newNode;       // 更新头指针指向新节点
    list->size++;               // 节点计数+1
}

// 在尾部插入：时间复杂度 O(n)，需要遍历到链表末尾
void insertTail(LinkedList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;       // 尾节点的next为NULL
    
    if (list->head == NULL) {
        list->head = newNode;   // 链表为空时，新节点成为头节点
    } else {
        Node *current = list->head;
        // 遍历到链表末尾
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode; // 将新节点链接到尾部
    }
    list->size++;
}

// 删除节点：先查找再删除，时间复杂度 O(n)
int deleteNode(LinkedList *list, int data) {
    if (list->head == NULL) return 0;  // 空链表无法删除
    
    // 如果要删除的是头节点
    if (list->head->data == data) {
        Node *temp = list->head;        // 临时保存头节点
        list->head = list->head->next;  // 头指针后移
        free(temp);                     // 释放原头节点内存
        list->size--;
        return 1;
    }
    
    // 查找要删除的节点及其前驱节点
    Node *current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    // 找到目标节点
    if (current->next != NULL) {
        Node *temp = current->next;              // 临时保存目标节点
        current->next = current->next->next;     // 跳过目标节点（解除链接）
        free(temp);                              // 释放目标节点内存
        list->size--;
        return 1;
    }
    return 0;  // 未找到要删除的节点
}

// 查找节点：遍历查找，时间复杂度 O(n)
Node* findNode(LinkedList *list, int data) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return current;  // 找到目标节点，返回指针
        }
        current = current->next;  // 移动到下一个节点
    }
    return NULL;  // 遍历完未找到，返回NULL
}

// 打印链表：遍历输出所有节点数据
void printList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 获取链表大小：O(1) 直接返回维护的size字段
int getSize(LinkedList *list) {
    return list->size;
}

// 释放链表：遍历释放每个节点内存，最后释放链表结构体
void freeList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;        // 保存当前节点
        current = current->next;     // 移动到下一个节点
        free(temp);                  // 释放当前节点内存
    }
    free(list);  // 释放链表结构体内存
}

int main() {
    LinkedList *list = createList();
    
    insertTail(list, 1);
    insertTail(list, 2);
    insertHead(list, 0);
    insertTail(list, 3);
    
    printf("链表内容: ");
    printList(list);
    printf("链表大小: %d\n", getSize(list));
    
    printf("查找节点2: %s\n", findNode(list, 2) ? "找到" : "未找到");
    
    printf("删除节点2\n");
    deleteNode(list, 2);
    printf("链表内容: ");
    printList(list);
    
    freeList(list);
    return 0;
}
