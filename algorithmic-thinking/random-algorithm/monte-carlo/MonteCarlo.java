/**
 * 蒙特卡洛算法实现 (Java)
 * 
 * 特点：
 * - 运行时间固定
 * - 给出正确答案的概率很高
 * - 可能会返回错误答案，但概率可控
 */

import java.util.Random;
import java.util.function.DoubleUnaryOperator;

public class MonteCarlo {
    
    private static final Random random = new Random();
    
    /**
     * 蒙特卡洛方法估算π
     */
    public static double monteCarloPi(int numSamples) {
        int insideCircle = 0;
        
        for (int i = 0; i < numSamples; i++) {
            // 在 [0, 1] × [0, 1] 内随机生成点
            double x = random.nextDouble();
            double y = random.nextDouble();
            
            // 判断是否在原点为中心、半径为 1 的圆内
            if (x * x + y * y <= 1.0) {
                insideCircle++;
            }
        }
        
        // 圆的面积 / 正方形面积 = π/4
        // 所以 π ≈ 4 * (圆内的点数 / 总点数)
        return 4.0 * insideCircle / numSamples;
    }
    
    /**
     * 蒙特卡洛方法计算积分
     */
    public static double monteCarloIntegration(DoubleUnaryOperator func, double a, double b, int numSamples) {
        double sumValues = 0.0;
        
        for (int i = 0; i < numSamples; i++) {
            // 在 [a, b] 内随机生成 x
            double x = a + (b - a) * random.nextDouble();
            sumValues += func.applyAsDouble(x);
        }
        
        // 积分 ≈ (b - a) * (平均函数值)
        return (b - a) * sumValues / numSamples;
    }
    
    /**
     * 蒙特卡洛方法估算概率
     */
    public static double monteCarloProbability(int numTrials, int successThreshold) {
        int successes = 0;
        
        for (int i = 0; i < numTrials; i++) {
            // 模拟随机事件：掷骰子
            int diceRoll = random.nextInt(6) + 1;
            
            // 假设成功条件是掷出大于等于 successThreshold 的点数
            if (diceRoll >= successThreshold) {
                successes++;
            }
        }
        
        return (double) successes / numTrials;
    }
    
    /**
     * 蒙特卡洛方法求解Buffon's针问题估算π
     */
    public static double monteCarloBuffonNeedle(int numTrials, double needleLength, double lineSpacing) {
        int intersections = 0;
        
        for (int i = 0; i < numTrials; i++) {
            // 随机生成针的中心位置和角度
            double centerY = random.nextDouble() * lineSpacing;
            double angle = random.nextDouble() * Math.PI; // [0, π]
            
            // 计算针的两端到最近线的距离
            double halfLength = needleLength / 2.0;
            double y1 = centerY - halfLength * Math.sin(angle);
            double y2 = centerY + halfLength * Math.sin(angle);
            
            // 检查是否与线相交
            if ((int)(y1 / lineSpacing) != (int)(y2 / lineSpacing)) {
                intersections++;
            }
        }
        
        // Buffon's针公式：π ≈ (2 * needleLength * numTrials) / (lineSpacing * intersections)
        if (intersections == 0) return 0.0; // 避免除零
        return (2.0 * needleLength * numTrials) / (lineSpacing * intersections);
    }
    
    /**
     * 蒙特卡洛方法估算圆周率（改进版：使用拒绝采样）
     */
    public static double monteCarloPiRejectionSampling(int numSamples) {
        int totalPoints = 0;
        double sumDistance = 0.0;
        
        while (totalPoints < numSamples) {
            // 在 [-1, 1] × [-1, 1] 内随机生成点
            double x = 2.0 * random.nextDouble() - 1.0;
            double y = 2.0 * random.nextDouble() - 1.0;
            
            // 只考虑在单位圆内的点（拒绝采样）
            if (x * x + y * y <= 1.0) {
                sumDistance += Math.sqrt(x * x + y * y);
                totalPoints++;
            }
        }
        
        // 平均距离 ≈ 2/3，所以可以用来验证随机性
        return sumDistance / numSamples;
    }
    
    /**
     * 蒙特卡洛方法估算高维积分
     */
    public static double monteCarloHighDimensionalIntegration(int dimensions, int numSamples) {
        double sumValues = 0.0;
        
        for (int i = 0; i < numSamples; i++) {
            double product = 1.0;
            for (int d = 0; d < dimensions; d++) {
                double x = random.nextDouble();
                product *= x; // 计算 ∏ x_i
            }
            sumValues += product;
        }
        
        // 在 [0,1]^d 空间内，∫∏ x_i dx = 1/(d+1)^d
        return sumValues / numSamples;
    }
    
    /**
     * 蒙特卡洛方法模拟排队论问题
     */
    public static double monteCarloQueueSimulation(int numCustomers, double arrivalRate, double serviceRate) {
        double totalTime = 0.0;
        double currentTime = 0.0;
        
        for (int i = 0; i < numCustomers; i++) {
            // 顾客到达时间间隔（指数分布）
            double arrivalTime = -Math.log(random.nextDouble()) / arrivalRate;
            currentTime += arrivalTime;
            
            // 服务时间（指数分布）
            double serviceTime = -Math.log(random.nextDouble()) / serviceRate;
            totalTime += serviceTime;
        }
        
        return totalTime / numCustomers; // 平均服务时间
    }
    
    public static void main(String[] args) {
        System.out.println("=== 蒙特卡洛算法演示 ===\n");
        
        // 测试π估算
        System.out.println("1. 蒙特卡洛方法估算π");
        int samples = 1000000;
        double piEstimate = monteCarloPi(samples);
        System.out.printf("采样数: %d\n", samples);
        System.out.printf("π估算值: %.6f\n", piEstimate);
        System.out.printf("π真实值: %.6f\n", Math.PI);
        System.out.printf("误差: %.6f\n\n", Math.abs(piEstimate - Math.PI));
        
        // 测试数值积分
        System.out.println("2. 蒙特卡洛方法计算积分");
        System.out.println("计算: ∫[0,1] x² dx");
        DoubleUnaryOperator funcXSquared = x -> x * x;
        double integralEst = monteCarloIntegration(funcXSquared, 0.0, 1.0, 100000);
        System.out.printf("估算值: %.6f\n", integralEst);
        System.out.printf("真实值: %.6f\n", 1.0/3.0);
        System.out.printf("误差: %.6f\n\n", Math.abs(integralEst - 1.0/3.0));
        
        System.out.println("计算: ∫[0,π] sin(x) dx");
        DoubleUnaryOperator funcSin = Math::sin;
        integralEst = monteCarloIntegration(funcSin, 0.0, Math.PI, 100000);
        System.out.printf("估算值: %.6f\n", integralEst);
        System.out.printf("真实值: %.6f\n", 2.0);
        System.out.printf("误差: %.6f\n\n", Math.abs(integralEst - 2.0));
        
        // 测试概率估算
        System.out.println("3. 蒙特卡洛方法估算概率");
        System.out.println("模拟掷骰子，求掷出≥4点的概率");
        double probEstimate = monteCarloProbability(100000, 4);
        System.out.printf("估算概率: %.6f\n", probEstimate);
        System.out.printf("理论概率: %.6f\n", 3.0/6.0);
        System.out.printf("误差: %.6f\n\n", Math.abs(probEstimate - 3.0/6.0));
        
        // 测试Buffon's针问题
        System.out.println("4. Buffon's针问题估算π");
        double needleLength = 1.0;
        double lineSpacing = 2.0;
        double piBuffon = monteCarloBuffonNeedle(100000, needleLength, lineSpacing);
        System.out.printf("针长度: %.1f, 线间距: %.1f\n", needleLength, lineSpacing);
        System.out.printf("π估算值: %.6f\n", piBuffon);
        System.out.printf("π真实值: %.6f\n", Math.PI);
        System.out.printf("误差: %.6f\n\n", Math.abs(piBuffon - Math.PI));
        
        // 测试拒绝采样
        System.out.println("5. 蒙特卡洛拒绝采样");
        double avgDistance = monteCarloPiRejectionSampling(100000);
        System.out.printf("单位圆内点到原点的平均距离: %.6f\n", avgDistance);
        System.out.printf("理论值: %.6f\n", 2.0/3.0);
        System.out.printf("误差: %.6f\n\n", Math.abs(avgDistance - 2.0/3.0));
        
        // 测试高维积分
        System.out.println("6. 蒙特卡洛高维积分");
        int dimensions = 5;
        double highDimIntegral = monteCarloHighDimensionalIntegration(dimensions, 100000);
        double theoreticalValue = 1.0 / Math.pow(dimensions + 1, dimensions);
        System.out.printf("%d维积分 ∫[0,1]^%d ∏x_i dx\n", dimensions, dimensions);
        System.out.printf("估算值: %.6f\n", highDimIntegral);
        System.out.printf("理论值: %.6f\n", theoreticalValue);
        System.out.printf("误差: %.6f\n\n", Math.abs(highDimIntegral - theoreticalValue));
        
        // 测试排队论模拟
        System.out.println("7. 蒙特卡洛排队论模拟");
        int numCustomers = 1000;
        double arrivalRate = 2.0; // 每分钟2个顾客
        double serviceRate = 3.0; // 每分钟服务3个顾客
        double avgServiceTime = monteCarloQueueSimulation(numCustomers, arrivalRate, serviceRate);
        System.out.printf("顾客数: %d\n", numCustomers);
        System.out.printf("到达率: %.1f/分钟, 服务率: %.1f/分钟\n", arrivalRate, serviceRate);
        System.out.printf("平均服务时间: %.6f分钟\n", avgServiceTime);
        System.out.printf("理论平均服务时间: %.6f分钟\n", 1.0 / serviceRate);
    }
}
