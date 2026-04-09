// Copyright https://github.com/microwind
// Fast Power (Binary Exponentiation)

fn fast_power(mut base: i64, mut exponent: i64, mod_val: i64) -> i64 {
    let mut result = 1i64;
    base = base % mod_val;
    while exponent > 0 {
        if exponent & 1 == 1 {
            result = (result * base) % mod_val;
        }
        base = (base * base) % mod_val;
        exponent >>= 1;
    }
    result
}

fn main() {
    println!("2^10 = {}", fast_power(2, 10, 1000000007));
    println!("3^5 = {}", fast_power(3, 5, 1000000007));
}
