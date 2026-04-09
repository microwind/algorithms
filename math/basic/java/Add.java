/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 整数加法运算 (Integer Addition)
 * 演示基本的算术运算和溢出检测
 * 时间复杂度: O(1)
 */

public class Add {
    
    /**
     * 安全加法 - 带溢出检测
     * 
     * 算法原理：
     * - 检查溢出条件：
     *   正 + 正 = 负 → 正溢出
     *   负 + 负 = 正 → 负溢出
     * 
     * 参数:
     *     a: 第一个加数
     *     b: 第二个加数
     * 返回:
     *     两数之和（如果溢出则抛出异常）
     * 
     * 时间复杂度: O(1)
     * 空间复杂度: O(1)
     */
    public static int safeAdd(int a, int b) throws ArithmeticException {
        int result = a + b;
        
        // 溢出检测
        // 情况1: 两个正数相加得到负数 → 正溢出
        // 情况2: 两个负数相加得到正数 → 负溢出
        if (((a > 0) && (b > 0) && (result < 0)) ||
            ((a < 0) && (b < 0) && (result > 0))) {
            throw new ArithmeticException("整数溢出: " + a + " + " + b);
        }
        
        return result;
    }
    
    /**
     * 长整型安全加法
     */
    public static long safeAddLong(long a, long b) throws ArithmeticException {
        long result = a + b;
        
        if (((a > 0) && (b > 0) && (result < 0)) ||
            ((a < 0) && (b < 0) && (result > 0))) {
            throw new ArithmeticException("长整数溢出: " + a + " + " + b);
        }
        
        return result;
    }
    
    /**
     * 使用Math.addExact (Java 8+)
     */
    public static int addExact(int a, int b) {
        return Math.addExact(a, b);
    }
    
    /**
     * 累加多个数
     */
    public static int sum(int... numbers) {
        int sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        return sum;
    }
    
    /**
     * 安全累加（带溢出检测）
     */
    public static int safeSum(int... numbers) throws ArithmeticException {
        int sum = 0;
        for (int num : numbers) {
            sum = safeAdd(sum, num);
        }
        return sum;
    }
    
    public static void main(String[] args) {
        System.out.println("========================================");
        System.out.println("    整数加法运算 (Integer Addition)");
        System.out.println("========================================\n");
        
        // 基本加法测试
        System.out.println("基本加法测试:");
        System.out.println("----------------------------------------");
        int a = 100, b = 200;
        System.out.printf("%d + %d = %d%n", a, b, safeAdd(a, b));
        
        a = -50; b = -30;
        System.out.printf("%d + %d = %d%n", a, b, safeAdd(a, b));
        
        a = -100; b = 50;
        System.out.printf("%d + %d = %d%n", a, b, safeAdd(a, b));
        
        // 溢出测试
        System.out.println("\n溢出测试:");
        System.out.println("----------------------------------------");
        
        int max = Integer.MAX_VALUE;
        int min = Integer.MIN_VALUE;
        
        try {
            System.out.printf("%d + 1 = ?%n", max);
            int result = safeAdd(max, 1);
            System.out.println("结果: " + result);
        } catch (ArithmeticException e) {
            System.out.println("捕获溢出: " + e.getMessage());
        }
        
        try {
            System.out.printf("%d + (-1) = ?%n", min);
            int result = safeAdd(min, -1);
            System.out.println("结果: " + result);
        } catch (ArithmeticException e) {
            System.out.println("捕获溢出: " + e.getMessage());
        }
        
        // 累加测试
        System.out.println("\n累加测试:");
        System.out.println("----------------------------------------");
        System.out.println("1+2+3+4+5 = " + sum(1, 2, 3, 4, 5));
        System.out.println("10+20+30 = " + sum(10, 20, 30));
        
        // 加法性质
        System.out.println("\n========================================");
        System.out.println("加法数学性质:");
        System.out.println("========================================");
        System.out.println("• 交换律: a + b = b + a");
        System.out.println("• 结合律: (a + b) + c = a + (b + c)");
        System.out.println("• 恒等元: a + 0 = a");
        System.out.println("• 逆元:   a + (-a) = 0");
        
        // 应用场景
        System.out.println("\n========================================");
        System.out.println("应用场景:");
        System.out.println("========================================");
        System.out.println("• 财务计算: 金额累加（必须防溢出）");
        System.out.println("• 数据统计: 求和、平均值计算");
        System.out.println("• 坐标运算: 向量加法");
        System.out.println("• 密码学: 模运算加法");
        System.out.println("• 科学计算: 数值积分");
    }
}
