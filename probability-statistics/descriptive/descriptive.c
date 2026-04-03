#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int compare_doubles(const void *a, const void *b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

double mean(double *data, int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum / size;
}

double median(double *data, int size) {
    // 创建副本并排序
    double *sorted = malloc(size * sizeof(double));
    memcpy(sorted, data, size * sizeof(double));
    qsort(sorted, size, sizeof(double), compare_doubles);
    
    double result;
    if (size % 2 == 0) {
        result = (sorted[size/2 - 1] + sorted[size/2]) / 2;
    } else {
        result = sorted[size/2];
    }
    
    free(sorted);
    return result;
}

double variance(double *data, int size) {
    double mean_value = mean(data, size);
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += pow(data[i] - mean_value, 2);
    }
    return sum / size;
}

double standard_deviation(double *data, int size) {
    return sqrt(variance(data, size));
}

double percentile(double *data, int size, double percentile) {
    // 创建副本并排序
    double *sorted = malloc(size * sizeof(double));
    memcpy(sorted, data, size * sizeof(double));
    qsort(sorted, size, sizeof(double), compare_doubles);
    
    double index = (percentile / 100.0) * (size - 1);
    int lower = (int)floor(index);
    int upper = (int)ceil(index);
    
    double result;
    if (lower == upper) {
        result = sorted[lower];
    } else {
        double weight = index - lower;
        result = sorted[lower] * (1 - weight) + sorted[upper] * weight;
    }
    
    free(sorted);
    return result;
}

double skewness(double *data, int size) {
    double mean_value = mean(data, size);
    double std = standard_deviation(data, size);
    double sum = 0;
    
    for (int i = 0; i < size; i++) {
        sum += pow((data[i] - mean_value) / std, 3);
    }
    
    return sum / size;
}

double kurtosis(double *data, int size) {
    double mean_value = mean(data, size);
    double std = standard_deviation(data, size);
    double sum = 0;
    
    for (int i = 0; i < size; i++) {
        sum += pow((data[i] - mean_value) / std, 4);
    }
    
    return sum / size - 3; // 减去3得到超额峰度
}

int main() {
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(data) / sizeof(data[0]);
    
    printf("描述统计测试:\n");
    printf("均值: %.2f\n", mean(data, size));
    printf("中位数: %.2f\n", median(data, size));
    printf("方差: %.2f\n", variance(data, size));
    printf("标准差: %.2f\n", standard_deviation(data, size));
    printf("25%%分位数: %.2f\n", percentile(data, size, 25));
    printf("75%%分位数: %.2f\n", percentile(data, size, 75));
    printf("偏度: %.2f\n", skewness(data, size));
    printf("峰度: %.2f\n", kurtosis(data, size));
    
    return 0;
}
