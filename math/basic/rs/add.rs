pub fn add(a: i32, b: i32) -> i32 {
    a + b
}

pub fn safe_add(a: i32, b: i32) -> Option<i32> {
    a.checked_add(b)
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_add() {
        assert_eq!(add(5, 3), 8);
        assert_eq!(add(100, 200), 300);
    }
}
