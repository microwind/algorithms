/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 温度转换 (Temperature Conversion)
 * 摄氏度、华氏度、开尔文之间的相互转换
 * 
 * 转换公式：
 * - 摄氏度转华氏度: °F = °C × 9/5 + 32
 * - 华氏度转摄氏度: °C = (°F - 32) × 5/9
 * - 摄氏度转开尔文: K = °C + 273.15
 * - 开尔文转摄氏度: °C = K - 273.15
 */

class TemperatureConversion {
    
    /**
     * 摄氏度转华氏度
     * 公式: °F = °C × 9/5 + 32
     */
    static double celsiusToFahrenheit(double celsius) {
        return celsius * 9.0 / 5.0 + 32.0;
    }
    
    /**
     * 华氏度转摄氏度
     * 公式: °C = (°F - 32) × 5/9
     */
    static double fahrenheitToCelsius(double fahrenheit) {
        return (fahrenheit - 32.0) * 5.0 / 9.0;
    }
    
    /**
     * 摄氏度转开尔文
     * 公式: K = °C + 273.15
     */
    static double celsiusToKelvin(double celsius) {
        return celsius + 273.15;
    }
    
    /**
     * 开尔文转摄氏度
     * 公式: °C = K - 273.15
     */
    static double kelvinToCelsius(double kelvin) {
        return kelvin - 273.15;
    }
    
    /**
     * 华氏度转开尔文
     */
    static double fahrenheitToKelvin(double fahrenheit) {
        return celsiusToKelvin(fahrenheitToCelsius(fahrenheit));
    }
    
    /**
     * 开尔文转华氏度
     */
    static double kelvinToFahrenheit(double kelvin) {
        return celsiusToFahrenheit(kelvinToCelsius(kelvin));
    }
    
    // 测试主函数
    public static void main(String[] args) {
        System.out.println("温度转换测试");
        System.out.println("============");
        
        double celsius = 25.0;
        System.out.printf("摄氏度 %.2f°C = 华氏度 %.2f°F%n", 
                         celsius, celsiusToFahrenheit(celsius));
        System.out.printf("摄氏度 %.2f°C = 开尔文 %.2fK%n", 
                         celsius, celsiusToKelvin(celsius));
        
        double fahrenheit = 98.6;
        System.out.printf("华氏度 %.2f°F = 摄氏度 %.2f°C%n", 
                         fahrenheit, fahrenheitToCelsius(fahrenheit));
        
        double kelvin = 300.0;
        System.out.printf("开尔文 %.2fK = 摄氏度 %.2f°C%n", 
                         kelvin, kelvinToCelsius(kelvin));
        System.out.printf("开尔文 %.2fK = 华氏度 %.2f°F%n", 
                         kelvin, kelvinToFahrenheit(kelvin));
    }
}
