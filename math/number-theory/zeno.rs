// Copyright https://github.com/microwind
// Zeno's Paradox - Dichotomy Paradox

fn zeno_paradox(total_distance: f64, steps: i32) {
    let mut remaining = total_distance;
    println!("Zeno's Dichotomy Paradox:");
    for i in 1..=steps {
        remaining /= 2.0;
        println!("Step {}: remaining distance = {:.6}", i, remaining);
    }
}

fn main() {
    zeno_paradox(1.0, 10);
}
