class DescriptiveStatistics {
    static mean(data: number[]): number {
        return data.reduce((sum, value) => sum + value, 0) / data.length;
    }
    
    static median(data: number[]): number {
        const sorted = [...data].sort((a, b) => a - b);
        const n = sorted.length;
        if (n % 2 === 0) {
            return (sorted[n/2 - 1] + sorted[n/2]) / 2;
        } else {
            return sorted[Math.floor(n/2)];
        }
    }
    
    static variance(data: number[]): number {
        const mean = this.mean(data);
        const sum = data.reduce((sum, value) => sum + Math.pow(value - mean, 2), 0);
        return sum / data.length;
    }
    
    static standardDeviation(data: number[]): number {
        return Math.sqrt(this.variance(data));
    }
    
    static percentile(data: number[], percentile: number): number {
        const sorted = [...data].sort((a, b) => a - b);
        const index = (percentile / 100.0) * (sorted.length - 1);
        const lower = Math.floor(index);
        const upper = Math.ceil(index);
        
        if (lower === upper) {
            return sorted[lower];
        } else {
            const weight = index - lower;
            return sorted[lower] * (1 - weight) + sorted[upper] * weight;
        }
    }
    
    static skewness(data: number[]): number {
        const mean = this.mean(data);
        const std = this.standardDeviation(data);
        const sum = data.reduce((sum, value) => sum + Math.pow((value - mean) / std, 3), 0);
        return sum / data.length;
    }
    
    static kurtosis(data: number[]): number {
        const mean = this.mean(data);
        const std = this.standardDeviation(data);
        const sum = data.reduce((sum, value) => sum + Math.pow((value - mean) / std, 4), 0);
        return sum / data.length - 3; // 减去3得到超额峰度
    }
    
    static main(): void {
        const data = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
        
        console.log("描述统计测试:");
        console.log(`均值: ${this.mean(data).toFixed(2)}`);
        console.log(`中位数: ${this.median(data).toFixed(2)}`);
        console.log(`方差: ${this.variance(data).toFixed(2)}`);
        console.log(`标准差: ${this.standardDeviation(data).toFixed(2)}`);
        console.log(`25%分位数: ${this.percentile(data, 25).toFixed(2)}`);
        console.log(`75%分位数: ${this.percentile(data, 75).toFixed(2)}`);
        console.log(`偏度: ${this.skewness(data).toFixed(2)}`);
        console.log(`峰度: ${this.kurtosis(data).toFixed(2)}`);
    }
}

// 示例使用
DescriptiveStatistics.main();
