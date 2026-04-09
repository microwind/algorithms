// Copyright https://github.com/microwind
// Perfect Number Check

fn is_perfect(n: i32) -> bool {
    if n <= 1 {
        return false;
    }
    let mut sum = 1;
    let mut i = 2;
    while i * i <= n {
        if n % i == 0 {
            sum += i;
            if i != n / i {
                sum += n / i;
            }
        }
        i += 1;
    }
    sum == n
}

fn main() {
    print!("Perfect numbers up to 1000: ");
    for i in 1..=1000 {
        if is_perfect(i) {
            print!("{} ", i);
        }
    }
    println!();
}
