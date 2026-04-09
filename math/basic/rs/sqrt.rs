pub fn sqrt_newton(n: f64, epsilon: f64) -> f64 {
    if n < 0.0 {
        panic!("cannot sqrt negative number");
    }
    if n == 0.0 {
        return 0.0;
    }
    let mut x = n;
    while (x * x - n).abs() > epsilon {
        x = (x + n / x) / 2.0;
    }
    x
}
