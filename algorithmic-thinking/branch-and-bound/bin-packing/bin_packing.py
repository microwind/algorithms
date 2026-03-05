"""
装箱问题 - 分支定界算法
将n个物品装入最少数量的容量相同的箱子中
"""

class BinPacking:
    def __init__(self, items, bin_capacity):
        """
        初始化装箱求解器
        items: 物品重量列表
        bin_capacity: 每个箱的最大容量
        时间: O(n), 空间: O(n)
        """
        self.items = items
        self.bin_capacity = bin_capacity
        self.n = len(items)
        # 首先应用描准
        self.items.sort(reverse=True)
        
        self.min_bins = float('inf')
        self.best_packing = []
        self.current_bins = []
    
    def lower_bound(self, item_idx):
        """
        使用空间法砼计算下界
        时间: O(n), 空间: O(n)
        """
        # 最少我们需要ceil(剩余物品/箱容量)个箱子
        total_weight = sum(self.items[item_idx:])
        return -(-total_weight // self.bin_capacity)  # Ceiling division
    
    def branch_and_bound(self, item_idx=0):
        """
        分支定界及剪枝
        时间: 指数级及剪枝, 空间: O(最优箱子数)
        """
        # 剪枝：当前箱数 + 下界 >= 最优，跳过
        if len(self.current_bins) + self.lower_bound(item_idx) >= self.min_bins:
            return
        
        # 基础情况：所有物品已装
        if item_idx == self.n:
            if len(self.current_bins) < self.min_bins:
                self.min_bins = len(self.current_bins)
                self.best_packing = [bin[:] for bin in self.current_bins]
            return
        
        # 尝试把物品放入现有的箱子
        item = self.items[item_idx]
        placed = False
        
        for bin_idx in range(len(self.current_bins)):
            if sum(self.current_bins[bin_idx]) + item <= self.bin_capacity:
                self.current_bins[bin_idx].append(item)
                self.branch_and_bound(item_idx + 1)
                self.current_bins[bin_idx].pop()
                placed = True
                break
        
        # 尝试加入一个新箱子
        if len(self.current_bins) < self.min_bins:
            self.current_bins.append([item])
            self.branch_and_bound(item_idx + 1)
            self.current_bins.pop()
    
    def solve(self):
        """
        求解并返回最少箱数和装箱方案
        """
        # Initialize with First Fit Decreasing estimate
        temp_bins = []
        for item in self.items:
            placed = False
            for bin_idx in range(len(temp_bins)):
                if sum(temp_bins[bin_idx]) + item <= self.bin_capacity:
                    temp_bins[bin_idx].append(item)
                    placed = True
                    break
            if not placed:
                temp_bins.append([item])
        
        self.min_bins = len(temp_bins)
        self.best_packing = [bin[:] for bin in temp_bins]
        
        # Try to optimize with branch and bound
        self.branch_and_bound()
        
        return self.min_bins, self.best_packing


# 测试和例子
if __name__ == "__main__":
    print("=" * 60)
    print("Bin Packing Problem - Branch and Bound")
    print("=" * 60)
    
    # Test case 1
    items = [7, 5, 5, 3, 3, 3, 2]
    bin_capacity = 10
    
    print(f"\nItems: {items}")
    print(f"Bin Capacity: {bin_capacity}")
    print(f"Total Weight: {sum(items)}")
    
    solver = BinPacking(items, bin_capacity)
    num_bins, packing = solver.solve()
    
    print(f"\nMinimum Number of Bins: {num_bins}")
    print("\nPacking:")
    for i, bin_items in enumerate(packing):
        bin_weight = sum(bin_items)
        print(f"Bin {i}: {bin_items} (weight: {bin_weight}/{bin_capacity})")
    
    # Test case 2
    print("\n" + "=" * 60)
    items2 = [4, 8, 1, 4, 2, 1]
    bin_capacity2 = 10
    
    print(f"\nItems: {items2}")
    print(f"Bin Capacity: {bin_capacity2}")
    print(f"Total Weight: {sum(items2)}")
    
    solver2 = BinPacking(items2, bin_capacity2)
    num_bins2, packing2 = solver2.solve()
    
    print(f"\nMinimum Number of Bins: {num_bins2}")
    print("\nPacking:")
    for i, bin_items in enumerate(packing2):
        bin_weight = sum(bin_items)
        print(f"Bin {i}: {bin_items} (weight: {bin_weight}/{bin_capacity2})")
