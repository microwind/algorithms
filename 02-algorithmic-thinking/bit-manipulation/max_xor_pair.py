"""
最大XOR对 - 找数组中最大的XOR值

问题：给定一个数组，找到任意两个元素的最大XOR值

核心思想：
- 暴力法：比较所有对
- 字典树(Trie)：高效地查找最大XOR

时间复杂度:
- 暴力法: O(n^2)
- Trie方法: O(n * k) 其中k是整数的位数

空间复杂度: O(n * k) for Trie
"""


def max_xor_pair_brute_force(nums):
    """
    暴力法：比较所有对

    时间复杂度: O(n^2)
    空间复杂度: O(1)
    """
    max_xor = 0
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            xor_val = nums[i] ^ nums[j]
            max_xor = max(max_xor, xor_val)
    return max_xor


class TrieNode:
    """Trie树的节点"""
    def __init__(self):
        self.children = {}


class BitTrie:
    """位Trie树：用于高效查找最大XOR"""
    def __init__(self):
        self.root = TrieNode()

    def insert(self, num):
        """将数字的二进制表示插入Trie"""
        node = self.root
        # 从最高位到最低位遍历
        for i in range(31, -1, -1):
            bit = (num >> i) & 1
            bit_str = str(bit)
            if bit_str not in node.children:
                node.children[bit_str] = TrieNode()
            node = node.children[bit_str]

    def find_max_xor(self, num):
        """
        找与给定数字最大XOR的数

        贪心策略：对于每一位，尽可能走不同的路径以最大化XOR
        """
        node = self.root
        max_xor = 0
        # 从最高位到最低位遍历
        for i in range(31, -1, -1):
            bit = (num >> i) & 1
            # 优先走相反的路径（这样XOR结果该位为1）
            toggle_bit = 1 - bit
            toggle_bit_str = str(toggle_bit)

            if toggle_bit_str in node.children:
                max_xor |= (1 << i)
                node = node.children[toggle_bit_str]
            elif str(bit) in node.children:
                node = node.children[str(bit)]
            else:
                # 不应该出现这种情况
                break

        return max_xor


def max_xor_pair_trie(nums):
    """
    使用Trie树找最大XOR对

    时间复杂度: O(n * 32) = O(n)
    空间复杂度: O(n * 32) = O(n)
    """
    if len(nums) < 2:
        return 0

    trie = BitTrie()
    # 构建Trie树
    for num in nums:
        trie.insert(num)

    max_xor = 0
    # 对每个数字，找与它最大XOR的数
    for num in nums:
        xor_val = trie.find_max_xor(num)
        max_xor = max(max_xor, xor_val)

    return max_xor


def max_xor_pair_greedy(nums):
    """
    贪心法（不用Trie）：逐位构建答案

    时间复杂度: O(n * 32) = O(n)
    空间复杂度: O(n)
    """
    max_xor = 0
    prefix_mask = 0

    # 从最高位到最低位
    for i in range(31, -1, -1):
        prefix_mask |= (1 << i)  # 当前考虑的前缀
        prefixes = {num & prefix_mask for num in nums}

        # 尝试在当前位设为1
        temp = max_xor | (1 << i)

        # 检查是否存在两个数的前缀异或为temp
        for prefix in prefixes:
            if (temp ^ prefix) in prefixes:
                max_xor = temp
                break

    return max_xor


if __name__ == "__main__":
    print("=== 最大XOR对 ===\n")

    # 测试用例1：基本用例
    print("1. 基本用例:")
    test_cases = [
        [1, 2, 3, 4, 5],
        [8, 10, 2],
        [14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70],
    ]

    for nums in test_cases:
        brute = max_xor_pair_brute_force(nums)
        trie = max_xor_pair_trie(nums)
        greedy = max_xor_pair_greedy(nums)
        print(f"  数组: {nums}")
        print(f"  最大XOR (暴力): {brute}")
        print(f"  最大XOR (Trie): {trie}")
        print(f"  最大XOR (贪心): {greedy}")
        all_match = (brute == trie == greedy)
        print(f"  所有方法一致: {all_match}")
        print()

    # 测试用例2：XOR对的详细信息
    print("2. XOR对的详细信息:")
    nums = [1, 2, 3, 4, 5]
    print(f"  数组: {nums}")
    max_xor = 0
    best_pair = None
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            xor_val = nums[i] ^ nums[j]
            if xor_val > max_xor:
                max_xor = xor_val
                best_pair = (nums[i], nums[j])
            if xor_val >= 4:  # 只显示较大的XOR值
                print(f"    {nums[i]} ^ {nums[j]} = {xor_val}")
    print(f"  最大XOR对: {best_pair[0]} ^ {best_pair[1]} = {max_xor}")
    print()

    # 测试用例3：单个元素和两个元素
    print("3. 边界情况:")
    test_cases = [
        [5],
        [5, 3],
        [1],
        [7, 7],
    ]
    for nums in test_cases:
        result = max_xor_pair_trie(nums)
        print(f"  数组: {nums} -> 最大XOR: {result}")
    print()

    # 测试用例4：性能对比（大数组）
    print("4. 性能对比（较大数组）:")
    large_nums = list(range(1, 101))
    import time

    start = time.time()
    result_greedy = max_xor_pair_greedy(large_nums)
    greedy_time = time.time() - start

    start = time.time()
    result_trie = max_xor_pair_trie(large_nums)
    trie_time = time.time() - start

    print(f"  数组大小: {len(large_nums)}")
    print(f"  贪心法结果: {result_greedy}, 耗时: {greedy_time:.6f}s")
    print(f"  Trie法结果: {result_trie}, 耗时: {trie_time:.6f}s")
