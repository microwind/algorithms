#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// 哈希表节点
typedef struct Node
{
  int key;           // 键值
  int value;         // 对应值
  struct Node *next; // 下一个节点（用于链表法处理冲突）
} Node;

// 哈希表结构
typedef struct HashTable
{
  Node *table[TABLE_SIZE]; // 哈希表存储桶
} HashTable;

// 哈希函数：根据整数键计算哈希值
// unsigned int hash(int key)
// {
//   return key % TABLE_SIZE;
// }

// DJB2 哈希函数
unsigned int hash(int key)
{
  unsigned int hash = 5381;
  int c;

  while (key)
  {
    c = key % 256; // 模拟字符读取
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
    key /= 256; // 移动到下一个字符
  }

  return hash % TABLE_SIZE;
}

// 创建哈希表
HashTable *createHashTable()
{
  HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    hashTable->table[i] = NULL;
  }
  return hashTable;
}

// 插入或更新键值对
void insert(HashTable *hashTable, int key, int value)
{
  unsigned int index = hash(key);
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->key = key;
  newNode->value = value;
  newNode->next = hashTable->table[index];
  hashTable->table[index] = newNode;
}

// 查找指定键对应的值
int search(HashTable *hashTable, int key)
{
  unsigned int index = hash(key);
  Node *current = hashTable->table[index];
  while (current)
  {
    if (current->key == key)
    {
      return current->value;
    }
    current = current->next;
  }
  return -1; // 找不到键
}

// 删除指定键的元素
void delete(HashTable *hashTable, int key)
{
  unsigned int index = hash(key);
  Node *current = hashTable->table[index];
  Node *prev = NULL;
  while (current)
  {
    if (current->key == key)
    {
      if (prev)
      {
        prev->next = current->next;
      }
      else
      {
        hashTable->table[index] = current->next;
      }
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
  printf("Key not found\n");
}

// 打印哈希表中的所有元素
void printHashTable(HashTable *hashTable)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *current = hashTable->table[i];
    while (current)
    {
      printf("Key: %d, Value: %d\n", current->key, current->value);
      current = current->next;
    }
  }
}

// 释放哈希表的内存
void freeHashTable(HashTable *hashTable)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *current = hashTable->table[i];
    while (current)
    {
      Node *temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(hashTable);
}

// 主函数
int main()
{
  // 创建哈希表
  HashTable *hashTable = createHashTable();

  // 插入键值对
  insert(hashTable, 1, 100);
  insert(hashTable, 2, 200);
  insert(hashTable, 3, 300);

  // 查找键对应的值
  printf("Value of key 2: %d\n", search(hashTable, 2));

  // 删除键值对
  delete (hashTable, 2);
  printf("After removing key 2:\n");
  printHashTable(hashTable);

  // 打印哈希表中的所有元素
  printf("All key-value pairs in the hash table:\n");
  printHashTable(hashTable);

  // 释放哈希表的内存
  freeHashTable(hashTable);

  return 0;
}

/**
jarry@MacBook-Pro hash % gcc hash_table.c
jarry@MacBook-Pro hash % ./a.out
Value of key 2: 200
After removing key 2:
Key: 1, Value: 100
Key: 3, Value: 300
All key-value pairs in the hash table:
Key: 1, Value: 100
Key: 3, Value: 300
 */