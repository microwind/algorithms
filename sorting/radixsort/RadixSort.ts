/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供6种不同的实现方式，适合不同场景和性能需求
 * 
 * ==================== 6个基数排序算法的相同与区别 ====================
 * 
 * 【相同点】
 * 1. 核心原理：都是基于基数排序思想，按位数进行排序
 * 2. 稳定性：所有算法都保持排序的稳定性
 * 3. 基数范围：都使用10进制基数（0-9）
 * 4. 适用场景：都适合整数排序，特别是大范围数字
 * 5. 时间复杂度：理论时间复杂度都是O(d * (n + k))，d为位数，k为基数
 * 
 * 【区别点】
 * 
 * 1. radixSort1 - 计数排序基数排序版本
 *    - 实现方式：基于计数排序的LSD（最低位优先）实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k) 需要计数数组和输出数组
 *    - 特点：经典实现，代码清晰易懂
 * 
 * 2. radixSort2 - 内联计数排序基数排序版本
 *    - 实现方式：内联计数排序逻辑的LSD实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k) 需要计数数组和输出数组
 *    - 特点：减少函数调用开销，性能略优
 * 
 * 3. radixSort3 - 迭代MSD基数排序版本
 *    - 实现方式：使用栈模拟递归的MSD（最高位优先）实现
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k + s) s为栈空间
 *    - 特点：避免递归深度过大，适合大数据集
 * 
 * 4. radixSort4 - 桶优化基数排序版本
 *    - 实现方式：动态桶大小的LSD实现
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k') k'为实际使用的基数范围（≤k）
 *    - 特点：内存优化，适合稀疏数据
 * 
 * 5. radixSort5 - 递归基数排序版本
 *    - 实现方式：递归处理每一位的LSD实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k + d) d为递归栈深度
 *    - 特点：代码简洁，递归深度由数字位数决定
 * 
 * 6. radixSort6 - MSD基数排序版本
 *    - 实现方式：递归MSD实现，从最高位开始排序
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k) 需要桶和计数数组
 *    - 特点：适合字符串或变长数据，高位优先处理
 * 
 * 【性能对比】
 * - 最快：radixSort5（递归版本）和radixSort4（桶优化版本）
 * - 内存最优：radixSort4（动态桶大小）
 * - 最稳定：radixSort3（迭代MSD，避免递归栈溢出）
 * - 代码最简洁：radixSort5（递归实现）
 * 
 * 【选择建议】
 * - 一般情况：推荐radixSort2（内联计数排序）
 * - 大数据集：推荐radixSort3（迭代MSD）
 * - 内存敏感：推荐radixSort4（桶优化）
 * - 代码简洁：推荐radixSort5（递归版本）
 * - 字符串排序：推荐radixSort6（MSD版本）
 */

function printArray(arr: number[], label: string): void {
    console.log(`${label}: [${arr.join(', ')}]`);
}

function performanceTest(sortFunc: (arr: number[]) => void, arr: number[], name: string): void {
    // 创建数组副本，避免修改原数组
    const testArr = [...arr];
    printArray(testArr, name);
    
    // 开始计时
    console.time(name);
    sortFunc(testArr);
    console.timeEnd(name);
    
    printArray(testArr, `${name}排序结果`);
    console.log(''); // 空行分隔
}

// ==================== 测试数据 ====================

// 测试数据：包含大数字的典型数组
const testData: number[] = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431];

// 负数测试数据
const negativeTestData: number[] = [170, 45, 75, -90, -802, 24, 2, 66, -5, 0];

/**
 * 获取数字的指定位数
 * @param num - 数字
 * @param exp - 指数（10的幂）
 * @return 指定位数的值
 */
function getDigit(num: number, exp: number): number {
    return Math.floor(Math.abs(num) / exp) % 10;
}

/**
 * 计数排序，根据基数按位进行计数
 * 
 * ## 算法特点
 * - 按位进行计数排序，支持负数处理
 * - 使用最小值偏移处理负数
 * - 稳定排序：保持相等元素的相对位置
 * - 适用于基数排序的按位处理
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(n + k)，k为基数范围（通常为10）
 * - 空间复杂度：O(n + k) - 需要计数数组和输出数组
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @param exponent - 当前处理的位数基数（1, 10, 100, ...）
 */
function countingSort(arr: number[], exponent: number): void {
    // 第一步：初始化变量和数组，按10个桶大小，0-9的个位数
    const arrLen = arr.length;
    const bucketRange = 10;
    const countList: number[] = [];
    for (let i = 0; i < bucketRange; i++) {
        countList[i] = 0;
    }
    const sortedList = new Array(arrLen);

    // 第二步：找出最小值
    // 关键点：处理负数情况，需要找到最小值进行偏移
    const minValue = Math.min(...arr);

    // 第三步：初始化计数数组
    // 关键点：将计数数组清零
    for (let i = 0; i < bucketRange; i++) {
        countList[i] = 0;
    }

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - minValue来处理负数，确保索引为正数
    for (let i = 0; i < arrLen; i++) {
        const item = arr[i] - minValue;
        const idx = Math.floor((item / exponent) % bucketRange);
        countList[idx]++;
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for (let i = 1; i < bucketRange; i++) {
        countList[i] += countList[i - 1];
    }
    console.log(`radixSort1 countingSort countList:[${countList.join(', ')}]`);

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for (let i = arrLen - 1; i >= 0; i--) {
        const item = arr[i] - minValue;
        const idx = Math.floor((item / exponent) % bucketRange);
        sortedList[countList[idx] - 1] = arr[i];
        countList[idx]--;
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for (let i = 0; i < arrLen; i++) {
        arr[i] = sortedList[i];
    }
    console.log(`radixSort1 -> sortedList:[${sortedList.join(', ')}]`);
}

/**
 * 基数排序，从低位到高位LSD版，基于计数排序
 * 
 * ## 算法特点
 * - 从低位到高位进行排序（LSD - Least Significant Digit）
 * - 基于计数排序实现，支持负数处理
 * - 稳定排序：保持相等元素的相对位置
 * - 适用于整数排序，特别是大范围数字
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * - 空间复杂度：O(n + k) - 需要额外的计数和输出数组
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
function radixSort1(arr: number[]): number[] {
    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if (arr.length === 0) {
        return arr;
    }

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    const maxValue = Math.max(...arr);
    const minValue = Math.min(...arr);

    // 第三步：根据最大值，逐个按进位(基数)来应用排序
    // 关键点：exponent即数位基数，按个十百千递增
    // 最大减去最小得到数位，最小按0来计算，这样可以支持负数
    for (let exponent = 1; Math.floor((maxValue - minValue) / exponent) > 0; exponent *= 10) {
        countingSort(arr, exponent);
    }

    return arr;
}

/**
 * 内联计数排序基数排序版本
 * 
 * ## 算法特点
 * - 基于计数排序的LSD实现，内联处理逻辑
 * - 支持负数处理，使用最小值偏移
 * - 稳定排序：保持相等元素的相对位置
 * - 适用于整数排序，特别是大范围数字
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * - 空间复杂度：O(n + k) - 需要计数数组和输出数组
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
function radixSort2(arr: number[]): number[] {
    // 第一步：初始化变量
    // 关键点：获取数组长度，设置基数范围
    const arrLen = arr.length;
    const range = 10;
    const sortedList = new Array(arrLen);

    // 第二步：找出最大值
    // 关键点：遍历数组找出最大值，用于确定位数
    const max = Math.max(...arr);

    // 第三步：找出最小值以支持负数
    // 关键点：处理负数情况，需要找到最小值进行偏移
    const min = Math.min(...arr);

    // 第四步：根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
    // 关键点：从1开始，每10进位，逐位进行比较和排序，一直到最大减去最小数
    for (let exponent = 1; Math.floor((max - min) / exponent) > 0; exponent *= range) {
        // 步骤4.1：创建计数数组
        // 关键点：计数数组长度为10，0-9一共10个数字
        const countList: number[] = [];
        for (let i = 0; i < range; i++) {
            countList[i] = 0;
        }

        // 步骤4.2：根据基数得到当前位数，并给计数数组对应位置加1
        // 关键点：使用arr[i] - min来处理负数，确保索引为正数
        for (let i = 0; i < arrLen; i++) {
            const item = arr[i] - min;
            const idx = Math.floor((item / exponent) % range);
            countList[idx]++;
        }

        // 步骤4.3：计数排序构建
        // 关键点：自前往后，逐个将上一项的值存入当前项
        for (let i = 1; i < range; i++) {
            countList[i] += countList[i - 1];
        }

        console.log(`radixSort2 -> countList:[${countList.join(', ')}]`);

        // 步骤4.4：根据计数数组按顺序取出排序内容
        // 关键点：从后向前遍历，保持排序的稳定性
        for (let i = arrLen - 1; i >= 0; i--) {
            const item = arr[i] - min;
            const idx = Math.floor((item / exponent) % range);
            sortedList[countList[idx] - 1] = arr[i];
            countList[idx]--;
        }

        console.log(`radixSort2 -> sortedList:[${sortedList.join(', ')}]`);

        // 步骤4.5：将新顺序赋值给原数组
        // 关键点：将排序结果复制回原数组，准备下一位处理
        for (let i = 0; i < arr.length; i++) {
            arr[i] = sortedList[i];
        }
    }

    return sortedList;
}

/**
 * MSD递归排序函数
 * 
 * ## 算法特点
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 使用递归处理子数组
 * - 桶排序实现，动态分配内存
 * - 适合处理字符串或变长数据
 * 
 * @param arr - 待排序的数字数组
 * @param left - 左边界索引
 * @param right - 右边界索引
 * @param exp - 当前处理的位数基数
 */
function msdSort(arr: number[], left: number, right: number, exp: number): void {
    // 第一步：递归终止条件检查
    // 关键点：范围无效或位数不足时返回
    if (left >= right || exp < 1) {
        return;
    }

    // 第二步：创建桶
    // 关键点：创建10个桶，对应0-9的数字
    const buckets: number[][] = [];
    for (let i = 0; i < 10; i++) {
        buckets[i] = [];
    }

    // 第三步：分配到桶中
    // 关键点：根据当前位数将元素分配到对应桶中
    for (let i = left; i <= right; i++) {
        const digit = getDigit(arr[i], exp);
        buckets[digit].push(arr[i]);
    }

    // 第四步：重新排序并递归处理每个桶
    // 关键点：将桶中元素复制回原数组，并递归处理子数组
    let index = left;
    for (let i = 0; i < 10; i++) {
        if (buckets[i].length > 0) {
            // 步骤4.1：复制桶中元素回原数组
            // 关键点：按桶的顺序复制元素，保持稳定性
            for (let j = 0; j < buckets[i].length; j++) {
                arr[index++] = buckets[i][j];
            }

            // 步骤4.2：递归处理下一个位数
            // 关键点：递归处理当前桶的子数组
            msdSort(arr, left, index - 1, Math.floor(exp / 10));
            left = index;
        }
    }
}

/**
 * MSD基数排序版本
 * 
 * ## 算法特点
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 使用递归处理子数组
 * - 桶排序实现，动态分配内存
 * - 适合处理字符串或变长数据
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k) - 需要桶和计数数组
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
function radixSort6(arr: number[]): number[] {
    console.log('radixSort6 MSD:');

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if (arr.length === 0) {
        return arr;
    }

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    const max = Math.max(...arr);

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    let exp = 1;
    while (Math.floor(max / exp) > 0) {
        exp *= 10;
    }

    // 第四步：调用MSD递归排序
    // 关键点：从最高位开始递归排序
    msdSort(arr, 0, arr.length - 1, Math.floor(exp / 10));

    // 第五步：输出排序结果
    printArray(arr, '排序后数组');
    return arr;
}

/**
 * 迭代MSD基数排序版本
 * 
 * ## 算法特点
 * - 使用栈模拟递归，避免递归深度过大
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 桶排序实现，动态分配内存
 * - 适合处理大数据集
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k + s) - s为栈空间
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
function radixSort3(arr: number[]): number[] {
    console.log('radixSort3 iterative MSD:');

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if (arr.length === 0) {
        return arr;
    }

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    const max = Math.max(...arr);

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    let exp = 1;
    while (Math.floor(max / exp) > 0) {
        exp *= 10;
    }

    // 第四步：使用栈模拟递归
    // 关键点：创建栈数组，初始化栈顶指针
    const stack: Array<{left: number, right: number, exp: number}> = [{left: 0, right: arr.length - 1, exp: Math.floor(exp / 10)}];

    // 第五步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while (stack.length > 0) {
        // 步骤5.1：从栈中取出待处理的范围
        // 关键点：后进先出，取出栈顶元素
        const {left: stackLeft, right, exp: currentExp} = stack.pop()!;

        // 步骤5.2：递归终止条件检查
        // 关键点：范围无效或位数不足时跳过
        if (stackLeft >= right || currentExp < 1) {
            continue;
        }

        // 步骤5.3：创建桶
        // 关键点：创建10个桶，对应0-9的数字
        const buckets: number[][] = [];
        for (let i = 0; i < 10; i++) {
            buckets[i] = [];
        }

        // 步骤5.4：分配到桶中
        // 关键点：根据当前位数将元素分配到对应桶中
        for (let i = stackLeft; i <= right; i++) {
            const digit = getDigit(arr[i], currentExp);
            buckets[digit].push(arr[i]);
        }

        // 步骤5.5：重新排序并将子问题入栈
        // 关键点：将桶中元素复制回原数组，并将子问题入栈
        let index = stackLeft;
        let nextLeft = stackLeft;
        for (let i = 0; i < 10; i++) {
            if (buckets[i].length > 0) {
                // 步骤5.5.1：复制桶中元素回原数组
                // 关键点：按桶的顺序复制元素，保持稳定性
                for (let j = 0; j < buckets[i].length; j++) {
                    arr[index++] = buckets[i][j];
                }

                // 步骤5.5.2：将子问题入栈
                // 关键点：将子数组范围和下一位数入栈，逆序处理保持正确顺序
                stack.push({left: nextLeft, right: index - 1, exp: Math.floor(currentExp / 10)});
                nextLeft = index;
            }
        }
    }

    // 第六步：输出排序结果
    printArray(arr, '排序后数组');
    return arr;
}

/**
 * 桶优化基数排序版本
 * 
 * ## 算法特点
 * - 使用动态桶大小，优化内存使用
 * - 适合处理稀疏数据
 * - 减少不必要的内存分配
 * - 提高处理效率
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为实际使用的基数范围
 * - 空间复杂度：O(n + k') - k'为实际使用的基数范围（≤k）
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
function radixSort4(arr: number[]): number[] {
    console.log('radixSort4 bucket optimized:');

    // 第一步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定处理位数
    const max = Math.max(...arr);

    // 第二步：对每个位数进行计数排序
    // 关键点：从个位开始，逐位处理，直到最高位
    for (let exp = 1; Math.floor(max / exp) > 0; exp *= 10) {
        // 步骤2.1：分配输出数组
        // 关键点：为当前位数的排序结果分配内存
        const n = arr.length;
        const output = new Array(n);

        // 步骤2.2：动态确定桶范围
        // 关键点：统计当前位数的最小和最大值，减少桶数量
        let minDigit = 9, maxDigit = 0;
        for (let i = 0; i < n; i++) {
            const digit = getDigit(arr[i], exp);
            minDigit = Math.min(minDigit, digit);
            maxDigit = Math.max(maxDigit, digit);
        }

        // 步骤2.3：创建动态大小的计数数组
        // 关键点：只创建实际需要的桶大小，优化内存使用
        const bucketSize = maxDigit - minDigit + 1;
        const count: number[] = [];
        for (let i = 0; i < bucketSize; i++) {
            count[i] = 0;
        }

        // 步骤2.4：统计每个数字的出现次数
        // 关键点：使用偏移量处理，支持任意范围的数字
        for (let i = 0; i < n; i++) {
            const digit = getDigit(arr[i], exp);
            count[digit - minDigit]++;
        }

        // 步骤2.5：计算累计计数
        // 关键点：当前位置加上左侧位置，形成累积计数
        for (let i = 1; i < bucketSize; i++) {
            count[i] += count[i - 1];
        }

        // 步骤2.6：构建输出数组
        // 关键点：从后向前遍历，保持排序的稳定性
        for (let i = n - 1; i >= 0; i--) {
            const digit = getDigit(arr[i], exp);
            output[count[digit - minDigit] - 1] = arr[i];
            count[digit - minDigit]--;
        }

        // 步骤2.7：复制回原数组
        // 关键点：将排序结果复制回原数组，准备下一位处理
        for (let i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }

    // 第三步：输出排序结果
    printArray(arr, '排序后数组');
    return arr;
}

/**
 * 递归基数排序辅助函数
 * 
 * ## 算法特点
 * - 递归处理每一位的计数排序
 * - 从最低位开始递归到最高位
 * - 基于计数排序实现
 * - 使用计数排序作为基础
 * 
 * @param arr - 待排序的数字数组
 * @param exponent - 当前处理的位数基数
 * @param minValue - 数组最小值，用于负数处理
 * @param maxValue - 数组最大值，用于确定递归终止条件
 */
function recursiveRadixSort(arr: number[], exponent: number, minValue: number, maxValue: number): void {
    // 第一步：递归终止条件检查
    // 关键点：当基数超过最大值时停止递归
    if (Math.floor((maxValue - minValue) / exponent) === 0) {
        return;
    }

    // 第二步：初始化计数排序变量
    // 关键点：为当前位数的计数排序准备变量
    const range = 10;
    const countList: number[] = [];
    for (let i = 0; i < range; i++) {
        countList[i] = 0;
    }
    const sortedList = new Array(arr.length);

    // 第三步：初始化计数数组
    // 关键点：将计数数组清零
    for (let i = 0; i < range; i++) {
        countList[i] = 0;
    }

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - minValue来处理负数，确保索引为正数
    for (let i = 0; i < arr.length; i++) {
        const item = arr[i] - minValue;
        const idx = Math.floor((item / exponent) % range);
        countList[idx]++;
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for (let i = 1; i < range; i++) {
        countList[i] += countList[i - 1];
    }

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for (let i = arr.length - 1; i >= 0; i--) {
        const item = arr[i] - minValue;
        const idx = Math.floor((item / exponent) % range);
        sortedList[countList[idx] - 1] = arr[i];
        countList[idx]--;
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for (let i = 0; i < arr.length; i++) {
        arr[i] = sortedList[i];
    }

    // 第八步：递归处理下一位
    // 关键点：递归调用处理更高位数
    recursiveRadixSort(arr, exponent * 10, minValue, maxValue);
}

/**
 * 递归基数排序版本
 * 
 * ## 算法特点
 * - 使用递归处理每一位的排序
 * - 基于计数排序的LSD实现
 * - 支持负数处理
 * - 递归深度由数字位数决定
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * - 空间复杂度：O(n + k + d) - 需要额外空间和递归栈
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
function radixSort5(arr: number[]): number[] {
    // 第一步：输出测试信息
    // 关键点：标识当前测试的算法类型
    console.log('radixSort5 递归基数排序:');

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    const maxValue = Math.max(...arr);
    const minValue = Math.min(...arr);

    // 第三步：调用递归基数排序
    // 关键点：从最低位（个位）开始递归排序
    recursiveRadixSort(arr, 1, minValue, maxValue);

    // 第四步：输出排序结果
    // 关键点：显示排序后的数组，验证算法正确性
    printArray(arr, '排序后数组');
    return arr;
}

// ==================== 算法测试和性能对比 ====================

// 测试1：radixSort1 - 计数排序基数排序版本（支持负数）
performanceTest(radixSort1, testData, 'radixSort1 - 计数排序基数排序版本');

// 测试2：radixSort2 - 内联计数排序基数排序版本（支持负数）
performanceTest(radixSort2, testData, 'radixSort2 - 内联计数排序基数排序版本');

// 测试3：radixSort3 - 递归基数排序版本（支持负数）
performanceTest(radixSort3, testData, 'radixSort3 - 递归基数排序版本');

// 测试4：radixSort4 - MSD基数排序版本
performanceTest(radixSort4, testData, 'radixSort4 - MSD基数排序版本');

// 测试5：radixSort5 - 迭代MSD基数排序版本
performanceTest(radixSort5, testData, 'radixSort5 - 迭代MSD基数排序版本');

// 测试6：radixSort6 - 桶优化基数排序版本
performanceTest(radixSort6, testData, 'radixSort6 - 桶优化基数排序版本');

// 测试7：负数数据处理
console.log('\n=== 负数测试 ===');
performanceTest(radixSort5, negativeTestData, 'radixSort3 - 递归基数排序版本（负数测试）');

console.log('=== 算法对比总结 ===');
console.log('1. radixSort1：计数排序基数排序版本，支持负数');
console.log('2. radixSort2：内联计数排序基数排序版本，支持负数');
console.log('3. radixSort3：递归基数排序版本，递归处理每一位');
console.log('4. radixSort4：MSD基数排序版本，高位优先递归处理');
console.log('5. radixSort5：迭代MSD基数排序版本，避免递归性能稳定');
console.log('6. radixSort6：桶优化基数排序版本，动态桶大小内存优化');

/*
打印结果
jarry@Mac radixsort % node-ts RadixSort.ts
zsh: command not found: node-ts
jarry@Mac radixsort % ts-node RadixSort.ts
radixSort1 - 计数排序基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort1 countingSort countList:[2, 4, 4, 5, 5, 5, 7, 8, 8, 10]
radixSort1 -> sortedList:[4, 323454, 15, 1235, 7, 10, 200, 87431, 33, 43]
radixSort1 countingSort countList:[3, 4, 6, 8, 8, 9, 9, 9, 9, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 87431, 33, 1235, 43, 323454, 200]
radixSort1 countingSort countList:[6, 7, 8, 8, 10, 10, 10, 10, 10, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort1 countingSort countList:[7, 8, 8, 9, 9, 9, 9, 10, 10, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radixSort1 countingSort countList:[8, 8, 9, 9, 9, 9, 9, 9, 10, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radixSort1 countingSort countList:[9, 9, 9, 10, 10, 10, 10, 10, 10, 10]
radixSort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort1 - 计数排序基数排序版本: 0.176ms
radixSort1 - 计数排序基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort2 - 内联计数排序基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort2 -> countList:[2, 4, 4, 5, 5, 5, 7, 8, 8, 10]
radixSort2 -> sortedList:[4, 323454, 15, 1235, 7, 10, 200, 87431, 33, 43]
radixSort2 -> countList:[3, 4, 6, 8, 8, 9, 9, 9, 9, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 87431, 33, 1235, 43, 323454, 200]
radixSort2 -> countList:[6, 7, 8, 8, 10, 10, 10, 10, 10, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort2 -> countList:[7, 8, 8, 9, 9, 9, 9, 10, 10, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radixSort2 -> countList:[8, 8, 9, 9, 9, 9, 9, 9, 10, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radixSort2 -> countList:[9, 9, 9, 10, 10, 10, 10, 10, 10, 10]
radixSort2 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort2 - 内联计数排序基数排序版本: 0.082ms
radixSort2 - 内联计数排序基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort3 - 递归基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort3 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort3 - 递归基数排序版本: 0.084ms
radixSort3 - 递归基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort4 - MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort4 - MSD基数排序版本: 0.069ms
radixSort4 - MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort5 - 迭代MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort5 递归基数排序:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort5 - 迭代MSD基数排序版本: 0.061ms
radixSort5 - 迭代MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort6 - 桶优化基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort6 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort6 - 桶优化基数排序版本: 0.053ms
radixSort6 - 桶优化基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]


=== 负数测试 ===
radixSort3 - 递归基数排序版本（负数测试）: [170, 45, 75, -90, -802, 24, 2, 66, -5, 0]
radixSort5 递归基数排序:
排序后数组: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]
radixSort3 - 递归基数排序版本（负数测试）: 0.015ms
radixSort3 - 递归基数排序版本（负数测试）排序结果: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]

=== 算法对比总结 ===
1. radixSort1：计数排序基数排序版本，支持负数
2. radixSort2：内联计数排序基数排序版本，支持负数
3. radixSort3：递归基数排序版本，递归处理每一位
4. radixSort4：MSD基数排序版本，高位优先递归处理
5. radixSort5：迭代MSD基数排序版本，避免递归性能稳定
6. radixSort6：桶优化基数排序版本，动态桶大小内存优化
*/
