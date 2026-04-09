pub fn average(numbers: &[f64]) -> f64 {
    if numbers.is_empty() {
        return 0.0;
    }
    let sum: f64 = numbers.iter().sum();
    sum / numbers.len() as f64
}

pub fn average_safe(a: i64, b: i64) -> f64 {
    a as f64 / 2.0 + b as f64 / 2.0
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_average() {
        let numbers = vec![10.0, 20.0, 30.0, 40.0, 50.0];
        assert_eq!(average(&numbers), 30.0);
    }
}
