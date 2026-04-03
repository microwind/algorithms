import java.util.function.Function;

public class NumericalIntegration {
    
    // 梯形法则
    public static double trapezoidalRule(Function<Double, Double> f, double a, double b, int n) {
        double h = (b - a) / n;
        double sum = 0.5 * (f.apply(a) + f.apply(b));
        
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            sum += f.apply(x);
        }
        
        return sum * h;
    }
    
    // 辛普森法则
    public static double simpsonsRule(Function<Double, Double> f, double a, double b, int n) {
        if (n % 2 != 0) n++; // 确保n为偶数
        
        double h = (b - a) / n;
        double sum = f.apply(a) + f.apply(b);
        
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            if (i % 2 == 0) {
                sum += 2 * f.apply(x);
            } else {
                sum += 4 * f.apply(x);
            }
        }
        
        return sum * h / 3;
    }
    
    // 蒙特卡洛积分
    public static double monteCarloIntegration(Function<Double, Double> f, double a, double b, int samples) {
        double sum = 0;
        java.util.Random random = new java.util.Random();
        
        for (int i = 0; i < samples; i++) {
            double x = a + (b - a) * random.nextDouble();
            sum += f.apply(x);
        }
        
        return (b - a) * sum / samples;
    }
    
    public static void main(String[] args) {
        // 测试函数：f(x) = x^2
        Function<Double, Double> f = x -> x * x;
        
        double a = 0, b = 1;
        int n = 1000;
        
        System.out.println("数值积分测试 (f(x) = x^2, [0,1]):");
        
        double trapezoidal = trapezoidalRule(f, a, b, n);
        System.out.printf("梯形法则: %.6f\n", trapezoidal);
        
        double simpson = simpsonsRule(f, a, b, n);
        System.out.printf("辛普森法则: %.6f\n", simpson);
        
        double monteCarlo = monteCarloIntegration(f, a, b, 10000);
        System.out.printf("蒙特卡洛积分: %.6f\n", monteCarlo);
        
        System.out.printf("精确值: %.6f\n", 1.0/3.0);
    }
}
