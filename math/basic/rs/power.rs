pub fn power(base: f64, exp: i32) -> f64 {
    if exp < 0 {
        return 1.0 / power(base, -exp);
    }
    if exp == 0 {
        return 1.0;
    }
    let mut result = 1.0;
    let mut current = base;
    let mut e = exp;
    while e > 0 {
        if e & 1 == 1 {
            result *= current;
        }
        current *= current;
        e >>= 1;
    }
    result
}
