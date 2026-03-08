"""
汉诺塔问题 - 经典递归示例

问题：将 n 个盘子从 A 柱移动到 C 柱
规则：
- 每次只能移动一个盘子
- 大盘子不能放在小盘子上面
"""

move_count = 0

def hanoi(n, source, target, auxiliary):
    """
    解决汉诺塔问题
    时间复杂度: O(2^n - 1)
    空间复杂度: O(n) - 递归栈深度
    """
    global move_count
    
    # 基本情况：如果只有一个盘子，直接从 source 移动到 target
    if n == 1:
        # 移动盘子1 从 source 到 target
        move_count += 1
        print(f"Move disk 1 from {source} to {target}")
        return
    
    # 第一步：将 n-1 个盘子从 source 移到 auxiliary
    hanoi(n - 1, source, auxiliary, target)
    
    # 第二步：将第 n 个盘子从 source 移到 target
    move_count += 1
    print(f"Move disk {n} from {source} to {target}")
    
    # 第三步：将 n-1 个盘子从 auxiliary 移到 target
    hanoi(n - 1, auxiliary, target, source)

if __name__ == "__main__":
    print("=== 汉诺塔问题 ===\n")
    
    for n in [2, 3, 4]:
        print(f"n = {n}:")
        move_count = 0
        hanoi(n, 'A', 'C', 'B')
        print(f"总移动次数: {move_count} (应为 {2**n - 1})\n")
