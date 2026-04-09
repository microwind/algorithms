/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 绝对值计算 (Absolute Value)
 * 计算整数的绝对值
 * 时间复杂度: O(1)
 */

public class Abs {

    /**
     * 计算整数的绝对值
     * 
     * 算法原理：
     * - 正数：绝对值就是其本身
     * - 负数：绝对值是其相反数
     * - 零：绝对值是零
     * 
     * 参数:
     *     n: 要求绝对值的整数
     * 返回:
     *     n的绝对值
     * 
     * 时间复杂度: O(1) - 常数时间
     * 空间复杂度: O(1) - 常数空间
     */
    public static int absoluteValue(int n) {
        // 使用位运算技巧（避免分支预测失败）
        // 注意：对于Integer.MIN_VALUE会溢出，应使用Math.abs()的健壮版本
        int mask = n >> 31;  // 获取符号位：负数时为-1(全1)，非负数时为0
        return (n + mask) ^ mask;  // 负数时：n-1再取反；非负数：不变
        // 等价于: return n < 0 ? -n : n;
    }

    /**
     * 使用Math库的标准实现
     */
    public static int absoluteValueStandard(int n) {
        return Math.abs(n);
    }

    /**
     * 长整型的绝对值
     */
    public static long absoluteValueLong(long n) {
        return Math.abs(n);
    }

    /**
     * 浮点数的绝对值
     */
    public static double absoluteValueDouble(double n) {
        return Math.abs(n);
    }

    public static void main(String[] args) {
        System.out.println("========================================");
        System.out.println("    绝对值计算演示 (Absolute Value)");
        System.out.println("========================================\n");
        
        // 测试用例
        int[] testCases = {-42, 0, 100, -Integer.MAX_VALUE, Integer.MIN_VALUE};
        
        System.out.println("测试数据及结果:");
        System.out.println("----------------------------------------");
        for (int num : testCases) {
            int result = absoluteValue(num);
            int stdResult = absoluteValueStandard(num);
            System.out.printf("输入: %12d | 自定义: %12d | 标准库: %12d%n", 
                            num, result, stdResult);
        }
        
        // 数学性质
        System.out.println("\n========================================");
        System.out.println("数学性质:");
        System.out.println("========================================");
        System.out.println("• 非负性: |x| ≥ 0");
        System.out.println("• 正定性: |x| = 0 当且仅当 x = 0");
        System.out.println("• 对称性: |-x| = |x|");
        System.out.println("• 三角不等式: |x + y| ≤ |x| + |y|");
        System.out.println("• 乘法性质: |x × y| = |x| × |y|");
        
        // 应用场景
        System.out.println("\n========================================");
        System.out.println("应用场景:");
        System.out.println("========================================");
        System.out.println("• 距离计算: 曼哈顿距离、欧几里得距离");
        System.out.println("• 误差分析: 绝对误差、相对误差");
        System.out.println("• 数值比较: 比较浮点数精度");
        System.out.println("• 向量运算: 向量的模（长度）");
        System.out.println("• 复数运算: 复数的模");
    }
}
