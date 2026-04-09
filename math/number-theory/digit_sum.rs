// Copyright https://github.com/microwind
// Digit Sum

fn digit_sum(mut n: i32) -> i32 {
    let mut sum = 0;
    while n > 0 {
        sum += n % 10;
        n /= 10;
    }
    sum
}

fn main() {
    let n = 12345;
    println!("Digit sum of {} = {}", n, digit_sum(n));
}
