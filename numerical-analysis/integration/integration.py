import numpy as np
import random

def trapezoidal_rule(f, a, b, n):
    """梯形法则数值积分"""
    h = (b - a) / n
    sum_val = 0.5 * (f(a) + f(b))
    
    for i in range(1, n):
        x = a + i * h
        sum_val += f(x)
    
    return sum_val * h

def simpsons_rule(f, a, b, n):
    """辛普森法则数值积分"""
    if n % 2 != 0:
        n += 1  # 确保n为偶数
    
    h = (b - a) / n
    sum_val = f(a) + f(b)
    
    for i in range(1, n):
        x = a + i * h
        if i % 2 == 0:
            sum_val += 2 * f(x)
        else:
            sum_val += 4 * f(x)
    
    return sum_val * h / 3

def monte_carlo_integration(f, a, b, samples):
    """蒙特卡洛积分"""
    sum_val = 0
    
    for _ in range(samples):
        x = a + (b - a) * random.random()
        sum_val += f(x)
    
    return (b - a) * sum_val / samples

def main():
    # 测试函数：f(x) = x^2
    f = lambda x: x**2
    
    a, b = 0, 1
    n = 1000
    
    print("数值积分测试 (f(x) = x^2, [0,1]):")
    
    trapezoidal = trapezoidal_rule(f, a, b, n)
    print(f"梯形法则: {trapezoidal:.6f}")
    
    simpson = simpsons_rule(f, a, b, n)
    print(f"辛普森法则: {simpson:.6f}")
    
    monte_carlo = monte_carlo_integration(f, a, b, 10000)
    print(f"蒙特卡洛积分: {monte_carlo:.6f}")
    
    print(f"精确值: {1/3:.6f}")

if __name__ == "__main__":
    main()
