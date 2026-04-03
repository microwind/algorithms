class NumericalIntegration {
    static trapezoidalRule(f, a, b, n) {
        const h = (b - a) / n;
        let sum = 0.5 * (f(a) + f(b));
        
        for (let i = 1; i < n; i++) {
            const x = a + i * h;
            sum += f(x);
        }
        
        return sum * h;
    }
    
    static simpsonsRule(f, a, b, n) {
        if (n % 2 !== 0) n++; // 确保n为偶数
        
        const h = (b - a) / n;
        let sum = f(a) + f(b);
        
        for (let i = 1; i < n; i++) {
            const x = a + i * h;
            if (i % 2 === 0) {
                sum += 2 * f(x);
            } else {
                sum += 4 * f(x);
            }
        }
        
        return sum * h / 3;
    }
    
    static monteCarloIntegration(f, a, b, samples) {
        let sum = 0;
        
        for (let i = 0; i < samples; i++) {
            const x = a + (b - a) * Math.random();
            sum += f(x);
        }
        
        return (b - a) * sum / samples;
    }
    
    static main() {
        // 测试函数：f(x) = x^2
        const f = (x) => x * x;
        
        const a = 0, b = 1;
        const n = 1000;
        
        console.log("数值积分测试 (f(x) = x^2, [0,1]):");
        
        const trapezoidal = NumericalIntegration.trapezoidalRule(f, a, b, n);
        console.log(`梯形法则: ${trapezoidal.toFixed(6)}`);
        
        const simpson = NumericalIntegration.simpsonsRule(f, a, b, n);
        console.log(`辛普森法则: ${simpson.toFixed(6)}`);
        
        const monteCarlo = NumericalIntegration.monteCarloIntegration(f, a, b, 10000);
        console.log(`蒙特卡洛积分: ${monteCarlo.toFixed(6)}`);
        
        console.log(`精确值: ${(1/3).toFixed(6)}`);
    }
}

// 示例使用
NumericalIntegration.main();
