#include <stdio.h>
#include <stdlib.h>

// 定义节点结构体
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
    temp = temp->next;
  } while (temp != head);
  printf("(back to head)\n");
}

// 插入节点到尾部
void appendNode(struct Node **head, int data)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  struct Node *last = *head;

  newNode->data = data;
  newNode->next = *head;
  newNode->prev = NULL;

  if (*head == NULL)
  {
    *head = newNode;
    newNode->next = newNode;
    newNode->prev = newNode;
    return;
  }

  while (last->next != *head)
  {
    last = last->next;
  }
  last->next = newNode;
  newNode->prev = last;
  (*head)->prev = newNode;
}

int main()
{
  struct Node *head = NULL;

  // 插入节点
  appendNode(&head, 1);
  appendNode(&head, 2);
  appendNode(&head, 3);

  printList(head); // 输出：1 <-> 2 <-> 3 <-> (back to head)
  return 0;
}

/*
jarry@MacBook-Pro linked % gcc doubly_circular_linked.c
jarry@MacBook-Pro linked % ./a.out
1 <-> 2 <-> 3 <-> (back to head)
*/