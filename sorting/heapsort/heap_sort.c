/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

int get_left(int i)
{
  return i * 2 + 1;
}

int get_right(int i)
{
  return i * 2 + 2;
}

void swap(int arr[], int from, int to)
{
  int temp = arr[from];
  arr[from] = arr[to];
  arr[to] = temp;
}
/**
 * 始终保持大顶堆特性
 */
void max_heapify(int arr[], int idx, int size)
{
  int max = idx;
  int left = get_left(max);
  int right = get_right(max);
  if (left < size && arr[left] > arr[max])
  {
    max = left;
  }
  if (right < size && arr[right] > arr[max])
  {
    max = right;
  }

  printf("\r\nidx=%d, left=%d, right=%d, max=%d, size=%d", idx, left, right, max, size);

  if (max != idx)
  {
    // swap the current width max value
    swap(arr, idx, max);
    // make max tree recursive
    max_heapify(arr, max, size);
  }
}

void heap_sort(int arr[], int len)
{
  int parent = (len - 1) / 2 - 1;
  int child = len - 1;
  while (parent >= 0)
  {
    max_heapify(arr, parent, len);
    printf("\r\nparent=%d, len=%d", parent, len);
    parent--;
  }

  printf("child start: parent=%d child=%d", parent, child);

  while (child > 0)
  {
    swap(arr, 0, child);
    max_heapify(arr, 0, child);
    printf("\r\nchild=%d, parent=%d", 0, child);
    child--;
  }
}

int main()
{
  int arr[7] = {7, 11, 9, 10, 12, 13, 8};
  int len = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
  float startTime = clock();
  heap_sort(arr, len);
  printf("\nsort end:\n");
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  return 0;
}

/*
jarrys-MacBook-Pro:heapsort jarry$ gcc ./heap_sort.c
jarrys-MacBook-Pro:heapsort jarry$ ./a.out
7 11 9 10 12 13 8
idx=2, left=5, right=6, max=5, size=7
idx=5, left=11, right=12, max=5, size=7
parent=2, len=7
idx=1, left=3, right=4, max=4, size=7
idx=4, left=9, right=10, max=4, size=7
parent=1, len=7
idx=0, left=1, right=2, max=2, size=7
idx=2, left=5, right=6, max=5, size=7
idx=5, left=11, right=12, max=5, size=7
parent=0, len=7child start: parent=-1 child=6
idx=0, left=1, right=2, max=1, size=6
idx=1, left=3, right=4, max=4, size=6
idx=4, left=9, right=10, max=4, size=6
child=0, parent=6
idx=0, left=1, right=2, max=1, size=5
idx=1, left=3, right=4, max=3, size=5
idx=3, left=7, right=8, max=3, size=5
child=0, parent=5
idx=0, left=1, right=2, max=1, size=4
idx=1, left=3, right=4, max=1, size=4
child=0, parent=4
idx=0, left=1, right=2, max=2, size=3
idx=2, left=5, right=6, max=2, size=3
child=0, parent=3
idx=0, left=1, right=2, max=1, size=2
idx=1, left=3, right=4, max=1, size=2
child=0, parent=2
idx=0, left=1, right=2, max=0, size=1
child=0, parent=1
sort end:
7 8 9 10 11 12 13
time: 0.073000 ms
*/

/**
oringal array: [7, 11, 9, 10, 12, 13, 8]
heap:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  12(4)  13(5)  8(6)

父节点步骤
1. maxHeapify: idx= 2 left= 5 right= 6 max= 5 size= 7
              7(0)
          /         \
        11(1)        13(2)
       /    \      /     \
   10(3)  12(4)  9(5)  8(6)

2. maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 7
              7(0)
          /         \
        12(1)        13(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

3. maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 7
              13(0)
          /         \
        12(1)        7(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

3.1 maxHeapify recursion: idx= 2 left= 5 right= 6 max= 5 size= 7
              13(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  8(6)

子节点堆排序:
1. swap, child = 6:
              8(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

1.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 6
              12(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

1.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 4 size= 6
              12(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  7(5)  13(6)

2. swap, child = 5:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

2.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 5
              11(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

2.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 3 size= 5
              11(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  8(4)  12(5)  13(6)

3. swap, child = 4:
              8(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

3.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 4
              10(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

3.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 1 size= 4

4. swap, child = 3:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

4.1 maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 3
              9(0)
          /         \
        8(1)        7(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

4.2 maxHeapify recursion: idx= 2 left= 5 right= 6 max= 2 size= 3

5. swap, child = 2:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

5.1 maxHeapify: idx= 0 left= 1 right= 2 max= 1 size= 2
              8(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

5.2 maxHeapify recursion: idx= 1 left= 3 right= 4 max= 1 size= 2

6. swap, child = 1:
              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

6.1 maxHeapify: idx= 0 left= 1 right= 2 max= 0 size= 1

 */