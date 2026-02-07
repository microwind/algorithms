#include <stdio.h>
#include <stdlib.h>

// 定义节点结构体
struct Node
{
  int data;
  struct Node *next;
};

// 打印链表
void printList(struct Node *head)
{
  struct Node *temp = head;
  while (temp != NULL)
  {
    printf("%d -> ", temp->data);
    temp = temp->next;
  }
  printf("NULL\n");
}

// 插入新节点到链表尾部
void appendNode(struct Node **head, int data)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  struct Node *last = *head;

  newNode->data = data;
  newNode->next = NULL;

  if (*head == NULL)
  {
    *head = newNode;
    return;
  }

  while (last->next != NULL)
  {
    last = last->next;
  }
  last->next = newNode;
}

int main()
{
  struct Node *head = NULL;

  // 插入节点
  appendNode(&head, 1);
  appendNode(&head, 2);
  appendNode(&head, 3);

  printList(head); // 输出：1 -> 2 -> 3 -> NULL
  return 0;
}

/*
jarry@MacBook-Pro linked % gcc singly_linked.c
jarry@MacBook-Pro linked % ./a.out
1 -> 2 -> 3 -> NULL
 */