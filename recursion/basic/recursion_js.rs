/**
 * 递归算法示例集合（基于JavaScript版本）
 * 包含阶乘、递归计算等示例
 */

/**
 * 阶乘递归计算（版本1）
 */
fn factorial(x: i32) -> i32 {
    println!("x= {}", x);
    if x < 1 {
        return 0;
    }
    if x == 1 {
        return 1;
    }
    // 递归调用：x * (x-1) * (x-2) * ... * 1
    x * factorial(x - 1)
}

/**
 * 阶乘递归计算（版本2）
 */
fn factorial2(x: i32) -> i32 {
    println!("x= {}", x);
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
    println!("begin: n= {}", n);
    if n >= 15 {
        return n;
    }
    let n = n * 3;
    // 递归调用：recursion(n + 1) + recursion(n * 2)
    recursion(n + 1) + recursion(n * 2)
}

/**
 * 递归计算示例2
 */
fn recursion2(n: i32) -> i32 {
    println!("begin: n= {}", n);
    if n >= 15 {
        return n;
    }
    let n = n * 3;
    recursion2(n + 1) - recursion2(n * 2)
}

fn main() {
    println!("factorial(5) {}", factorial(5));
    println!("recursion(1)= {}", recursion(1));
    println!("recursion2(1)= {}", recursion2(1));
}
