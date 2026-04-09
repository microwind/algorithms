/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 平均值计算 (Average)
 * 计算算术平均值，避免溢出
 */

public class Average {
    
    public static double average(int[] numbers) {
        if (numbers == null || numbers.length == 0) {
            throw new IllegalArgumentException("数组不能为空");
        }
        
        long sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        return (double) sum / numbers.length;
    }
    
    public static double averageSafe(int a, int b) {
        return a / 2.0 + b / 2.0;
    }
    
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50};
        System.out.println("平均值计算:");
        System.out.printf("numbers = {10, 20, 30, 40, 50}%n");
        System.out.printf("平均值 = %.2f%n", average(numbers));
        
        System.out.println("\n避免溢出计算:");
        int a = Integer.MAX_VALUE - 100;
        int b = Integer.MAX_VALUE - 200;
        System.out.printf("a = %d, b = %d%n", a, b);
        System.out.printf("平均值 = %.2f%n", averageSafe(a, b));
    }
}
