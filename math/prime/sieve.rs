// Copyright https://github.com/microwind
// Sieve of Eratosthenes

fn sieve(n: usize) {
    let mut is_prime = vec![true; n + 1];
    is_prime[0] = false;
    if n > 0 { is_prime[1] = false; }
    
    for p in 2..=n {
        if p * p > n { break; }
        if is_prime[p] {
            let mut i = p * p;
            while i <= n {
                is_prime[i] = false;
                i += p;
            }
        }
    }
    
    print!("Primes up to {}: ", n);
    for i in 2..=n {
        if is_prime[i] { print!("{} ", i); }
    }
    println!();
}

fn main() {
    sieve(50);
}
