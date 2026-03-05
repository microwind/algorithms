// 分支限界法求解最小装箱数问题

/*
问题描述：
给定 n 个物品及其体积和箱子容量，问最少需要多少个箱子能装下所有物品。
每个箱子容量为 cap，每个物品只能放入一个箱子。

算法思路：
- 按物品顺序尝试放入已有箱子或新箱子
- 剪枝：当前箱子数+下界>=最优解时直接返回
- 下界估计：剩余物品总和/箱子容量向上取整
*/

fn bin_packing_branch_and_bound(
    items: &[usize],
    cap: usize,
    bins: &mut Vec<usize>,
    idx: usize,
    best: &mut usize,
) {
    if bins.len() >= *best {
        return;
    }
    if idx == items.len() {
        *best = bins.len().min(*best);
        return;
    }
    // 剪枝：下界估计
    let remain_sum: usize = items[idx..].iter().sum();
    let lower = (remain_sum + cap - 1) / cap;
    if bins.len() + lower >= *best {
        return;
    }
    // 尝试放入已有箱子
    for i in 0..bins.len() {
        if bins[i] + items[idx] <= cap {
            bins[i] += items[idx];
            bin_packing_branch_and_bound(items, cap, bins, idx + 1, best);
            bins[i] -= items[idx];
        }
    }
    // 尝试新开一个箱子
    bins.push(items[idx]);
    bin_packing_branch_and_bound(items, cap, bins, idx + 1, best);
    bins.pop();
}

fn min_bins(items: &[usize], cap: usize) -> usize {
    let mut best = items.len();
    let mut bins = Vec::new();
    bin_packing_branch_and_bound(items, cap, &mut bins, 0, &mut best);
    best
}

fn main() {
    println!("==============================");
    println!("Bin Packing Problem (Rust)");
    println!("==============================\n");
    let items = vec![7, 5, 5, 3, 3, 3, 2];
    let cap = 10;
    println!("物品体积: {:?}", items);
    println!("箱子容量: {}", cap);
    let min_bin = min_bins(&items, cap);
    println!("最小箱子数: {}", min_bin);
    // 更多测试
    let items2 = vec![8, 8, 8, 8, 2, 2, 2, 2];
    let min_bin2 = min_bins(&items2, 10);
    println!("\n物品体积: {:?}", items2);
    println!("箱子容量: 10");
    println!("最小箱子数: {}", min_bin2);
}

/*
输出示例：
==============================
Bin Packing Problem (Rust)
==============================

物品体积: [7, 5, 5, 3, 3, 3, 2]
箱子容量: 10
最小箱子数: 3

物品体积: [8, 8, 8, 8, 2, 2, 2, 2]
箱子容量: 10
最小箱子数: 4
*/
