"""
递归算法（Recursion）- 自相似问题的优雅解法

递归的本质：
- 函数调用自身
- 问题通过自身的简化版本来解决
- 必须有明确的终止条件（基础情况）

递归的三个要素：
1. 基础情况（Base Case）
   - 最简单的问题实例
   - 不需要递归直接返回答案
   - 防止无限递归

2. 递归关系（Recursive Relation）
   - 将原问题分解为更小的相同问题
   - f(n) 通过 f(n-1)、f(n-2) 等表示

3. 递归调用（Recursive Call）
   - 调用自身处理更小的问题
   - 每次调用规模都在减小

递归的优点：
- 代码简洁，逻辑清晰
- 问题定义与解决方案的对应

递归的缺点：
- 可能导致栈溢出（深度递归）
- 需要额外的栈空间
- 可能有重复计算

优化技巧：
- 记忆化（Memoization）：缓存子问题的结果
- 尾递归优化：某些编译器能优化直接返回递归调用的函数
- 迭代化：将递归改写为迭代

常见应用：
- 数学序列：阶乘、斐波那契
- 数据结构：树的遍历和操作
- 分治算法：归并排序、快速排序
- 搜索问题：DFS、回溯、组合等
- 字符串/数组处理
"""

# 问题 1: 阶乘（Factorial）
def factorial(n):
    """
    计算 n!（阶乘）
    
    数学定义：
    n! = n × (n-1) × (n-2) × ... × 1
    特殊定义：0! = 1
    
    递推关系：
    n! = n × (n-1)!
    基础情况：0! = 1 或 1! = 1
    
    时间复杂度：O(n)
    空间复杂度：O(n)（递归调用栈深度）
    
    参数:
        n: 非负整数
    
    返回:
        n 的阶乘
    
    示例:
        factorial(5) → 5 * 4 * 3 * 2 * 1 = 120
    """
    # 基础情况：任何数与 0 的阶乘定义为 1
    if n == 0 or n == 1:
        return 1
    
    # 递归关系：n! = n * (n-1)!
    # 关键：每次递归调用的参数规模减小（n → n-1）
    return n * factorial(n - 1)

# 问题 2: 斐波那契数列（Fibonacci）
def fibonacci(n):
    """
    计算第 n 个斐波那契数（带记忆化）
    
    数列定义：F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
    序列：0, 1, 1, 2, 3, 5, 8, 13, 21, ...
    
    递推关系：
    F(n) = F(n-1) + F(n-2)
    基础情况：F(0) = 0, F(1) = 1
    
    警告：朴素递归会导致大量重复计算！
    例如 F(5) 会计算 F(3) 两次、F(2) 三次等
    解决方案：使用记忆化缓存已计算的结果
    
    时间复杂度：O(n)（带记忆化），O(2^n)（朴素递归）
    空间复杂度：O(n)
    
    参数:
        n: 斐波那契数列的位置
    
    返回:
        第 n 个斐波那契数
    
    示例:
        fibonacci(6) → 8
        调用树：
            F(6)
            ├─ F(5)
            │  ├─ F(4)
            │  │  ├─ F(3)
            │  │  │  ├─ F(2)
            │  │  │  │  ├─ F(1) = 1
            │  │  │  │  └─ F(0) = 0
            │  │  │  └─ F(1) = 1
    """
    # 使用字典作为缓存（记忆化）
    memo = {}
    
    def _fibonacci_helper(n):
        # 检查缓存：如果已计算过，直接返回
        if n in memo:
            return memo[n]
        
        # 基础情况：递归的终止条件
        if n == 0:
            return 0
        if n == 1:
            return 1
        
        # 递归关系：F(n) = F(n-1) + F(n-2)
        # 分别计算两个子问题
        result = _fibonacci_helper(n - 1) + _fibonacci_helper(n - 2)
        
        # 缓存结果：避免重复计算
        memo[n] = result
        
        return result
    
    return _fibonacci_helper(n)

# 问题 3: 幂集（Power Set）
def power_set(nums):
    """
    生成一个集合的所有子集
    
    幂集定义：集合 S 的幂集是 S 的所有子集组成的集合
    例如：{1, 2} 的幂集是 {∅, {1}, {2}, {1,2}}
    
    递推关系：
    power_set([1,2,3]) 可以从 power_set([1,2]) 得到
    新增的 3 可以：
    - 不加到已有的所有子集中
    - 加到已有的所有子集中
    
    基础情况：power_set([]) = [[]]（只有空集）
    
    时间复杂度：O(n * 2^n)（有 2^n 个子集，每个平均 n/2 个元素）
    空间复杂度：O(2^n)（存储所有子集）
    
    参数:
        nums: 输入集合（用列表表示）
    
    返回:
        所有子集的列表
    
    示例:
        power_set([1, 2]) → [[], [1], [2], [1, 2]]
    """
    # 基础情况：空集的子集只有自己
    if not nums:
        return [[]]
    
    # 递归关系：取出第一个元素
    first = nums[0]
    rest = nums[1:]
    
    # 递归求解：得到剩余元素的幂集
    rest_power_set = power_set(rest)
    
    # 合并：构建包含第一个元素的所有子集
    result = []
    
    # 第一部分：不包含 first 的所有子集（直接来自剩余的幂集）
    result.extend(rest_power_set)
    
    # 第二部分：包含 first 的所有子集（在剩余幂集的每个子集前加上 first）
    for subset in rest_power_set:
        result.append([first] + subset)
    
    return result

# 问题 4: 树的深度优先搜索（DFS）
class TreeNode:
    """
    二叉树节点定义，用于树的递归操作
    """
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def dfs_preorder(root):
    """
    深度优先搜索 - 前序遍历（先根遍历）
    
    遍历顺序：根 → 左子树 → 右子树
    
    递推关系：
    访问根节点，递归遍历左子树，递归遍历右子树
    
    基础情况：节点为 None 时返回
    
    时间复杂度：O(n)（访问每个节点一次）
    空间复杂度：O(h)（h 是树的高度，递归栈深度）
    
    应用：
    - 复制树
    - 序列化树
    - 表达式求值（中缀变前缀）
    """
    result = []
    
    def dfs(node):
        # 基础情况：遇到空节点停止递归
        if node is None:
            return
        
        # 访问根节点
        result.append(node.val)
        
        # 递归遍历左子树
        dfs(node.left)
        
        # 递归遍历右子树
        dfs(node.right)
    
    dfs(root)
    return result

def dfs_inorder(root):
    """
    深度优先搜索 - 中序遍历
    
    遍历顺序：左子树 → 根 → 右子树
    
    特点：对二叉搜索树进行中序遍历可得到递增序列
    """
    result = []
    
    def dfs(node):
        if node is None:
            return
        
        # 递归遍历左子树
        dfs(node.left)
        
        # 访问根节点
        result.append(node.val)
        
        # 递归遍历右子树
        dfs(node.right)
    
    dfs(root)
    return result

# 问题 5: 括号匹配验证
def is_valid_parentheses(s):
    """
    验证括号是否匹配
    
    问题：判断字符串中的括号是否正确配对
    支持的括号：()、[]、{}
    
    递推思路：
    - 如果字符串首尾不是匹配的括号，直接返回 False
    - 否则，问题归结为验证内部是否匹配
    
    基础情况：
    - 空字符串：True（没有括号，视为匹配）
    - 长度为奇数：False（不可能匹配）
    
    时间复杂度：O(n)（平均），最坏 O(n^2)
    空间复杂度：O(n)（递归调用栈）
    
    参数:
        s: 输入字符串
    
    返回:
        True 如果括号匹配，False 否则
    
    示例:
        is_valid_parentheses("()[]{}") → True
        is_valid_parentheses("([{}])") → True
        is_valid_parentheses("([)]") → False
    """
    # 基础情况 1：空字符串或长度为 0
    if not s:
        return True
    
    # 基础情况 2：长度为奇数，不可能匹配
    if len(s) % 2 != 0:
        return False
    
    # 定义括号对
    pairs = {'(': ')', '[': ']', '{': '}'}
    
    # 递归关系：检查首尾是否匹配
    if len(s) >= 2:
        # 如果首字符是左括号且下一字符是对应的右括号
        if s[0] in pairs and s[1] == pairs[s[0]]:
            # 递归验证去掉首尾后的内部字符串
            return is_valid_parentheses(s[2:])
        
        # 尝试其他配对方式（处理更复杂的嵌套）
        # 例如 [(){}]：首字符 [ 与某个 ] 配对，递归验证中间部分
        for i in range(2, len(s), 2):
            if s[0] in pairs and s[i] == pairs[s[0]]:
                # 验证 [1, i] 之间是否有效（开括号到闭括号之间）
                # 以及 [i+1, 末尾] 之后是否有效
                if is_valid_parentheses(s[1:i]) and is_valid_parentheses(s[i+1:]):
                    return True
    
    return False

# 问题 6: 反转字符串
def reverse_string(s):
    """
    递归反转字符串
    
    思路：
    - 基础情况：空字符串或单个字符返回原值
    - 递推：reverse(s) = reverse(s[1:]) + s[0]
    
    时间复杂度：O(n²)（字符串拼接）
    空间复杂度：O(n)（递归栈 + 字符串存储）
    
    参数:
        s: 输入字符串
    
    返回:
        反转后的字符串
    
    示例:
        reverse_string("hello") → "olleh"
    """
    # 基础情况：空字符串或单字符
    if len(s) <= 1:
        return s
    
    # 递推：[最后一个字符] + [剩余字符反转]
    return reverse_string(s[1:]) + s[0]

# 测试代码
if __name__ == "__main__":
    print("=" * 70)
    print("递归算法 - 完整中文注释版本")
    print("=" * 70)
    
    # 测试阶乘
    print("\n1. 阶乘计算")
    n = 5
    result = factorial(n)
    print(f"   {n}! = {result}")
    print(f"   递推关系：{n}! = {n} × {n-1}! = {n} × {factorial(n-1)}")
    
    # 测试斐波那契
    print("\n2. 斐波那契数列（带记忆化）")
    n = 10
    result = fibonacci(n)
    print(f"   F({n}) = {result}")
    print(f"   序列：", end="")
    for i in range(n + 1):
        print(f"F({i})={fibonacci(i)}", end=" ")
    print()
    
    # 测试幂集
    print("\n3. 幂集（Power Set）")
    nums = [1, 2, 3]
    subsets = power_set(nums)
    print(f"   集合 {nums} 的幂集（共 {len(subsets)} 个子集）:")
    for i, subset in enumerate(subsets):
        print(f"      {i}: {subset}")
    
    # 测试树的遍历
    print("\n4. 树的深度优先搜索")
    # 构建测试树：
    #       1
    #      / \
    #     2   3
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    
    preorder = dfs_preorder(root)
    inorder = dfs_inorder(root)
    print(f"   前序遍历（Pre-order）: {preorder}")
    print(f"   中序遍历（In-order）: {inorder}")
    
    # 测试括号匹配
    print("\n5. 括号匹配验证")
    test_cases = ["()", "([{}])", "([)]", ""]
    for case in test_cases:
        result = is_valid_parentheses(case)
        print(f"   '{case}' → {result}")
    
    # 测试字符串反转
    print("\n6. 字符串反转（递归）")
    s = "hello"
    reversed_s = reverse_string(s)
    print(f"   '{s}' → '{reversed_s}'")
    
    print("\n" + "=" * 70)
