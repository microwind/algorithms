/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
import java.util.Arrays;
public class HeapSort {
  
  private static int getLeft(int i) {
    return i * 2 + 1;
  }

  private static int getRight(int i) {
    return i * 2 + 2;
  }

  static void swap(int arr[], int from, int to) {
    int temp = arr[from];
    arr[from] = arr[to];
    arr[to] = temp;
  }

  private static void maxHeapify(int arr[], int idx, int size) {
    int max = idx;
    int left = getLeft(idx);
    int right = getRight(idx);
    if (left < size && arr[left] > arr[max]) {
      max = left;
    }
    if (right < size && arr[right] > arr[max]) {
      max = right;
    }
    System.out.println("idx=" + idx + " left=" + left + " right=" + right + " max=" + max + " size=" + size);
    if (max != idx) {
      swap(arr, idx, max);
      maxHeapify(arr, max, size);
    }
  }

  static void heapSort(int arr[]) {
    int len = arr.length;
    int parent = (len - 1) / 2 - 1;
    int child = len - 1;

    while (parent >= 0) {
      maxHeapify(arr, parent, len);
      System.out.println("parent sort:" + parent + " " + len + " ");
      parent--;
    }

    System.out.println("child start: parent=" + parent + " child=" + child);

    while (child > 0) {
      swap(arr, 0, child);
      maxHeapify(arr, 0, child);
      System.out.println("child sort:" + 0 + " " + child + " ");
      child--;
    }
  }
  
  public static void main(String[] args) {
    int arr[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("sort start:" + Arrays.toString(arr));
    long startTime = System.currentTimeMillis();
    HeapSort.heapSort(arr);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(arr));
  }
}

/*
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

/**
jarrys-MacBook-Pro:heapsort jarry$ javac HeapSort.java
jarrys-MacBook-Pro:heapsort jarry$ java HeapSort
sort start:[7, 11, 9, 10, 12, 13, 8]
idx=2 left=5 right=6 max=5 size=7
idx=5 left=11 right=12 max=5 size=7
parent sort:2 7 
idx=1 left=3 right=4 max=4 size=7
idx=4 left=9 right=10 max=4 size=7
parent sort:1 7 
idx=0 left=1 right=2 max=2 size=7
idx=2 left=5 right=6 max=5 size=7
idx=5 left=11 right=12 max=5 size=7
parent sort:0 7 
child start: parent=-1 child=6
idx=0 left=1 right=2 max=1 size=6
idx=1 left=3 right=4 max=4 size=6
idx=4 left=9 right=10 max=4 size=6
child sort:0 6 
idx=0 left=1 right=2 max=1 size=5
idx=1 left=3 right=4 max=3 size=5
idx=3 left=7 right=8 max=3 size=5
child sort:0 5 
idx=0 left=1 right=2 max=1 size=4
idx=1 left=3 right=4 max=1 size=4
child sort:0 4 
idx=0 left=1 right=2 max=2 size=3
idx=2 left=5 right=6 max=2 size=3
child sort:0 3 
idx=0 left=1 right=2 max=1 size=2
idx=1 left=3 right=4 max=1 size=2
child sort:0 2 
idx=0 left=1 right=2 max=0 size=1
child sort:0 1 

time:55 ms.
sorted:[7, 8, 9, 10, 11, 12, 13]
 */