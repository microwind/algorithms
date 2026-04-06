/**
 * 阶乘递归示例
 * n! = n × (n-1) × (n-2) × ... × 1
 */

// 方法1: 递归版本
fn factorial_recursive(n: i32) -> i64 {
    /* 递归计算阶乘，O(n) 时间复杂度，O(n) 空间复杂度 */
    if n <= 1 {
        return 1;
    }
    n as i64 * factorial_recursive(n - 1);
}

// 方法2: 迭代版本
fn factorial_iterative(n: i32) -> i64 {
    /* 迭代计算阶乘，O(n) 时间复杂度，O(1) 空间复杂度 */
    let mut result: i64 = 1;
    for i in 2..=n {
        result *= i as i64;
    }
    result
}

// 方法3: 尾递归
fn factorial_tail(n: i32, acc: i64) -> i64 {
    /* 尾递归版本 */
    if n <= 1 {
        return acc;
    }
    factorial_tail(n - 1, n as i64 * acc);
}

fn factorial_tail_wrapper(n: i32) -> i64 {
    factorial_tail(n, 1)
}

fn main() {
    println!("=== 阶乘计算 ===\n");
    
    let test_values = [5, 10, 20];
    
    for &n in &test_values {
        println!("{}! = {}", n, factorial_recursive(n));
        println!("迭代版本: {}! = {}", n, factorial_iterative(n));
        println!("尾递归版本: {}! = {}", n, factorial_tail_wrapper(n));
        println!();
    }
}
