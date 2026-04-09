pub fn is_prime(n: u32) -> bool {
    if n < 2 {
        return false;
    }
    if n == 2 {
        return true;
    }
    if n % 2 == 0 {
        return false;
    }
    let mut i = 3;
    while i * i <= n {
        if n % i == 0 {
            return false;
        }
        i += 2;
    }
    true
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_is_prime() {
        assert!(is_prime(2));
        assert!(is_prime(17));
        assert!(!is_prime(4));
    }
}
