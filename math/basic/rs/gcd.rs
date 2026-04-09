pub fn gcd(a: u32, b: u32) -> u32 {
    let mut a = a;
    let mut b = b;
    while b != 0 {
        let temp = b;
        b = a % b;
        a = temp;
    }
    a
}

pub fn lcm(a: u32, b: u32) -> u32 {
    if a == 0 || b == 0 {
        return 0;
    }
    (a / gcd(a, b)) * b
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_gcd() {
        assert_eq!(gcd(48, 18), 6);
        assert_eq!(lcm(4, 6), 12);
    }
}
