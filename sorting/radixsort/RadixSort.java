
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供6种不同的实现方式，适合不同场景和性能需求
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

import java.util.Arrays;

public class RadixSort {

    // ==================== 测试数据 ====================

    // 测试数据：包含大数字的典型数组
    private static final int[] testData = { 33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431 };

    // 负数测试数据
    private static final int[] negativeTestData = { 170, 45, 75, -90, -802, 24, 2, 66, -5, 0 };

    /**
     * 打印数组内容的辅助函数
     * 
     * @param arr   - 要打印的数组
     * @param label - 数组的标签说明
     */
    private static void printArray(int[] arr, String label) {
        System.out.println(label + ": " + Arrays.toString(arr));
    }

    /**
     * 性能测试辅助函数
     * 
     * @param sortFunc - 排序函数接口
     * @param arr      - 测试数组
     * @param name     - 测试名称
     */
    private static void performanceTest(SortFunction sortFunc, int[] arr, String name) {
        // 创建数组副本，避免修改原数组
        int[] testArr = Arrays.copyOf(arr, arr.length);
        printArray(testArr, name);

        // 开始计时
        long startTime = System.nanoTime();
        sortFunc.sort(testArr);
        long endTime = System.nanoTime();

        System.out.println(name + ": " + String.format("%.3f", (endTime - startTime) / 1_000_000.0) + "ms");
        printArray(testArr, name + "排序结果");
        System.out.println(); // 空行分隔
    }

    /**
     * 获取数字的指定位数
     * 
     * @param num - 数字
     * @param exp - 指数（10的幂）
     * @return int - 指定位数的值
     */
    private static int getDigit(int num, int exp) {
        return Math.abs(num) / exp % 10;
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
     * @param arr      - 待排序的数字数组
     * @param exponent - 当前处理的位数基数（1, 10, 100, ...）
     * @return int[] - 排序后的数组
     */
    private static int[] countingSort(int[] arr, int exponent) {
        // 第一步：初始化变量和数组，按10个桶大小，0-9的个位数
        int range = 10;
        int[] countList = new int[range];
        int[] sortedList = new int[arr.length];

        // 第二步：找出最小值
        // 关键点：处理负数情况，需要找到最小值进行偏移
        int min = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }

        // 第三步：初始化计数数组
        // 关键点：将计数数组清零
        for (int i = 0; i < range; i++) {
            countList[i] = 0;
        }

        // 第四步：根据数字所在位置进行计数
        // 关键点：使用arr[i] - min来处理负数，确保索引为正数
        for (int i = 0; i < arr.length; i++) {
            int item = arr[i] - min;
            // 根据exponent获得当前位置的数字是几，存入对应计数数组
            int idx = (item / exponent) % range;
            countList[idx] += 1;
        }

        // 第五步：构建计数排序
        // 关键点：后面的位数为前面的累加之和，形成累积计数
        for (int i = 1; i < range; i++) {
            countList[i] += countList[i - 1];
        }
        System.out.println("radixSort1 countingSort countList:" + Arrays.toString(countList));

        // 第六步：构建输出数组
        // 关键点：从后向前遍历，保持排序的稳定性
        for (int i = arr.length - 1; i >= 0; i--) {
            int item = arr[i] - min;
            int idx = (item / exponent) % range;
            // 根据计数位置得到顺序
            sortedList[countList[idx] - 1] = arr[i];
            countList[idx] -= 1;
        }

        // 第七步：复制到数组重排原始数组
        // 关键点：将排序结果复制回原数组
        for (int i = 0; i < arr.length; i++) {
            arr[i] = sortedList[i];
        }
        System.out.println("radixSort1 -> sortedList:" + Arrays.toString(sortedList));
        return sortedList;
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
     * @return int[] - 排序后的数组
     */
    public static int[] radixSort1(int[] arr) {
        // 第一步：递归终止条件检查
        // 关键点：空数组直接返回
        if (arr.length == 0) {
            return arr;
        }

        // 第二步：找出最大值
        // 关键点：确定排序的位数范围
        int max = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        // 第三步：根据最大值，逐个按进位(基数)来应用排序
        // 关键点：exponent即数位基数，按个十百千递增
        for (int exponent = 1; (max / exponent) > 0; exponent *= 10) {
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
     * @return int[] - 排序后的数组
     */
    public static int[] radixSort2(int[] arr) {
        // 第一步：初始化变量
        // 关键点：获取数组长度，设置基数范围
        int arrLen = arr.length;
        int range = 10;
        int[] sortedList = new int[arrLen];

        // 第二步：找出最大值
        // 关键点：遍历数组找出最大值，用于确定位数
        int max = arr[0];
        for (int i = 0; i < arrLen; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        // 第三步：找出最小值以支持负数
        // 关键点：处理负数情况，需要找到最小值进行偏移
        int min = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }

        // 第四步：根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
        // 关键点：从1开始，每10进位，逐位进行比较和排序，一直到最大减去最小数
        for (int exponent = 1; ((max - min) / exponent) > 0; exponent *= range) {
            // 步骤4.1：创建计数数组
            // 关键点：计数数组长度为10，0-9一共10个数字
            int[] countList = new int[range];

            // 步骤4.2：根据基数得到当前位数，并给计数数组对应位置加1
            // 关键点：使用arr[i] - min来处理负数，确保索引为正数
            for (int i = 0; i < arrLen; i++) {
                int item = arr[i] - min;
                int idx = (item / exponent) % range;
                countList[idx] += 1;
            }

            // 步骤4.3：计数排序构建
            // 关键点：自前往后，逐个将上一项的值存入当前项
            for (int i = 1; i < range; i++) {
                countList[i] += countList[i - 1];
            }

            System.out.println("radixSort2 -> countList:" + Arrays.toString(countList));

            // 步骤4.4：根据计数数组按顺序取出排序内容
            // 关键点：从后向前遍历，保持排序的稳定性
            for (int i = arrLen - 1; i >= 0; i--) {
                int item = arr[i] - min;
                int idx = (item / exponent) % range;
                sortedList[countList[idx] - 1] = arr[i];
                countList[idx] -= 1;
            }

            System.out.println("radixSort2 -> sortedList:" + Arrays.toString(sortedList));

            // 步骤4.5：将新顺序赋值给原数组
            // 关键点：将排序结果复制回原数组，准备下一位处理
            for (int i = 0; i < arr.length; i++) {
                arr[i] = sortedList[i];
            }
        }

        return sortedList;
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
     * @return int[] - 排序后的数组
     */
    public static int[] radixSort3(int[] arr) {
        System.out.println("radixSort3 iterative MSD:");

        // 第一步：递归终止条件检查
        // 关键点：空数组直接返回
        if (arr.length == 0) {
            return arr;
        }

        // 第二步：找到最大值以确定位数
        // 关键点：遍历数组找出最大值，用于确定最高位数
        int max = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        // 第三步：计算最高位对应的基数
        // 关键点：exp从1开始，不断乘以10直到超过最大值
        int exp = 1;
        while (max / exp > 0) {
            exp *= 10;
        }

        // 第四步：使用栈模拟递归
        // 关键点：创建栈数组，初始化栈顶指针
        java.util.Stack<int[]> stack = new java.util.Stack<>();
        stack.push(new int[] { 0, arr.length - 1, exp / 10 });

        // 第五步：循环处理栈中的范围
        // 关键点：栈不为空时继续处理，模拟递归调用过程
        while (!stack.isEmpty()) {
            // 步骤5.1：从栈中取出待处理的范围
            // 关键点：后进先出，取出栈顶元素
            int[] params = stack.pop();
            int left = params[0];
            int right = params[1];
            int currentExp = params[2];

            // 步骤5.2：递归终止条件检查
            // 关键点：范围无效或位数不足时跳过
            if (left >= right || currentExp < 1) {
                continue;
            }

            // 步骤5.3：创建桶
            // 关键点：创建10个桶，对应0-9的数字
            @SuppressWarnings("unchecked")
            java.util.ArrayList<Integer>[] buckets = new java.util.ArrayList[10];
            for (int i = 0; i < 10; i++) {
                buckets[i] = new java.util.ArrayList<>();
            }

            // 步骤5.4：分配到桶中
            // 关键点：根据当前位数将元素分配到对应桶中
            for (int i = left; i <= right; i++) {
                int digit = getDigit(arr[i], currentExp);
                buckets[digit].add(arr[i]);
            }

            // 步骤5.5：重新排序并将子问题入栈
            // 关键点：将桶中元素复制回原数组，并将子问题入栈
            int index = left;
            int nextLeft = left;
            for (int i = 0; i < 10; i++) {
                if (!buckets[i].isEmpty()) {
                    // 步骤5.5.1：复制桶中元素回原数组
                    // 关键点：按桶的顺序复制元素，保持稳定性
                    for (int j = 0; j < buckets[i].size(); j++) {
                        arr[index++] = buckets[i].get(j);
                    }

                    // 步骤5.5.2：将子问题入栈
                    // 关键点：将子数组范围和下一位数入栈，逆序处理保持正确顺序
                    stack.push(new int[] { nextLeft, index - 1, currentExp / 10 });
                    nextLeft = index;
                }
            }
        }

        // 第六步：输出排序结果
        printArray(arr, "排序后数组");
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
     * @return int[] - 排序后的数组
     */
    public static int[] radixSort4(int[] arr) {
        System.out.println("radixSort4 bucket optimized:");

        // 第一步：找到最大值以确定位数
        // 关键点：遍历数组找出最大值，用于确定处理位数
        int max = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        // 第二步：对每个位数进行计数排序
        // 关键点：从个位开始，逐位处理，直到最高位
        for (int exp = 1; max / exp > 0; exp *= 10) {
            // 步骤2.1：分配输出数组
            // 关键点：为当前位数的排序结果分配内存
            int n = arr.length;
            int[] output = new int[n];

            // 步骤2.2：动态确定桶范围
            // 关键点：统计当前位数的最小和最大值，减少桶数量
            int minDigit = 9, maxDigit = 0;
            for (int i = 0; i < n; i++) {
                int digit = getDigit(arr[i], exp);
                minDigit = Math.min(minDigit, digit);
                maxDigit = Math.max(maxDigit, digit);
            }

            // 步骤2.3：创建动态大小的计数数组
            // 关键点：只创建实际需要的桶大小，优化内存使用
            int bucketSize = maxDigit - minDigit + 1;
            int[] count = new int[bucketSize];

            // 步骤2.4：统计每个数字的出现次数
            // 关键点：使用偏移量处理，支持任意范围的数字
            for (int i = 0; i < n; i++) {
                int digit = getDigit(arr[i], exp);
                count[digit - minDigit]++;
            }

            // 步骤2.5：计算累计计数
            // 关键点：当前位置加上左侧位置，形成累积计数
            for (int i = 1; i < bucketSize; i++) {
                count[i] += count[i - 1];
            }

            // 步骤2.6：构建输出数组
            // 关键点：从后向前遍历，保持排序的稳定性
            for (int i = n - 1; i >= 0; i--) {
                int digit = getDigit(arr[i], exp);
                output[count[digit - minDigit] - 1] = arr[i];
                count[digit - minDigit]--;
            }

            // 步骤2.7：复制回原数组
            // 关键点：将排序结果复制回原数组，准备下一位处理
            System.arraycopy(output, 0, arr, 0, n);
        }

        // 第三步：输出排序结果
        printArray(arr, "排序后数组");
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
     * @param arr      - 待排序的数字数组
     * @param exponent - 当前处理的位数基数
     * @param minValue - 数组最小值，用于负数处理
     * @param maxValue - 数组最大值，用于确定递归终止条件
     * @return void - 无返回值，直接修改原数组
     */
    private static void recursiveRadixSort(int[] arr, int exponent, int minValue, int maxValue) {
        // 第一步：递归终止条件检查
        // 关键点：当基数超过最大值时停止递归
        if ((maxValue - minValue) / exponent == 0) {
            return;
        }

        // 第二步：初始化计数排序变量
        // 关键点：为当前位数的计数排序准备变量
        int range = 10;
        int[] countList = new int[range];
        int[] sortedList = new int[arr.length];

        // 第三步：初始化计数数组
        // 关键点：将计数数组清零
        for (int i = 0; i < range; i++) {
            countList[i] = 0;
        }

        // 第四步：根据数字所在位置进行计数
        // 关键点：使用arr[i] - minValue来处理负数，确保索引为正数
        for (int i = 0; i < arr.length; i++) {
            int item = arr[i] - minValue;
            int idx = (item / exponent) % range;
            countList[idx] += 1;
        }

        // 第五步：构建计数排序
        // 关键点：后面的位数为前面的累加之和，形成累积计数
        for (int i = 1; i < range; i++) {
            countList[i] += countList[i - 1];
        }

        // 第六步：构建输出数组
        // 关键点：从后向前遍历，保持排序的稳定性
        for (int i = arr.length - 1; i >= 0; i--) {
            int item = arr[i] - minValue;
            int idx = (item / exponent) % range;
            sortedList[countList[idx] - 1] = arr[i];
            countList[idx] -= 1;
        }

        // 第七步：复制到数组重排原始数组
        // 关键点：将排序结果复制回原数组
        for (int i = 0; i < arr.length; i++) {
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
     * @return int[] - 排序后的数组
     */
    public static int[] radixSort5(int[] arr) {
        // 第一步：输出测试信息
        // 关键点：标识当前测试的算法类型
        System.out.println("radixSort5 递归基数排序:");

        // 第二步：找出最大值和最小值
        // 关键点：确定排序的位数范围和处理负数
        int maxValue = arr[0];
        int minValue = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > maxValue) {
                maxValue = arr[i];
            }
            if (arr[i] < minValue) {
                minValue = arr[i];
            }
        }

        // 第三步：调用递归基数排序
        // 关键点：从最低位（个位）开始递归排序
        recursiveRadixSort(arr, 1, minValue, maxValue);

        // 第四步：输出排序结果
        // 关键点：显示排序后的数组，验证算法正确性
        printArray(arr, "排序后数组");
        return arr;
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
     * @param arr   - 待排序的数字数组
     * @param left  - 左边界索引
     * @param right - 右边界索引
     * @param exp   - 当前处理的位数基数
     * @return void - 无返回值，直接修改原数组
     */
    private static void msdSort(int[] arr, int left, int right, int exp) {
        // 第一步：递归终止条件检查
        // 关键点：范围无效或位数不足时返回
        if (left >= right || exp < 1) {
            return;
        }

        // 第二步：创建桶
        // 关键点：创建10个桶，对应0-9的数字
        @SuppressWarnings("unchecked")
        java.util.ArrayList<Integer>[] buckets = new java.util.ArrayList[10];
        for (int i = 0; i < 10; i++) {
            buckets[i] = new java.util.ArrayList<>();
        }

        // 第三步：分配到桶中
        // 关键点：根据当前位数将元素分配到对应桶中
        for (int i = left; i <= right; i++) {
            int digit = getDigit(arr[i], exp);
            buckets[digit].add(arr[i]);
        }

        // 第四步：重新排序并递归处理每个桶
        // 关键点：将桶中元素复制回原数组，并递归处理子数组
        int index = left;
        for (int i = 0; i < 10; i++) {
            if (!buckets[i].isEmpty()) {
                // 步骤4.1：复制桶中元素回原数组
                // 关键点：按桶的顺序复制元素，保持稳定性
                for (int j = 0; j < buckets[i].size(); j++) {
                    arr[index++] = buckets[i].get(j);
                }

                // 步骤4.2：递归处理下一个位数
                // 关键点：递归处理当前桶的子数组
                msdSort(arr, left, index - 1, exp / 10);
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
     * @return int[] - 排序后的数组
     */
    public static int[] radixSort6(int[] arr) {
        System.out.println("radixSort6 MSD:");

        // 第一步：递归终止条件检查
        // 关键点：空数组直接返回
        if (arr.length == 0) {
            return arr;
        }

        // 第二步：找到最大值以确定位数
        // 关键点：遍历数组找出最大值，用于确定最高位数
        int max = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        // 第三步：计算最高位对应的基数
        // 关键点：exp从1开始，不断乘以10直到超过最大值
        int exp = 1;
        while (max / exp > 0) {
            exp *= 10;
        }

        // 第四步：调用MSD递归排序
        // 关键点：从最高位开始递归排序
        msdSort(arr, 0, arr.length - 1, exp / 10);

        // 第五步：输出排序结果
        printArray(arr, "排序后数组");
        return arr;
    }

    // ==================== 算法测试和性能对比 ====================

    @FunctionalInterface
    private interface SortFunction {
        void sort(int[] arr);
    }

    public static void main(String[] args) {
        // 测试1：radixSort1 - 计数排序基数排序版本（支持负数）
        performanceTest(RadixSort::radixSort1, testData, "radixSort1 - 计数排序基数排序版本");

        // 测试2：radixSort2 - 内联计数排序基数排序版本（支持负数）
        performanceTest(RadixSort::radixSort2, testData, "radixSort2 - 内联计数排序基数排序版本");

        // 测试3：radixSort3 - 递归基数排序版本（支持负数）
        performanceTest(RadixSort::radixSort3, testData, "radixSort3 - 递归基数排序版本");

        // 测试4：radixSort4 - MSD基数排序版本
        performanceTest(RadixSort::radixSort4, testData, "radixSort4 - MSD基数排序版本");

        // 测试5：radixSort5 - 迭代MSD基数排序版本
        performanceTest(RadixSort::radixSort5, testData, "radixSort5 - 迭代MSD基数排序版本");

        // 测试6：radixSort6 - 桶优化基数排序版本
        performanceTest(RadixSort::radixSort6, testData, "radixSort6 - 桶优化基数排序版本");

        // 测试7：负数数据处理
        System.out.println("\n=== 负数测试 ===");
        performanceTest(RadixSort::radixSort5, negativeTestData, "radixSort3 - 递归基数排序版本（负数测试）");

        System.out.println("=== 算法对比总结 ===");
        System.out.println("1. radixSort1：计数排序基数排序版本，支持负数");
        System.out.println("2. radixSort2：内联计数排序基数排序版本，支持负数");
        System.out.println("3. radixSort3：递归基数排序版本，递归处理每一位");
        System.out.println("4. radixSort4：MSD基数排序版本，高位优先递归处理");
        System.out.println("5. radixSort5：迭代MSD基数排序版本，避免递归性能稳定");
        System.out.println("6. radixSort6：桶优化基数排序版本，动态桶大小内存优化");
    }
}

/*
 * 打印结果
jarry@Mac radixsort % java RadixSort.java 
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
radixSort1 - 计数排序基数排序版本: 0.203ms
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
radixSort2 - 内联计数排序基数排序版本: 0.130ms
radixSort2 - 内联计数排序基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort3 - 递归基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort3 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort3 - 递归基数排序版本: 0.325ms
radixSort3 - 递归基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort4 - MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort4 - MSD基数排序版本: 0.039ms
radixSort4 - MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort5 - 迭代MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort5 递归基数排序:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort5 - 迭代MSD基数排序版本: 0.033ms
radixSort5 - 迭代MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort6 - 桶优化基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort6 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort6 - 桶优化基数排序版本: 0.033ms
radixSort6 - 桶优化基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]


=== 负数测试 ===
radixSort3 - 递归基数排序版本（负数测试）: [170, 45, 75, -90, -802, 24, 2, 66, -5, 0]
radixSort5 递归基数排序:
排序后数组: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]
radixSort3 - 递归基数排序版本（负数测试）: 0.123ms
radixSort3 - 递归基数排序版本（负数测试）排序结果: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]

=== 算法对比总结 ===
1. radixSort1：计数排序基数排序版本，支持负数
2. radixSort2：内联计数排序基数排序版本，支持负数
3. radixSort3：递归基数排序版本，递归处理每一位
4. radixSort4：MSD基数排序版本，高位优先递归处理
5. radixSort5：迭代MSD基数排序版本，避免递归性能稳定
6. radixSort6：桶优化基数排序版本，动态桶大小内存优化
 */
