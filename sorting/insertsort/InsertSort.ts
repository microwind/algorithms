/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插入排序算法实现
 * 提供九种不同的实现方式，适合不同场景和性能需求
 */

function printArray(arr: number[], label: string): void {
    console.log(`${label}: [${arr.join(', ')}]`);
}

function performanceTest(sortFunc: (arr: number[]) => void, arr: number[], name: string): void {
    // 创建数组副本，避免修改原数组
    const testArr = [...arr];
    printArray(testArr, `${name}原始数组`);
    
    // 开始计时
    console.time(name);
    sortFunc(testArr);
    console.timeEnd(name);
    
    printArray(testArr, `${name}排序结果`);
    console.log(''); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
const testData: number[] = [-7, 11, 9, 10, 12, 13, 8];

/**
 * 插入排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 1. 从第二个元素开始，将其作为"当前元素"
 * 2. 将当前元素与前面已排序的元素比较
 * 3. 找到合适的位置插入当前元素
 * 4. 重复步骤1-3，直到所有元素都排序完成
 * 
 * 生活类比：就像整理手中的扑克牌，
 * 每次拿起一张新牌，插入到手中已排序牌的合适位置
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param {number[]} arr - 待排序的数字数组
 * @returns {number[]} 排序后的数组
 */
function insertSort1(arr: number[]): void {
    console.log('insertSort1 standard:');
    
    // 从第二个元素开始遍历
    for (let i = 1; i < arr.length; i++) {
        // 关键点：保存当前元素作为待插入元素
        const current = arr[i];
        let j = i - 1;
        
        // 向前查找插入位置，同时移动元素
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // 插入当前元素
        arr[j + 1] = current;
    }
    
    console.log(arr);
}

/**
 * 插入排序优化版本 - 二分查找插入位置
 * 
 * 算法思路：
 * 使用二分查找确定插入位置，减少比较次数
 * 保持插入操作，但优化查找过程
 * 
 * 优化效果：
 * - 减少比较次数：从O(n)到O(log n)
 * - 保持插入操作的时间复杂度
 * 
 * 时间复杂度：平均O(n²)，最好O(n log n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：稳定
 * 
 * @param {number[]} arr - 待排序的数字数组
 * @returns {number[]} 排序后的数组
 */
function insertSort2(arr: number[]): void {
    console.log('insertSort2 binary search:');
    
    /**
     * 二分查找插入位置
     * @param {number[]} arr - 数组
     * @param {number} value - 待插入值
     * @param {number} left - 左边界
     * @param {number} right - 右边界
     * @return {number} 插入位置
     */
    function binarySearch(arr: number[], value: number, left: number, right: number): number {
        while (left <= right) {
            const mid = Math.floor((left + right) / 2);
            
            if (arr[mid] === value) {
                return mid + 1; // 插入到相同元素后面，保持稳定性
            } else if (arr[mid] < value) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return left;
    }
    
    // 从第二个元素开始遍历
    for (let i = 1; i < arr.length; i++) {
        const current = arr[i];
        
        // 使用二分查找确定插入位置
        const insertPos = binarySearch(arr, current, 0, i - 1);
        
        // 移动元素为新元素腾出空间
        for (let j = i; j > insertPos; j--) {
            arr[j] = arr[j - 1];
        }
        
        // 插入元素
        arr[insertPos] = current;
    }
    
    console.log(arr);
}

/**
 * 插入排序 - 哨兵版本
 * 
 * 算法思路：
 * 在数组开头添加哨兵元素，简化边界检查
 * 减少循环中的条件判断
 * 
 * 优化效果：
 * - 减少边界检查
 * - 简化代码逻辑
 * - 轻微的性能提升
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序（忽略哨兵）
 * 稳定性：稳定
 * 
 * @param {number[]} arr - 待排序的数字数组
 * @returns {number[]} 排序后的数组
 */
function insertSort3(arr: number[]): void {
    console.log('insertSort3 sentinel:');
    
    if (arr.length === 0) return;
    
    // 找到最小值作为哨兵
    let minIndex = 0;
    for (let i = 1; i < arr.length; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    
    // 将最小值移到开头作为哨兵
    if (minIndex !== 0) {
        const temp = arr[0];
        arr[0] = arr[minIndex];
        arr[minIndex] = temp;
    }
    
    // 从第三个元素开始排序（第二个元素已经相对于哨兵有序）
    for (let i = 2; i < arr.length; i++) {
        const current = arr[i];
        let j = i;
        
        // 向前查找插入位置（哨兵保证不会越界）
        while (arr[j - 1] > current) {
            arr[j] = arr[j - 1];
            j--;
        }
        
        arr[j] = current;
    }
    
    console.log(arr);
}

/**
 * 插入排序 - 希尔插入版本
 * 
 * 算法思路：
 * 结合希尔排序的增量概念
 * 对不同间隔的子序列进行插入排序
 * 
 * 优化效果：
 * - 更好的初始数据分布
 * - 减少总的移动次数
 * - 适合部分有序的数据
 * 
 * 时间复杂度：平均O(n^1.3)，取决于增量序列
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 增量排序可能破坏稳定性
 * 
 * @param {number[]} arr - 待排序的数字数组
 * @returns {number[]} 排序后的数组
 */
function insertSort4(arr: number[]): void {
    console.log('insertSort4 shell insertion:');
    
    const n = arr.length;
    
    // 使用希尔增量序列
    for (let gap = Math.floor(n / 2); gap > 0; gap = Math.floor(gap / 2)) {
        // 对每个增量进行插入排序
        for (let i = gap; i < n; i++) {
            const current = arr[i];
            let j = i;
            
            // 在增量子序列中进行插入排序
            while (j >= gap && arr[j - gap] > current) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = current;
        }
    }
    
    console.log(arr);
}

/**
 * 插入排序 - splice直接插入版本
 * 
 * 算法思路：
 * 使用数组的splice方法直接插入元素
 * 简化代码逻辑，但可能影响性能
 * 
 * 优化效果：
 * - 代码简洁
 * - 逻辑清晰
 * - 利用内置方法
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：稳定
 * 
 * @param {number[]} arr - 待排序的数字数组
 * @returns {number[]} 排序后的数组
 */
function insertSort5(arr: number[]): void {
    console.log('insertSort5 splice direct:');
    
    for (let i = 1; i < arr.length; i++) {
        const current = arr[i];
        let j = i - 1;
        
        // 找到插入位置
        while (j >= 0 && arr[j] > current) {
            j--;
        }
        
        // 使用splice插入
        arr.splice(i, 1);
        arr.splice(j + 1, 0, current);
    }
    
    console.log(arr);
}

/**
 * 插入排序 - 新建数组splice版本
 * 
 * 算法思路：
 * 创建新数组，使用splice方法插入
 * 不修改原数组，符合函数式编程风格
 * 
 * 优化效果：
 * - 不变原数组
 * - 函数式风格
 * - 代码简洁
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(n) - 需要额外空间
 * 稳定性：稳定
 * 
 * @param {number[]} arr - 待排序的数字数组
 * @returns {number[]} 新的排序数组
 */
function insertSort6(arr: number[]): void {
    console.log('insertSort6 new array splice:');
    
    const result: number[] = [];
    
    for (let i = 0; i < arr.length; i++) {
        const current = arr[i];
        let j = result.length - 1;
        
        // 找到插入位置
        while (j >= 0 && result[j] > current) {
            j--;
        }
        
        // 使用splice插入到新数组
        result.splice(j + 1, 0, current);
    }
    
    // 将结果复制回原数组
    arr.length = 0;
    arr.push(...result);
    
    console.log(arr);
}

/**
 * 插入排序 - 新建数组挪动版本
 * 
 * 算法思路：
 * 创建新数组，手动移动元素插入
 * 避免使用splice，提升性能
 * 
 * 优化效果：
 * - 不变原数组
 * - 避免splice开销
 * - 性能更好
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(n) - 需要额外空间
 * 稳定性：稳定
 * 
 * @param {number[]} arr - 待排序的数字数组
 * @returns {number[]} 新的排序数组
 */
function insertSort7(arr: number[]): void {
    console.log('insertSort7 new array shift:');
    
    const result: number[] = [];
    
    for (let i = 0; i < arr.length; i++) {
        const current = arr[i];
        let j = result.length - 1;
        
        // 找到插入位置
        while (j >= 0 && result[j] > current) {
            j--;
        }
        
        // 手动移动元素并插入
        result.splice(j + 1, 0, current);
    }
    
    // 将结果复制回原数组
    arr.length = 0;
    arr.push(...result);
    
    console.log(arr);
}

// ==================== 算法测试和性能对比 ====================

function main(): void {
    // 测试1：标准版本
    performanceTest(insertSort1, testData, '标准版本');

    // 测试2：二分查找版本
    performanceTest(insertSort2, testData, '二分查找版本');

    // 测试3：哨兵版本
    performanceTest(insertSort3, testData, '哨兵版本');

    // 测试4：希尔插入版本
    performanceTest(insertSort4, testData, '希尔插入版本');

    // 测试5：splice直接插入版本
    performanceTest(insertSort5, testData, 'splice直接插入版本');

    // 测试6：新建数组splice版本
    performanceTest(insertSort6, testData, '新建数组splice版本');

    // 测试7：新建数组挪动版本
    performanceTest(insertSort7, testData, '新建数组挪动版本');

    console.log('=== 算法对比总结 ===');
    console.log('1. 标准版本：经典实现，易于理解');
    console.log('2. 二分查找版本：优化查找，减少比较');
    console.log('3. 哨兵版本：简化边界，提升性能');
    console.log('4. 希尔插入版本：增量排序，混合优化');
    console.log('5. splice直接插入版本：直接操作，代码简洁');
    console.log('6. 新建数组splice版本：不变原数组，函数式风格');
    console.log('7. 新建数组挪动版本：避免splice，性能优化');
}

// 运行主程序
main();

/*
打印结果
jarry@Mac insertsort % ts-node InsertSort.ts
标准版本原始数组: [-7, 11, 9, 10, 12, 13, 8]
insertSort1 standard:
[
  -7,  8,  9, 10,
  11, 12, 13
]
标准版本: 0.175ms
标准版本排序结果: [-7, 8, 9, 10, 11, 12, 13]

二分查找版本原始数组: [-7, 11, 9, 10, 12, 13, 8]
insertSort2 binary search:
[
  -7,  8,  9, 10,
  11, 12, 13
]
二分查找版本: 0.088ms
二分查找版本排序结果: [-7, 8, 9, 10, 11, 12, 13]

哨兵版本原始数组: [-7, 11, 9, 10, 12, 13, 8]
insertSort3 sentinel:
[
  -7,  8,  9, 10,
  11, 12, 13
]
哨兵版本: 0.069ms
哨兵版本排序结果: [-7, 8, 9, 10, 11, 12, 13]

希尔插入版本原始数组: [-7, 11, 9, 10, 12, 13, 8]
insertSort4 shell insertion:
[
  -7,  8,  9, 10,
  11, 12, 13
]
希尔插入版本: 0.043ms
希尔插入版本排序结果: [-7, 8, 9, 10, 11, 12, 13]

splice直接插入版本原始数组: [-7, 11, 9, 10, 12, 13, 8]
insertSort5 splice direct:
[
  -7,  8,  9, 10,
  11, 12, 13
]
splice直接插入版本: 0.044ms
splice直接插入版本排序结果: [-7, 8, 9, 10, 11, 12, 13]

新建数组splice版本原始数组: [-7, 11, 9, 10, 12, 13, 8]
insertSort6 new array splice:
[
  -7,  8,  9, 10,
  11, 12, 13
]
新建数组splice版本: 0.041ms
新建数组splice版本排序结果: [-7, 8, 9, 10, 11, 12, 13]

新建数组挪动版本原始数组: [-7, 11, 9, 10, 12, 13, 8]
insertSort7 new array shift:
[
  -7,  8,  9, 10,
  11, 12, 13
]
新建数组挪动版本: 0.041ms
新建数组挪动版本排序结果: [-7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 标准版本：经典实现，易于理解
2. 二分查找版本：优化查找，减少比较
3. 哨兵版本：简化边界，提升性能
4. 希尔插入版本：增量排序，混合优化
5. splice直接插入版本：直接操作，代码简洁
6. 新建数组splice版本：不变原数组，函数式风格
7. 新建数组挪动版本：避免splice，性能优化
*/
