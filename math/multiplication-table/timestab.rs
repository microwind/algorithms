// Copyright https://github.com/microwind
// Multiplication Table

fn print_table(max_n: i32) {
    for i in 1..=max_n {
        for j in 1..=i {
            print!("{}×{}={:2}  ", j, i, i * j);
        }
        println!();
    }
}

fn main() {
    println!("Multiplication Table (9x9):");
    print_table(9);
}
