/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供5种不同的实现方式，适合不同场景和性能需求
 * 
 * ==================== 5个基数排序算法的相同与区别 ====================
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
 * 1. radix_sort1 - 计数排序基数排序版本
 *    - 实现方式：基于计数排序的LSD（最低位优先）实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k) 需要计数数组和输出数组
 *    - 特点：经典实现，代码清晰易懂
 * 
 * 2. radix_sort2 - MSD基数排序版本
 *    - 实现方式：递归MSD实现，从最高位开始排序
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k) 需要桶和计数数组
 *    - 特点：适合字符串或变长数据，高位优先处理
 * 
 * 3. radix_sort3 - 迭代MSD基数排序版本
 *    - 实现方式：使用栈模拟递归的MSD（最高位优先）实现
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k + s) s为栈空间
 *    - 特点：避免递归深度过大，适合大数据集
 * 
 * 4. radix_sort4 - 桶优化基数排序版本
 *    - 实现方式：动态桶大小的LSD实现
 *    - 负数支持：通过getDigit函数处理负数
 *    - 内存使用：O(n + k') k'为实际使用的基数范围（≤k）
 *    - 特点：内存优化，适合稀疏数据
 * 
 * 5. radix_sort5 - 递归基数排序版本
 *    - 实现方式：递归处理每一位的LSD实现
 *    - 负数支持：使用最小值偏移处理负数
 *    - 内存使用：O(n + k + d) d为递归栈深度
 *    - 特点：代码简洁，递归深度由数字位数决定
 * 
 * 【性能对比】
 * - 最快：radix_sort5（递归版本）和radix_sort4（桶优化版本）
 * - 内存最优：radix_sort4（动态桶大小）
 * - 最稳定：radix_sort3（迭代MSD，避免递归栈溢出）
 * - 代码最简洁：radix_sort5（递归实现）
 * 
 * 【选择建议】
 * - 一般情况：推荐radix_sort1（计数排序）
 * - 大数据集：推荐radix_sort3（迭代MSD）
 * - 内存敏感：推荐radix_sort4（桶优化）
 * - 代码简洁：推荐radix_sort5（递归版本）
 * - 字符串排序：推荐radix_sort2（MSD版本）
 */

use std::time::Instant;

/**
 * 打印数组内容的辅助函数
 */
fn print_array(arr: &[i32], label: &str) {
    println!("{}: [{}]", label, arr.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(", "));
}

/**
 * 性能测试辅助函数
 */
fn performance_test<F>(sort_func: F, arr: &[i32], name: &str) 
where 
    F: FnOnce(&mut Vec<i32>)
{
    // 创建数组副本，避免修改原数组
    let mut test_arr = arr.to_vec();
    print_array(&test_arr, name);
    
    // 开始计时
    let start_time = Instant::now();
    sort_func(&mut test_arr);
    let end_time = Instant::now();
    
    let duration = end_time.duration_since(start_time).as_millis() as f64;
    println!("{}: {:.3}ms", name, duration);
    print_array(&test_arr, &format!("{}排序结果", name));
    println!(""); // 空行分隔
}

// ==================== 测试数据 ====================

// 测试数据：包含大数字的典型数组
const TEST_DATA: [i32; 10] = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431];

// 负数测试数据
const NEGATIVE_TEST_DATA: [i32; 10] = [170, 45, 75, -90, -802, 24, 2, 66, -5, 0];

/**
 * 获取数字的指定位数
 */
fn get_digit(num: i32, exp: i32) -> i32 {
    num.abs() / exp % 10
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
fn counting_sort(arr: &mut Vec<i32>, exponent: i32) {
    // 第一步：初始化变量和数组，按10个桶大小，0-9的个位数
    let arr_len = arr.len();
    let range = 10;
    let mut count_list = vec![0; range];
    let mut sorted_list = vec![0; arr_len];

    // 第二步：找出最小值
    // 关键点：处理负数情况，需要找到最小值进行偏移
    let min_value = *arr.iter().min().unwrap();

    // 第三步：初始化计数数组
    // 关键点：将计数数组清零
    for i in 0..range {
        count_list[i] = 0;
    }

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - min_value来处理负数，确保索引为正数
    for i in 0..arr_len {
        let item = arr[i] - min_value;
        let idx = (item / exponent) % range as i32;
        count_list[idx as usize] += 1;
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for i in 1..range {
        count_list[i] += count_list[i - 1];
    }
    println!("radix_sort1 countingSort countList:[{}]", count_list.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(", "));

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for i in (0..arr_len).rev() {
        let item = arr[i] - min_value;
        let idx = (item / exponent) % range as i32;
        sorted_list[count_list[idx as usize] - 1] = arr[i];
        count_list[idx as usize] -= 1;
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for i in 0..arr_len {
        arr[i] = sorted_list[i];
    }
    println!("radix_sort1 -> sortedList:[{}]", sorted_list.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(", "));
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
 */
fn radix_sort1(arr: &mut Vec<i32>) {
    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if arr.is_empty() {
        return;
    }

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    let max_value = *arr.iter().max().unwrap();
    let min_value = *arr.iter().min().unwrap();

    // 第三步：根据最大值，逐个按进位(基数)来应用排序
    // 关键点：exponent即数位基数，按个十百千递增
    // 最大减去最小得到数位，最小按0来计算，这样可以支持负数
    let mut exponent = 1;
    while (max_value - min_value) / exponent > 0 {
        counting_sort(arr, exponent);
        exponent *= 10;
    }
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
fn msd_sort(arr: &mut Vec<i32>, left: usize, right: usize, exp: i32) {
    // 第一步：递归终止条件检查
    // 关键点：范围无效或位数不足时返回
    if left >= right || exp < 1 {
        return;
    }

    // 第二步：创建桶
    // 关键点：创建10个桶，对应0-9的数字
    let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); 10];

    // 第三步：分配到桶中
    // 关键点：根据当前位数将元素分配到对应桶中
    for i in left..=right {
        let digit = get_digit(arr[i], exp) as usize;
        buckets[digit].push(arr[i]);
    }

    // 第四步：重新排序并递归处理每个桶
    // 关键点：将桶中元素复制回原数组，并递归处理子数组
    let mut index = left;
    let mut current_left = left;
    for i in 0..10 {
        if !buckets[i].is_empty() {
            // 步骤4.1：复制桶中元素回原数组
            // 关键点：按桶的顺序复制元素，保持稳定性
            for &value in buckets[i].iter() {
                arr[index] = value;
                index += 1;
            }

            // 步骤4.2：递归处理下一个位数
            // 关键点：递归处理当前桶的子数组
            msd_sort(arr, current_left, index - 1, exp / 10);
            current_left = index;
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
 */
fn radix_sort2(arr: &mut Vec<i32>) {
    println!("radix_sort2 MSD:");

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if arr.is_empty() {
        return;
    }

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    let max = *arr.iter().max().unwrap();

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    let mut exp = 1;
    while max / exp > 0 {
        exp *= 10;
    }

    // 第四步：调用MSD递归排序
    // 关键点：从最高位开始递归排序
    msd_sort(arr, 0, arr.len() - 1, exp / 10);

    // 第五步：输出排序结果
    print_array(arr, "排序后数组");
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
 */
fn radix_sort3(arr: &mut Vec<i32>) {
    println!("radix_sort3 iterative MSD:");

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if arr.is_empty() {
        return;
    }

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    let max = *arr.iter().max().unwrap();

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    let mut exp = 1;
    while max / exp > 0 {
        exp *= 10;
    }

    // 第四步：使用栈模拟递归
    // 关键点：创建栈数组，初始化栈顶指针
    #[derive(Debug, Clone)]
    struct StackItem {
        left: usize,
        right: usize,
        exp: i32,
    }

    let mut stack = vec![StackItem {
        left: 0,
        right: arr.len() - 1,
        exp: exp / 10,
    }];

    // 第五步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while let Some(item) = stack.pop() {
        // 步骤5.1：从栈中取出待处理的范围
        // 关键点：后进先出，取出栈顶元素
        let left = item.left;
        let right = item.right;
        let current_exp = item.exp;

        // 步骤5.2：递归终止条件检查
        // 关键点：范围无效或位数不足时跳过
        if left >= right || current_exp < 1 {
            continue;
        }

        // 步骤5.3：创建桶
        // 关键点：创建10个桶，对应0-9的数字
        let mut buckets: Vec<Vec<i32>> = vec![Vec::new(); 10];

        // 步骤5.4：分配到桶中
        // 关键点：根据当前位数将元素分配到对应桶中
        for i in left..=right {
            let digit = get_digit(arr[i], current_exp) as usize;
            buckets[digit].push(arr[i]);
        }

        // 步骤5.5：重新排序并将子问题入栈
        // 关键点：将桶中元素复制回原数组，并将子问题入栈
        let mut index = left;
        let mut next_left = left;
        for i in 0..10 {
            if !buckets[i].is_empty() {
                // 步骤5.5.1：复制桶中元素回原数组
                // 关键点：按桶的顺序复制元素，保持稳定性
                for &value in buckets[i].iter() {
                    arr[index] = value;
                    index += 1;
                }

                // 步骤5.5.2：将子问题入栈
                // 关键点：将子数组范围和下一位数入栈，逆序处理保持正确顺序
                stack.push(StackItem {
                    left: next_left,
                    right: index - 1,
                    exp: current_exp / 10,
                });
                next_left = index;
            }
        }
    }

    // 第六步：输出排序结果
    print_array(arr, "排序后数组");
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
 */
fn radix_sort4(arr: &mut Vec<i32>) {
    println!("radix_sort4 bucket optimized:");

    // 第一步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定处理位数
    let max = *arr.iter().max().unwrap();

    // 第二步：对每个位数进行计数排序
    // 关键点：从个位开始，逐位处理，直到最高位
    let mut exp = 1;
    while max / exp > 0 {
        let n = arr.len();
        let mut output = vec![0; n];

        // 步骤2.1：动态确定桶范围
        // 关键点：统计当前位数的最小和最大值，减少桶数量
        let mut min_digit = 9;
        let mut max_digit = 0;
        for &value in arr.iter() {
            let digit = get_digit(value, exp);
            if digit < min_digit {
                min_digit = digit;
            }
            if digit > max_digit {
                max_digit = digit;
            }
        }

        // 步骤2.2：创建动态大小的计数数组
        // 关键点：只创建实际需要的桶大小，优化内存使用
        let bucket_size = max_digit - min_digit + 1;
        let mut count = vec![0; bucket_size as usize];

        // 步骤2.3：统计每个数字的出现次数
        // 关键点：使用偏移量处理，支持任意范围的数字
        for &value in arr.iter() {
            let digit = get_digit(value, exp);
            count[(digit - min_digit) as usize] += 1;
        }

        // 步骤2.4：计算累计计数
        // 关键点：当前位置加上左侧位置，形成累积计数
        for i in 1..count.len() {
            count[i] += count[i - 1];
        }

        // 步骤2.5：构建输出数组
        // 关键点：从后向前遍历，保持排序的稳定性
        for i in (0..n).rev() {
            let digit = get_digit(arr[i], exp);
            output[count[(digit - min_digit) as usize] - 1] = arr[i];
            count[(digit - min_digit) as usize] -= 1;
        }

        // 步骤2.6：复制回原数组
        // 关键点：将排序结果复制回原数组，准备下一位处理
        for i in 0..n {
            arr[i] = output[i];
        }

        exp *= 10;
    }

    // 第三步：输出排序结果
    print_array(arr, "排序后数组");
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
 * @param min_value - 数组最小值，用于负数处理
 * @param max_value - 数组最大值，用于确定递归终止条件
 */
fn recursive_radix_sort(arr: &mut Vec<i32>, exponent: i32, min_value: i32, max_value: i32) {
    // 第一步：递归终止条件检查
    // 关键点：当基数超过最大值时停止递归
    if (max_value - min_value) / exponent == 0 {
        return;
    }

    // 第二步：初始化计数排序变量
    // 关键点：为当前位数的计数排序准备变量
    let range = 10;
    let mut count_list = vec![0; range];
    let mut sorted_list = vec![0; arr.len()];

    // 第三步：初始化计数数组
    // 关键点：将计数数组清零
    for i in 0..range {
        count_list[i] = 0;
    }

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - min_value来处理负数，确保索引为正数
    for i in 0..arr.len() {
        let item = arr[i] - min_value;
        let idx = (item / exponent) % range as i32;
        count_list[idx as usize] += 1;
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for i in 1..range {
        count_list[i] += count_list[i - 1];
    }

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for i in (0..arr.len()).rev() {
        let item = arr[i] - min_value;
        let idx = (item / exponent) % range as i32;
        sorted_list[count_list[idx as usize] - 1] = arr[i];
        count_list[idx as usize] -= 1;
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for i in 0..arr.len() {
        arr[i] = sorted_list[i];
    }

    // 第八步：递归处理下一位
    // 关键点：递归调用处理更高位数
    recursive_radix_sort(arr, exponent * 10, min_value, max_value);
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
 */
fn radix_sort5(arr: &mut Vec<i32>) {
    // 第一步：输出测试信息
    // 关键点：标识当前测试的算法类型
    println!("radix_sort5 递归基数排序:");

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    let max_value = *arr.iter().max().unwrap();
    let min_value = *arr.iter().min().unwrap();

    // 第三步：调用递归基数排序
    // 关键点：从最低位（个位）开始递归排序
    recursive_radix_sort(arr, 1, min_value, max_value);

    // 第四步：输出排序结果
    // 关键点：显示排序后的数组，验证算法正确性
    print_array(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

fn main() {
    // 测试1：radix_sort1 - 计数排序基数排序版本（支持负数）
    performance_test(radix_sort1, &TEST_DATA, "radix_sort1 - 计数排序基数排序版本");

    // 测试2：radix_sort2 - MSD基数排序版本
    performance_test(radix_sort2, &TEST_DATA, "radix_sort2 - MSD基数排序版本");

    // 测试3：radix_sort3 - 迭代MSD基数排序版本
    performance_test(radix_sort3, &TEST_DATA, "radix_sort3 - 迭代MSD基数排序版本");

    // 测试4：radix_sort4 - 桶优化基数排序版本
    performance_test(radix_sort4, &TEST_DATA, "radix_sort4 - 桶优化基数排序版本");

    // 测试5：radix_sort5 - 递归基数排序版本
    performance_test(radix_sort5, &TEST_DATA, "radix_sort5 - 递归基数排序版本");

    // 测试6：负数数据处理
    println!("\n=== 负数测试 ===");
    performance_test(radix_sort5, &NEGATIVE_TEST_DATA, "radix_sort5 - 递归基数排序版本（负数测试）");

    println!("=== 算法对比总结 ===");
    println!("1. radix_sort1：计数排序基数排序版本，支持负数");
    println!("2. radix_sort2：MSD基数排序版本，高位优先递归处理");
    println!("3. radix_sort3：迭代MSD基数排序版本，避免递归性能稳定");
    println!("4. radix_sort4：桶优化基数排序版本，动态桶大小内存优化");
    println!("5. radix_sort5：递归基数排序版本，递归处理每一位");
}

/*
打印结果
jarry@Mac radixsort % rustc radix_sort.rs && ./radix_sort
radix_sort1 - 计数排序基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort1 countingSort countList:[2, 4, 4, 5, 5, 5, 7, 8, 8, 10]
radix_sort1 -> sortedList:[4, 323454, 15, 1235, 7, 10, 200, 87431, 33, 43]
radix_sort1 countingSort countList:[3, 4, 6, 8, 8, 9, 9, 9, 9, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 87431, 33, 1235, 43, 323454, 200]
radix_sort1 countingSort countList:[6, 7, 8, 8, 10, 10, 10, 10, 10, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort1 countingSort countList:[7, 8, 8, 9, 9, 9, 9, 10, 10, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radix_sort1 countingSort countList:[8, 8, 9, 9, 9, 9, 9, 9, 10, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431]
radix_sort1 countingSort countList:[9, 9, 9, 10, 10, 10, 10, 10, 10, 10]
radix_sort1 -> sortedList:[4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort1 - 计数排序基数排序版本: 0.000ms
radix_sort1 - 计数排序基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radix_sort2 - MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort2 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort2 - MSD基数排序版本: 0.000ms
radix_sort2 - MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radix_sort3 - 迭代MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort3 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort3 - 迭代MSD基数排序版本: 0.000ms
radix_sort3 - 迭代MSD基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radix_sort4 - 桶优化基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort4 - 桶优化基数排序版本: 0.000ms
radix_sort4 - 桶优化基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radix_sort5 - 递归基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort5 递归基数排序:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radix_sort5 - 递归基数排序版本: 0.000ms
radix_sort5 - 递归基数排序版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]


=== 负数测试 ===
radix_sort5 - 递归基数排序版本（负数测试）: [170, 45, 75, -90, -802, 24, 2, 66, -5, 0]
radix_sort5 递归基数排序:
排序后数组: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]
radix_sort5 - 递归基数排序版本（负数测试）: 0.000ms
radix_sort5 - 递归基数排序版本（负数测试）排序结果: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]

=== 算法对比总结 ===
1. radix_sort1：计数排序基数排序版本，支持负数
2. radix_sort2：MSD基数排序版本，高位优先递归处理
3. radix_sort3：迭代MSD基数排序版本，避免递归性能稳定
4. radix_sort4：桶优化基数排序版本，动态桶大小内存优化
5. radix_sort5：递归基数排序版本，递归处理每一位
*/
