/*
 * 数学转换 - 温度单位转换 (Temperature Unit Conversion)
 * 摄氏度与华氏度之间的相互转换
 * 时间复杂度: O(1)
 */

#include <stdio.h>
#include <stdlib.h>

// 转换参数配置
#define LOWER_LIMIT 0       // 摄氏度下限
#define UPPER_LIMIT 100     // 摄氏度上限
#define STEP_SIZE 5         // 步长

/**
 * 摄氏度转华氏度
 * 
 * 转换公式：°F = °C × 9/5 + 32
 * 
 * 推导过程：
 * 1. 水的冰点：0°C = 32°F
 * 2. 水的沸点：100°C = 212°F
 * 3. 温度范围：100°C = 180°F → 1°C = 1.8°F = 9/5°F
 * 4. 公式：°F = 9/5 × °C + 32
 * 
 * 参数:
 *     c: 摄氏度温度
 * 返回:
 *     对应的华氏度温度
 */
double celsius_to_fahrenheit(double c);

/**
 * 华氏度转摄氏度
 * 
 * 转换公式：°C = (°F - 32) × 5/9
 * 
 * 推导过程：
 * 1. 从华氏度公式：°F = 9/5 × °C + 32
 * 2. 移项：°F - 32 = 9/5 × °C
 * 3. 两边乘以5/9：(°F - 32) × 5/9 = °C
 * 
 * 参数:
 *     f: 华氏度温度
 * 返回:
 *     对应的摄氏度温度
 */
int fahrenheit_to_celsius(int f);

/**
 * 生成摄氏度到华氏度的转换表
 * 
 * 参数:
 *     start: 起始摄氏度
 *     end: 结束摄氏度
 *     step: 步长
 */
void print_conversion_table(int start, int end, int step);

/**
 * 温度转换演示程序
 * 
 * 功能：
 * - 生成摄氏度到华氏度转换表
 * - 提供华氏度到摄氏度的转换功能
 * - 展示转换公式的推导过程
 * 
 * 输出样例：
 * Celsius to Fahrenheit table
 *   0  |  32
 *   5  |  41
 *  10  |  50
 *  15  |  59
 *  20  |  68
 *  25  |  77
 *  30  |  86
 *  35  |  95
 */
int main()
{
    printf("温度单位转换演示\n");
    printf("================\n\n");
    
    // 生成转换表
    print_conversion_table(LOWER_LIMIT, UPPER_LIMIT, STEP_SIZE);
    
    // 交互式转换
    printf("\n华氏度转摄氏度转换器\n");
    printf("请输入华氏度温度: ");
    
    int fahrenheit;
    if (scanf("%d", &fahrenheit) == 1) {
        int celsius = fahrenheit_to_celsius(fahrenheit);
        printf("%d°F = %d°C\n", fahrenheit, celsius);
        
        // 验证转换
        double verify = celsius_to_fahrenheit(celsius);
        printf("验证: %d°C = %.1f°F\n", celsius, verify);
    } else {
        printf("输入错误！\n");
    }
    
    printf("\n转换公式说明:\n");
    printf("• 摄氏度→华氏度: °F = °C × 9/5 + 32\n");
    printf("• 华氏度→摄氏度: °C = (°F - 32) × 5/9\n");
    
    printf("\n常用温度点:\n");
    printf("• 水的冰点: 0°C = 32°F\n");
    printf("• 人体体温: 37°C = 98.6°F\n");
    printf("• 水的沸点: 100°C = 212°F\n");
    printf("• 绝对零度: -273.15°C = -459.67°F\n");
    
    printf("\n应用场景:\n");
    printf("• 国际旅行\n");
    printf("• 天气预报\n");
    printf("• 烹饪温度\n");
    printf("• 科学实验\n");
    
    getchar(); // 清除输入缓冲区
    getchar(); // 等待用户按键
    return 0;
}

/**
 * 摄氏度转华氏度实现
 * 使用标准转换公式，返回浮点数结果
 */
double celsius_to_fahrenheit(double c)
{
    return 9.0 / 5.0 * c + 32;
}

/**
 * 华氏度转摄氏度实现
 * 使用整数运算，返回整数结果（四舍五入）
 */
int fahrenheit_to_celsius(int f)
{
    return 5 * (f - 32) / 9;
}

/**
 * 生成温度转换表
 * 格式化输出摄氏度到华氏度的对应关系
 */
void print_conversion_table(int start, int end, int step)
{
    printf("摄氏度到华氏度转换表\n");
    printf("摄氏度 | 华氏度\n");
    printf("-------|-------\n");
    
    for (int c = start; c <= end; c += step)
    {
        double f = celsius_to_fahrenheit(c);
        printf("%6d  | %6.1f\n", c, f);
    }
}
