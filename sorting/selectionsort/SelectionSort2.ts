/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
 * 提供双向选择优化版本，适合不同场景和性能需求
 */
class SelectionSort2 {

    // ==================== 主程序：算法演示和性能测试 ====================
    
    // 测试数据：
    private static readonly testData: number[] = [7, 11, 9, 10, 12, 13, 8];

    /**
     * 选择排序双向选择优化版本
     *
     * 算法原理：
     * 1. 每轮同时选择最小和最大元素
     * 2. 将最小元素放到左侧，最大元素放到右侧
     * 3. 减少排序轮数，提高效率
     *
     * ## 实现步骤
     * 1. 初始化左右边界指针
     * 2. 外循环控制排序轮数，同时处理两端
     * 3. 内循环在未排序区域查找最小和最大元素
     * 4. 交换最小元素到左侧，最大元素到右侧
     * 5. 调整边界指针
     *
     * @param arr 待排序的数字数组
     * @return 排序后的数组
     */
    static selectionSort(arr: number[]): number[] {
        console.log('selectionSort bidirectional:');
        let minValue: number, maxValue: number, minIdx: number, maxIdx: number;
        let minListIdx: number, maxListIdx: number;
        const arrLen: number = arr.length;
        
        for (let i = 0; i < arrLen - 1; i++) {
            // 初始化最小值和下标
            minIdx = i;
            minValue = arr[minIdx];
            // 初始化最大值和下标
            maxIdx = i;
            maxValue = arr[maxIdx];
            
            // 设置左右边界交换位置
            // 左边界从前往后递增，右边界从后往前递减
            minListIdx = minIdx;
            maxListIdx = arrLen - 1 - i;
            
            // 如果左右边界相遇，说明只剩一个元素，终止循环
            if (minListIdx === maxListIdx) {
                break;
            }

            // 在待排序区间查找最小和最大值
            // 待排序区间：从i+1到arrLen-i-1
            let j: number;
            for (j = i + 1; j < arrLen - i; j++) {
                // 更新最小值
                if (arr[j] < minValue) {
                    minIdx = j;
                    minValue = arr[minIdx];
                } else if (arr[j] > maxValue) {
                    // 更新最大值
                    maxIdx = j;
                    maxValue = arr[maxIdx];
                }
            }

            // 如果元素已在正确位置，跳过交换
            if (arr[minIdx] === arr[minListIdx] && arr[maxIdx] === arr[maxListIdx]) {
                continue;
            }

            console.log(`i=${i} j=${j} min=${minValue} max=${maxValue} minIdx=${minIdx} maxIdx=${maxIdx} minListIdx=${minListIdx} maxListIdx=${maxListIdx} arr[]=${JSON.stringify(arr)}`);

            // 执行双向交换，先交换最小值到左边界
            arr[minIdx] = arr[minListIdx];
            arr[minListIdx] = minValue;
            // 处理最大值位置变化的特殊情况
            if (arr[minIdx] === maxValue) {
                maxIdx = minIdx;
            }
            // 交换最大值到右边界
            arr[maxIdx] = arr[maxListIdx];
            arr[maxListIdx] = maxValue;
        }
        return arr;
    }

    /**
     * 性能测试方法
     *
     * @param sortFunction 排序函数
     * @param data 测试数据
     * @param versionName 版本名称
     */
    private static performanceTest(sortFunction: (arr: number[]) => number[], data: number[], versionName: string): void {
        const testData = [...data];
        console.log(`${versionName}原始数组: ${JSON.stringify(testData)}`);
        
        const startTime = performance.now();
        const result = sortFunction(testData);
        const endTime = performance.now();
        
        console.log(`${versionName}: ${(endTime - startTime).toFixed(3)}ms`);
        console.log(`${versionName}排序结果: ${JSON.stringify(result)}`);
        console.log();
    }

    public static main(): void {
        // 测试：双向选择优化版本
        SelectionSort2.performanceTest(SelectionSort2.selectionSort, SelectionSort2.testData, "双向选择优化版本");

        console.log("=== 算法对比总结 ===");
        console.log("1. 双向选择优化版本：同时选择最大最小，效率提升");
    }
}

// 执行测试
SelectionSort2.main();

/*
jarry@Mac selectionsort % ts-node SelectionSort2.ts
双向选择优化版本原始数组: [7,11,9,10,12,13,8]
selectionSort bidirectional:
i=0 j=7 min=7 max=13 minIdx=0 maxIdx=5 minListIdx=0 maxListIdx=6 arr[]=[7,11,9,10,12,13,8]
i=1 j=6 min=8 max=12 minIdx=5 maxIdx=4 minListIdx=1 maxListIdx=5 arr[]=[7,11,9,10,12,8,13]
双向选择优化版本: 0.061ms
双向选择优化版本排序结果: [7,8,9,10,11,12,13]

=== 算法总结 ===
1. 双向选择优化版本：同时选择最大最小，效率提升
*/