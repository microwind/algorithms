// 蒙特卡洛算法实现 (Rust)
//
// 特点：
// - 运行时间固定
// - 给出正确答案的概率很高
// - 可能会返回错误答案，但概率可控

use std::time::{SystemTime, UNIX_EPOCH};

// 生成 [0, 1] 范围内的随机数
fn random_double() -> f64 {
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);
    rng.gen_range(0.0..1.0)
}

// 蒙特卡洛方法估算π
fn monte_carlo_pi(num_samples: usize) -> f64 {
    let mut inside_circle = 0;
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    for _ in 0..num_samples {
        // 在 [0, 1] × [0, 1] 内随机生成点
        let x: f64 = rng.gen_range(0.0..1.0);
        let y: f64 = rng.gen_range(0.0..1.0);

        // 判断是否在原点为中心、半径为 1 的圆内
        if x * x + y * y <= 1.0 {
            inside_circle += 1;
        }
    }

    // 圆的面积 / 正方形面积 = π/4
    // 所以 π ≈ 4 * (圆内的点数 / 总点数)
    4.0 * inside_circle as f64 / num_samples as f64
}

// 蒙特卡洛方法计算积分
fn monte_carlo_integration<F>(func: F, a: f64, b: f64, num_samples: usize) -> f64
where
    F: Fn(f64) -> f64,
{
    let mut sum_values = 0.0;
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    for _ in 0..num_samples {
        // 在 [a, b] 内随机生成 x
        let x = a + (b - a) * rng.gen_range(0.0..1.0);
        sum_values += func(x);
    }

    // 积分 ≈ (b - a) * (平均函数值)
    (b - a) * sum_values / num_samples as f64
}

// 测试函数：x²
fn func_x_squared(x: f64) -> f64 {
    x * x
}

// 测试函数：sin(x)
fn func_sin(x: f64) -> f64 {
    x.sin()
}

// 蒙特卡洛方法估算概率
fn monte_carlo_probability(num_trials: usize, success_threshold: i32) -> f64 {
    let mut successes = 0;
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    for _ in 0..num_trials {
        // 模拟随机事件：掷骰子
        let dice_roll = rng.gen_range(1..=6);

        // 假设成功条件是掷出大于等于 success_threshold 的点数
        if dice_roll >= success_threshold {
            successes += 1;
        }
    }

    successes as f64 / num_trials as f64
}

// 蒙特卡洛方法求解Buffon's针问题估算π
fn monte_carlo_buffon_needle(num_trials: usize, needle_length: f64, line_spacing: f64) -> f64 {
    let mut intersections = 0;
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    for _ in 0..num_trials {
        // 随机生成针的中心位置和角度
        let center_y = rng.gen_range(0.0..line_spacing);
        let angle = rng.gen_range(0.0..std::f64::consts::PI); // [0, π]

        // 计算针的两端到最近线的距离
        let half_length = needle_length / 2.0;
        let y1 = center_y - half_length * angle.sin();
        let y2 = center_y + half_length * angle.sin();

        // 检查是否与线相交
        if (y1 / line_spacing) as i32 != (y2 / line_spacing) as i32 {
            intersections += 1;
        }
    }

    // Buffon's针公式：π ≈ (2 * needleLength * numTrials) / (lineSpacing * intersections)
    if intersections == 0 {
        0.0 // 避免除零
    } else {
        (2.0 * needle_length * num_trials as f64) / (line_spacing * intersections as f64)
    }
}

// 蒙特卡洛方法估算圆周率（改进版：使用拒绝采样）
fn monte_carlo_pi_rejection_sampling(num_samples: usize) -> f64 {
    let mut total_points = 0;
    let mut sum_distance = 0.0;
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    while total_points < num_samples {
        // 在 [-1, 1] × [-1, 1] 内随机生成点
        let x = 2.0 * rng.gen_range(0.0..1.0) - 1.0;
        let y = 2.0 * rng.gen_range(0.0..1.0) - 1.0;

        // 只考虑在单位圆内的点（拒绝采样）
        if x * x + y * y <= 1.0 {
            sum_distance += (x * x + y * y).sqrt();
            total_points += 1;
        }
    }

    // 平均距离 ≈ 2/3，所以可以用来验证随机性
    sum_distance / num_samples as f64
}

// 蒙特卡洛方法估算高维积分
fn monte_carlo_high_dimensional_integration(dimensions: usize, num_samples: usize) -> f64 {
    let mut sum_values = 0.0;
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    for _ in 0..num_samples {
        let mut product = 1.0;
        for _ in 0..dimensions {
            let x: f64 = rng.gen_range(0.0..1.0);
            product *= x; // 计算 ∏ x_i
        }
        sum_values += product;
    }

    // 在 [0,1]^d 空间内，∫∏ x_i dx = 1/(d+1)^d
    sum_values / num_samples as f64
}

// 蒙特卡洛方法模拟排队论问题
fn monte_carlo_queue_simulation(num_customers: usize, arrival_rate: f64, service_rate: f64) -> f64 {
    let mut total_time = 0.0;
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    for _ in 0..num_customers {
        // 顾客到达时间间隔（指数分布）
        let _arrival_time = -rng.gen_range(0.0..1.0).ln() / arrival_rate;

        // 服务时间（指数分布）
        let service_time = -rng.gen_range(0.0..1.0).ln() / service_rate;
        total_time += service_time;
    }

    total_time / num_customers as f64 // 平均服务时间
}

// 生成标准正态分布随机数（Box-Muller变换）
fn normal_random() -> f64 {
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);
    
    let mut u = 0.0;
    let mut v = 0.0;
    while u == 0.0 {
        u = rng.gen_range(0.0..1.0); // 避免log(0)
    }
    while v == 0.0 {
        v = rng.gen_range(0.0..1.0);
    }

    (-2.0 * u.ln()).sqrt() * (2.0 * std::f64::consts::PI * v).cos()
}

// 蒙特卡洛方法模拟股票价格（几何布朗运动）
fn monte_carlo_stock_price(
    initial_price: f64,
    drift: f64,
    volatility: f64,
    time_steps: usize,
    dt: f64,
) -> Vec<f64> {
    let mut price = initial_price;
    let mut prices = vec![price];
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    for _ in 0..time_steps {
        // 几何布朗运动：dS = μS dt + σS dW
        let random_shock = dt.sqrt() * normal_random();
        price = price * ((drift - 0.5 * volatility * volatility) * dt + volatility * random_shock).exp();
        prices.push(price);
    }

    prices
}

// 蒙特卡洛方法计算欧式期权价格
fn monte_carlo_option_price(
    spot_price: f64,
    strike_price: f64,
    risk_free_rate: f64,
    volatility: f64,
    time_to_maturity: f64,
    num_simulations: usize,
) -> f64 {
    let mut payoffs = Vec::new();
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);

    for _ in 0..num_simulations {
        // 模拟到期时的股票价格
        let terminal_price = spot_price
            * ((risk_free_rate - 0.5 * volatility * volatility) * time_to_maturity
                + volatility * time_to_maturity.sqrt() * normal_random())
                .exp();

        // 计算期权收益
        let payoff = (terminal_price - strike_price).max(0.0);
        payoffs.push(payoff);
    }

    // 折现期望收益
    let discounted_payoff = (-risk_free_rate * time_to_maturity).exp() * payoffs.iter().sum::<f64>() / num_simulations as f64;
    discounted_payoff
}

fn main() {
    println!("=== 蒙特卡洛算法演示 ===\n");

    // 测试π估算
    println!("1. 蒙特卡洛方法估算π");
    let samples = 1_000_000;
    let pi_estimate = monte_carlo_pi(samples);
    println!("采样数: {}", samples);
    println!("π估算值: {:.6}", pi_estimate);
    println!("π真实值: {:.6}", std::f64::consts::PI);
    println!("误差: {:.6}\n", (pi_estimate - std::f64::consts::PI).abs());

    // 测试数值积分
    println!("2. 蒙特卡洛方法计算积分");
    println!("计算: ∫[0,1] x² dx");
    let integral_est = monte_carlo_integration(func_x_squared, 0.0, 1.0, 100_000);
    println!("估算值: {:.6}", integral_est);
    println!("真实值: {:.6}", 1.0 / 3.0);
    println!("误差: {:.6}\n", (integral_est - 1.0 / 3.0).abs());

    println!("计算: ∫[0,π] sin(x) dx");
    let integral_est = monte_carlo_integration(func_sin, 0.0, std::f64::consts::PI, 100_000);
    println!("估算值: {:.6}", integral_est);
    println!("真实值: {:.6}", 2.0);
    println!("误差: {:.6}\n", (integral_est - 2.0).abs());

    // 测试概率估算
    println!("3. 蒙特卡洛方法估算概率");
    println!("模拟掷骰子，求掷出≥4点的概率");
    let prob_estimate = monte_carlo_probability(100_000, 4);
    println!("估算概率: {:.6}", prob_estimate);
    println!("理论概率: {:.6}", 3.0 / 6.0);
    println!("误差: {:.6}\n", (prob_estimate - 3.0 / 6.0).abs());

    // 测试Buffon's针问题
    println!("4. Buffon's针问题估算π");
    let needle_length = 1.0;
    let line_spacing = 2.0;
    let pi_buffon = monte_carlo_buffon_needle(100_000, needle_length, line_spacing);
    println!("针长度: {:.1}, 线间距: {:.1}", needle_length, line_spacing);
    println!("π估算值: {:.6}", pi_buffon);
    println!("π真实值: {:.6}", std::f64::consts::PI);
    println!("误差: {:.6}\n", (pi_buffon - std::f64::consts::PI).abs());

    // 测试拒绝采样
    println!("5. 蒙特卡洛拒绝采样");
    let avg_distance = monte_carlo_pi_rejection_sampling(100_000);
    println!("单位圆内点到原点的平均距离: {:.6}", avg_distance);
    println!("理论值: {:.6}", 2.0 / 3.0);
    println!("误差: {:.6}\n", (avg_distance - 2.0 / 3.0).abs());

    // 测试高维积分
    println!("6. 蒙特卡洛高维积分");
    let dimensions = 5;
    let high_dim_integral = monte_carlo_high_dimensional_integration(dimensions, 100_000);
    let theoretical_value = 1.0 / (dimensions + 1).pow(dimensions as u32) as f64;
    println!("{}维积分 ∫[0,1]^{} ∏x_i dx", dimensions, dimensions);
    println!("估算值: {:.6}", high_dim_integral);
    println!("理论值: {:.6}", theoretical_value);
    println!("误差: {:.6}\n", (high_dim_integral - theoretical_value).abs());

    // 测试排队论模拟
    println!("7. 蒙特卡洛排队论模拟");
    let num_customers = 1000;
    let arrival_rate = 2.0; // 每分钟2个顾客
    let service_rate = 3.0; // 每分钟服务3个顾客
    let avg_service_time = monte_carlo_queue_simulation(num_customers, arrival_rate, service_rate);
    println!("顾客数: {}", num_customers);
    println!("到达率: {:.1}/分钟, 服务率: {:.1}/分钟", arrival_rate, service_rate);
    println!("平均服务时间: {:.6}分钟", avg_service_time);
    println!("理论平均服务时间: {:.6}分钟\n", 1.0 / service_rate);

    // 测试股票价格模拟
    println!("8. 蒙特卡洛股票价格模拟");
    let initial_price = 100.0;
    let drift = 0.05; // 5%年化收益率
    let volatility = 0.2; // 20%年化波动率
    let time_steps = 252; // 一年的交易日
    let dt = 1.0 / 252.0; // 每日时间步长

    let stock_prices = monte_carlo_stock_price(initial_price, drift, volatility, time_steps, dt);
    println!("初始价格: ${:.2}", initial_price);
    println!("年化收益率: {:.1}%, 年化波动率: {:.1}%", drift * 100.0, volatility * 100.0);
    println!(
        "模拟{}个交易日后的价格: ${:.2}",
        time_steps,
        stock_prices[stock_prices.len() - 1]
    );
    println!(
        "价格区间: ${:.2} - ${:.2}",
        stock_prices.iter().fold(f64::INFINITY, |a, &b| a.min(b)),
        stock_prices.iter().fold(0.0, |a, &b| a.max(b))
    );

    // 测试期权定价
    println!("\n9. 蒙特卡洛期权定价");
    let spot_price = 100.0;
    let strike_price = 105.0;
    let risk_free_rate = 0.03; // 3%无风险利率
    let option_volatility = 0.25; // 25%波动率
    let time_to_maturity = 1.0; // 1年到期

    let option_price = monte_carlo_option_price(
        spot_price,
        strike_price,
        risk_free_rate,
        option_volatility,
        time_to_maturity,
        100_000,
    );

    println!("标的资产价格: ${:.2}", spot_price);
    println!("执行价格: ${:.2}", strike_price);
    println!("无风险利率: {:.1}%", risk_free_rate * 100.0);
    println!("波动率: {:.1}%", option_volatility * 100.0);
    println!("到期时间: {:.1}年", time_to_maturity);
    println!("欧式看涨期权价格: ${:.4}", option_price);
}
