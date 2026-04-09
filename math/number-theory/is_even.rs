// Copyright https://github.com/microwind
// Check if number is even/odd

fn is_even(n: i32) -> bool {
    n % 2 == 0
}

fn main() {
    let test_numbers = [2, 3, 4, 5, 10, 15];
    for n in test_numbers {
        println!("{} is {}", n, if is_even(n) { "even" } else { "odd" });
    }
}
