#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @date: ${date} ${time}
 * @version: 1.0
"""
# https://levelup.gitconnected.com/heapsort-for-javascript-newbies-598d25477d55
# http://www.cppcns.com/wangluo/javascript/149148.html
# https://www.programiz.com/dsa/heap-sort
import time
class HeapSort:

  def __init__(self, arr):
    self.arr = arr

  def get_parent(self, i):
    return int((i - 1) / 2)

  def get_left(self, i):
    return 2 * i + 1

  def get_right(self, i):
    return 2 * i + 2

  # 始终保持大顶堆特性
  def max_heapify(self, idx, size):
    arr = self.arr
    max = idx
    left = self.get_left(idx)
    right = self.get_right(idx)
    if (left < size and arr[left] > arr[max]):
      max = left
    
    if (right < size and arr[right] > arr[max]):
      max = right
    
    print('idx=', idx, 'left=', left, 'right=', right, 'max=', max, 'size=', size)

    if (max != idx):
      [arr[idx], arr[max]] = [arr[max], arr[idx]]
      self.max_heapify(max, size)
  
  def build_max_heap(self):
    arr = self.arr
    length = len(arr)
    last_parent = self.get_parent(length) - 1
    for parent in range(last_parent, -1, -1):
      self.max_heapify(parent, length)
      print('parent sort:', parent, arr)

  def sort_tree(self):
    arr = self.arr
    length = len(arr)
    child = length - 1
    while (child > 0):
      [arr[0], arr[child]] = [arr[child], arr[0]]
      self.max_heapify(0, child)
      print('child sort:', child, arr)
      child -= 1

  def start(self):
    self.build_max_heap()
    print('child start:')
    self.sort_tree()
    return arr

arr = [7, 11, 9, 10, 12, 13, 8]
print("start:", arr)
start_time = time.time()
HeapSort(arr).start()
print("sorted:", arr)
print("time:" + str((time.time() - start_time) * 1000) + " ms")

'''
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

'''

'''
jarrys-MacBook-Pro:heapsort jarry$ python heap_sort.py 
('start:', [7, 11, 9, 10, 12, 13, 8])
('idx=', 2, 'left=', 5, 'right=', 6, 'max=', 5, 'size=', 7)
('idx=', 5, 'left=', 11, 'right=', 12, 'max=', 5, 'size=', 7)
('parent sort:', 2, [7, 11, 13, 10, 12, 9, 8])
('idx=', 1, 'left=', 3, 'right=', 4, 'max=', 4, 'size=', 7)
('idx=', 4, 'left=', 9, 'right=', 10, 'max=', 4, 'size=', 7)
('parent sort:', 1, [7, 12, 13, 10, 11, 9, 8])
('idx=', 0, 'left=', 1, 'right=', 2, 'max=', 2, 'size=', 7)
('idx=', 2, 'left=', 5, 'right=', 6, 'max=', 5, 'size=', 7)
('idx=', 5, 'left=', 11, 'right=', 12, 'max=', 5, 'size=', 7)
('parent sort:', 0, [13, 12, 9, 10, 11, 7, 8])
child start:
('idx=', 0, 'left=', 1, 'right=', 2, 'max=', 1, 'size=', 6)
('idx=', 1, 'left=', 3, 'right=', 4, 'max=', 4, 'size=', 6)
('idx=', 4, 'left=', 9, 'right=', 10, 'max=', 4, 'size=', 6)
('child sort:', 6, [12, 11, 9, 10, 8, 7, 13])
('idx=', 0, 'left=', 1, 'right=', 2, 'max=', 1, 'size=', 5)
('idx=', 1, 'left=', 3, 'right=', 4, 'max=', 3, 'size=', 5)
('idx=', 3, 'left=', 7, 'right=', 8, 'max=', 3, 'size=', 5)
('child sort:', 5, [11, 10, 9, 7, 8, 12, 13])
('idx=', 0, 'left=', 1, 'right=', 2, 'max=', 1, 'size=', 4)
('idx=', 1, 'left=', 3, 'right=', 4, 'max=', 1, 'size=', 4)
('child sort:', 4, [10, 8, 9, 7, 11, 12, 13])
('idx=', 0, 'left=', 1, 'right=', 2, 'max=', 2, 'size=', 3)
('idx=', 2, 'left=', 5, 'right=', 6, 'max=', 2, 'size=', 3)
('child sort:', 3, [9, 8, 7, 10, 11, 12, 13])
('idx=', 0, 'left=', 1, 'right=', 2, 'max=', 1, 'size=', 2)
('idx=', 1, 'left=', 3, 'right=', 4, 'max=', 1, 'size=', 2)
('child sort:', 2, [8, 7, 9, 10, 11, 12, 13])
('idx=', 0, 'left=', 1, 'right=', 2, 'max=', 0, 'size=', 1)
('child sort:', 1, [7, 8, 9, 10, 11, 12, 13])
('sorted:', [7, 8, 9, 10, 11, 12, 13])
time:0.188112258911 ms
'''