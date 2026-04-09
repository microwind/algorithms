// Copyright https://github.com/microwind
// GCD - Greatest Common Divisor

fn gcd(mut x: i32, mut y: i32) -> i32 {
    while y != 0 {
        let temp = y;
        y = x % y;
        x = temp;
    }
    x
}

fn main() {
    println!("GCD(48, 18) = {}", gcd(48, 18));
    println!("GCD(56, 98) = {}", gcd(56, 98));
}
