/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 温度单位转换 (Temperature Unit Conversion)
 * 摄氏度与华氏度之间的相互转换
 */

class CelsiusToFahrenheit {
    
    public static double celsiusToFahrenheit(double c) {
        return 9.0 / 5.0 * c + 32;
    }
    
    public static int fahrenheitToCelsius(int f) {
        return 5 * (f - 32) / 9;
    }
    
    public static void printConversionTable(int start, int end, int step) {
        System.out.println("摄氏度到华氏度转换表");
        System.out.println("摄氏度 | 华氏度");
        System.out.println("-------|-------");
        
        for (int c = start; c <= end; c += step) {
            double f = celsiusToFahrenheit(c);
            System.out.printf("%6d  | %6.1f%n", c, f);
        }
    }
    
    public static void main(String[] args) {
        System.out.println("温度单位转换演示");
        System.out.println("================\n");
        
        printConversionTable(0, 100, 5);
        
        System.out.println("\n转换公式:");
        System.out.println("• 摄氏度→华氏度: °F = °C × 9/5 + 32");
        System.out.println("• 华氏度→摄氏度: °C = (°F - 32) × 5/9");
    }
}
