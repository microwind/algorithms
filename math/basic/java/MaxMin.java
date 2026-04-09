/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 最大值和最小值 (Max and Min)
 * 支持多种数据类型的比较运算
 * 时间复杂度: O(1)
 */

public class MaxMin {
    
    // ========== 整数类型 ==========
    
    /**
     * 求两个整数的最大值
     */
    public static int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    /**
     * 求两个整数的最小值
     */
    public static int min(int a, int b) {
        return (a < b) ? a : b;
    }
    
    /**
     * 求多个整数的最大值
     */
    public static int max(int... numbers) {
        if (numbers.length == 0) throw new IllegalArgumentException("至少需要一个参数");
        int max = numbers[0];
        for (int i = 1; i < numbers.length; i++) {
            if (numbers[i] > max) max = numbers[i];
        }
        return max;
    }
    
    /**
     * 求多个整数的最小值
     */
    public static int min(int... numbers) {
        if (numbers.length == 0) throw new IllegalArgumentException("至少需要一个参数");
        int min = numbers[0];
        for (int i = 1; i < numbers.length; i++) {
            if (numbers[i] < min) min = numbers[i];
        }
        return min;
    }
    
    // ========== 长整型 ==========
    
    public static long max(long a, long b) {
        return (a > b) ? a : b;
    }
    
    public static long min(long a, long b) {
        return (a < b) ? a : b;
    }
    
    // ========== 浮点类型 ==========
    
    public static double max(double a, double b) {
        return Math.max(a, b);
    }
    
    public static double min(double a, double b) {
        return Math.min(a, b);
    }
    
    public static float max(float a, float b) {
        return Math.max(a, b);
    }
    
    public static float min(float a, float b) {
        return Math.min(a, b);
    }
    
    /**
     * 使用位运算求最大值（不使用比较）
     * 原理: max(a,b) = a - ((a-b) & ((a-b) >> 31))
     */
    public static int maxBitwise(int a, int b) {
        int diff = a - b;
        int sign = (diff >> 31) & 1;  // 0 if a>=b, 1 if a<b
        return a - sign * diff;
    }
    
    /**
     * 交换两个整数（不使用临时变量）
     * 使用异或运算: a = a ^ b; b = a ^ b; a = a ^ b;
     */
    public static void swap(int[] arr, int i, int j) {
        if (i != j) {
            arr[i] = arr[i] ^ arr[j];
            arr[j] = arr[i] ^ arr[j];
            arr[i] = arr[i] ^ arr[j];
        }
    }
    
    /**
     * 求数组中的最大值和最小值（同时）
     * 优化算法: 成对比较，减少比较次数
     * 普通方法: 2n次比较
     * 优化方法: 3n/2次比较
     */
    public static int[] findMinMax(int[] arr) {
        if (arr == null || arr.length == 0) {
            throw new IllegalArgumentException("数组不能为空");
        }
        
        int min, max;
        int i = 0;
        
        // 如果数组长度为奇数，第一个元素同时作为min和max
        if (arr.length % 2 == 1) {
            min = max = arr[0];
            i = 1;
        } else {
            // 如果为偶数，比较前两个
            if (arr[0] < arr[1]) {
                min = arr[0];
                max = arr[1];
            } else {
                min = arr[1];
                max = arr[0];
            }
            i = 2;
        }
        
        // 成对处理剩余元素
        while (i < arr.length - 1) {
            int localMin, localMax;
            if (arr[i] < arr[i + 1]) {
                localMin = arr[i];
                localMax = arr[i + 1];
            } else {
                localMin = arr[i + 1];
                localMax = arr[i];
            }
            
            if (localMin < min) min = localMin;
            if (localMax > max) max = localMax;
            
            i += 2;
        }
        
        return new int[]{min, max};
    }
    
    public static void main(String[] args) {
        System.out.println("========================================");
        System.out.println("  最大值和最小值 (Max and Min)");
        System.out.println("========================================\n");
        
        // 基本测试
        System.out.println("基本测试:");
        System.out.println("----------------------------------------");
        System.out.printf("max(5, 3) = %d%n", max(5, 3));
        System.out.printf("min(5, 3) = %d%n", min(5, 3));
        System.out.printf("max(-10, -20) = %d%n", max(-10, -20));
        System.out.printf("max(3.14, 2.71) = %.2f%n", max(3.14, 2.71));
        
        // 多参数测试
        System.out.println("\n多参数测试:");
        System.out.println("----------------------------------------");
        System.out.printf("max(1, 5, 3, 9, 2) = %d%n", max(1, 5, 3, 9, 2));
        System.out.printf("min(1, 5, 3, 9, 2) = %d%n", min(1, 5, 3, 9, 2));
        
        // 数组测试
        System.out.println("\n数组MinMax测试:");
        System.out.println("----------------------------------------");
        int[] arr = {45, 12, 78, 23, 67, 89, 34, 56};
        int[] minMax = findMinMax(arr);
        System.out.printf("数组: ");
        for (int num : arr) System.out.print(num + " ");
        System.out.printf("%n最小值: %d, 最大值: %d%n", minMax[0], minMax[1]);
        
        // 位运算max测试
        System.out.println("\n位运算Max测试:");
        System.out.println("----------------------------------------");
        System.out.printf("maxBitwise(100, 50) = %d%n", maxBitwise(100, 50));
        System.out.printf("maxBitwise(-10, 5) = %d%n", maxBitwise(-10, 5));
        
        // 数学性质
        System.out.println("\n========================================");
        System.out.println("数学性质:");
        System.out.println("========================================");
        System.out.println("• 幂等律: max(a, a) = a, min(a, a) = a");
        System.out.println("• 交换律: max(a, b) = max(b, a)");
        System.out.println("• 结合律: max(a, max(b, c)) = max(max(a, b), c)");
        System.out.println("• 分配律: max(a, min(a, b)) = a");
        System.out.println("• 与加法关系: max(a+c, b+c) = max(a, b) + c");
        
        // 应用场景
        System.out.println("\n========================================");
        System.out.println("应用场景:");
        System.out.println("========================================");
        System.out.println("• 数据范围限制: 限制输入在有效范围内");
        System.out.println("• 图形学: 裁剪、边界框计算");
        System.out.println("• 游戏开发: 碰撞检测、视野范围");
        System.out.println("• 金融: 止损止盈价格设定");
        System.out.println("• 机器学习: ReLU激活函数 max(0, x)");
    }
}
