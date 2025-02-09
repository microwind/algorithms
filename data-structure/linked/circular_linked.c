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
  if (head == NULL)
    return;

  struct Node *temp = head;
  do
  {
    printf("%d -> ", temp->data);
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

  if (*head == NULL)
  {
    *head = newNode;
    newNode->next = *head; // 指向自己，形成环
    return;
  }

  while (last->next != *head)
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

  printList(head); // 输出：1 -> 2 -> 3 -> (back to head)
  return 0;
}

/*
jarry@MacBook-Pro linked % gcc circular_linked.c
jarry@MacBook-Pro linked % ./a.out
1 -> 2 -> 3 -> (back to head)
*/