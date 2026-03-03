#!/usr/bin/env python
#-*- encoding: UTF-8-*-
"""
 * Copyright © https:#github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
"""
import time
"""
   * 双指针合并两个已排序数组。
   * 新建数组复制法，比较数组1和数组2的当前项，将小的添加到新数组中
   * @param:list one
   * @param:list two
"""


def merge_sorted1(one, two):
    # 数组1下标
    i = 0
    # 数组2下标
    j = 0
    # 结果数组下标
    k = 0

    one_len = len(one)
    two_len = len(two)
    result = [None] * (one_len + two_len)

    # 循环遍历两个数组，直到有1个数组里面的全部被比较过
    while i < one_len and j < two_len:
        # 逐个比较数组1和数组2的项，将小的项添加到新数组中，右移小项的指针再继续比较
        if one[i] < two[j]:
            result[k] = one[i]
            i += 1
        else:
            result[k] = two[j]
            j += 1
        k += 1

    # 如果数组1还有剩余的没有添加完，就全部追加到新数组最后
    while i < one_len:
        result[k] = one[i]
        k += 1
        i += 1

    # 如果数组2还有剩余的没有添加完，就全部追加到新数组最后
    while (j < two_len):
        result[k] = two[j]
        k += 1
        j += 1

    return result


"""
  * 合并两个已排序数组。
  * 插入法，从第一个数组里取出一项，自前往后逐个与第二个数组项进行比较，插入到第二个数组中
  * @param:list one
  * @param:lisit two
"""


def merge_sorted2(one, two):
    one_len = len(one)
    two_len = len(two)
    j = 0
    for i in range(one_len):
        for j in range(two_len):
            # 从数组1里拿出一项来与数组2逐个(自前往后)进行比较
            # 当遇到比它大的项时，则把它插入到数组2里该项的前面
            # 同时数组2下标与长度增加一位，跳出当前循环，进入下一轮比较
            if (one[i] < two[j]):
                two.insert(j, one[i])
                two_len += 1
                break
            else:
                # 如果全部比较完成，且数组2里面没有比它还大的，则添加到最后
                # 也可以一次性添加数组1里面全部剩余项，后面的就无需再比较了
                if j == two_len - 1:
                    two.append(one[i])
                    two_len += 1
                    break

    return two


"""
  * 合并两个已排序数组。
  * 合并数组再采取普通排序法
  * @param:list one
  * @param:list two
"""


def merge_sorted3(one, two):
    one_len = len(one)
    two_len = len(two)

    result = one + two
    # 从第2个数组开始遍历，采用插入排序
    for i in range(one_len, one_len + two_len):
        j = i - 1
        current = result[i]
        # 如果当前项小于已排序的项，则逐个右移1位
        while (j >= 0 and current < result[j]):
            result[j + 1] = result[j]
            j -= 1

        # 空出位置插入比较项
        result[j + 1] = current

    return result


if __name__ == '__main__':

    # 1. merge_sorted1
    arr1 = [-3, 7, 9, 10, 11, 15, 16]
    arr2 = [-1, 5, 6, 9, 12]
    print("\r\n Source array1:")
    print(arr1, arr2)
    start_time = time.time()
    arr = merge_sorted1(arr1, arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("merge_sorted1 sorted: ", arr)

    # 2. merge_sorted2
    arr1 = [-3, 7, 9, 10, 11, 15, 16]
    arr2 = [-1, 5, 6, 9, 12]
    print("\r\n Source array2:")
    print(arr1, arr2)
    start_time = time.time()
    merge_sorted2(arr1, arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("merge_sorted2 sorted: ", arr)

    # 3. merge_sorted3
    arr1 = [-3, 7, 9, 10, 11, 15, 16]
    arr2 = [-1, 5, 6, 9, 12]
    print("\r\n Source array3:")
    print(arr1, arr2)
    start_time = time.time()
    merge_sorted3(arr1, arr2)
    print("time:" + str((time.time() - start_time) * 1000) + " ms")
    print("merge_sorted3 sorted: ", arr)


"""
jarry@jarrys-MacBook-Pro mergesort % python merge_sorted_array.py

 Source array1:
([-3, 7, 9, 10, 11, 15, 16], [-1, 5, 6, 9, 12])
time:0.00810623168945 ms
('merge_sorted1 sorted: ', [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16])

 Source array2:
([-3, 7, 9, 10, 11, 15, 16], [-1, 5, 6, 9, 12])
time:0.014066696167 ms
('merge_sorted2 sorted: ', [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16])

 Source array3:
([-3, 7, 9, 10, 11, 15, 16], [-1, 5, 6, 9, 12])
time:0.00619888305664 ms
('merge_sorted3 sorted: ', [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16])
"""