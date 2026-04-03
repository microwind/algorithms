/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 归并排序算法实现
 * 提供五种不同的实现方式，适合不同场景和性能需求
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
const testData: number[] = [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4];

/**
 * 合并两个有序数组
 */
function merge(left: number[], right: number[]): number[] {
    // 步骤1：初始化结果数组和索引指针
    // 关键点：使用三个指针分别跟踪两个输入数组和结果数组
    const result: number[] = [];
    let leftIndex = 0;
    let rightIndex = 0;
    
    // 步骤2：同时遍历两个数组，按顺序合并
    // 关键点：当两个数组都还有元素时继续比较
    while (leftIndex < left.length && rightIndex < right.length) {
        // 步骤2.1：比较当前元素
        // 关键点：选择较小的元素放入结果数组
        if (left[leftIndex] <= right[rightIndex]) {
            result.push(left[leftIndex]);
            leftIndex++;
        } else {
            result.push(right[rightIndex]);
            rightIndex++;
        }
    }
    
    // 步骤3：处理剩余元素
    // 关键点：将未处理完的数组元素直接添加到结果数组
    // TypeScript特点：使用扩展运算符处理剩余元素
    result.push(...left.slice(leftIndex));
    result.push(...right.slice(rightIndex));
    
    return result;
}

/**
 * 递归归并排序函数
 */
function mergeSortRecursive(arr: number[]): number[] {
    // 步骤1：检查递归终止条件
    // 关键点：数组长度小于2时已经有序，直接返回
    if (arr.length <= 1) {
        return arr;
    }
    
    // 步骤2：分割数组为两半
    // 关键点：取得当前数组的中间位置，将数组分为两半
    const middle = Math.floor(arr.length / 2);
    const left = arr.slice(0, middle);   // 左半部分
    const right = arr.slice(middle);     // 右半部分
    
    // 步骤3：递归调用
    // 关键点：递归调用，不断重复直到当前数组拆分剩1项
    // TypeScript特点：使用slice创建新数组，避免修改原数组
    return merge(mergeSortRecursive(left), mergeSortRecursive(right));
}

/**
 * 归并排序基础版本 - 递归实现
 * 
 * 算法原理：
 * 1. 将数组递归地分成两半，直到每个子数组只有一个元素
 * 2. 将相邻的两个有序子数组合并成一个更大的有序数组
 * 3. 重复合并过程，直到最终得到一个完全有序的数组
 * 
 * 生活类比：就像整理一副扑克牌，先把牌分成两堆，
 * 每堆分别整理好，然后将两堆有序地合并在一起
 * 
 * 时间复杂度：O(n log n) - 无论如何都需要O(n log n)次比较
 * 空间复杂度：O(n) - 需要额外的数组空间来存储合并结果
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
function mergeSort1(arr: number[]): void {
    console.log('mergeSort1 recursive:');
    const result = mergeSortRecursive(arr);
    arr.length = 0;
    arr.push(...result);
    printArray(arr, '排序后数组');
}

/**
 * 原地合并两个有序子数组
 */
function mergeInPlace(arr: number[], left: number, mid: number, right: number): void {
    // 步骤1：创建临时数组存储左半部分
    // 关键点：临时数组用于存储左半部分，避免数据覆盖
    const leftArr = arr.slice(left, mid + 1);
    
    // 步骤2：初始化指针
    // 关键点：i指向左数组，j指向右数组，k指向合并位置
    let i = 0; // 左数组索引
    let j = mid + 1; // 右数组索引
    let k = left; // 合并位置索引
    
    // 步骤3：合并两个有序子数组
    // 关键点：按顺序合并，保持稳定性
    while (i < leftArr.length && j <= right) {
        if (leftArr[i] <= arr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = arr[j];
            j++;
        }
        k++;
    }
    
    // 步骤4：复制左数组剩余元素
    // 关键点：左数组可能还有未处理的元素
    while (i < leftArr.length) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
}

/**
 * 递归归并排序函数 - 原地版本
 */
function mergeSortInPlaceRecursive(arr: number[], left: number, right: number): void {
    // 步骤1：检查递归终止条件
    // 关键点：left >= right时子数组已经有序
    if (left < right) {
        // 步骤2：计算中间值
        // 关键点：使用Math.floor避免浮点数问题
        const mid = Math.floor((left + right) / 2);
        
        // 步骤3：递归排序左半部分
        // 关键点：处理范围 [left, mid]
        mergeSortInPlaceRecursive(arr, left, mid);
        
        // 步骤4：递归排序右半部分
        // 关键点：处理范围 [mid+1, right]
        mergeSortInPlaceRecursive(arr, mid + 1, right);
        
        // 步骤5：合并左右结果
        // 关键点：将两个有序子数组合并为一个更大的有序子数组
        mergeInPlace(arr, left, mid, right);
    }
}

/**
 * 归并排序优化版本 - 原地合并
 * 
 * 优化思路：
 * 减少空间复杂度，尝试在原数组上进行合并操作
 * 使用索引操作而不是创建新数组
 * 
 * 优化效果：
 * - 减少了内存分配
 * - 提高了空间效率
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(log n) - 仅递归栈空间
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
function mergeSort2(arr: number[]): void {
    console.log('mergeSort2 in-place:');
    if (arr.length > 0) {
        mergeSortInPlaceRecursive(arr, 0, arr.length - 1);
    }
    printArray(arr, '排序后数组');
}

/**
 * 合并两个有序子数组 - 迭代版本
 */
function mergeIterative(arr: number[], temp: number[], left: number, mid: number, right: number): void {
    // 步骤1：初始化索引指针
    // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
    let i = left; // 左子数组索引
    let j = mid + 1; // 右子数组索引
    let k = left; // 临时数组索引
    
    // 步骤2：合并到临时数组
    // 关键点：按顺序合并两个有序子数组
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    
    // 步骤3：复制左子数组剩余元素
    // 关键点：左子数组可能还有未处理的元素
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    
    // 步骤4：复制右子数组剩余元素
    // 关键点：右子数组可能还有未处理的元素
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    
    // 步骤5：将临时数组复制回原数组
    // 关键点：使用循环逐个复制，确保数据正确性
    // TypeScript特点：也可以使用slice和concat，但循环更直观
    for (let index = left; index <= right; index++) {
        arr[index] = temp[index];
    }
}

/**
 * 归并排序 - 迭代版本
 * 
 * 算法思路：
 * 使用迭代方式代替递归，避免递归栈开销
 * 从小规模合并开始，逐步扩大合并规模
 * 
 * 优化效果：
 * - 避免了递归调用的开销
 * - 更好的缓存局部性
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
function mergeSort3(arr: number[]): void {
    console.log('mergeSort3 iterative:');
    
    const n = arr.length;
    const temp = new Array(n);
    
    // 步骤1：迭代合并，步长从1开始翻倍
    // 关键点：通过迭代方式模拟递归的合并过程
    for (let size = 1; size < n; size *= 2) {
        // 步骤2：处理所有相邻的子数组对
        // 关键点：每次处理两个大小为size的相邻子数组
        for (let left = 0; left < n - size; left += 2 * size) {
            // 步骤3：计算当前合并的边界
            // 关键点：确定左子数组 [left, mid] 和右子数组 [mid+1, right]
            const mid = left + size - 1;
            const right = Math.min(left + 2 * size - 1, n - 1);
            
            // 步骤4：执行迭代合并
            // 关键点：使用迭代方式合并两个有序子数组
            mergeIterative(arr, temp, left, mid, right);
        }
    }
    
    printArray(arr, '排序后数组');
}

/**
 * 合并两个相邻的有序子数组 - 自底向上版本
 */
function mergeBottomUp(arr: number[], temp: number[], left: number, mid: number, right: number): void {
    // 步骤1：初始化索引指针
    // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
    let i = left;
    let j = mid;
    let k = left;
    
    // 步骤2：合并两个有序子数组到临时数组
    // 关键点：按顺序合并，保持稳定性
    while (i < mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    
    // 步骤3：复制剩余元素
    // 关键点：将未处理完的数组元素直接添加到临时数组
    while (i < mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    
    // 步骤4：复制回原数组
    // 关键点：使用循环逐个复制，确保数据正确性
    for (let index = left; index <= right; index++) {
        arr[index] = temp[index];
    }
}

/**
 * 归并排序 - 自底向上版本
 * 
 * 算法思路：
 * 先将数组分成单个元素，然后两两合并
 * 逐步扩大合并规模，直到整个数组有序
 * 
 * 优化效果：
 * - 更好的内存访问模式
 * - 适合外部排序（处理大数据）
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
function mergeSort4(arr: number[]): void {
    console.log('mergeSort4 bottom-up:');
    
    const n = arr.length;
    const temp = new Array(n);
    
    // 步骤1：自底向上合并
    // 关键点：从单个元素开始，逐步扩大合并规模
    for (let width = 1; width < n; width *= 2) {
        // 步骤2：处理所有相邻的子数组对
        // 关键点：每次处理两个大小为width的相邻子数组
        for (let i = 0; i < n; i += 2 * width) {
            // 步骤3：计算当前合并的边界
            // 关键点：确定左子数组 [i, mid] 和右子数组 [mid, right)
            const left = i;
            const mid = Math.min(i + width, n);
            const right = Math.min(i + 2 * width, n);
            
            // 步骤4：执行自底向上合并
            // 关键点：只有当mid < right时才需要合并
            if (mid < right) {
                mergeBottomUp(arr, temp, left, mid, right - 1);
            }
        }
    }
    
    printArray(arr, '排序后数组');
}

/**
 * 归并排序 - 非递归合并版本
 * 
 * 算法思路：
 * 使用非递归方式进行合并操作，避免递归调用
 * 通过迭代方式处理合并过程，提高内存效率
 * 
 * 优化效果：
 * - 避免递归栈开销
 * - 更好的内存访问模式
 * - 适合大数据处理
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
function mergeSort5(arr: number[]): void {
    console.log('mergeSort5 non-recursive merge:');
    
    // 非递归合并两个有序子数组
    const mergeNonRecursive = (arr: number[], temp: number[], left: number, mid: number, right: number) => {
        // 步骤1：初始化索引指针
        // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
        let i = left;      // 左子数组索引
        let j = mid + 1;   // 右子数组索引
        let k = left;      // 临时数组索引
        
        // 步骤2：合并到临时数组
        // 关键点：按顺序合并两个有序子数组
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k] = arr[i];
                i++;
            } else {
                temp[k] = arr[j];
                j++;
            }
            k++;
        }
        
        // 步骤3：复制左子数组剩余元素
        // 关键点：左子数组可能还有未处理的元素
        while (i <= mid) {
            temp[k] = arr[i];
            i++;
            k++;
        }
        
        // 步骤4：复制右子数组剩余元素
        // 关键点：右子数组可能还有未处理的元素
        while (j <= right) {
            temp[k] = arr[j];
            j++;
            k++;
        }
        
        // 步骤5：将临时数组复制回原数组
        // 关键点：使用循环逐个复制，确保数据正确性
        // TypeScript特点：也可以使用slice和concat，但循环更直观
        for (let index = left; index <= right; index++) {
            arr[index] = temp[index];
        }
    };
    
    const n = arr.length;
    if (n <= 1) {
        return;
    }
    
    // 步骤1：创建临时数组
    // 关键点：临时数组用于存储合并过程中的中间结果
    const temp = new Array(n);
    
    // 步骤2：非递归合并过程
    // 关键点：通过迭代方式模拟递归的合并过程
    for (let size = 1; size < n; size *= 2) {
        // 步骤3：处理所有相邻的子数组对
        // 关键点：每次处理两个大小为size的相邻子数组
        for (let left = 0; left < n - size; left += 2 * size) {
            // 步骤4：计算当前合并的边界
            // 关键点：确定左子数组 [left, mid] 和右子数组 [mid+1, right]
            const mid = left + size - 1;
            let right = left + 2 * size - 1;
            if (right >= n) {
                right = n - 1;
            }
            
            // 步骤5：执行非递归合并
            // 关键点：使用迭代方式合并两个有序子数组
            mergeNonRecursive(arr, temp, left, mid, right);
        }
    }
    
    printArray(arr, '排序后数组');
}

// ==================== 算法测试和性能对比 ====================

// 测试1：递归版本
performanceTest(mergeSort1, testData, '递归版本');

// 测试2：原地合并版本
performanceTest(mergeSort2, testData, '原地合并版本');

// 测试3：迭代版本
performanceTest(mergeSort3, testData, '迭代版本');

// 测试4：自底向上版本
performanceTest(mergeSort4, testData, '自底向上版本');

// 测试5：非递归合并版本
performanceTest(mergeSort5, testData, '非递归合并版本');

console.log('=== 算法对比总结 ===');
console.log('1. 递归版本：经典实现，易于理解');
console.log('2. 原地版本：空间优化，减少内存使用');
console.log('3. 迭代版本：避免递归，性能稳定');
console.log('4. 底向上版本：适合大数据，外部排序');
console.log('5. 非递归合并版本：迭代合并，高效内存');

/*
打印结果
jarry@Mac mergesort % node MergeSort.ts
递归版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort1 recursive:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
递归版本: 0.071ms
递归版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

原地合并版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort2 in-place:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
原地合并版本: 0.064ms
原地合并版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort3 iterative:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.054ms
迭代版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

自底向上版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort4 bottom-up:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
自底向上版本: 0.044ms
自底向上版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

非递归合并版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort5 non-recursive merge:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
非递归合并版本: 0.055ms
非递归合并版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归版本：经典实现，易于理解
2. 原地版本：空间优化，减少内存使用
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 非递归合并版本：迭代合并，高效内存
*/
