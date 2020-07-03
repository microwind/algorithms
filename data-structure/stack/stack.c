#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* stack.h */

typedef int item;

typedef struct stack *Stack;

// dynamic locate memory
Stack stack_create(int);

void stack_println(Stack);

bool stack_push(Stack, item);

// get first item on empty
item stack_pop(Stack);

bool stack_is_full(Stack);
bool stack_is_empty(Stack);
void stack_make_empty(Stack);
int stack_len(Stack);

/* stack.c */

struct stack
{
  int top;
  int size;
  item *data_array;
};

Stack stack_create(int size)
{
  Stack s = malloc(sizeof(struct stack));
  if (s == NULL)
  {
    return NULL;
  }
  
  s->data_array = malloc(sizeof(int) * size);
  if (s->data_array == NULL)
  {
    return NULL;
  }

  s->top = 0;
  s->size = size;
  return s;
}

void stack_println(Stack s)
{
  for (int i = 0; i < s->top; i++)
  {
    printf("%d ", s->data_array[i]);
  }

  printf("\n");
}

bool stack_is_full(Stack s)
{
  return s->top == s->size;
}

bool stack_is_empty(Stack s)
{
  return s->top == 0;
}

bool stack_push(Stack s, item data)
{
  if (stack_is_full(s))
  {
    return false;
  }

  s->data_array[s->top++] = data;
  return true;
}

item stack_pop(Stack s)
{
  if (stack_is_empty(s))
  {
    return 0;
  }

  return s->data_array[--s->top];
}

void stack_make_empty(Stack s)
{
  s->top = 0;
  return;
}

int stack_len(Stack s)
{
  return s->top;
}

/* test */
int main()
{
  Stack s = stack_create(5);
  printf("push\n");

  printf("push: %s\n", stack_push(s, 1) ? "true" : "false");
  stack_println(s);
  printf("push: %s\n", stack_push(s, 2) ? "true" : "false");
  stack_println(s);
  printf("pop\n");

  printf("pop: %d\n", stack_pop(s));
  stack_println(s);
  printf("pop: %d\n", stack_pop(s));
  stack_println(s);
  printf("pop: %d\n", stack_pop(s));
  stack_println(s);

  printf("make empty\n");
  stack_make_empty(s);

  printf("operating end.\n");
  stack_println(s);
  free(s);
}