/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  双向循环链表基础实现（C语言）
 *  功能：结合双向链表和循环链表特性，支持双向循环遍历
 *  用途：学习最复杂的链表结构，实现高级循环队列、双向循环缓冲区
 */

#include <stdio.h>
#include <stdlib.h>

// 节点结构体：数据、下一个节点、上一个节点
struct Node
{
  int data;
  struct Node *next;
  struct Node *prev;
};

// 打印链表
void printList(struct Node *head)
{
  if (head == NULL)
    return;

  struct Node *temp = head;
  do
  {
    printf("%d <-> ", temp->data);
    temp = temp->next;  // 移动到下一个节点
  } while (temp != head);  // 循环直到回到头节点
  printf("(back to head)\n");
}

// 向链表尾部添加节点
void appendNode(struct Node **head, int data)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  struct Node *last = *head;

  newNode->data = data;
  newNode->next = *head;  // 新节点的next指向头节点
  newNode->prev = NULL;

  if (*head == NULL)
  {
    *head = newNode;  // 链表为空，新节点作为头节点
    newNode->next = newNode;  // 指向自己，形成环
    newNode->prev = newNode;  // 指向自己，形成环
    return;
  }

  while (last->next != *head)
  {
    last = last->next;  // 找到最后一个节点（其next指向头节点）
  }
  last->next = newNode;  // 将新节点链接到尾部
  newNode->prev = last;  // 设置新节点的前驱指针
  (*head)->prev = newNode;  // 更新头节点的前驱指针
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
jarry@MacBook-Pro linked % gcc doubly_circular_linked.c
jarry@MacBook-Pro linked % ./a.out
1 <-> 2 <-> 3 <-> (back to head)
*/