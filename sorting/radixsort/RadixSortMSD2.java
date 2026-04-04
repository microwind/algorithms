
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序MSD版本实现（非递归方式）
 * 基于桶排序的MSD（最高位优先）实现，使用迭代处理
 * 
 * ## 算法特点
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 使用迭代方式处理，避免递归深度过大
 * - 桶排序实现，动态分配内存
 * - 适合处理大数据集和字符串排序
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k) - 需要桶和计数数组
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * ## 负数处理
 * - 使用最小值偏移处理负数
 * - 通过arr[i] - min确保索引为正数
 * - 支持包含负数的整数数组排序
 * 
 * ## 实现原理
 * 1. 找出数组中最大的数，确定其位数
 * 2. MSD是从高位开始，依次按照位数的值将数字放入到不同桶中
 * 3. 使用迭代方式处理每个桶，避免递归深度过大
 * 4. 如果桶里的长度超过1，则继续按桶排序
 * 5. 重复步骤2-4，直到按照最高位排序完成
 */

import java.util.*;

public class RadixSortMSD2 {
    
    /**
     * 基数排序，从高到低逐位排序，非递归方式，基于桶排序
     * 
     * ## 实现步骤
     * 1. 找出数组中的最大值和最小值
     * 2. 计算数字的位数，确定最高位的基数
     * 3. 调用迭代桶排序函数进行排序
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

        // 第四步：计算数字的位数
        // 关键点：获取数字一共有几位，减去min得到最大值，以支持负数和减少最大值
        int maxLength = (int) (Math.log10(max - min) + 1);
        
        // 第五步：输出调试信息并开始排序
        // 关键点：显示位数信息，便于调试
        System.out.println("maxLength:" + maxLength);
        
        // 第六步：调用迭代桶排序
        // 关键点：从最高位开始迭代排序
        return bucketSort(arr, len, 1, maxLength);
    }

    /**
     * 获取数字第n位的值，不足最大长度时补零
     * 
     * ## 功能说明
     * - 补齐数位，从左往右查找
     * - 当位数不足最大长度时返回0
     * - 支持不同长度的数字比较
     * 
     * ## 实现原理
     * - 计算数字的实际长度
     * - 判断查询位置是否超出数字长度
     * - 使用除法和取余运算获取指定位数
     * 
     * @param num       - 要处理的数字（非负数）
     * @param position  - 位数位置（从左到右，1=最高位）
     * @param maxLength - 数字的最大长度
     * @return int       - 指定位数的值（0-9）
     */
    private static int getDigitByPosition(int num, int position, int maxLength) {
        // 第一步：特殊情况处理
        // 关键点：数字为0时直接返回0
        if (num == 0) {
            return 0;
        }
        
        // 第二步：计算数字长度
        // 关键点：获取数字的实际位数
        int numberLength = (int) (Math.log10(num) + 1);
        
        // 第三步：位置超出检查
        // 关键点：查询的位置加上自身长度不足最大长度则返回0
        if ((position + numberLength) < maxLength) {
            return 0;
        }
        
        // 第四步：计算指定位数的值
        // 关键点：通过除法和取余获取指定位数
        int exponent = (int) Math.pow(10, numberLength - position);
        int digit = 0;
        if (exponent > 0) {
            digit = (num / exponent) % 10;
        }
        
        // 第五步：输出调试信息
        // 关键点：显示计算过程，便于调试
        System.out.println("num=" + num + " position=" + position + " numberLength=" + numberLength + " exponent="
                + exponent + " position=" + position);
        
        return digit;
    }

    /**
     * 递归桶排序实现基数排序
     * 
     * ## 实现原理
     * - 使用桶排序对指定位数进行排序
     * - 递归处理每个桶中的子数组
     * - 从最高位向最低位逐层处理
     * 
     * @param arr       - 待排序的数组
     * @param len       - 数组长度
     * @param position  - 当前处理的位置（从左到右）
     * @param maxLength - 数字的最大长度
     * @return int[]     - 排序后的数组
     */
    private static int[] bucketSort(int[] arr, int len, int position, int maxLength) {
        // 第一步：输出调试信息
        // 关键点：显示当前排序状态，便于调试
        System.out.println("origin arr:" + Arrays.toString(arr) + " position:" + position + " maxLength:" + maxLength);
        
        // 第二步：递归终止条件检查
        // 关键点：数组长度为1或位置超过最大长度时停止递归
        if (len <= 1 || position > maxLength) {
            return arr;
        }
        
        System.out.println("prepared arr:" + Arrays.toString(arr) + " position:" + position + " maxLength:" + maxLength);

        // 第三步：找出数组中的最小值
        // 关键点：用于处理负数，计算偏移量
        int min = arr[0];
        for (int i = 0; i < len; i++) {
            if (min > arr[i]) {
                min = arr[i];
            }
        }

        // 第四步：初始化桶结构
        // 关键点：位数按10递进，定义桶二维数组，长度为10，放入0-9的数字
        int range = 10;
        int[][] buckets = new int[range][len];
        int[] bucketCountList = new int[range];
        
        // 第五步：将数据分配到桶中
        // 关键点：根据数位上的值，减去最小值，分配到对应的桶里
        for (int i = 0; i < len; i++) {
            int item = arr[i] - min;
            int bucketIdx = getDigitByPosition(item, position, maxLength);
            
            // 步骤5.1：把数据按下标插入到桶里
            // 关键点：使用桶计数器记录插入位置
            int numberIdx = bucketCountList[bucketIdx];
            buckets[bucketIdx][numberIdx] = arr[i];
            bucketCountList[bucketIdx] += 1;
        }

        System.out.println("bucketCountList=" + Arrays.toString(bucketCountList) + "arr=" + Arrays.toString(arr));

        // 第六步：将每个桶的数据按顺序逐个取出，重新赋值给原数组
        // 关键点：按桶的顺序重新组合数组
        int sortedIdx = 0;

        for (int i = 0; i < range; i++) {
            int[] bucket = buckets[i];
            int bucketLen = bucketCountList[i];
            
            // 步骤6.1：如果只有一个值，则直接更新到原数组
            // 关键点：单元素桶无需递归处理
            if (bucketCountList[i] == 1) {
                arr[sortedIdx] = bucket[0];
                sortedIdx += 1;
            } else if (bucket.length > 0 && bucketLen > 0) {
                // 步骤6.2：如果是数组且记录大于1则继续递归调用，位置增加1位
                // 关键点：递归调用传参时需要传入当前子序列、子序列长度、当前分解的位数基数
                int[] sortedBucket = bucketSort(bucket, bucketLen, position + 1, maxLength);
                
                // 步骤6.3：依照已排序的子序列实际长度，把各个桶里的值按顺序赋给原数组
                // 关键点：将递归排序的结果复制回原数组
                for (int j = 0; j < bucketLen; j++) {
                    int num = sortedBucket[j];
                    System.out.println("bucket:" + Arrays.toString(bucket) + " sortedBucket:" + Arrays.toString(sortedBucket)
                            + " sortedIdx:" + sortedIdx
                            + " set arr:" + Arrays.toString(arr));
                    arr[sortedIdx] = num;
                    sortedIdx += 1;
                }
            }
        }
        
        // 第七步：输出当前轮次排序结果
        // 关键点：显示当前位置排序后的数组状态
        System.out.println("position:" + position + " sorted arr:" + Arrays.toString(arr));
        return arr;
    }

    /**
     * 测试函数
     * 
     * ## 测试内容
     * - 包含正数的整数数组排序测试
     * - 包含负数的整数数组排序测试
     * - 性能测试和时间统计
     * - 排序结果验证
     */
    public static void main(String args[]) {
        // 测试1：仅包含正数的数组
        int arr1[] = { 89, 195, 196, 275, 276, 272, 2343 };
        System.out.println("sort1 start:" + Arrays.toString(arr1));
        long startTime = System.currentTimeMillis();
        arr1 = RadixSortMSD2.radixSort(arr1);
        System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
        System.out.println("sort1 sorted:" + Arrays.toString(arr1));

        // 测试2：包含正数和负数的混合数组
        int arr2[] = { 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 };
        System.out.println("sort2 start:" + Arrays.toString(arr2));
        long startTime2 = System.currentTimeMillis();
        arr2 = RadixSortMSD2.radixSort(arr2);
        System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime2) + " ms.");
        System.out.println("sort2 sorted:" + Arrays.toString(arr2));
    }
}

/*
jarry@jarrys-MacBook-Pro radixsort % javac RadixSortMSD2.java
jarry@jarrys-MacBook-Pro radixsort % java RadixSortMSD2      
sort1 start:[89, 195, 196, 275, 276, 272, 2343]
maxLength:4
origin arr:[89, 195, 196, 275, 276, 272, 2343] position:1 maxLength:4
prepared arr:[89, 195, 196, 275, 276, 272, 2343] position:1 maxLength:4
num=106 position=1 numberLength=3 exponent=100 position=1
num=107 position=1 numberLength=3 exponent=100 position=1
num=186 position=1 numberLength=3 exponent=100 position=1
num=187 position=1 numberLength=3 exponent=100 position=1
num=183 position=1 numberLength=3 exponent=100 position=1
num=2254 position=1 numberLength=4 exponent=1000 position=1
bucketCountList=[1, 5, 1, 0, 0, 0, 0, 0, 0, 0]arr=[89, 195, 196, 275, 276, 272, 2343]
origin arr:[195, 196, 275, 276, 272, 0, 0] position:2 maxLength:4
prepared arr:[195, 196, 275, 276, 272, 0, 0] position:2 maxLength:4
num=80 position=2 numberLength=2 exponent=1 position=2
num=81 position=2 numberLength=2 exponent=1 position=2
num=77 position=2 numberLength=2 exponent=1 position=2
bucketCountList=[3, 1, 0, 0, 0, 0, 0, 1, 0, 0]arr=[195, 196, 275, 276, 272, 0, 0]
origin arr:[195, 196, 275, 0, 0] position:3 maxLength:4
prepared arr:[195, 196, 275, 0, 0] position:3 maxLength:4
num=1 position=3 numberLength=1 exponent=0 position=3
num=80 position=3 numberLength=2 exponent=0 position=3
bucketCountList=[3, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[195, 196, 275, 0, 0]
origin arr:[195, 196, 275] position:4 maxLength:4
prepared arr:[195, 196, 275] position:4 maxLength:4
num=1 position=4 numberLength=1 exponent=0 position=4
num=80 position=4 numberLength=2 exponent=0 position=4
bucketCountList=[3, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[195, 196, 275]
origin arr:[195, 196, 275] position:5 maxLength:4
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:0 set arr:[195, 196, 275]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:1 set arr:[195, 196, 275]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:2 set arr:[195, 196, 275]
position:4 sorted arr:[195, 196, 275]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:0 set arr:[195, 196, 275, 0, 0]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:1 set arr:[195, 196, 275, 0, 0]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:2 set arr:[195, 196, 275, 0, 0]
position:3 sorted arr:[195, 196, 275, 0, 0]
bucket:[195, 196, 275, 0, 0] sortedBucket:[195, 196, 275, 0, 0] sortedIdx:0 set arr:[195, 196, 275, 276, 272, 0, 0]
bucket:[195, 196, 275, 0, 0] sortedBucket:[195, 196, 275, 0, 0] sortedIdx:1 set arr:[195, 196, 275, 276, 272, 0, 0]
bucket:[195, 196, 275, 0, 0] sortedBucket:[195, 196, 275, 0, 0] sortedIdx:2 set arr:[195, 196, 275, 276, 272, 0, 0]
position:2 sorted arr:[195, 196, 275, 276, 272, 0, 0]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:1 set arr:[89, 195, 196, 275, 276, 272, 2343]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:2 set arr:[89, 195, 196, 275, 276, 272, 2343]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:3 set arr:[89, 195, 196, 275, 276, 272, 2343]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:4 set arr:[89, 195, 196, 275, 276, 272, 2343]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:5 set arr:[89, 195, 196, 275, 276, 272, 2343]
position:1 sorted arr:[89, 195, 196, 275, 276, 272, 2343]

time:62 ms.
sort1 sorted:[89, 195, 196, 275, 276, 272, 2343]
sort2 start:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
maxLength:6
origin arr:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431] position:1 maxLength:6
prepared arr:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431] position:1 maxLength:6
num=323487 position=1 numberLength=6 exponent=100000 position=1
num=323450 position=1 numberLength=6 exponent=100000 position=1
num=323469 position=1 numberLength=6 exponent=100000 position=1
num=323497 position=1 numberLength=6 exponent=100000 position=1
num=323461 position=1 numberLength=6 exponent=100000 position=1
num=323464 position=1 numberLength=6 exponent=100000 position=1
num=324689 position=1 numberLength=6 exponent=100000 position=1
num=323654 position=1 numberLength=6 exponent=100000 position=1
num=410885 position=1 numberLength=6 exponent=100000 position=1
bucketCountList=[1, 0, 0, 8, 1, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
origin arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0] position:2 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0] position:2 maxLength:6
num=1239 position=2 numberLength=4 exponent=100 position=2
bucketCountList=[7, 0, 1, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
origin arr:[33, -4, 15, 43, 7, 10, 200, 0] position:3 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10, 200, 0] position:3 maxLength:6
num=204 position=3 numberLength=3 exponent=1 position=3
bucketCountList=[6, 0, 0, 0, 1, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 200, 0]
origin arr:[33, -4, 15, 43, 7, 10, 0] position:4 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10, 0] position:4 maxLength:6
num=37 position=4 numberLength=2 exponent=0 position=4
num=19 position=4 numberLength=2 exponent=0 position=4
num=47 position=4 numberLength=2 exponent=0 position=4
num=11 position=4 numberLength=2 exponent=0 position=4
num=14 position=4 numberLength=2 exponent=0 position=4
bucketCountList=[6, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 0]
origin arr:[33, -4, 15, 43, 7, 10] position:5 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10] position:5 maxLength:6
num=37 position=5 numberLength=2 exponent=0 position=5
num=19 position=5 numberLength=2 exponent=0 position=5
num=47 position=5 numberLength=2 exponent=0 position=5
num=11 position=5 numberLength=2 exponent=0 position=5
num=14 position=5 numberLength=2 exponent=0 position=5
bucketCountList=[6, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10]
origin arr:[33, -4, 15, 43, 7, 10] position:6 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10] position:6 maxLength:6
num=37 position=6 numberLength=2 exponent=0 position=6
num=19 position=6 numberLength=2 exponent=0 position=6
num=47 position=6 numberLength=2 exponent=0 position=6
num=11 position=6 numberLength=2 exponent=0 position=6
num=14 position=6 numberLength=2 exponent=0 position=6
bucketCountList=[6, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10]
origin arr:[33, -4, 15, 43, 7, 10] position:7 maxLength:6
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10]
position:6 sorted arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10]
position:5 sorted arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10, 0]
position:4 sorted arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
position:3 sorted arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:6 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
position:2 sorted arr:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:1 set arr:[-323454, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:2 set arr:[-323454, 33, 15, 43, -323454, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:3 set arr:[-323454, 33, -4, 43, -323454, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:4 set arr:[-323454, 33, -4, 15, -323454, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:5 set arr:[-323454, 33, -4, 15, 43, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:6 set arr:[-323454, 33, -4, 15, 43, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:7 set arr:[-323454, 33, -4, 15, 43, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:8 set arr:[-323454, 33, -4, 15, 43, 7, 10, 200, 200, 87431]
position:1 sorted arr:[-323454, 33, -4, 15, 43, 7, 10, 200, 1235, 87431]

time:7 ms.
sort2 sorted:[-323454, 33, -4, 15, 43, 7, 10, 200, 1235, 87431]
 */
