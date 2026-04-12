/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  双向链表基础实现（C语言）
 *  功能：支持双向遍历的链表，包含prev和next指针
 *  用途：学习双向链表概念，理解前后指针操作
 */

#include <stdio.h>
#include <stdlib.h>

// 节点结构体：数据、下一个节点、上一个节点
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// 打印链表
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;  // 移动到下一个节点
    }
    printf("NULL\n");
}

// 向链表尾部添加节点
void appendNode(struct Node** head, int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    struct Node* last = *head;
    
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (*head == NULL) {
        *head = newNode;  // 链表为空，新节点作为头节点
        return;
    }
    
    while (last->next != NULL) {
        last = last->next;  // 找到最后一个节点
    }
    last->next = newNode;  // 将新节点链接到尾部
    newNode->prev = last;  // 设置新节点的前驱指针
}

int main() {
    struct Node* head = NULL;

    // 添加节点
    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);

    printList(head);
    return 0;
}

/*
jarry@MacBook-Pro linked % gcc doubly_linked.c
jarry@MacBook-Pro linked % ./a.out 
1 <-> 2 <-> 3 <-> NULL
*/