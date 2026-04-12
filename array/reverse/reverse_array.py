"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 数组反转算法 - Python实现

算法原理：
- 使用双指针技术，交换数组首尾元素
- 向中间移动指针，继续交换，直到相遇
- 只需遍历数组的一半，时间复杂度O(n/2) = O(n)

时间复杂度: O(n)
空间复杂度: O(1) - 仅使用一个临时变量

应用场景：
- 字符串反转
- 回文检查
- 数据预处理
"""


def reverse_array(arr):
    """
    反转数组
    使用双指针法，从数组两端向中间交换元素
    
    参数：
        arr - 待反转的数组
    """
    n = len(arr)
    # 交换数组的前后元素，只需要遍历数组的前一半
    for i in range(n // 2):
        # Python的交换语法：同时交换两个元素的值
        arr[i], arr[n - i - 1] = arr[n - i - 1], arr[i]


def print_array(arr):
    """打印数组"""
    print("[", end="")
    for i, v in enumerate(arr):
        print(v, end="")
        if i < len(arr) - 1:
            print(", ", end="")
    print("]")


if __name__ == '__main__':
    arr = [1, 2, 3, 4, 5]

    print("反转前的数组: ", end="")
    print_array(arr)

    reverse_array(arr)

    print("反转后的数组: ", end="")
    print_array(arr)

"""
输出结果：
反转前的数组: [1, 2, 3, 4, 5]
反转后的数组: [5, 4, 3, 2, 1]
"""