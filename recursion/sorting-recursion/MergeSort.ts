/**
 * 递归排序算法示例 - 归并排序
 * 
 * 算法特点：
 * - 使用分治递归实现稳定的排序算法
 * - 时间复杂度: O(n log n)，空间复杂度: O(n)
 * 
 * 学习重点：理解分治策略在排序中的应用
 */

/**
 * 合并两个有序数组
 * @param arr 原数组
 * @param left 左边界
 * @param mid 中间位置
 * @param right 右边界
 */
function merge(arr: number[], left: number, mid: number, right: number): void {
    const n1 = mid - left + 1;
    const n2 = right - mid;
    
    // 创建临时数组
    const L = new Array(n1);
    const R = new Array(n2);
    
    // 复制数据到临时数组
    for (let i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (let j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // 合并临时数组到原数组
    let i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // 复制剩余元素
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * 归并排序 - 递归实现
 * 时间复杂度: O(n log n)，空间复杂度: O(n)
 * @param arr 待排序数组
 * @param left 左边界
 * @param right 右边界
 */
function mergeSort(arr: number[], left: number, right: number): void {
    // 基础情况：只有一个元素
    if (left < right) {
        const mid = left + Math.floor((right - left) / 2);
        
        // 递归排序左半部分
        mergeSort(arr, left, mid);
        
        // 递归排序右半部分
        mergeSort(arr, mid + 1, right);
        
        // 合并两个有序部分
        merge(arr, left, mid, right);
    }
}

/**
 * 打印数组
 * @param arr 数组
 * @param size 数组大小
 */
function printArray(arr: number[], size: number): void {
    for (let i = 0; i < size; i++) {
        process.stdout.write(arr[i] + " ");
    }
    console.log();
}

/**
 * 主函数 - 测试归并排序
 */
function main(): void {
    const arr = [64, 34, 25, 12, 22, 11, 90];
    const n = arr.length;
    
    // 测试1：输出原始数组
    console.log("归并排序演示:");
    console.log();
    console.log("原始数组: ");
    printArray(arr, n);
    
    // 测试2：执行归并排序
    mergeSort(arr, 0, n - 1);
    
    // 测试3：输出排序结果
    console.log("排序结果: ");
    printArray(arr, n);
    
    // 输出递归分解过程
    console.log();
    console.log("递归分解过程:");
    console.log("  [64,34,25,12,22,11,90]");
    console.log("       /        \\");
    console.log("  [64,34,25,12]  [22,11,90]");
    console.log("    /    \\       /    \\");
    console.log("[64,34][25,12] [22,11][90]");
    console.log("  / \\    / \\    / \\    |");
    console.log("[64][34][25][12][22][11][90]");
    console.log();
    console.log("然后逐层合并...");
}

/*打印结果
jarry@Mac sorting-recursion % npx ts-node MergeSort.ts
归并排序演示:

原始数组: 64 34 25 12 22 11 90 
排序结果: 11 12 22 25 34 64 90 

递归分解过程:
  [64,34,25,12,22,11,90]
       /        \
  [64,34,25,12]  [22,11,90]
    /    \       /    \
[64,34][25,12] [22,11][90]
  / \    / \    / \    |
[64][34][25][12][22][11][90]

然后逐层合并...
*/

// 运行主函数
main();
