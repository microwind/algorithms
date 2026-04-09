pub fn max(a: i32, b: i32) -> i32 {
    if a > b { a } else { b }
}

pub fn min(a: i32, b: i32) -> i32 {
    if a < b { a } else { b }
}

pub fn max_of_slice(numbers: &[i32]) -> i32 {
    *numbers.iter().max().unwrap_or(&0)
}

pub fn min_of_slice(numbers: &[i32]) -> i32 {
    *numbers.iter().min().unwrap_or(&0)
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_max() {
        assert_eq!(max(5, 3), 5);
        assert_eq!(min(5, 3), 3);
    }
}
