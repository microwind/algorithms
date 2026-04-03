import java.util.*;

public class DescriptiveStatistics {
    
    // 基础统计量
    public static double mean(double[] data) {
        double sum = 0;
        for (double value : data) {
            sum += value;
        }
        return sum / data.length;
    }
    
    public static double median(double[] data) {
        Arrays.sort(data);
        int n = data.length;
        if (n % 2 == 0) {
            return (data[n/2 - 1] + data[n/2]) / 2;
        } else {
            return data[n/2];
        }
    }
    
    public static double variance(double[] data) {
        double mean = mean(data);
        double sum = 0;
        for (double value : data) {
            sum += Math.pow(value - mean, 2);
        }
        return sum / data.length;
    }
    
    public static double standardDeviation(double[] data) {
        return Math.sqrt(variance(data));
    }
    
    public static double percentile(double[] data, double percentile) {
        Arrays.sort(data);
        double index = (percentile / 100.0) * (data.length - 1);
        int lower = (int) Math.floor(index);
        int upper = (int) Math.ceil(index);
        
        if (lower == upper) {
            return data[lower];
        } else {
            double weight = index - lower;
            return data[lower] * (1 - weight) + data[upper] * weight;
        }
    }
    
    public static void main(String[] args) {
        double[] data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        System.out.println("描述统计测试:");
        System.out.printf("均值: %.2f\n", mean(data));
        System.out.printf("中位数: %.2f\n", median(data));
        System.out.printf("方差: %.2f\n", variance(data));
        System.out.printf("标准差: %.2f\n", standardDeviation(data));
        System.out.printf("25%分位数: %.2f\n", percentile(data, 25));
        System.out.printf("75%分位数: %.2f\n", percentile(data, 75));
    }
}
