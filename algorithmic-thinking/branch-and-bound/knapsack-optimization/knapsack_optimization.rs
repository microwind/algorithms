// 0-1 Knapsack Branch and Bound (Rust)

use std::cmp;

#[derive(Clone, Debug)]
struct Item {
    weight: i32,
    value: i32,
    index: usize,
    ratio: f64,
}

fn sort_items(weights: &[i32], values: &[i32]) -> Vec<Item> {
    // 创建物品列表并按价值/重量比排序
    let mut items: Vec<Item> = weights.iter().enumerate().map(|(i, &w)| {
        Item {
            weight: w,
            value: values[i],
            index: i,
            ratio: values[i] as f64 / w as f64,
        }
    }).collect();
    items.sort_by(|a, b| b.ratio.partial_cmp(&a.ratio).unwrap());
    items
}

fn upper_bound(idx: usize, weight: i32, profit: i32, items: &[Item], capacity: i32) -> i32 {
    if weight >= capacity { return profit; }
    let mut bound = profit as f64;
    let mut remain = capacity - weight;
    // 贪心选择，选择价值/重量比最高的物品
    for i in idx..items.len() {
        let item = &items[i];
        // 物品 i 可以完全放入背包
        if item.weight <= remain {
            bound += item.value as f64;
            remain -= item.weight;
        } else {
            // 物品 i 只能部分放入背包，加入剩余容量的分数部分价值
            bound += item.value as f64 * remain as f64 / item.weight as f64;
            break;
        }
    }
    bound as i32
}

fn branch_and_bound(
    idx: usize,
    weight: i32,
    profit: i32,
    items: &[Item],
    capacity: i32,
    cur_items: &mut Vec<u8>,
    best_items: &mut Vec<u8>,
    max_profit: &mut i32,
) {
    if upper_bound(idx, weight, profit, items, capacity) <= *max_profit { return; }
    if idx == items.len() {
        if profit > *max_profit {
            *max_profit = profit;
            best_items.clone_from(cur_items);
        }
        return;
    }
    let k = items[idx].index;
    // 分之1：包含当前物品, 递归处理下一个物品
    if weight + items[idx].weight <= capacity {
        cur_items[k] = 1;
        branch_and_bound(idx + 1, weight + items[idx].weight, profit + items[idx].value, items, capacity, cur_items, best_items, max_profit);
        cur_items[k] = 0;
    }
    // 分之2：不包含当前物品, 直接递归处理下一个物品
    branch_and_bound(idx + 1, weight, profit, items, capacity, cur_items, best_items, max_profit);
}

fn solve(weights: &[i32], values: &[i32], capacity: i32) -> (i32, Vec<u8>, i32) {
    let n = weights.len();
    let items = sort_items(weights, values);
    let mut cur_items = vec![0u8; n];
    let mut best_items = vec![0u8; n];
    let mut max_profit = 0;
    // 从物品 0 开始分支限界搜索
    branch_and_bound(0, 0, 0, &items, capacity, &mut cur_items, &mut best_items, &mut max_profit);
    let total_weight: i32 = best_items.iter().enumerate().map(|(i, &b)| if b == 1 { weights[i] } else { 0 }).sum();
    (max_profit, best_items, total_weight)
}

fn print_result(weights: &[i32], values: &[i32], capacity: i32, max_profit: i32, best_items: &[u8], total_weight: i32) {
    println!("Weights: {:?}", weights);
    println!("Values:  {:?}", values);
    println!("Capacity: {}", capacity);
    println!("Maximum Profit: {}", max_profit);
    print!("Selected Items: ");
    for (i, &b) in best_items.iter().enumerate() {
        if b == 1 { print!("{} ", i); }
    }
    println!("\nTotal Weight: {}", total_weight);
}

fn main() {
    println!("==============================");
    println!("0-1 Knapsack Optimization (Rust)");
    println!("==============================\n");
    // Test case 1
    let weights1 = vec![2, 3, 4, 5];
    let values1 = vec![3, 4, 5, 6];
    let capacity1 = 8;
    let (max_profit1, best_items1, total_weight1) = solve(&weights1, &values1, capacity1);
    println!("Test Case 1:");
    print_result(&weights1, &values1, capacity1, max_profit1, &best_items1, total_weight1);
    println!("\n==============================");
    // Test case 2
    let weights2 = vec![5, 4, 3, 4, 2];
    let values2 = vec![10, 40, 30, 50, 35];
    let capacity2 = 10;
    let (max_profit2, best_items2, total_weight2) = solve(&weights2, &values2, capacity2);
    println!("Test Case 2:");
    print_result(&weights2, &values2, capacity2, max_profit2, &best_items2, total_weight2);
}
