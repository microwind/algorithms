// Copyright https://github.com/microwind
// Fibonacci Sequence

fn fibonacci(n: i32) -> i64 {
    if n <= 1 {
        return n as i64;
    }
    let mut first: i64 = 0;
    let mut second: i64 = 1;
    let mut result: i64 = 0;
    for _ in 1..n {
        result = first + second;
        first = second;
        second = result;
    }
    result
}

fn main() {
    println!("Fibonacci Sequence:");
    for i in 0..=10 {
        println!("F({}) = {}", i, fibonacci(i));
    }
}
