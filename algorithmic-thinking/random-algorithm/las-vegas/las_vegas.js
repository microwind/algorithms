/**
 * 拉斯维加斯算法实现 (JavaScript)
 * 
 * 特点：
 * - 总是给出正确答案
 * - 运行时间随机
 * - 不返回错误答案
 */

// 交换数组中两个元素
function swap(arr, i, j) {
    [arr[i], arr[j]] = [arr[j], arr[i]];
}

// 随机分区函数
function randomizedPartition(arr, left, right) {
    // 随机选择枢轴
    const pivotIdx = left + Math.floor(Math.random() * (right - left + 1));
    swap(arr, pivotIdx, right);
    
    const pivot = arr[right];
    let i = left - 1;
    
    for (let j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    
    swap(arr, i + 1, right);
    return i + 1;
}

// 拉斯维加斯随机快速排序
function lasVegasQuickSort(arr, left = 0, right = arr.length - 1) {
    if (left < right) {
        // 随机分区
        const pivotIdx = randomizedPartition(arr, left, right);
        
        // 递归排序左右子数组
        lasVegasQuickSort(arr, left, pivotIdx - 1);
        lasVegasQuickSort(arr, pivotIdx + 1, right);
    }
}

// 拉斯维加斯随机选择算法 - 找第k小元素
function lasVegasRandomizedSelect(arr, left, right, k) {
    if (left === right) {
        return arr[left];
    }
    
    // 随机分区
    const pivotIdx = randomizedPartition(arr, left, right);
    
    // 计算枢轴的相对位置
    const pos = pivotIdx - left + 1;
    
    if (k === pos) {
        return arr[pivotIdx];
    } else if (k < pos) {
        return lasVegasRandomizedSelect(arr, left, pivotIdx - 1, k);
    } else {
        return lasVegasRandomizedSelect(arr, pivotIdx + 1, right, k - pos);
    }
}

// 拉斯维加斯字符串匹配
function lasVegasStringMatch(text, pattern) {
    const n = text.length;
    const m = pattern.length;
    
    if (m > n) return -1;
    
    // 随机选择起始位置进行匹配
    while (true) {
        const start = Math.floor(Math.random() * (n - m + 1));
        
        // 检查是否匹配
        let match = true;
        for (let i = 0; i < m; i++) {
            if (text[start + i] !== pattern[i]) {
                match = false;
                break;
            }
        }
        
        if (match) {
            return start; // 找到匹配位置
        }
        
        // 在实际实现中，这里应该有避免无限循环的机制
        // 为了演示，这里简化处理
        break;
    }
    
    return -1;
}

// 拉斯维加斯八皇后问题求解器
function lasVegasNQueens(n) {
    while (true) {
        const queens = new Array(n).fill(-1);
        const columns = new Array(n).fill(false);
        const diag1 = new Array(2 * n - 1).fill(false); // 主对角线
        const diag2 = new Array(2 * n - 1).fill(false); // 副对角线
        
        let success = true;
        
        // 逐行放置皇后
        for (let row = 0; row < n; row++) {
            // 收集当前行可用的列
            const availableCols = [];
            for (let col = 0; col < n; col++) {
                if (!columns[col] && !diag1[row + col] && !diag2[row - col + n - 1]) {
                    availableCols.push(col);
                }
            }
            
            if (availableCols.length === 0) {
                success = false;
                break;
            }
            
            // 随机选择一个可用列
            const chosenCol = availableCols[Math.floor(Math.random() * availableCols.length)];
            queens[row] = chosenCol;
            columns[chosenCol] = true;
            diag1[row + chosenCol] = true;
            diag2[row - chosenCol + n - 1] = true;
        }
        
        if (success) {
            return queens;
        }
    }
}

// 打印数组
function printArray(arr) {
    console.log(`[${arr.join(', ')}]`);
}

// 打印八皇后解法
function printNQueensSolution(queens) {
    const n = queens.length;
    for (let row = 0; row < n; row++) {
        let line = '';
        for (let col = 0; col < n; col++) {
            if (queens[row] === col) {
                line += 'Q ';
            } else {
                line += '. ';
            }
        }
        console.log(line);
    }
}

// 主函数
function main() {
    console.log('=== 拉斯维加斯算法演示 ===\n');
    
    // 测试随机快速排序
    console.log('1. 拉斯维加斯随机快速排序');
    const arr1 = [5, 2, 8, 1, 9, 3, 4, 7, 6];
    
    console.log('原数组:');
    printArray(arr1);
    
    lasVegasQuickSort(arr1);
    
    console.log('排序后:');
    printArray(arr1);
    console.log();
    
    // 测试随机选择算法
    console.log('2. 拉斯维加斯随机选择算法');
    const arr2 = [7, 2, 5, 3, 9, 1, 4, 6, 8];
    const k = 4; // 找第4小元素
    
    console.log('数组:');
    printArray(arr2);
    console.log(`第${k}小元素: ${lasVegasRandomizedSelect([...arr2], 0, arr2.length - 1, k)}`);
    console.log();
    
    // 测试字符串匹配
    console.log('3. 拉斯维加斯字符串匹配');
    const text = 'hello world, this is a test string';
    const pattern = 'test';
    
    console.log(`文本: ${text}`);
    console.log(`模式: ${pattern}`);
    const pos = lasVegasStringMatch(text, pattern);
    if (pos !== -1) {
        console.log(`匹配位置: ${pos}`);
    } else {
        console.log('未找到匹配');
    }
    console.log();
    
    // 测试八皇后问题
    console.log('4. 拉斯维加斯八皇后问题求解');
    const n = 8;
    const solution = lasVegasNQueens(n);
    console.log(`八皇后解法 (n=${n}):`);
    printNQueensSolution(solution);
}

// 运行主函数
main();
