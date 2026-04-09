// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

/// 组合计算 (Combination)
/// 计算从n个元素中选取k个元素的组合数

fn factorial(n: i64) -> i64 {
    let mut product = 1i64;
    for i in 1..=n {
        product *= i;
    }
    product
}

fn combine(n: i64, k: i64) -> i64 {
    factorial(n) / (factorial(k) * factorial(n - k))
}

fn main() {
    let n = 5;
    println!("组合计算 C(n,k)");
    println!("===============");
    
    for k in 1..=n {
        let result = combine(n, k);
        println!("C({},{}) = {}", n, k, result);
    }
}
