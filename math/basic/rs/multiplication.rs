pub fn multiply(a: i32, b: i32) -> i32 {
    a * b
}

pub fn safe_multiply(a: i32, b: i32) -> Option<i32> {
    a.checked_mul(b)
}
