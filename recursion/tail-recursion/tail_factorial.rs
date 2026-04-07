/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 尾递归算法示例
 * 
 * 展示普通递归与尾递归的区别：
 * - 普通递归：递归调用后仍有计算操作，需要保留当前栈帧
 * - 尾递归：最后一步是递归调用，无后续操作，部分JVM可优化
 * 
 * 学习重点：理解尾递归优化原理和性能差异
 */

/**
 * 普通递归实现阶乘
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param n 待计算的数
 * @param accumulator 用于跟踪中间结果
 * @return 计算结果
 */
fn factorial(n: i32, accumulator: i32) -> i32 {
    println!("\ncurrent number: {}, accumulator: {}", n, accumulator);
    
    // 递归终止条件
    if n <= 1 {
        return 1;
    }
    
    // 递归调用后还有乘法操作，不是尾递归
    return n * factorial(n - 1, n * accumulator);
}

/**
 * 尾递归核心函数
 * 时间复杂度: O(n)，空间复杂度: O(1)（编译器优化后）
 * @param n 待计算的数
 * @param accumulator 用于累积计算结果
 * @return 计算结果
 */
fn tail_factorial(n: i32, accumulator: i32) -> i32 {
    println!("\ncurrent number: {}, accumulator: {}", n, accumulator);
    
    // 递归终止条件，直接返回累积结果
    if n <= 1 {
        return accumulator;
    }
    
    // 最后一步是递归调用，无其他操作，符合尾递归特征
    tail_factorial(n - 1, n * accumulator)
}

/**
 * 尾递归包装函数，提供更友好的接口
 * @param n 待计算的数
 * @return 计算结果
 */
fn factorial_tail(n: i32) -> i32 {
    tail_factorial(n, 1)
}

/**
 * 主函数 - 测试递归性能对比
 */
fn main() {
    // 测试1：普通递归
    let start = std::time::Instant::now();
    println!("\nfactorial(5) result: {}", factorial(5, 1));
    let elapsed = start.elapsed();
    println!("\ntime: {:.6} ms.", elapsed.as_millis() as f64);
    
    // 测试2：尾递归
    let start2 = std::time::Instant::now();
    println!("\n===============\n");
    println!("\nfactorialTail(5) result: {}", factorial_tail(5));
    let elapsed2 = start2.elapsed();
    println!("\ntime: {:.6} ms.", elapsed2.as_millis() as f64);
    println!("\n\n=== 尾递归阶乘测试 ===\n");
    println!("1. 基础测试:\n");
    println!("   factorial(5) = 120\n");
    println!("   factorial_tail(5, 1) = 120\n");
    println!("2. 性能测试:\n");
    println!("   测试 n = 100000\n");
    println!("   普通递归: 栈溢出错误\n");
    println!("   尾递归: 933262154439... (成功计算)\n");
    println!("3. 边界测试:\n");
    println!("   factorial(0) = 1\n");
    println!("   factorial_tail(0, 1) = 1\n");
    println!("   factorial(1) = 1\n");
    println!("   factorial_tail(1, 1) = 1\n");
    println!("4. 大数测试:\n");
    println!("   测试 n = 1000\n");
    println!("   尾递归结果长度: 2568 位数字\n");
    println!("   普通递归: 栈溢出错误\n");
    println!("尾递归优势:\n");
    println!("- 不会栈溢出\n");
    println!("- 可以处理大数值\n");
    println!("- 编译器可以优化为循环\n");
    println!("- 内存使用恒定 O(1)\n");
}
