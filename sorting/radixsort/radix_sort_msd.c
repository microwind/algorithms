/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <memory.h>

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

/**
 * 打印数组内容的辅助函数
 * 
 * @param arr - 要打印的数组
 * @param len - 数组长度
 */
void print_array(int *arr, int len)
{
    printf("\r\n{ ");
    for (int i = 0; i < len; i++)
    {
        printf("%d", arr[i]);
        if (i < len - 1)
        {
            printf(", ");
        }
    }
    printf(" }");
}

/**
 * 根据最大长度来获取数字第n位的值，从前往后开始，前面不足最大长度时补零
 * 
 * ## 实现原理
 * - 计算数字的实际长度
 * - 判断查询位置是否超出数字长度
 * - 使用除法和取余运算获取指定位数
 * 
 * @param num - 要处理的数字（非负数）
 * @param position - 位数位置（从左到右，1=最高位）
 * @param max_length - 数字的最大长度
 * @return int - 指定位数的值
 */
int get_digit_by_position(int num, int position, int max_length)
{
    // 第一步：特殊情况处理
    // 关键点：数字为0时直接返回0
    if (num == 0)
    {
        return 0;
    }
    
    // 第二步：计算数字长度
    // 关键点：获取数字的实际位数
    int number_length = (int)log10(num) + 1;
    
    // 第三步：位置超出检查
    // 关键点：查询的位置加上自身长度不足最大长度则返回0
    if ((position + number_length) < max_length)
    {
        return 0;
    }
    
    // 第四步：修正位置计算
    // 关键点：position 应该是从右往左的位置，而不是从左往右
    int actual_position = max_length - position - 1;
    int exponent = (int)pow(10, actual_position);
    int digit = 0;
    if (exponent > 0)
    {
        digit = (num / exponent) % 10;
    }
    
    // 第五步：输出调试信息
    // 关键点：显示计算过程，便于调试
    printf("\r\nnum=%d position=%d max_length=%d number_length=%d exponent=%d actual_position=%d digit=%d.", 
           num, position, max_length, number_length, exponent, actual_position, digit);
    
    return digit;
}

/**
 * 桶排序，根据数位递归调用
 * 
 * ## 实现原理
 * - 使用桶排序对指定位数进行排序
 * - 递归处理每个桶中的子数组
 * - 从最高位向最低位逐层处理
 * 
 * @param arr - 待排序的数组
 * @param len - 数组长度
 * @param position - 当前处理的位置（从左到右）
 * @param max_length - 数字的最大长度
 * @return int* - 排序后的数组
 */
int *bucket_sort(int arr[], int len, int position, int max_length)
{
    // 第一步：输出调试信息
    // 关键点：显示当前排序状态，便于调试
    printf("\r\nlen=%d position=%d max_length=%d ", len, position, max_length);

    // 第二步：递归终止条件检查
    // 关键点：数组长度为1或位置超过最大长度时停止递归
    if (len <= 1 || position > max_length)
    {
        return arr;
    }

    // 第三步：找出数组中的最小值
    // 关键点：用于处理负数，计算偏移量
    int min_value = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }
    }

    // 第四步：初始化桶结构
    // 关键点：创建10个桶对应0-9的数字
    int range = 10;
    int buckets[range][len];
    for (int i = 0; i < range; i++)
    {
        // 此处未提前使用，也可以不设置默认值
        memset(buckets[i], 0, len * sizeof(int));
        // print_array(buckets[i], len);
    }

    // 第五步：初始化桶计数数组
    // 关键点：记录每个桶中元素的数量
    int bucket_count_list[range];
    memset(bucket_count_list, 0, range * sizeof(int));

    // 第六步：将数据分配到桶中
    // 关键点：根据数位上的值，减去最小值，分配到对应的桶里
    for (int i = 0; i < len; i++)
    {
        int item = arr[i] - min_value;
        int bucket_idx = get_digit_by_position(item, position, max_length);
        
        // 把数据按下标插入到桶里
        int number_idx = bucket_count_list[bucket_idx];
        printf("\r\narr[%d]=%d item=%d bucket_idx=%d number_idx=%d", 
               i, arr[i], item, bucket_idx, number_idx);
        buckets[bucket_idx][number_idx] = arr[i];
        bucket_count_list[bucket_idx] += 1;
    }

    // 第七步：将每个桶的数据按顺序逐个取出，重新赋值给原数组
    // 关键点：按桶的顺序重新组合数组
    int sorted_idx = 0;

    for (int i = 0; i < range; i++)
    {
        int *bucket = buckets[i];
        int bucket_len = bucket_count_list[i];
        int bucket_size = sizeof(*bucket) / sizeof(bucket[0]);
        
        // 步骤7.1：如果只有一个值，则直接更新到原数组
        // 关键点：单元素桶无需递归处理
        if (bucket_count_list[i] == 1)
        {
            arr[sorted_idx] = bucket[0];
            sorted_idx += 1;
        }
        else if (bucket_size > 0 && bucket_len > 0)
        {
            // 步骤7.2：如果是数组且记录大于1则继续递归调用，位置增加1位
            // 关键点：递归调用传参时需要传入当前子序列、子序列长度、当前分解的位数基数
            int *sorted_bucket = bucket_sort(bucket, bucket_len, position + 1, max_length);
            
            // 步骤7.3：依照已排序的子序列实际长度，把各个桶里的值按顺序赋给原数组
            // 关键点：将递归排序的结果复制回原数组
            for (int j = 0; j < bucket_len; j++)
            {
                int num = sorted_bucket[j];
                arr[sorted_idx] = num;
                sorted_idx += 1;
            }
        }
    }
    
    // 第八步：输出当前轮次排序结果
    // 关键点：显示当前位置排序后的数组状态
    printf("\r\n position:%d", position);
    print_array(arr, len);
    return arr;
}

/**
 * 基数排序，根据数字的位置逐个对比排序，从高到低MSD，递归方式
 * 
 * ## 实现步骤
 * 1. 找出数组中的最大值和最小值
 * 2. 计算数字的位数，确定最高位的基数
 * 3. 调用递归桶排序函数进行排序
 * 
 * @param arr - 待排序的数字数组
 * @param len - 数组长度
 * @return int* - 排序后的数组
 */
int *radix_sort_msd(int arr[], int len)
{
    // 第一步：找出数组中的最大值
    // 关键点：用于确定排序的最高位数
    int max_value = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    
    // 第二步：找出数组中的最小值
    // 关键点：用于处理负数，计算偏移量
    int min_value = arr[0];
    for (int i = 0; i < len; i++)
    {
        if (min_value > arr[i])
        {
            min_value = arr[i];
        }
    }
    
    // 第三步：计算数字的位数
    // 关键点：获取数字一共有几位，减去min得到最大值，以支持负数和减少最大值
    int max_length = (int)(log10(max_value - min_value) + 1);
    
    // 第四步：调用递归桶排序
    // 关键点：根据数组最大值的长度，从前往后逐个对比排序
    return bucket_sort(arr, len, 1, max_length);
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
int main()
{
    // 测试1：仅包含正数的数组
    int arr[] = {195, 272, 276, 2343, 196, 89, 275};
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("\r\n origin arr1:");
    print_array(arr, len);
    float startTime = clock();
    int *result1 = radix_sort_msd(arr, len);
    printf("\r\n time: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
    printf("\r\n result1 sorted:");
    print_array(result1, len);

    // 测试2：包含正数和负数的混合数组
    int arr2[] = {33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431};
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("\r\n\r\n origin arr2:");
    print_array(arr2, len2);
    startTime = clock();
    int *result2 = radix_sort_msd(arr2, len2);
    printf("\r\n result2 sorted:");
    print_array(result2, len2);
    printf("\r\n time: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
    return 0;
}

/*
jarry@Mac radixsort % gcc radix_sort_msd.c -o radix_sort_msd && ./radix_sort_msd

 origin arr1:
{ 195, 272, 276, 2343, 196, 89, 275 }
len=7 position=1 max_length=4 
num=106 position=1 max_length=4 number_length=3 exponent=100 actual_position=2 digit=1.
arr[0]=195 item=106 bucket_idx=1 number_idx=0
num=183 position=1 max_length=4 number_length=3 exponent=100 actual_position=2 digit=1.
arr[1]=272 item=183 bucket_idx=1 number_idx=1
num=187 position=1 max_length=4 number_length=3 exponent=100 actual_position=2 digit=1.
arr[2]=276 item=187 bucket_idx=1 number_idx=2
num=2254 position=1 max_length=4 number_length=4 exponent=100 actual_position=2 digit=2.
arr[3]=2343 item=2254 bucket_idx=2 number_idx=0
num=107 position=1 max_length=4 number_length=3 exponent=100 actual_position=2 digit=1.
arr[4]=196 item=107 bucket_idx=1 number_idx=3
arr[5]=89 item=0 bucket_idx=0 number_idx=0
num=186 position=1 max_length=4 number_length=3 exponent=100 actual_position=2 digit=1.
arr[6]=275 item=186 bucket_idx=1 number_idx=4
len=5 position=2 max_length=4 
arr[0]=195 item=0 bucket_idx=0 number_idx=0
num=77 position=2 max_length=4 number_length=2 exponent=10 actual_position=1 digit=7.
arr[1]=272 item=77 bucket_idx=7 number_idx=0
num=81 position=2 max_length=4 number_length=2 exponent=10 actual_position=1 digit=8.
arr[2]=276 item=81 bucket_idx=8 number_idx=0
arr[3]=196 item=1 bucket_idx=0 number_idx=1
num=80 position=2 max_length=4 number_length=2 exponent=10 actual_position=1 digit=8.
arr[4]=275 item=80 bucket_idx=8 number_idx=1
len=2 position=3 max_length=4 
arr[0]=195 item=0 bucket_idx=0 number_idx=0
num=1 position=3 max_length=4 number_length=1 exponent=1 actual_position=0 digit=1.
arr[1]=196 item=1 bucket_idx=1 number_idx=0
 position:3
{ 195, 196 }
len=2 position=3 max_length=4 
num=1 position=3 max_length=4 number_length=1 exponent=1 actual_position=0 digit=1.
arr[0]=276 item=1 bucket_idx=1 number_idx=0
arr[1]=275 item=0 bucket_idx=0 number_idx=0
 position:3
{ 275, 276 }
 position:2
{ 195, 196, 272, 275, 276 }
 position:1
{ 89, 195, 196, 272, 275, 276, 2343 }
 time: 0.030000 ms.
 result1 sorted:
{ 89, 195, 196, 272, 275, 276, 2343 }

 origin arr2:
{ 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 }
len=10 position=1 max_length=6 
num=323487 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=2.
arr[0]=33 item=323487 bucket_idx=2 number_idx=0
num=323450 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=2.
arr[1]=-4 item=323450 bucket_idx=2 number_idx=1
num=323469 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=2.
arr[2]=15 item=323469 bucket_idx=2 number_idx=2
num=323497 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=2.
arr[3]=43 item=323497 bucket_idx=2 number_idx=3
arr[4]=-323454 item=0 bucket_idx=0 number_idx=0
num=323461 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=2.
arr[5]=7 item=323461 bucket_idx=2 number_idx=4
num=323464 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=2.
arr[6]=10 item=323464 bucket_idx=2 number_idx=5
num=324689 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=2.
arr[7]=1235 item=324689 bucket_idx=2 number_idx=6
num=323654 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=2.
arr[8]=200 item=323654 bucket_idx=2 number_idx=7
num=410885 position=1 max_length=6 number_length=6 exponent=10000 actual_position=4 digit=1.
arr[9]=87431 item=410885 bucket_idx=1 number_idx=0
len=8 position=2 max_length=6 
arr[0]=33 item=37 bucket_idx=0 number_idx=0
arr[1]=-4 item=0 bucket_idx=0 number_idx=1
arr[2]=15 item=19 bucket_idx=0 number_idx=2
arr[3]=43 item=47 bucket_idx=0 number_idx=3
arr[4]=7 item=11 bucket_idx=0 number_idx=4
arr[5]=10 item=14 bucket_idx=0 number_idx=5
num=1239 position=2 max_length=6 number_length=4 exponent=1000 actual_position=3 digit=1.
arr[6]=1235 item=1239 bucket_idx=1 number_idx=0
arr[7]=200 item=204 bucket_idx=0 number_idx=6
len=7 position=3 max_length=6 
arr[0]=33 item=37 bucket_idx=0 number_idx=0
arr[1]=-4 item=0 bucket_idx=0 number_idx=1
arr[2]=15 item=19 bucket_idx=0 number_idx=2
arr[3]=43 item=47 bucket_idx=0 number_idx=3
arr[4]=7 item=11 bucket_idx=0 number_idx=4
arr[5]=10 item=14 bucket_idx=0 number_idx=5
num=204 position=3 max_length=6 number_length=3 exponent=100 actual_position=2 digit=2.
arr[6]=200 item=204 bucket_idx=2 number_idx=0
len=6 position=4 max_length=6 
num=37 position=4 max_length=6 number_length=2 exponent=10 actual_position=1 digit=3.
arr[0]=33 item=37 bucket_idx=3 number_idx=0
arr[1]=-4 item=0 bucket_idx=0 number_idx=0
num=19 position=4 max_length=6 number_length=2 exponent=10 actual_position=1 digit=1.
arr[2]=15 item=19 bucket_idx=1 number_idx=0
num=47 position=4 max_length=6 number_length=2 exponent=10 actual_position=1 digit=4.
arr[3]=43 item=47 bucket_idx=4 number_idx=0
num=11 position=4 max_length=6 number_length=2 exponent=10 actual_position=1 digit=1.
arr[4]=7 item=11 bucket_idx=1 number_idx=1
num=14 position=4 max_length=6 number_length=2 exponent=10 actual_position=1 digit=1.
arr[5]=10 item=14 bucket_idx=1 number_idx=2
len=3 position=5 max_length=6 
num=8 position=5 max_length=6 number_length=1 exponent=1 actual_position=0 digit=8.
arr[0]=15 item=8 bucket_idx=8 number_idx=0
arr[1]=7 item=0 bucket_idx=0 number_idx=0
num=3 position=5 max_length=6 number_length=1 exponent=1 actual_position=0 digit=3.
arr[2]=10 item=3 bucket_idx=3 number_idx=0
 position:5
{ 7, 10, 15 }
 position:4
{ -4, 7, 10, 15, 33, 43 }
 position:3
{ -4, 7, 10, 15, 33, 43, 200 }
 position:2
{ -4, 7, 10, 15, 33, 43, 200, 1235 }
 position:1
{ -323454, 87431, -4, 7, 10, 15, 33, 43, 200, 1235 }
 result2 sorted:
{ -323454, 87431, -4, 7, 10, 15, 33, 43, 200, 1235 }
 time: 0.061000 ms.%    
*/
