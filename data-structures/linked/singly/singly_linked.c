/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  单向链表基础实现（C语言）
 *  功能：提供链表节点创建、尾部追加、打印输出
 *  用途：学习链表基本概念，理解指针和内存分配
 */

#include <stdio.h>
#include <stdlib.h>

// 节点结构体：数据、下一个节点指针
struct Node
{
  int data;              // 节点数据
  struct Node *next;     // 指向下一个节点
};

// 打印链表
void printList(struct Node *head)
{
  struct Node *temp = head;
  while (temp != NULL)
  {
    printf("%d -> ", temp->data);
    temp = temp->next; // 移动到下一个节点
  }
  printf("NULL\n");
}

// 向链表尾部添加节点
void appendNode(struct Node **head, int data)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  struct Node *last = *head;

  newNode->data = data;
  newNode->next = NULL;

  if (*head == NULL)
  {
    *head = newNode; // 链表为空，新节点作为头节点
    return;
  }

  while (last->next != NULL)
  {
    last = last->next; // 找到最后一个节点
  }
  last->next = newNode; // 将新节点链接到尾部
}

int main()
{
  struct Node *head = NULL;

  // 添加节点
  appendNode(&head, 1);
  appendNode(&head, 2);
  appendNode(&head, 3);

  printList(head);
  return 0;
}

/*
jarry@MacBook-Pro linked % gcc singly_linked.c
jarry@MacBook-Pro linked % ./a.out
1 -> 2 -> 3 -> NULL
 */