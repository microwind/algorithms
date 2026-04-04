
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序MSD版本实现
 * 递归MSD（最高位优先）实现，基于桶排序
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
 * ## 负数处理
 * - 使用最小值偏移处理负数
 * - 通过arr[i] - min确保索引为正数
 * - 支持包含负数的整数数组排序
 * 
 * ## 实现原理
 * 1. 找出数组中最大的数，确定其位数
 * 2. MSD是从高位开始，依次按照位数的值将数字放入到不同桶中
 * 3. 如果桶里的长度超过1，则通过递归继续按桶排序
 * 4. 当桶里的数据只有1位时添加到原列表对应位置
 * 5. 重复步骤2和3，直到按照最高位排序完成
 */

import java.util.*;

public class RadixSortMSD {
    
    /**
     * 基数排序，从高到低逐位排序，递归方式，基于桶排序
     * 
     * ## 实现步骤
     * 1. 找出数组中的最大值和最小值
     * 2. 计算数字的位数，确定最高位的基数
     * 3. 调用递归桶排序函数进行排序
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
        int numberOfDigits = (int) (Math.log10(max - min) + 1);
        int exponent = (int) (Math.pow(10, numberOfDigits - 1));
        
        // 第五步：输出调试信息并开始排序
        // 关键点：显示位数和基数信息，便于调试
        System.out.println("numberOfDigits:" + numberOfDigits + " exponent:" + exponent);
        
        // 第六步：调用递归桶排序
        // 关键点：从最高位开始递归排序
        return bucketSort(arr, len, exponent);
    }

    /**
     * 递归桶排序实现基数排序
     * 
     * ## 实现原理
     * - 使用桶排序对指定位数进行排序
     * - 递归处理每个桶中的子数组
     * - 从最高位向最低位逐层处理
     * 
     * @param arr      - 待排序的数组
     * @param len      - 数组长度
     * @param exponent - 当前处理的位数基数
     * @return int[]   - 排序后的数组
     */
    private static int[] bucketSort(int[] arr, int len, int exponent) {
        // 第一步：输出调试信息
        // 关键点：显示当前排序状态，便于调试
        System.out.println("origin arr:" + Arrays.toString(arr) + " len=" + len + " exponent:" + exponent);
        
        // 第二步：递归终止条件检查
        // 关键点：数组长度为1或位数为0时停止递归
        if (len <= 1 || exponent < 1) {
            return arr;
        }
        
        System.out.println("prepared arr:" + Arrays.toString(arr) + " len=" + len + " exponent:" + exponent);

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
        int[] bucketsCount = new int[range];
        
        // 第五步：将数据分配到桶中
        // 关键点：根据数位上的值，把数据追加到对应的桶里，减去min是支持负数
        for (int i = 0; i < len; i++) {
            int item = arr[i] - min;
            int bucketIdx = (item / exponent) % range;
            System.out.println("arr[" + i + "]=" + arr[i] + " item=" + item + " bucketIdx=" + bucketIdx);
            
            // 步骤5.1：把数据按下标插入到桶里
            // 关键点：使用桶计数器记录插入位置
            int numberIndex = bucketsCount[bucketIdx];
            buckets[bucketIdx][numberIndex] = arr[i];
            bucketsCount[bucketIdx] += 1;
        }

        System.out.println("bucketsCount=" + Arrays.toString(bucketsCount) + "arr=" + Arrays.toString(arr));
        
        // 第六步：将每个桶的数据按顺序逐个取出，重新赋值给原数组
        // 关键点：按桶的顺序重新组合数组
        int sortedIdx = 0;

        for (int i = 0; i < range; i++) {
            int[] bucket = buckets[i];
            int bucketLen = bucketsCount[i];
            
            // 步骤6.1：如果只有一个值，则直接更新到原数组
            // 关键点：单元素桶无需递归处理
            if (bucketsCount[i] == 1) {
                arr[sortedIdx] = bucket[0];
                sortedIdx += 1;
            } else if (bucket.length > 0 && bucketLen > 0) {
                // 步骤6.2：如果是数组且记录大于1则继续递归调用，位数降低1位
                // 关键点：递归调用传参时需要传入当前子序列、子序列长度、当前分解的位数基数
                int[] sortedBucket = bucketSort(bucket, bucketLen, (int) (exponent / range));
                
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
        // 关键点：显示当前位数排序后的数组状态
        System.out.println("exponent:" + exponent + " sorted arr:" + Arrays.toString(arr));
        return arr;
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
        System.out.println("sort1 start:" + Arrays.toString(arr1));
        
        // 性能测试：记录开始时间
        long startTime = System.currentTimeMillis();
        
        // 执行排序
        arr1 = RadixSortMSD.radixSort(arr1);
        
        // 计算并输出执行时间
        System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
        System.out.println("sort1 sorted:" + Arrays.toString(arr1));
    }
}

/*
 * jarry@jarrys-MacBook-Pro radixsort % javac RadixSortLSD.java
 * jarry@jarrys-MacBook-Pro radixsort % java RadixSortLSD
 * sort1 start:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
 * numberOfDigits:6 exponent:100000
 * origin arr:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431] len=10
 * exponent:100000
 * prepared arr:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431] len=10
 * exponent:100000
 * arr[0]=33 item=323487 bucketIdx=3
 * arr[1]=-4 item=323450 bucketIdx=3
 * arr[2]=15 item=323469 bucketIdx=3
 * arr[3]=43 item=323497 bucketIdx=3
 * arr[4]=-323454 item=0 bucketIdx=0
 * arr[5]=7 item=323461 bucketIdx=3
 * arr[6]=10 item=323464 bucketIdx=3
 * arr[7]=1235 item=324689 bucketIdx=3
 * arr[8]=200 item=323654 bucketIdx=3
 * arr[9]=87431 item=410885 bucketIdx=4
 * bucketsCount=[1, 0, 0, 8, 1, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, -323454, 7,
 * 10, 1235, 200, 87431]
 * origin arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0] len=8 exponent:10000
 * prepared arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0] len=8 exponent:10000
 * arr[0]=33 item=37 bucketIdx=0
 * arr[1]=-4 item=0 bucketIdx=0
 * arr[2]=15 item=19 bucketIdx=0
 * arr[3]=43 item=47 bucketIdx=0
 * arr[4]=7 item=11 bucketIdx=0
 * arr[5]=10 item=14 bucketIdx=0
 * arr[6]=1235 item=1239 bucketIdx=0
 * arr[7]=200 item=204 bucketIdx=0
 * bucketsCount=[8, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 1235,
 * 200, 0, 0]
 * origin arr:[33, -4, 15, 43, 7, 10, 1235, 200] len=8 exponent:1000
 * prepared arr:[33, -4, 15, 43, 7, 10, 1235, 200] len=8 exponent:1000
 * arr[0]=33 item=37 bucketIdx=0
 * arr[1]=-4 item=0 bucketIdx=0
 * arr[2]=15 item=19 bucketIdx=0
 * arr[3]=43 item=47 bucketIdx=0
 * arr[4]=7 item=11 bucketIdx=0
 * arr[5]=10 item=14 bucketIdx=0
 * arr[6]=1235 item=1239 bucketIdx=1
 * arr[7]=200 item=204 bucketIdx=0
 * bucketsCount=[7, 1, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 1235,
 * 200]
 * origin arr:[33, -4, 15, 43, 7, 10, 200, 0] len=7 exponent:100
 * prepared arr:[33, -4, 15, 43, 7, 10, 200, 0] len=7 exponent:100
 * arr[0]=33 item=37 bucketIdx=0
 * arr[1]=-4 item=0 bucketIdx=0
 * arr[2]=15 item=19 bucketIdx=0
 * arr[3]=43 item=47 bucketIdx=0
 * arr[4]=7 item=11 bucketIdx=0
 * arr[5]=10 item=14 bucketIdx=0
 * arr[6]=200 item=204 bucketIdx=2
 * bucketsCount=[6, 0, 1, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 200,
 * 0]
 * origin arr:[33, -4, 15, 43, 7, 10, 0] len=6 exponent:10
 * prepared arr:[33, -4, 15, 43, 7, 10, 0] len=6 exponent:10
 * arr[0]=33 item=37 bucketIdx=3
 * arr[1]=-4 item=0 bucketIdx=0
 * arr[2]=15 item=19 bucketIdx=1
 * arr[3]=43 item=47 bucketIdx=4
 * arr[4]=7 item=11 bucketIdx=1
 * arr[5]=10 item=14 bucketIdx=1
 * bucketsCount=[1, 3, 0, 1, 1, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 0]
 * origin arr:[15, 7, 10, 0, 0, 0] len=3 exponent:1
 * prepared arr:[15, 7, 10, 0, 0, 0] len=3 exponent:1
 * arr[0]=15 item=8 bucketIdx=8
 * arr[1]=7 item=0 bucketIdx=0
 * arr[2]=10 item=3 bucketIdx=3
 * bucketsCount=[1, 0, 0, 1, 0, 0, 0, 0, 1, 0]arr=[15, 7, 10, 0, 0, 0]
 * exponent:1 sorted arr:[7, 10, 15, 0, 0, 0]
 * bucket:[7, 10, 15, 0, 0, 0] sortedBucket:[7, 10, 15, 0, 0, 0] sortedIdx:1 set
 * arr:[-4, -4, 15, 43, 7, 10, 0]
 * bucket:[7, 10, 15, 0, 0, 0] sortedBucket:[7, 10, 15, 0, 0, 0] sortedIdx:2 set
 * arr:[-4, 7, 15, 43, 7, 10, 0]
 * bucket:[7, 10, 15, 0, 0, 0] sortedBucket:[7, 10, 15, 0, 0, 0] sortedIdx:3 set
 * arr:[-4, 7, 10, 43, 7, 10, 0]
 * exponent:10 sorted arr:[-4, 7, 10, 15, 33, 43, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:1 set arr:[-4, -4, 15, 43, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:2 set arr:[-4, 7, 15, 43, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:3 set arr:[-4, 7, 10, 43, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:4 set arr:[-4, 7, 10, 15, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:5 set arr:[-4, 7, 10, 15, 33, 10, 200, 0]
 * exponent:100 sorted arr:[-4, 7, 10, 15, 33, 43, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:1 set arr:[-4, -4, 15, 43, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:2 set arr:[-4, 7, 15, 43, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:3 set arr:[-4, 7, 10, 43, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:4 set arr:[-4, 7, 10, 15, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:5 set arr:[-4, 7, 10, 15, 33, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:6 set arr:[-4, 7, 10, 15, 33, 43, 1235, 200]
 * exponent:1000 sorted arr:[-4, 7, 10, 15, 33, 43, 200, 1235]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:1 set arr:[-4, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:2 set arr:[-4, 7, 15, 43, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:3 set arr:[-4, 7, 10, 43, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:4 set arr:[-4, 7, 10, 15, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:5 set arr:[-4, 7, 10, 15, 33, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:6 set arr:[-4, 7, 10, 15, 33, 43, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:7 set arr:[-4, 7, 10, 15, 33, 43, 200, 200, 0, 0]
 * exponent:10000 sorted arr:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:1 set arr:[-323454, -4, 15, 43, -323454,
 * 7, 10, 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:2 set arr:[-323454, -4, 15, 43, -323454,
 * 7, 10, 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:3 set arr:[-323454, -4, 7, 43, -323454, 7,
 * 10, 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:4 set arr:[-323454, -4, 7, 10, -323454, 7,
 * 10, 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:5 set arr:[-323454, -4, 7, 10, 15, 7, 10,
 * 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:6 set arr:[-323454, -4, 7, 10, 15, 33, 10,
 * 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:7 set arr:[-323454, -4, 7, 10, 15, 33, 43,
 * 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:8 set arr:[-323454, -4, 7, 10, 15, 33, 43,
 * 200, 200, 87431]
 * exponent:100000 sorted arr:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 * 
 * time:49 ms.
 * sort1 sorted:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 */
