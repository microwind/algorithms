/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  循环链表基础实现（C语言）
 *  功能：尾节点指向头节点形成环形结构，支持循环遍历
 *  用途：学习循环链表概念，实现轮询调度、环形队列等场景
 */

#include <stdio.h>
#include <stdlib.h>

// 节点结构体：数据、下一个节点
struct Node
{
  int data;
  struct Node *next;
};

// 打印链表
void printList(struct Node *head)
{
  if (head == NULL)
    return;

  struct Node *temp = head;
  do
  {
    printf("%d -> ", temp->data);
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
  newNode->next = *head;  // 新节点的next指向头节点，形成环

  if (*head == NULL)
  {
    *head = newNode;  // 链表为空，新节点作为头节点
    newNode->next = *head;  // 指向自己，形成环
    return;
  }

  while (last->next != *head)
  {
    last = last->next;  // 找到最后一个节点（其next指向头节点）
  }
  last->next = newNode;  // 将新节点链接到尾部
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
jarry@MacBook-Pro linked % gcc circular_linked.c
jarry@MacBook-Pro linked % ./a.out
1 -> 2 -> 3 -> (back to head)
*/