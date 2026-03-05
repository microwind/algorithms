"""
蒙特卡洛算法实现 (Python)

特点：
- 运行时间固定
- 给出正确答案的概率很高
- 可能会返回错误答案，但概率可控
"""

import random
import math
from typing import Callable, List

def monte_carlo_pi(num_samples: int) -> float:
    """
    蒙特卡洛方法估算π
    """
    inside_circle = 0
    
    for _ in range(num_samples):
        # 在 [0, 1] × [0, 1] 内随机生成点
        x = random.random()
        y = random.random()
        
        # 判断是否在原点为中心、半径为 1 的圆内
        if x * x + y * y <= 1.0:
            inside_circle += 1
    
    # 圆的面积 / 正方形面积 = π/4
    # 所以 π ≈ 4 * (圆内的点数 / 总点数)
    return 4.0 * inside_circle / num_samples

def monte_carlo_integration(func: Callable[[float], float], a: float, b: float, num_samples: int) -> float:
    """
    蒙特卡洛方法计算积分
    """
    sum_values = 0.0
    
    for _ in range(num_samples):
        # 在 [a, b] 内随机生成 x
        x = a + (b - a) * random.random()
        sum_values += func(x)
    
    # 积分 ≈ (b - a) * (平均函数值)
    return (b - a) * sum_values / num_samples

def func_x_squared(x: float) -> float:
    """测试函数：x²"""
    return x * x

def func_sin(x: float) -> float:
    """测试函数：sin(x)"""
    return math.sin(x)

def monte_carlo_probability(num_trials: int, success_threshold: int) -> float:
    """
    蒙特卡洛方法估算概率
    """
    successes = 0
    
    for _ in range(num_trials):
        # 模拟随机事件：掷骰子
        dice_roll = random.randint(1, 6)
        
        # 假设成功条件是掷出大于等于 success_threshold 的点数
        if dice_roll >= success_threshold:
            successes += 1
    
    return successes / num_trials

def monte_carlo_buffon_needle(num_trials: int, needle_length: float, line_spacing: float) -> float:
    """
    蒙特卡洛方法求解Buffon's针问题估算π
    """
    intersections = 0
    
    for _ in range(num_trials):
        # 随机生成针的中心位置和角度
        center_y = random.random() * line_spacing
        angle = random.random() * math.pi  # [0, π]
        
        # 计算针的两端到最近线的距离
        half_length = needle_length / 2.0
        y1 = center_y - half_length * math.sin(angle)
        y2 = center_y + half_length * math.sin(angle)
        
        # 检查是否与线相交
        if int(y1 / line_spacing) != int(y2 / line_spacing):
            intersections += 1
    
    # Buffon's针公式：π ≈ (2 * needleLength * numTrials) / (lineSpacing * intersections)
    if intersections == 0:
        return 0.0  # 避免除零
    return (2.0 * needle_length * num_trials) / (line_spacing * intersections)

def monte_carlo_pi_rejection_sampling(num_samples: int) -> float:
    """
    蒙特卡洛方法估算圆周率（改进版：使用拒绝采样）
    """
    total_points = 0
    sum_distance = 0.0
    
    while total_points < num_samples:
        # 在 [-1, 1] × [-1, 1] 内随机生成点
        x = 2.0 * random.random() - 1.0
        y = 2.0 * random.random() - 1.0
        
        # 只考虑在单位圆内的点（拒绝采样）
        if x * x + y * y <= 1.0:
            sum_distance += math.sqrt(x * x + y * y)
            total_points += 1
    
    # 平均距离 ≈ 2/3，所以可以用来验证随机性
    return sum_distance / num_samples

def monte_carlo_high_dimensional_integration(dimensions: int, num_samples: int) -> float:
    """
    蒙特卡洛方法估算高维积分
    """
    sum_values = 0.0
    
    for _ in range(num_samples):
        product = 1.0
        for _ in range(dimensions):
            x = random.random()
            product *= x  # 计算 ∏ x_i
        sum_values += product
    
    # 在 [0,1]^d 空间内，∫∏ x_i dx = 1/(d+1)^d
    return sum_values / num_samples

def monte_carlo_queue_simulation(num_customers: int, arrival_rate: float, service_rate: float) -> float:
    """
    蒙特卡洛方法模拟排队论问题
    """
    total_time = 0.0
    current_time = 0.0
    
    for _ in range(num_customers):
        # 顾客到达时间间隔（指数分布）
        arrival_time = -math.log(random.random()) / arrival_rate
        current_time += arrival_time
        
        # 服务时间（指数分布）
        service_time = -math.log(random.random()) / service_rate
        total_time += service_time
    
    return total_time / num_customers  # 平均服务时间

def monte_carlo_stock_price(initial_price: float, drift: float, volatility: float, 
                           time_steps: int, dt: float) -> List[float]:
    """
    蒙特卡洛方法模拟股票价格（几何布朗运动）
    """
    price = initial_price
    prices = [price]
    
    for _ in range(time_steps):
        # 几何布朗运动：dS = μS dt + σS dW
        random_shock = math.sqrt(dt) * normal_random()  # 正态分布随机数
        price = price * math.exp((drift - 0.5 * volatility * volatility) * dt + volatility * random_shock)
        prices.append(price)
    
    return prices

def normal_random() -> float:
    """
    生成标准正态分布随机数（Box-Muller变换）
    """
    u = 0.0
    v = 0.0
    while u == 0.0:
        u = random.random()  # 避免log(0)
    while v == 0.0:
        v = random.random()
    
    return math.sqrt(-2.0 * math.log(u)) * math.cos(2.0 * math.pi * v)

def monte_carlo_option_price(spot_price: float, strike_price: float, risk_free_rate: float,
                             volatility: float, time_to_maturity: float, num_simulations: int) -> float:
    """
    蒙特卡洛方法计算欧式期权价格
    """
    payoffs = []
    
    for _ in range(num_simulations):
        # 模拟到期时的股票价格
        terminal_price = spot_price * math.exp(
            (risk_free_rate - 0.5 * volatility * volatility) * time_to_maturity +
            volatility * math.sqrt(time_to_maturity) * normal_random()
        )
        
        # 计算期权收益
        payoff = max(terminal_price - strike_price, 0.0)
        payoffs.append(payoff)
    
    # 折现期望收益
    discounted_payoff = math.exp(-risk_free_rate * time_to_maturity) * sum(payoffs) / num_simulations
    return discounted_payoff

def main():
    """主函数"""
    print("=== 蒙特卡洛算法演示 ===\n")
    
    # 测试π估算
    print("1. 蒙特卡洛方法估算π")
    samples = 1000000
    pi_estimate = monte_carlo_pi(samples)
    print(f"采样数: {samples}")
    print(f"π估算值: {pi_estimate:.6f}")
    print(f"π真实值: {math.pi:.6f}")
    print(f"误差: {abs(pi_estimate - math.pi):.6f}\n")
    
    # 测试数值积分
    print("2. 蒙特卡洛方法计算积分")
    print("计算: ∫[0,1] x² dx")
    integral_est = monte_carlo_integration(func_x_squared, 0.0, 1.0, 100000)
    print(f"估算值: {integral_est:.6f}")
    print(f"真实值: {1.0/3.0:.6f}")
    print(f"误差: {abs(integral_est - 1.0/3.0):.6f}\n")
    
    print("计算: ∫[0,π] sin(x) dx")
    integral_est = monte_carlo_integration(func_sin, 0.0, math.pi, 100000)
    print(f"估算值: {integral_est:.6f}")
    print(f"真实值: {2.0:.6f}")
    print(f"误差: {abs(integral_est - 2.0):.6f}\n")
    
    # 测试概率估算
    print("3. 蒙特卡洛方法估算概率")
    print("模拟掷骰子，求掷出≥4点的概率")
    prob_estimate = monte_carlo_probability(100000, 4)
    print(f"估算概率: {prob_estimate:.6f}")
    print(f"理论概率: {3.0/6.0:.6f}")
    print(f"误差: {abs(prob_estimate - 3.0/6.0):.6f}\n")
    
    # 测试Buffon's针问题
    print("4. Buffon's针问题估算π")
    needle_length = 1.0
    line_spacing = 2.0
    pi_buffon = monte_carlo_buffon_needle(100000, needle_length, line_spacing)
    print(f"针长度: {needle_length:.1f}, 线间距: {line_spacing:.1f}")
    print(f"π估算值: {pi_buffon:.6f}")
    print(f"π真实值: {math.pi:.6f}")
    print(f"误差: {abs(pi_buffon - math.pi):.6f}\n")
    
    # 测试拒绝采样
    print("5. 蒙特卡洛拒绝采样")
    avg_distance = monte_carlo_pi_rejection_sampling(100000)
    print(f"单位圆内点到原点的平均距离: {avg_distance:.6f}")
    print(f"理论值: {2.0/3.0:.6f}")
    print(f"误差: {abs(avg_distance - 2.0/3.0):.6f}\n")
    
    # 测试高维积分
    print("6. 蒙特卡洛高维积分")
    dimensions = 5
    high_dim_integral = monte_carlo_high_dimensional_integration(dimensions, 100000)
    theoretical_value = 1.0 / math.pow(dimensions + 1, dimensions)
    print(f"{dimensions}维积分 ∫[0,1]^{dimensions} ∏x_i dx")
    print(f"估算值: {high_dim_integral:.6f}")
    print(f"理论值: {theoretical_value:.6f}")
    print(f"误差: {abs(high_dim_integral - theoretical_value):.6f}\n")
    
    # 测试排队论模拟
    print("7. 蒙特卡洛排队论模拟")
    num_customers = 1000
    arrival_rate = 2.0  # 每分钟2个顾客
    service_rate = 3.0  # 每分钟服务3个顾客
    avg_service_time = monte_carlo_queue_simulation(num_customers, arrival_rate, service_rate)
    print(f"顾客数: {num_customers}")
    print(f"到达率: {arrival_rate:.1f}/分钟, 服务率: {service_rate:.1f}/分钟")
    print(f"平均服务时间: {avg_service_time:.6f}分钟")
    print(f"理论平均服务时间: {1.0/service_rate:.6f}分钟\n")
    
    # 测试股票价格模拟
    print("8. 蒙特卡洛股票价格模拟")
    initial_price = 100.0
    drift = 0.05  # 5%年化收益率
    volatility = 0.2  # 20%年化波动率
    time_steps = 252  # 一年的交易日
    dt = 1.0 / 252  # 每日时间步长
    
    stock_prices = monte_carlo_stock_price(initial_price, drift, volatility, time_steps, dt)
    print(f"初始价格: ${initial_price:.2f}")
    print(f"年化收益率: {drift * 100:.1f}%, 年化波动率: {volatility * 100:.1f}%")
    print(f"模拟{time_steps}个交易日后的价格: ${stock_prices[-1]:.2f}")
    print(f"价格区间: ${min(stock_prices):.2f} - ${max(stock_prices):.2f}\n")
    
    # 测试期权定价
    print("9. 蒙特卡洛期权定价")
    spot_price = 100.0
    strike_price = 105.0
    risk_free_rate = 0.03  # 3%无风险利率
    option_volatility = 0.25  # 25%波动率
    time_to_maturity = 1.0  # 1年到期
    
    option_price = monte_carlo_option_price(
        spot_price, strike_price, risk_free_rate, 
        option_volatility, time_to_maturity, 100000
    )
    
    print(f"标的资产价格: ${spot_price:.2f}")
    print(f"执行价格: ${strike_price:.2f}")
    print(f"无风险利率: {risk_free_rate * 100:.1f}%")
    print(f"波动率: {option_volatility * 100:.1f}%")
    print(f"到期时间: {time_to_maturity:.1f}年")
    print(f"欧式看涨期权价格: ${option_price:.4f}")

if __name__ == "__main__":
    main()
