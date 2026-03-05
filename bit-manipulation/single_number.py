"""
单数问题 - 使用XOR技巧找到单个数字

问题：给定一个整数数组，其中除了一个元素出现一次外，
其他元素都出现两次。找到只出现一次的那个元素。

核心思想：
- XOR 的性质：a ^ a = 0, a ^ 0 = a
- 对所有元素进行XOR操作，两个相同的数会相消，留下单个数字

时间复杂度: O(n)
空间复杂度: O(1)
"""


def single_number_xor(nums):
    """
    使用XOR技巧找到单个数字

    原理：
    - 0 ^ x = x
    - x ^ x = 0
    - XOR满足交换律和结合律
    - 对所有数字XOR，重复数字相消，留下单个数字

    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    result = 0
    for num in nums:
        result ^= num
    return result


def single_number_hash(nums):
    """
    使用哈希表统计频数（备选方案）

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    count = {}
    for num in nums:
        count[num] = count.get(num, 0) + 1

    for num, cnt in count.items():
        if cnt == 1:
            return num

    return -1


def single_number_sort(nums):
    """
    排序后相邻比较（备选方案）

    时间复杂度: O(n log n)
    空间复杂度: O(1) 如果使用原地排序
    """
    nums_sorted = sorted(nums)

    for i in range(0, len(nums_sorted) - 1, 2):
        if nums_sorted[i] != nums_sorted[i + 1]:
            return nums_sorted[i]

    return nums_sorted[-1]


if __name__ == "__main__":
    print("=== 单数问题 ===\n")

    # 测试用例1：基本用例
    print("1. 基本用例:")
    nums1 = [2, 2, 1]
    print(f"  数组: {nums1}")
    print(f"  单数: {single_number_xor(nums1)}")
    print()

    # 测试用例2：较大数组
    print("2. 较大数组:")
    nums2 = [4, 1, 2, 1, 2]
    print(f"  数组: {nums2}")
    print(f"  单数: {single_number_xor(nums2)}")
    print()

    # 测试用例3：负数
    print("3. 包含负数:")
    nums3 = [-1, -1, 5, 5, 3]
    print(f"  数组: {nums3}")
    print(f"  单数: {single_number_xor(nums3)}")
    print()

    # 测试用例4：单个元素
    print("4. 单个元素:")
    nums4 = [42]
    print(f"  数组: {nums4}")
    print(f"  单数: {single_number_xor(nums4)}")
    print()

    # 性能比较
    print("5. 不同方法的结果比较:")
    nums5 = [7, 7, 8, 8, 9]
    print(f"  数组: {nums5}")
    print(f"  XOR方法: {single_number_xor(nums5)}")
    print(f"  哈希方法: {single_number_hash(nums5)}")
    print(f"  排序方法: {single_number_sort(nums5)}")
