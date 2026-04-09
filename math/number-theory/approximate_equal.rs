// Copyright https://github.com/microwind
// Approximate Equality Check

fn approx_equal(a: f64, b: f64, epsilon: f64) -> bool {
    (a - b).abs() < epsilon
}

fn main() {
    println!("Approximate Equality Check:");
    println!("0.1 + 0.2 ≈ 0.3: {}", approx_equal(0.1 + 0.2, 0.3, 1e-10));
}
