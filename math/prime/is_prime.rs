// Copyright https://github.com/microwind
// Prime Number Check

fn is_prime(n: i32) -> bool {
    if n <= 1 {
        return false;
    }
    if n <= 3 {
        return true;
    }
    if n % 2 == 0 || n % 3 == 0 {
        return false;
    }
    let mut i = 5;
    while i * i <= n {
        if n % i == 0 || n % (i + 2) == 0 {
            return false;
        }
        i += 6;
    }
    true
}

fn main() {
    print!("Primes up to 50: ");
    for i in 1..=50 {
        if is_prime(i) {
            print!("{} ", i);
        }
    }
    println!();
}
