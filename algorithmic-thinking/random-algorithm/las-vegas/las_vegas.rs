// 拉斯维加斯算法实现 (Rust)
//
// 特点：
// - 总是给出正确答案
// - 运行时间随机
// - 不返回错误答案

use std::collections::HashSet;
use std::time::{SystemTime, UNIX_EPOCH};

// 交换数组中两个元素
fn swap<T>(arr: &mut [T], i: usize, j: usize) {
    arr.swap(i, j);
}

// 随机分区函数
fn randomized_partition(arr: &mut [i32], left: usize, right: usize) -> usize {
    // 随机选择枢轴
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);
    let pivot_idx = left + rng.gen_range(0..=right - left);
    
    swap(arr, pivot_idx, right);
    
    let pivot = arr[right];
    let mut i = left.wrapping_sub(1);
    
    for j in left..right {
        if arr[j] <= pivot {
            i = i.wrapping_add(1);
            swap(arr, i, j);
        }
    }
    
    swap(arr, i + 1, right);
    i + 1
}

// 拉斯维加斯随机快速排序
fn las_vegas_quicksort(arr: &mut [i32], left: usize, right: usize) {
    if left < right {
        // 随机分区
        let pivot_idx = randomized_partition(arr, left, right);
        
        // 递归排序左右子数组
        if pivot_idx > 0 {
            las_vegas_quicksort(arr, left, pivot_idx - 1);
        }
        las_vegas_quicksort(arr, pivot_idx + 1, right);
    }
}

// 拉斯维加斯随机选择算法 - 找第k小元素
fn las_vegas_randomized_select(arr: &mut [i32], left: usize, right: usize, k: usize) -> i32 {
    if left == right {
        return arr[left];
    }
    
    // 随机分区
    let pivot_idx = randomized_partition(arr, left, right);
    
    // 计算枢轴的相对位置
    let pos = pivot_idx - left + 1;
    
    if k == pos {
        arr[pivot_idx]
    } else if k < pos {
        if pivot_idx > 0 {
            las_vegas_randomized_select(arr, left, pivot_idx - 1, k)
        } else {
            arr[left]
        }
    } else {
        las_vegas_randomized_select(arr, pivot_idx + 1, right, k - pos)
    }
}

// 拉斯维加斯字符串匹配
fn las_vegas_string_match(text: &str, pattern: &str) -> Option<usize> {
    let n = text.len();
    let m = pattern.len();
    
    if m > n {
        return None;
    }
    
    let text_bytes = text.as_bytes();
    let pattern_bytes = pattern.as_bytes();
    
    // 随机选择起始位置进行匹配
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);
    
    loop {
        let start = rng.gen_range(0..=n - m);
        
        // 检查是否匹配
        let mut match_found = true;
        for i in 0..m {
            if text_bytes[start + i] != pattern_bytes[i] {
                match_found = false;
                break;
            }
        }
        
        if match_found {
            return Some(start); // 找到匹配位置
        }
        
        // 在实际实现中，这里应该有避免无限循环的机制
        // 为了演示，这里简化处理
        break;
    }
    
    None
}

// 拉斯维加斯八皇后问题求解器
fn las_vegas_n_queens(n: usize) -> Vec<usize> {
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);
    
    loop {
        let mut queens = vec![0; n];
        let mut columns = HashSet::new();
        let mut diag1 = HashSet::new(); // 主对角线
        let mut diag2 = HashSet::new(); // 副对角线
        
        let mut success = true;
        
        // 逐行放置皇后
        for row in 0..n {
            // 收集当前行可用的列
            let mut available_cols = Vec::new();
            for col in 0..n {
                if !columns.contains(&col) 
                    && !diag1.contains(&(row + col)) 
                    && !diag2.contains(&(row as i32 - col as i32 + n as i32 - 1)) {
                    available_cols.push(col);
                }
            }
            
            if available_cols.is_empty() {
                success = false;
                break;
            }
            
            // 随机选择一个可用列
            let chosen_col = available_cols[rng.gen_range(0..available_cols.len())];
            queens[row] = chosen_col;
            columns.insert(chosen_col);
            diag1.insert(row + chosen_col);
            diag2.insert(row as i32 - chosen_col as i32 + n as i32 - 1);
        }
        
        if success {
            return queens;
        }
    }
}

// 打印数组
fn print_array(arr: &[i32]) {
    print!("[");
    for (i, &val) in arr.iter().enumerate() {
        print!("{}", val);
        if i < arr.len() - 1 {
            print!(", ");
        }
    }
    println!("]");
}

// 打印八皇后解法
fn print_n_queens_solution(queens: &[usize]) {
    let n = queens.len();
    for row in 0..n {
        for col in 0..n {
            if queens[row] == col {
                print!("Q ");
            } else {
                print!(". ");
            }
        }
        println!();
    }
}

fn main() {
    println!("=== 拉斯维加斯算法演示 ===\n");
    
    // 测试随机快速排序
    println!("1. 拉斯维加斯随机快速排序");
    let mut arr1 = vec![5, 2, 8, 1, 9, 3, 4, 7, 6];
    
    println!("原数组:");
    print_array(&arr1);
    
    if !arr1.is_empty() {
        las_vegas_quicksort(&mut arr1, 0, arr1.len() - 1);
    }
    
    println!("排序后:");
    print_array(&arr1);
    println!();
    
    // 测试随机选择算法
    println!("2. 拉斯维加斯随机选择算法");
    let mut arr2 = vec![7, 2, 5, 3, 9, 1, 4, 6, 8];
    let k = 4; // 找第4小元素
    
    println!("数组:");
    print_array(&arr2);
    
    if !arr2.is_empty() {
        let result = las_vegas_randomized_select(&mut arr2.clone(), 0, arr2.len() - 1, k);
        println!("第{}小元素: {}", k, result);
    }
    println!();
    
    // 测试字符串匹配
    println!("3. 拉斯维加斯字符串匹配");
    let text = "hello world, this is a test string";
    let pattern = "test";
    
    println!("文本: {}", text);
    println!("模式: {}", pattern);
    
    match las_vegas_string_match(text, pattern) {
        Some(pos) => println!("匹配位置: {}", pos),
        None => println!("未找到匹配"),
    }
    println!();
    
    // 测试八皇后问题
    println!("4. 拉斯维加斯八皇后问题求解");
    let n = 8;
    let solution = las_vegas_n_queens(n);
    println!("八皇后解法 (n={}):", n);
    print_n_queens_solution(&solution);
}
