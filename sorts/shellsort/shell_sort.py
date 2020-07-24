#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time

# 希尔排序，基于插入排序进行了分组排序
def shell_sort1(arr):
    size = len(arr)
    # 设置分组间隔
    gap = size // 2
    print('gap:', gap)
    # 如果间隔大于0，则表示还可以继续分
    while gap > 0:
        for i in range(gap, size):
            current = arr[i]
            j = i
            print('gap=', gap, ' j=', j, 'arr:', arr)
            # 分组按照插入排序逐个位移
            while j >= gap and current < arr[j - gap]:
                arr[j] = arr[j - gap]
                j -= gap
            # 交换当前项
            arr[j] = current
        # 调整间距为1/2
        gap = gap // 2
    return arr


if __name__ == '__main__':

    # 1. shell_sort1
    arr = [7, 11, 9, 10, 12, 13, 8, -1, 23]
    print("\r\n Source array1:")
    print(arr)
    start_time = time.time()
    arr = shell_sort1(arr)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("shell_sort1 sorted: ", arr)

"""
jarry@jarrys-MacBook-Pro shellsort % python shell_sort.py

 Source array1:
[7, 11, 9, 10, 12, 13, 8, -1, 23]
('gap:', 4)
('gap=', 4, ' j=', 4)
('gap=', 4, ' j=', 5)
('gap=', 4, ' j=', 6)
('gap=', 4, ' j=', 7)
('gap=', 4, ' j=', 8)
('gap=', 2, ' j=', 2)
('gap=', 2, ' j=', 3)
('gap=', 2, ' j=', 4)
('gap=', 2, ' j=', 5)
('gap=', 2, ' j=', 6)
('gap=', 2, ' j=', 7)
('gap=', 2, ' j=', 8)
('gap=', 1, ' j=', 1)
('gap=', 1, ' j=', 2)
('gap=', 1, ' j=', 3)
('gap=', 1, ' j=', 4)
('gap=', 1, ' j=', 5)
('gap=', 1, ' j=', 6)
('gap=', 1, ' j=', 7)
('gap=', 1, ' j=', 8)
time:0.0698566436768 ms
('shell_sort1 sorted: ', [-1, 7, 8, 9, 10, 11, 12, 13, 23])
"""