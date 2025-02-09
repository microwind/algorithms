#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* stack.h */

// 定义栈元素的数据类型
typedef int item;

// 栈结构体前向声明
typedef struct stack *Stack;

// 动态创建栈
Stack create_stack(int);

// 打印栈的所有元素
void print_stack(Stack);

// 入栈操作
bool push(Stack, item);

// 出栈操作
item pop(Stack);

// 判断栈是否已满
bool is_full(Stack);

// 判断栈是否为空
bool is_empty(Stack);

// 清空栈
void make_empty(Stack);

// 获取栈的当前元素个数
int len(Stack);

/* stack.c */

// 栈结构体的定义
struct stack
{
  int top;          // 栈顶指针
  int size;         // 栈的最大容量
  item *data_array; // 存储栈元素的数组
};

// 动态创建栈，指定栈的最大容量
Stack create_stack(int size)
{
  Stack s = malloc(sizeof(struct stack)); // 为栈结构体分配内存
  if (s == NULL)
  {
    return NULL; // 如果内存分配失败，返回 NULL
  }

  s->data_array = malloc(sizeof(int) * size); // 为栈的存储数组分配内存
  if (s->data_array == NULL)
  {
    return NULL; // 如果内存分配失败，返回 NULL
  }

  s->top = 0;     // 栈顶指针初始化为 0
  s->size = size; // 设置栈的最大容量
  return s;
}

// 打印栈中的所有元素
void print_stack(Stack s)
{
  if (is_empty(s))
  {
    printf("栈为空\n");
    return;
  }

  for (int i = 0; i < s->top; i++)
  {
    printf("%d ", s->data_array[i]); // 打印栈中的每个元素
  }

  printf("\n");
}

// 判断栈是否已满
bool is_full(Stack s)
{
  return s->top == s->size; // 如果栈顶指针等于栈的最大容量，表示栈已满
}

// 判断栈是否为空
bool is_empty(Stack s)
{
  return s->top == 0; // 如果栈顶指针为 0，表示栈为空
}

// 入栈操作，将元素压入栈顶
bool push(Stack s, item data)
{
  if (is_full(s)) // 如果栈已满，返回 false
  {
    return false;
  }

  s->data_array[s->top++] = data; // 将数据压入栈顶，栈顶指针加 1
  return true;
}

// 出栈操作，返回栈顶元素并移除它
item pop(Stack s)
{
  if (is_empty(s)) // 如果栈为空，返回 0（假定 0 为无效值）
  {
    return 0;
  }

  return s->data_array[--s->top]; // 将栈顶指针减 1，返回栈顶元素
}

// 清空栈，将栈顶指针设置为 0
void make_empty(Stack s)
{
  s->top = 0; // 清空栈中的所有元素
}

// 获取栈的当前元素个数
int len(Stack s)
{
  return s->top; // 栈顶指针即为栈中元素的数量
}

/* test */

// 测试栈的功能
void test_stack()
{
  Stack s = create_stack(5); // 创建一个容量为 5 的栈
  printf("执行入栈操作\n");

  // 测试入栈
  printf("入栈 1: %s\n", push(s, 1) ? "成功" : "失败");
  print_stack(s);

  printf("入栈 2: %s\n", push(s, 2) ? "成功" : "失败");
  print_stack(s);

  // 测试出栈
  printf("执行出栈操作\n");
  printf("出栈: %d\n", pop(s));
  print_stack(s);

  printf("出栈: %d\n", pop(s));
  print_stack(s);

  // 测试栈为空的情况
  printf("出栈: %d\n", pop(s));
  print_stack(s);

  // 测试清空栈
  printf("清空栈\n");
  make_empty(s);
  print_stack(s);

  printf("测试结束。\n");

  free(s->data_array); // 释放栈的存储空间
  free(s);             // 释放栈结构体本身的空间
}

// 主函数
int main()
{
  test_stack(); // 调用测试栈的函数
  return 0;
}

/*
jarry@MacBook-Pro stack % gcc stack.c
jarry@MacBook-Pro stack % ./a.out
执行入栈操作
入栈 1: 成功
1
入栈 2: 成功
1 2
执行出栈操作
出栈: 2
1
出栈: 1
栈为空
出栈: 0
栈为空
清空栈
栈为空
测试结束。
*/