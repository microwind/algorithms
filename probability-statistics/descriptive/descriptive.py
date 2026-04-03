import numpy as np
from scipy import stats

class DescriptiveStatistics:
    
    @staticmethod
    def mean(data):
        """计算均值"""
        return np.mean(data)
    
    @staticmethod
    def median(data):
        """计算中位数"""
        return np.median(data)
    
    @staticmethod
    def variance(data):
        """计算方差"""
        return np.var(data)
    
    @staticmethod
    def standard_deviation(data):
        """计算标准差"""
        return np.std(data)
    
    @staticmethod
    def percentile(data, percentile):
        """计算分位数"""
        return np.percentile(data, percentile)
    
    @staticmethod
    def skewness(data):
        """计算偏度"""
        return stats.skew(data)
    
    @staticmethod
    def kurtosis(data):
        """计算峰度"""
        return stats.kurtosis(data)

def main():
    data = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    print("描述统计测试:")
    print(f"均值: {DescriptiveStatistics.mean(data):.2f}")
    print(f"中位数: {DescriptiveStatistics.median(data):.2f}")
    print(f"方差: {DescriptiveStatistics.variance(data):.2f}")
    print(f"标准差: {DescriptiveStatistics.standard_deviation(data):.2f}")
    print(f"25%分位数: {DescriptiveStatistics.percentile(data, 25):.2f}")
    print(f"75%分位数: {DescriptiveStatistics.percentile(data, 75):.2f}")
    print(f"偏度: {DescriptiveStatistics.skewness(data):.2f}")
    print(f"峰度: {DescriptiveStatistics.kurtosis(data):.2f}")

if __name__ == "__main__":
    main()
