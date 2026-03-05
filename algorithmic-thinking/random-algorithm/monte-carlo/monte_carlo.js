/**
 * 蒙特卡洛算法实现 (JavaScript)
 * 
 * 特点：
 * - 运行时间固定
 * - 给出正确答案的概率很高
 * - 可能会返回错误答案，但概率可控
 */

// 蒙特卡洛方法估算π
function monteCarloPi(numSamples) {
    let insideCircle = 0;
    
    for (let i = 0; i < numSamples; i++) {
        // 在 [0, 1] × [0, 1] 内随机生成点
        const x = Math.random();
        const y = Math.random();
        
        // 判断是否在原点为中心、半径为 1 的圆内
        if (x * x + y * y <= 1.0) {
            insideCircle++;
        }
    }
    
    // 圆的面积 / 正方形面积 = π/4
    // 所以 π ≈ 4 * (圆内的点数 / 总点数)
    return 4.0 * insideCircle / numSamples;
}

// 蒙特卡洛方法计算积分
function monteCarloIntegration(func, a, b, numSamples) {
    let sumValues = 0.0;
    
    for (let i = 0; i < numSamples; i++) {
        // 在 [a, b] 内随机生成 x
        const x = a + (b - a) * Math.random();
        sumValues += func(x);
    }
    
    // 积分 ≈ (b - a) * (平均函数值)
    return (b - a) * sumValues / numSamples;
}

// 测试函数：x²
function funcXSquared(x) {
    return x * x;
}

// 测试函数：sin(x)
function funcSin(x) {
    return Math.sin(x);
}

// 蒙特卡洛方法估算概率
function monteCarloProbability(numTrials, successThreshold) {
    let successes = 0;
    
    for (let i = 0; i < numTrials; i++) {
        // 模拟随机事件：掷骰子
        const diceRoll = Math.floor(Math.random() * 6) + 1;
        
        // 假设成功条件是掷出大于等于 successThreshold 的点数
        if (diceRoll >= successThreshold) {
            successes++;
        }
    }
    
    return successes / numTrials;
}

// 蒙特卡洛方法求解Buffon's针问题估算π
function monteCarloBuffonNeedle(numTrials, needleLength, lineSpacing) {
    let intersections = 0;
    
    for (let i = 0; i < numTrials; i++) {
        // 随机生成针的中心位置和角度
        const centerY = Math.random() * lineSpacing;
        const angle = Math.random() * Math.PI; // [0, π]
        
        // 计算针的两端到最近线的距离
        const halfLength = needleLength / 2.0;
        const y1 = centerY - halfLength * Math.sin(angle);
        const y2 = centerY + halfLength * Math.sin(angle);
        
        // 检查是否与线相交
        if (Math.floor(y1 / lineSpacing) !== Math.floor(y2 / lineSpacing)) {
            intersections++;
        }
    }
    
    // Buffon's针公式：π ≈ (2 * needleLength * numTrials) / (lineSpacing * intersections)
    if (intersections === 0) return 0.0; // 避免除零
    return (2.0 * needleLength * numTrials) / (lineSpacing * intersections);
}

// 蒙特卡洛方法估算圆周率（改进版：使用拒绝采样）
function monteCarloPiRejectionSampling(numSamples) {
    let totalPoints = 0;
    let sumDistance = 0.0;
    
    while (totalPoints < numSamples) {
        // 在 [-1, 1] × [-1, 1] 内随机生成点
        const x = 2.0 * Math.random() - 1.0;
        const y = 2.0 * Math.random() - 1.0;
        
        // 只考虑在单位圆内的点（拒绝采样）
        if (x * x + y * y <= 1.0) {
            sumDistance += Math.sqrt(x * x + y * y);
            totalPoints++;
        }
    }
    
    // 平均距离 ≈ 2/3，所以可以用来验证随机性
    return sumDistance / numSamples;
}

// 蒙特卡洛方法估算高维积分
function monteCarloHighDimensionalIntegration(dimensions, numSamples) {
    let sumValues = 0.0;
    
    for (let i = 0; i < numSamples; i++) {
        let product = 1.0;
        for (let d = 0; d < dimensions; d++) {
            const x = Math.random();
            product *= x; // 计算 ∏ x_i
        }
        sumValues += product;
    }
    
    // 在 [0,1]^d 空间内，∫∏ x_i dx = 1/(d+1)^d
    return sumValues / numSamples;
}

// 蒙特卡洛方法模拟排队论问题
function monteCarloQueueSimulation(numCustomers, arrivalRate, serviceRate) {
    let totalTime = 0.0;
    
    for (let i = 0; i < numCustomers; i++) {
        // 顾客到达时间间隔（指数分布）
        const arrivalTime = -Math.log(Math.random()) / arrivalRate;
        
        // 服务时间（指数分布）
        const serviceTime = -Math.log(Math.random()) / serviceRate;
        totalTime += serviceTime;
        
        // arrivalTime 在实际模拟中会用于计算等待时间，这里简化处理
    }
    
    return totalTime / numCustomers; // 平均服务时间
}

// 蒙特卡洛方法模拟股票价格（几何布朗运动）
function monteCarloStockPrice(initialPrice, drift, volatility, timeSteps, dt) {
    let price = initialPrice;
    const prices = [price];
    
    for (let i = 0; i < timeSteps; i++) {
        // 几何布朗运动：dS = μS dt + σS dW
        const randomShock = Math.sqrt(dt) * normalRandom(); // 正态分布随机数
        price = price * Math.exp((drift - 0.5 * volatility * volatility) * dt + volatility * randomShock);
        prices.push(price);
    }
    
    return prices;
}

// 生成标准正态分布随机数（Box-Muller变换）
function normalRandom() {
    let u = 0, v = 0;
    while (u === 0) u = Math.random(); // 避免log(0)
    while (v === 0) v = Math.random();
    
    return Math.sqrt(-2.0 * Math.log(u)) * Math.cos(2.0 * Math.PI * v);
}

// 主函数
function main() {
    console.log('=== 蒙特卡洛算法演示 ===\n');
    
    // 测试π估算
    console.log('1. 蒙特卡洛方法估算π');
    const samples = 1000000;
    const piEstimate = monteCarloPi(samples);
    console.log(`采样数: ${samples}`);
    console.log(`π估算值: ${piEstimate.toFixed(6)}`);
    console.log(`π真实值: ${Math.PI.toFixed(6)}`);
    console.log(`误差: ${Math.abs(piEstimate - Math.PI).toFixed(6)}\n`);
    
    // 测试数值积分
    console.log('2. 蒙特卡洛方法计算积分');
    console.log('计算: ∫[0,1] x² dx');
    let integralEst = monteCarloIntegration(funcXSquared, 0.0, 1.0, 100000);
    console.log(`估算值: ${integralEst.toFixed(6)}`);
    console.log(`真实值: ${(1.0/3.0).toFixed(6)}`);
    console.log(`误差: ${Math.abs(integralEst - 1.0/3.0).toFixed(6)}\n`);
    
    console.log('计算: ∫[0,π] sin(x) dx');
    integralEst = monteCarloIntegration(funcSin, 0.0, Math.PI, 100000);
    console.log(`估算值: ${integralEst.toFixed(6)}`);
    console.log(`真实值: ${2.0.toFixed(6)}`);
    console.log(`误差: ${Math.abs(integralEst - 2.0).toFixed(6)}\n`);
    
    // 测试概率估算
    console.log('3. 蒙特卡洛方法估算概率');
    console.log('模拟掷骰子，求掷出≥4点的概率');
    const probEstimate = monteCarloProbability(100000, 4);
    console.log(`估算概率: ${probEstimate.toFixed(6)}`);
    console.log(`理论概率: ${(3.0/6.0).toFixed(6)}`);
    console.log(`误差: ${Math.abs(probEstimate - 3.0/6.0).toFixed(6)}\n`);
    
    // 测试Buffon's针问题
    console.log('4. Buffon\'s针问题估算π');
    const needleLength = 1.0;
    const lineSpacing = 2.0;
    const piBuffon = monteCarloBuffonNeedle(100000, needleLength, lineSpacing);
    console.log(`针长度: ${needleLength.toFixed(1)}, 线间距: ${lineSpacing.toFixed(1)}`);
    console.log(`π估算值: ${piBuffon.toFixed(6)}`);
    console.log(`π真实值: ${Math.PI.toFixed(6)}`);
    console.log(`误差: ${Math.abs(piBuffon - Math.PI).toFixed(6)}\n`);
    
    // 测试拒绝采样
    console.log('5. 蒙特卡洛拒绝采样');
    const avgDistance = monteCarloPiRejectionSampling(100000);
    console.log(`单位圆内点到原点的平均距离: ${avgDistance.toFixed(6)}`);
    console.log(`理论值: ${(2.0/3.0).toFixed(6)}`);
    console.log(`误差: ${Math.abs(avgDistance - 2.0/3.0).toFixed(6)}\n`);
    
    // 测试高维积分
    console.log('6. 蒙特卡洛高维积分');
    const dimensions = 5;
    const highDimIntegral = monteCarloHighDimensionalIntegration(dimensions, 100000);
    const theoreticalValue = 1.0 / Math.pow(dimensions + 1, dimensions);
    console.log(`${dimensions}维积分 ∫[0,1]^${dimensions} ∏x_i dx`);
    console.log(`估算值: ${highDimIntegral.toFixed(6)}`);
    console.log(`理论值: ${theoreticalValue.toFixed(6)}`);
    console.log(`误差: ${Math.abs(highDimIntegral - theoreticalValue).toFixed(6)}\n`);
    
    // 测试排队论模拟
    console.log('7. 蒙特卡洛排队论模拟');
    const numCustomers = 1000;
    const arrivalRate = 2.0; // 每分钟2个顾客
    const serviceRate = 3.0; // 每分钟服务3个顾客
    const avgServiceTime = monteCarloQueueSimulation(numCustomers, arrivalRate, serviceRate);
    console.log(`顾客数: ${numCustomers}`);
    console.log(`到达率: ${arrivalRate.toFixed(1)}/分钟, 服务率: ${serviceRate.toFixed(1)}/分钟`);
    console.log(`平均服务时间: ${avgServiceTime.toFixed(6)}分钟`);
    console.log(`理论平均服务时间: ${(1.0/serviceRate).toFixed(6)}分钟\n`);
    
    // 测试股票价格模拟
    console.log('8. 蒙特卡洛股票价格模拟');
    const initialPrice = 100.0;
    const drift = 0.05; // 5%年化收益率
    const volatility = 0.2; // 20%年化波动率
    const timeSteps = 252; // 一年的交易日
    const dt = 1.0 / 252; // 每日时间步长
    
    const stockPrices = monteCarloStockPrice(initialPrice, drift, volatility, timeSteps, dt);
    console.log(`初始价格: $${initialPrice.toFixed(2)}`);
    console.log(`年化收益率: ${(drift * 100).toFixed(1)}%, 年化波动率: ${(volatility * 100).toFixed(1)}%`);
    console.log(`模拟${timeSteps}个交易日后的价格: $${stockPrices[stockPrices.length - 1].toFixed(2)}`);
    console.log(`价格区间: $${Math.min(...stockPrices).toFixed(2)} - $${Math.max(...stockPrices).toFixed(2)}`);
}

// 运行主函数
main();
