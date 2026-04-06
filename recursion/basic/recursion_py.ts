/**
 * 递归算法示例集合（基于Python版本）
 * 包含阶乘、斐波那契、汉诺塔、二分查找、数组求和、字符串反转等示例
 */

// 1. 阶乘 (Factorial)
// 时间复杂度: O(n), 空间复杂度: O(n)（递归栈深度）
function factorial(n: number): number {
    /* 计算 n 的阶乘 */
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 2. 斐波那契数列
// 普通递归: 时间复杂度 O(2^n)，空间复杂度 O(n)
function fibonacci(n: number): number {
    /* 计算斐波那契数列第 n 项（普通递归） */
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 优化版本（记忆化）
function fibonacciMemo(n: number, memo: { [key: number]: number } = {}): number {
    /* 计算斐波那契数列第 n 项（带记忆化） */
    if (n in memo) {
        return memo[n];
    }
    
    if (n <= 1) {
        memo[n] = n;
    } else {
        memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
    }
    
    return memo[n];
}

// 3. 汉诺塔问题
// 时间复杂度: O(2^n - 1)，空间复杂度: O(n)
function hanoi(n: number, source: string, target: string, auxiliary: string): void {
    /*
     * 解决汉诺塔问题
     * 将 n 个盘子从 source 柱移动到 target 柱
     */
    if (n === 1) {
        console.log(`Move disk 1 from ${source} to ${target}`);
        return;
    }
    
    // 将 n-1 个盘子从 source 移动到 auxiliary
    hanoi(n - 1, source, auxiliary, target);
    
    // 将最后一个盘子从 source 移动到 target
    console.log(`Move disk ${n} from ${source} to ${target}`);
    
    // 将 n-1 个盘子从 auxiliary 移动到 target
    hanoi(n - 1, auxiliary, target, source);
}

// 4. 二分查找（递归版本）
// 时间复杂度: O(log n)，空间复杂度: O(log n)
function binarySearch(arr: number[], target: number, low: number = 0, high: number = arr.length - 1): number {
    /* 在排序数组中递归查找目标值 */
    if (low > high) {
        return -1;
    }
    
    const mid = Math.floor((low + high) / 2);
    
    if (arr[mid] === target) {
        return mid;
    } else if (arr[mid] > target) {
        return binarySearch(arr, target, low, mid - 1);
    } else {
        return binarySearch(arr, target, mid + 1, high);
    }
}

// 5. 数组求和
// 时间复杂度: O(n)，空间复杂度: O(n)
function arraySum(arr: number[], index: number = 0): number {
    /* 递归计算数组元素和 */
    if (index >= arr.length) {
        return 0;
    }
    return arr[index] + arraySum(arr, index + 1);
}

// 6. 反转字符串
// 时间复杂度: O(n)，空间复杂度: O(n)
function reverseString(s: string): string {
    /* 递归反转字符串 */
    if (s === '') {
        return '';
    }
    return reverseString(s.slice(1)) + s[0];
}

// 测试代码
function main(): void {
    console.log("=== 递归算法测试 ===\n");
    
    // 测试阶乘
    console.log("1. 阶乘");
    console.log(`5! = ${factorial(5)}`);
    
    // 测试斐波那契
    console.log("\n2. 斐波那契数列");
    console.log(`fib(10) = ${fibonacci(10)}`);
    console.log(`fib(10) with memo = ${fibonacciMemo(10)}`);
    
    // 测试汉诺塔
    console.log("\n3. 汉诺塔问题 (n=3)");
    hanoi(3, 'A', 'C', 'B');
    
    // 测试二分查找
    console.log("\n4. 二分查找");
    const arr: number[] = [1, 3, 5, 7, 9, 11, 13];
    console.log(`查找 7: 索引 = ${binarySearch(arr, 7)}`);
    
    // 测试数组求和
    console.log("\n5. 数组求和");
    console.log(`sum([1,2,3,4,5]) = ${arraySum([1,2,3,4,5])}`);
    
    // 测试字符串反转
    console.log("\n6. 字符串反转");
    console.log(`reverse('hello') = ${reverseString('hello')}`);
}

main();
