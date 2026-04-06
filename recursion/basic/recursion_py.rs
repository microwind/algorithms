/**
 * 递归算法示例集合（基于Python版本）
 * 包含阶乘、斐波那契、汉诺塔、二分查找、数组求和、字符串反转等示例
 */
use std::collections::HashMap;

// 1. 阶乘 (Factorial)
// 时间复杂度: O(n), 空间复杂度: O(n)（递归栈深度）
fn factorial(n: i32) -> i32 {
    /* 计算 n 的阶乘 */
    if n <= 1 {
        return 1;
    }
    n * factorial(n - 1)
}

// 2. 斐波那契数列
// 普通递归: 时间复杂度 O(2^n)，空间复杂度 O(n)
fn fibonacci(n: i32) -> i32 {
    /* 计算斐波那契数列第 n 项（普通递归） */
    if n <= 1 {
        return n;
    }
    fibonacci(n - 1) + fibonacci(n - 2)
}

// 优化版本（记忆化）
fn fibonacci_memo_helper(n: i32, memo: &mut HashMap<i32, i32>) -> i32 {
    if let Some(&val) = memo.get(&n) {
        return val;
    }
    
    let result = if n <= 1 {
        n
    } else {
        fibonacci_memo_helper(n - 1, memo) + fibonacci_memo_helper(n - 2, memo)
    };
    
    memo.insert(n, result);
    result
}

fn fibonacci_memo(n: i32) -> i32 {
    /* 计算斐波那契数列第 n 项（带记忆化） */
    let mut memo: HashMap<i32, i32> = HashMap::new();
    fibonacci_memo_helper(n, &mut memo)
}

// 3. 汉诺塔问题
// 时间复杂度: O(2^n - 1)，空间复杂度: O(n)
fn hanoi(n: i32, source: &str, target: &str, auxiliary: &str) {
    /*
     * 解决汉诺塔问题
     * 将 n 个盘子从 source 柱移动到 target 柱
     */
    if n == 1 {
        println!("Move disk 1 from {} to {}", source, target);
        return;
    }
    
    // 将 n-1 个盘子从 source 移动到 auxiliary
    hanoi(n - 1, source, auxiliary, target);
    
    // 将最后一个盘子从 source 移动到 target
    println!("Move disk {} from {} to {}", n, source, target);
    
    // 将 n-1 个盘子从 auxiliary 移动到 target
    hanoi(n - 1, auxiliary, target, source);
}

// 4. 二分查找（递归版本）
// 时间复杂度: O(log n)，空间复杂度: O(log n)
fn binary_search(arr: &[i32], target: i32, low: usize, high: isize) -> isize {
    /* 在排序数组中递归查找目标值 */
    if low as isize > high {
        return -1;
    }
    
    let mid = (low as isize + high) / 2;
    
    if arr[mid as usize] == target {
        mid
    } else if arr[mid as usize] > target {
        binary_search(arr, target, low, mid - 1)
    } else {
        binary_search(arr, target, mid as usize + 1, high)
    }
}

fn binary_search_wrapper(arr: &[i32], target: i32) -> isize {
    binary_search(arr, target, 0, (arr.len() - 1) as isize)
}

// 5. 数组求和
// 时间复杂度: O(n)，空间复杂度: O(n)
fn array_sum(arr: &[i32], index: usize) -> i32 {
    /* 递归计算数组元素和 */
    if index >= arr.len() {
        return 0;
    }
    arr[index] + array_sum(arr, index + 1)
}

fn array_sum_wrapper(arr: &[i32]) -> i32 {
    array_sum(arr, 0)
}

// 6. 反转字符串
// 时间复杂度: O(n)，空间复杂度: O(n)
fn reverse_string(s: &str) -> String {
    /* 递归反转字符串 */
    if s.is_empty() {
        return String::new();
    }
    let chars: Vec<char> = s.chars().collect();
    if chars.len() == 1 {
        chars[0].to_string()
    } else {
        reverse_string(&chars[1..].iter().collect::<String>()) + &chars[0].to_string()
    }
}

fn main() {
    println!("=== 递归算法测试 ===\n");
    
    // 测试阶乘
    println!("1. 阶乘");
    println!("5! = {}", factorial(5));
    
    // 测试斐波那契
    println!("\n2. 斐波那契数列");
    println!("fib(10) = {}", fibonacci(10));
    println!("fib(10) with memo = {}", fibonacci_memo(10));
    
    // 测试汉诺塔
    println!("\n3. 汉诺塔问题 (n=3)");
    hanoi(3, "A", "C", "B");
    
    // 测试二分查找
    println!("\n4. 二分查找");
    let arr = [1, 3, 5, 7, 9, 11, 13];
    println!("查找 7: 索引 = {}", binary_search_wrapper(&arr, 7));
    
    // 测试数组求和
    println!("\n5. 数组求和");
    let sum_arr = [1, 2, 3, 4, 5];
    println!("sum([1,2,3,4,5]) = {}", array_sum_wrapper(&sum_arr));
    
    // 测试字符串反转
    println!("\n6. 字符串反转");
    println!("reverse('hello') = {}", reverse_string("hello"));
}
