/**
 * 递归算法示例集合
 * 包含阶乘、递归计算、尾递归等示例
 */

/**
 * 阶乘递归计算
 */
fn factorial(x: i32) -> i32 {
    println!("\nx={}", x);
    if x < 1 {
        return x;
    }
    if x == 1 {
        return x;
    }
    // 递归调用：x * (x-1) * (x-2) * ... * 1
    x * factorial(x - 1)
}

/**
 * 阶乘递归计算（改进版）
 */
fn factorial2(x: i32) -> i32 {
    println!("\nx={}", x);
    if x <= 1 {
        return x;
    }
    // 递归调用：x * (x-1) * (x-2) * ... * 1
    x * factorial2(x - 1)
}

/**
 * 递归计算示例
 */
fn recursion(n: i32) -> i32 {
    println!("\nbegin: n={}", n);
    if n >= 15 {
        return n;
    }
    let n = n * 3;
    recursion(n + 1) + recursion(n * 2)
}

/**
 * 尾递归示例（单一递归调用，无后续操作）
 */
fn tail_recursion(n: i32, accumulator: i32) -> i32 {
    if n >= 15 {
        return accumulator + n; // 终止时直接返回结果
    }
    tail_recursion(n * 3 + 1, accumulator) // 最后一步仅递归调用
}

/**
 * 递归计算示例2
 */
fn recursion2(n: i32) -> i32 {
    println!("\nbegin: n={}", n);
    if n >= 15 {
        return n;
    }
    let n = n * 3;
    recursion2(n + 1) - recursion2(n * 2)
}

fn main() {
    println!("\r\nfactorial(5) {}", factorial(5));
    println!("\r\n===");
    println!("\r\nfactorial2(5) {}", factorial2(5));
    println!("\r\n===");
    println!("\r\nrecursion(1) {}", recursion(1));
    println!("\r\n===");
    println!("\r\nrecursion2(1) {}", recursion2(1));
}
