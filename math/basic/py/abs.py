"""
数学基础 - 绝对值计算 (Absolute Value)
计算数值的绝对值
时间复杂度: O(1)
"""

def absolute_value(n):
    """
    计算整数的绝对值
    
    算法原理：
    - 正数：绝对值就是其本身
    - 负数：绝对值是其相反数
    - 零：绝对值是零
    
    参数:
        n: 要求绝对值的数
    返回:
        n的绝对值
    
    时间复杂度: O(1) - 常数时间
    空间复杂度: O(1) - 常数空间
    """
    return -n if n < 0 else n


def absolute_value_builtin(n):
    """
    使用Python内置abs函数
    """
    return abs(n)


def absolute_value_math(n):
    """
    使用math.fabs（返回浮点数）
    """
    import math
    return math.fabs(n)


def test_absolute_value():
    """测试函数"""
    print("=" * 40)
    print("    绝对值计算演示 (Absolute Value)")
    print("=" * 40)
    print()
    
    # 测试用例
    test_cases = [-42, 0, 100, -3.14, 2.718, -0, -999999, 1e10]
    
    print("测试数据及结果:")
    print("-" * 40)
    for num in test_cases:
        result = absolute_value(num)
        std_result = absolute_value_builtin(num)
        print(f"输入: {str(num):>12} | 自定义: {str(result):>12} | 内置: {str(std_result):>12}")
    
    # 数学性质
    print("\n" + "=" * 40)
    print("数学性质:")
    print("=" * 40)
    print("• 非负性: |x| ≥ 0")
    print("• 正定性: |x| = 0 当且仅当 x = 0")
    print("• 对称性: |-x| = |x|")
    print("• 三角不等式: |x + y| ≤ |x| + |y|")
    print("• 乘法性质: |x × y| = |x| × |y|")
    
    # 应用场景
    print("\n" + "=" * 40)
    print("应用场景:")
    print("=" * 40)
    print("• 距离计算: 曼哈顿距离、欧几里得距离")
    print("• 误差分析: 绝对误差、相对误差")
    print("• 数值比较: 比较浮点数精度")
    print("• 向量运算: 向量的模（长度）")
    
    # NumPy示例
    print("\n" + "=" * 40)
    print("NumPy向量化绝对值:")
    print("=" * 40)
    try:
        import numpy as np
        arr = np.array([-1, -2, -3, 4, 5])
        print(f"输入数组: {arr}")
        print(f"绝对值:   {np.abs(arr)}")
    except ImportError:
        print("NumPy未安装，跳过示例")
    
    # 代码示例
    print("\n" + "=" * 40)
    print("Python代码示例:")
    print("=" * 40)
    print("""
# 计算列表中所有数的绝对值
numbers = [-5, 3, -8, 1, -9]
abs_numbers = [abs(x) for x in numbers]  # [5, 3, 8, 1, 9]

# 使用map函数
abs_numbers = list(map(abs, numbers))

# 计算两点间曼哈顿距离
def manhattan_distance(x1, y1, x2, y2):
    return abs(x2 - x1) + abs(y2 - y1)

# 误差比较
def roughly_equal(a, b, epsilon=0.001):
    return abs(a - b) < epsilon
""")


if __name__ == "__main__":
    test_absolute_value()
