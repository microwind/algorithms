
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序LSD版本实现
 * 基于计数排序的LSD（最低位优先）实现
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
 * ## 负数处理
 * - 使用最小值偏移处理负数
 * - 通过arr[i] - min确保索引为正数
 * - 支持包含负数的整数数组排序
 */

import java.util.*;

public class RadixSortLSD {
    
    /**
     * 基数排序，由低位到高位，基于计数排序，非递归版
     * 
     * ## 实现步骤
     * 1. 找出数组中的最大值和最小值
     * 2. 计算最大位数，用于确定排序轮数
     * 3. 对每一位进行计数排序
     * 4. 从个位开始，逐位处理到最高位
     * 
     * @param arr - 待排序的数字数组
     * @return int[] - 排序后的数组
     */
    public static int[] radixSort(int[] arr) {
        // 第一步：初始化变量
        // 关键点：获取数组长度，用于后续循环
        int len = arr.length;
        
        // 第二步：找出数组中的最大值
        // 关键点：用于确定排序的最高位数
        int max = arr[0];
        for (int i = 0; i < len; i++) {
            if (max < arr[i]) {
                max = arr[i];
            }
        }

        // 第三步：找出数组中的最小值
        // 关键点：用于处理负数，计算偏移量
        int min = arr[0];
        for (int i = 0; i < len; i++) {
            if (min > arr[i]) {
                min = arr[i];
            }
        }

        // 第四步：计算最大数字范围
        // 关键点：maxNumber设为最大减去最小，以便支持负数和减少数位
        int maxNumber = max - min;

        // 第五步：计算数组里最大项数字的位数
        // 关键点：确定需要进行多少轮排序
        int maxLength = 0;
        while (maxNumber > 0) {
            maxLength++;
            maxNumber /= 10;
        }
        // 备选方案：通过log10求取
        // int maxLength = (int) (Math.log10(max - min) + 1);

        // 第六步：初始化排序所需的数据结构
        // 关键点：位数基准为10，计数数组长度也是10，分别放数字0-9
        int range = 10;
        int[] countList = new int[range];
        int[] buckets = new int[len];

        // 第七步：逐位计算和排序
        // 关键点：从低位到高位，从个位到高位进行排序
        for (int j = 1; j <= maxLength; j++) {

            // 步骤7.1：计数数组清零
            // 关键点：每轮排序前需要重置计数数组
            for (int i = 0; i < range; i++) {
                countList[i] = 0;
            }

            // 步骤7.2：根据基数得到当前位数，并给计数数组对应位置加1
            // 关键点：使用arr[i] - min处理负数，确保索引为正数
            for (int i = 0; i < len; i++) {
                int item = arr[i] - min;
                // 逐位获取数组项的值，先除以数位得到当前数位上的值，再除以10取余
                // int idx = item / ((int)Math.pow(range, j - 1)) % range;
                int idx = getDigitByPosition(item, j);
                countList[idx]++;
            }

            System.out.println("countList counted:" + Arrays.toString(countList));

            // 步骤7.3：计数排序构建
            // 关键点：自前往后，逐个将上一项的值存入当前项，形成累积计数
            for (int i = 1; i < range; i++) {
                countList[i] += countList[i - 1];
            }

            System.out.println("countList sorted:" + Arrays.toString(countList));

            // 步骤7.4：根据计数数组按顺序取出排序内容
            // 关键点：从后向前遍历，保持排序的稳定性
            for (int i = len - 1; i >= 0; i--) {
                int item = arr[i] - min;
                int idx = getDigitByPosition(item, j);
                buckets[countList[idx] - 1] = arr[i];
                countList[idx]--;
            }

            // 步骤7.5：将新顺序赋值给原数组
            // 关键点：将排序结果复制回原数组，准备下一轮排序
            int i = 0;
            while (i < len) {
                arr[i] = buckets[i];
                i++;
            }
        }
        
        // 第八步：输出最终排序结果
        // 关键点：显示排序后的数组，验证算法正确性
        System.out.println("arr sorted:" + Arrays.toString(arr));
        return arr;
    }

    /**
     * 获取数字倒数第n位的值
     * 
     * ## 功能说明
     * - 当num=1234, position=1时，返回4（个位）
     * - 当num=1234, position=2时，返回3（十位）
     * - 当num=1234, position=3时，返回2（百位）
     * 
     * ## 实现原理
     * - 使用除法和取余运算获取指定位数的数字
     * - 通过Math.pow(10, position-1)计算对应的权值
     * - 先除以权值，再对10取余得到指定位数
     * 
     * @param num      - 要处理的数字（非负数）
     * @param position - 位数位置（1=个位，2=十位，...）
     * @return int     - 指定位数的值（0-9）
     */
    private static int getDigitByPosition(int num, int position) {
        return (num / ((int) Math.pow(10, position - 1))) % 10;
    }

    /**
     * 测试函数
     * 
     * ## 测试内容
     * - 包含负数的整数数组排序
     * - 性能测试和时间统计
     * - 排序结果验证
     */
    public static void main(String args[]) {
        // 测试数据：包含正数和负数的混合数组
        int arr1[] = { 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 };
        // 备选测试数据：仅包含正数的数组
        // int arr1[] = { 33, 7, 10, 1235, 200, 87431 };
        
        System.out.println("sort1 start:" + Arrays.toString(arr1));
        
        // 性能测试：记录开始时间
        long startTime = System.currentTimeMillis();
        
        // 执行排序
        arr1 = RadixSortLSD.radixSort(arr1);
        
        // 计算并输出执行时间
        System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
        System.out.println("sort1 sorted:" + Arrays.toString(arr1));
    }
}

/*打印结果
jarry@Mac radixsort % java RadixSortLSD.java 
sort1 start:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
countList counted:[2, 1, 0, 0, 2, 1, 0, 2, 0, 2]
countList sorted:[2, 3, 3, 3, 5, 6, 6, 8, 8, 10]
countList counted:[1, 0, 0, 0, 0, 2, 3, 0, 3, 1]
countList sorted:[1, 1, 1, 1, 1, 3, 6, 6, 9, 10]
countList counted:[1, 0, 0, 0, 6, 0, 2, 0, 1, 0]
countList sorted:[1, 1, 1, 1, 7, 7, 9, 9, 10, 10]
countList counted:[2, 0, 0, 7, 1, 0, 0, 0, 0, 0]
countList sorted:[2, 2, 2, 9, 10, 10, 10, 10, 10, 10]
countList counted:[1, 1, 8, 0, 0, 0, 0, 0, 0, 0]
countList sorted:[1, 2, 10, 10, 10, 10, 10, 10, 10, 10]
countList counted:[1, 0, 0, 8, 1, 0, 0, 0, 0, 0]
countList sorted:[1, 1, 1, 9, 10, 10, 10, 10, 10, 10]
arr sorted:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]

time:0 ms.
sort1 sorted:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 */
