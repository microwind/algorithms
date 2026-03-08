/*
 * 日期时间 - 温度转换
 * 摄氏度、华氏度、开尔文之间的相互转换
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 摄氏度转华氏度: °F = °C × 9/5 + 32
 */
double celsius_to_fahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

/**
 * 华氏度转摄氏度: °C = (°F - 32) × 5/9
 */
double fahrenheit_to_celsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

/**
 * 摄氏度转开尔文: K = °C + 273.15
 */
double celsius_to_kelvin(double celsius) {
    return celsius + 273.15;
}

/**
 * 开尔文转摄氏度: °C = K - 273.15
 */
double kelvin_to_celsius(double kelvin) {
    return kelvin - 273.15;
}

/**
 * 华氏度转开尔文
 */
double fahrenheit_to_kelvin(double fahrenheit) {
    return celsius_to_kelvin(fahrenheit_to_celsius(fahrenheit));
}

/**
 * 开尔文转华氏度
 */
double kelvin_to_fahrenheit(double kelvin) {
    return celsius_to_fahrenheit(kelvin_to_celsius(kelvin));
}

/**
 * 温度转换结果结构
 */
typedef struct {
    double celsius;
    double fahrenheit;
    double kelvin;
} Temperature;

/**
 * 从摄氏度创建温度对象
 */
Temperature create_from_celsius(double celsius) {
    Temperature temp;
    temp.celsius = celsius;
    temp.fahrenheit = celsius_to_fahrenheit(celsius);
    temp.kelvin = celsius_to_kelvin(celsius);
    return temp;
}

/**
 * 从华氏度创建温度对象
 */
Temperature create_from_fahrenheit(double fahrenheit) {
    Temperature temp;
    temp.fahrenheit = fahrenheit;
    temp.celsius = fahrenheit_to_celsius(fahrenheit);
    temp.kelvin = celsius_to_kelvin(temp.celsius);
    return temp;
}

/**
 * 从开尔文创建温度对象
 */
Temperature create_from_kelvin(double kelvin) {
    Temperature temp;
    temp.kelvin = kelvin;
    temp.celsius = kelvin_to_celsius(kelvin);
    temp.fahrenheit = celsius_to_fahrenheit(temp.celsius);
    return temp;
}

/**
 * 验证转换的准确性
 */
int verify_conversion(double original, double converted, double tolerance) {
    return (original - converted) < tolerance && (converted - original) < tolerance;
}

/**
 * 打印温度信息
 */
void print_temperature(const char* label, Temperature temp) {
    printf("%-12s %8.2f°C %10.2f°F %10.2fK\n", 
           label, temp.celsius, temp.fahrenheit, temp.kelvin);
}

/**
 * 打印温度转换表
 */
void print_conversion_table() {
    printf("\n温度转换对照表:\n");
    printf("%-12s %8s %10s %10s\n", "描述", "摄氏°C", "华氏°F", "开尔文K");
    printf("------------------------------------------------\n");
    
    // 常见温度点
    struct {
        const char* name;
        double celsius;
    } test_cases[] = {
        {"绝对零度", -273.15},
        {"液氮沸点", -195.79},
        {"冰点", 0.0},
        {"室温", 20.0},
        {"人体体温", 37.0},
        {"沸点", 100.0},
        {"熔炉温度", 1500.0}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        Temperature temp = create_from_celsius(test_cases[i].celsius);
        print_temperature(test_cases[i].name, temp);
    }
}

/**
 * 双向转换验证
 */
void verify_bidirectional_conversion() {
    printf("\n双向转换验证:\n");
    
    double test_values[] = {-40.0, 0.0, 25.0, 100.0, 373.15};
    int num_values = sizeof(test_values) / sizeof(test_values[0]);
    double tolerance = 0.001;
    
    printf("原始值    → 转换结果    → 反向转换    → 误差\n");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < num_values; i++) {
        double original = test_values[i];
        
        // 摄氏度 → 华氏度 → 摄氏度
        double f = celsius_to_fahrenheit(original);
        double c_back = fahrenheit_to_celsius(f);
        double error_c = original - c_back;
        printf("%8.2f°C → %8.2f°F → %8.2f°C → %6.4f°C %s\n", 
               original, f, c_back, error_c,
               verify_conversion(original, c_back, tolerance) ? "✓" : "✗");
        
        // 摄氏度 → 开尔文 → 摄氏度
        double k = celsius_to_kelvin(original);
        c_back = kelvin_to_celsius(k);
        error_c = original - c_back;
        printf("%8.2f°C → %8.2fK  → %8.2f°C → %6.4f°C %s\n", 
               original, k, c_back, error_c,
               verify_conversion(original, c_back, tolerance) ? "✓" : "✗");
    }
}

/**
 * 温度范围检查
 */
void temperature_range_check() {
    printf("\n温度范围检查:\n");
    
    struct {
        const char* name;
        double min_celsius;
        double max_celsius;
    } ranges[] = {
        {"舒适室温", 18.0, 26.0},
        {"冰箱冷藏", 2.0, 8.0},
        {"冰箱冷冻", -18.0, -12.0},
        {"人体安全", -20.0, 50.0},
        {"水存在范围", 0.0, 100.0}
    };
    
    int num_ranges = sizeof(ranges) / sizeof(ranges[0]);
    
    printf("%-12s %-10s %-10s\n", "范围", "最小°C", "最大°C");
    printf("--------------------------------\n");
    
    for (int i = 0; i < num_ranges; i++) {
        printf("%-12s %8.1f°C %8.1f°C\n", 
               ranges[i].name, ranges[i].min_celsius, ranges[i].max_celsius);
        
        // 转换为华氏度和开尔文
        Temperature min_temp = create_from_celsius(ranges[i].min_celsius);
        Temperature max_temp = create_from_celsius(ranges[i].max_celsius);
        
        printf("            %8.1f°F %8.1f°F\n", 
               min_temp.fahrenheit, max_temp.fahrenheit);
        printf("            %8.1fK  %8.1fK\n", 
               min_temp.kelvin, max_temp.kelvin);
        printf("\n");
    }
}

/**
 * 交互式温度转换
 */
void interactive_conversion() {
    printf("\n交互式温度转换:\n");
    printf("输入格式: 值 单位 (例如: 25 C, 77 F, 298 K)\n");
    printf("输入 'q' 退出\n\n");
    
    char input[100];
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // 移除换行符
        input[strcspn(input, "\n")] = 0;
        
        if (input[0] == 'q' || input[0] == 'Q') {
            break;
        }
        
        double value;
        char unit;
        if (sscanf(input, "%lf %c", &value, &unit) != 2) {
            printf("格式错误，请重试\n");
            continue;
        }
        
        Temperature temp;
        switch (unit) {
            case 'C':
            case 'c':
                temp = create_from_celsius(value);
                break;
            case 'F':
            case 'f':
                temp = create_from_fahrenheit(value);
                break;
            case 'K':
            case 'k':
                temp = create_from_kelvin(value);
                break;
            default:
                printf("未知单位，请使用 C、F 或 K\n");
                continue;
        }
        
        printf("  摄氏度: %.2f°C\n", temp.celsius);
        printf("  华氏度: %.2f°F\n", temp.fahrenheit);
        printf("  开尔文: %.2fK\n", temp.kelvin);
        printf("\n");
    }
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("温度转换 (Temperature Conversion)\n");
    printf("==================================================\n");
    
    // 打印转换表
    print_conversion_table();
    
    // 验证双向转换
    verify_bidirectional_conversion();
    
    // 温度范围检查
    temperature_range_check();
    
    printf("\n转换公式:\n");
    printf("  摄氏度 → 华氏度: °F = °C × 9/5 + 32\n");
    printf("  华氏度 → 摄氏度: °C = (°F - 32) × 5/9\n");
    printf("  摄氏度 → 开尔文:  K = °C + 273.15\n");
    printf("  开尔文 → 摄氏度: °C = K - 273.15\n");
    
    printf("\n应用场景:\n");
    printf("  • 天气预报转换\n");
    printf("  • 科学计算统一单位\n");
    printf("  • 国际贸易产品规格\n");
    printf("  • 烹饪温度调整\n");
    printf("  • 工业过程控制\n");
    
    printf("\n注意事项:\n");
    printf("  • 开尔文是绝对温标，0K为绝对零度\n");
    printf("  • 摄氏度基于水的冰点和沸点\n");
    printf("  • 华氏度基于人体舒适度\n");
    printf("  • 科学计算通常使用开尔文\n");
    
    // 交互式转换（可选）
    // interactive_conversion();
    
    return 0;
}
