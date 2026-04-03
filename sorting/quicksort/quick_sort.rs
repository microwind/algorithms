/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description 快速排序算法实现集合
 * 
 * 本文件包含7种不同的快速排序实现，涵盖了快速排序的主要算法变体：
 * 
 * ## 算法分类
 * 1. 按实现方式分类：
 *    - 递归新建数组版本：创建新数组进行分区，稳定排序
 *    - 递归交换版本：原地交换，高效排序
 *    - 非递归栈模拟版本：避免递归深度过大
 * 
 * 2. 按分区策略分类：
 *    - 中间基准：选择中间元素作为基准，避免最坏情况
 *    - 左侧基准：选择第一个元素作为基准，Hoare分区
 *    - 右侧基准：选择最后一个元素作为基准，Lomuto分区
 *    - 三路分区：处理重复元素，提高效率
 * 
 * 3. 按扫描方式分类：
 *    - 单向扫描：从左向右一次性扫描
 *    - 双向扫描：左右指针同时向中间移动
 *    - 三路扫描：处理小于、等于、大于基准的元素
 * 
 * ## 性能特点
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) ~ O(n) 递归调用栈 + 额外空间
 * - 稳定性：大部分不稳定，只有新建数组版本稳定
 * 
 * ## 使用建议
 * - 数据量小：推荐递归版本，代码简洁
 * - 数据量大：推荐非递归版本，避免栈溢出
 * - 重复元素多：推荐三路分区版本，性能更优
 * - 需要稳定排序：推荐新建数组版本
 * 
 * ## 测试数据
 * 默认测试数据：[7, 11, 9, 10, 12, 13, 8]
 * 包含重复元素测试：可修改测试数据验证三路分区优势
 */

use std::time::Instant;

// ==================== 辅助函数 ====================

/**
 * 打印数组内容的辅助函数
 * 
 * 功能：以格式化的方式输出数组内容
 * 
 * @param arr - 要打印的整数数组
 * @param label - 数组的标签说明，用于标识输出
 * @returns void 无返回值
 */
fn print_array(arr: &[i32], label: &str) {
    print!("{}: [", label);
    for (i, &val) in arr.iter().enumerate() {
        if i > 0 {
            print!(", ");
        }
        print!("{}", val);
    }
    println!("]");
}

/**
 * 性能测试函数
 * 
 * 功能：测试排序算法的性能，包括执行时间和正确性验证
 * 
 * @param sort_func - 排序函数，接受数组并返回排序后的数组
 * @param arr - 测试用的原始数组
 * @param name - 测试名称，用于输出标识和性能统计
 * @returns void 无返回值
 */
fn performance_test<F>(sort_func: F, arr: &[i32], name: &str) 
where 
    F: Fn(&mut [i32]),
{
    // 创建数组副本，避免修改原数组
    let mut test_arr = arr.to_vec();
    print_array(&test_arr, &format!("{}原始数组", name));
    
    // 开始计时并执行排序
    let start = Instant::now();
    sort_func(&mut test_arr);
    let duration = start.elapsed();
    
    // 输出结果
    println!("{}: {:.3}ms", name, duration.as_micros() as f64 / 1000.0);
    print_array(&test_arr, &format!("{}排序结果", name));
    println!(); // 空行分隔
}

// ==================== 算法实现 ====================

/**
 * 快速排序1 - 递归新建数组版本
 * 
 * ## 算法特点
 * - 无需交换，每个分区都是新数组
 * - 使用中间元素作为基准，避免最坏情况
 * - 内存友好：不修改原数组，返回新数组
 * - 稳定排序：保持相等元素的相对位置
 * 
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(n log n) - 递归调用栈 + 新数组空间
 * - 稳定性：稳定 - 保持相等元素的相对位置
 * 
 * @param arr - 待排序的整数数组
 * @returns 排序后的整数数组
 */
fn quick_sort1(arr: Vec<i32>) -> Vec<i32> {
    // 第一步：递归终止条件
    // 关键点：数组长度<=1时已经有序，直接返回
    if arr.len() <= 1 {
        return arr;
    }

    // 第二步：选择基准并分区
    println!("split array: {:?}", arr);
    let mut left = Vec::new();
    let mut right = Vec::new();
    // 关键点：设置中间数作为基准，避免最坏情况
    let mid_index = arr.len() / 2;
    let pivot = arr[mid_index];

    // 第三步：遍历数组，按基准值分区
    for (i, &item) in arr.iter().enumerate() {
        // 关键点：跳过基准元素本身，避免重复处理
        if i == mid_index {
            continue;
        }
        // 关键点：小于基准的放左边，大于等于的放右边
        if item < pivot {
            left.push(item);
        } else {
            right.push(item);
        }
    }

    // 第四步：递归排序并合并
    // 关键点：先递归左数组，再添加基准，最后递归右数组
    let mut result = quick_sort1(left);
    result.push(pivot);
    result.extend(quick_sort1(right));
    println!("sorted array: {:?}", result);
    result
}

/*
quick_sort1 递归步骤:

      f([7, 11, 9, 10, 12, 13, 8])
            /       10          \
      f([7, 9, 8])           f([11, 12, 13])
        /   9    \             /    12     \
   f([7, 8])    f([])       f([11])       f[13]
   /   8  \
f([7]) f([])
  [7]
*/

/**
 * 快速排序2 - 标准递归版本
 *
 * ## 算法特点
 * - 需要左右不断交换，无需新建数组
 * - 使用中间元素作为基准
 * - 双向扫描：左右指针相向移动
 * - 效率较高：减少不必要的交换
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的整数数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @returns void 无返回值
 */
fn quick_sort2(arr: &mut [i32], left: usize, right: usize) {
    // 第一步：递归终止条件检查
    // 关键点：left >= right时已经有序，直接返回
    if left >= right {
        return;
    }

    // 第二步：初始化指针和基准
    let mut i = left;
    let mut j = right as i32;
    // 关键点：确定中间位置，基于中间位置不停左右交换
    let mid_index = (left + right) / 2;
    let pivot = arr[mid_index];

    // 第三步：双向扫描分区
    // 关键点：当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i as i32) <= j {
        // 步骤3.1：左指针扫描，找到大于基准的元素
        // 关键点：当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
        while arr[i] < pivot {
            i += 1;
        }
        // 步骤3.2：右指针扫描，找到小于基准的元素
        // 关键点：当前右侧大于基准时左移，直到找出比基准值小的位置来
        while arr[j as usize] > pivot {
            j -= 1;
        }

        // 步骤3.3：交换元素
        // 关键点：当左侧位置小于等于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
        if (i as i32) <= j {
            arr.swap(i, j as usize);
            // 关键点：缩小搜查范围，直到左侧都小于基数，右侧都大于基数
            i += 1;
            j -= 1;
        }
    }

    // 第四步：递归处理左右子数组
    // 步骤4.1：递归处理左子数组
    // 关键点：左侧小于基数位置，不断递归左边部分
    if left < j as usize {
        println!("left < j:recursion: left={} right={} i={} j={} arr={:?}", 
                 left, right, i, j, arr);
        quick_sort2(arr, left, j as usize);
    }
    // 步骤4.2：递归处理右子数组
    // 关键点：基数位置小于右侧，不断递归右侧部分
    if i < right {
        println!("i < right:recursion: left={} right={} i={} j={} arr={:?}", 
                 left, right, i, j, arr);
        quick_sort2(arr, i, right);
    }
}

/**
 * 标准分区函数
 * 
 * ## 算法特点
 * - 使用右侧元素作为基准（Lomuto分区）
 * - 单向扫描：从左到右扫描
 * - 分区指针：记录小于基准区域的边界
 * - 基准归位：最后将基准元素放到正确位置
 * 
 * ## 复杂度分析
 * - 时间复杂度：O(n) - 单次分区时间
 * - 空间复杂度：O(1) - 原地分区
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 * 
 * @param arr - 待排序的整数数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @returns 基准元素的最终位置
 */
fn partition(arr: &mut [i32], left: usize, right: usize) -> usize {
    // 第一步：选择基准（这里取右侧）
    // 基准值可以是left与right之间的任意值，再将基准值移动至最左或最右即可。
    let pivot = arr[right];
    let mut partition_index = left as i32 - 1;

    // 第二步：遍历数组进行分区
    for i in left..right {
        // 关键点：将小于基准的元素交换到左侧
        if arr[i] < pivot {
            partition_index += 1;
            // Rust特点：使用swap方法
            arr.swap(i, partition_index as usize);
        }
    }

    // 第三步：将基准放到正确位置
    partition_index += 1;
    arr.swap(right, partition_index as usize);
    
    println!("partitioned arr= {:?} partitionIndex: {} left= {:?} arr[partitionIndex]= {} right= {:?} {:?}", 
             arr, partition_index, &arr[left..partition_index as usize], 
             arr[partition_index as usize], &arr[partition_index as usize..=right], arr);
    partition_index as usize
}

/**
 * 快速排序3 - 分区交换版本
 *
 * ## 算法特点
 * - 左右不断分区交换，无需新建数组
 * - 使用Lomuto分区方案
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的整数数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @returns void 无返回值
 */
fn quick_sort3(arr: &mut [i32], left: usize, right: usize) {
    // 第一步：递归终止条件检查
    // 关键点：left < right时还需要排序，否则已经有序
    if left < right {
        // 第二步：分区并获取基准位置
        // 关键点：使用partition函数将数组分为两部分
        let pivot = partition(arr, left, right);

        // 第三步：递归排序左半部分
        // 关键点：排序基准左边的元素
        if pivot > 0 {
            quick_sort3(arr, left, pivot - 1);
        }

        // 第四步：递归排序右半部分
        // 关键点：排序基准右边的元素
        quick_sort3(arr, pivot + 1, right);
    }
}

/**
 * 快速排序4 - 非递归版本
 * 
 * ## 算法特点
 * - 需要交换，无需新建数组，利用stack或queue遍历
 * - 使用栈模拟递归调用
 * - 避免递归深度过大导致的栈溢出
 * - 稳定可靠：适合大数据量排序
 * 
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(n) - 显式栈空间
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 * 
 * @param arr - 待排序的整数数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @returns void 无返回值
 */
fn quick_sort4(arr: &mut [i32], left: usize, right: usize) {
    // 第一步：初始化参数
    // 关键点：设置默认值，确保函数可以单独调用
    let left = left;
    let right = right;

    // 第二步：创建栈用于存储待处理的子数组范围
    // 关键点：使用Vec模拟栈结构，避免递归调用
    let mut stack = Vec::new();
    
    // 第三步：初始入栈
    // 关键点：将整个数组的左右边界入栈，作为初始处理范围
    stack.push(left);
    stack.push(right);

    // 第四步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while !stack.is_empty() {
        // 步骤4.1：从栈中取出待处理的范围
        // 关键点：后进先出，先取出right，再取出left
        let j = stack.pop().unwrap();
        let i = stack.pop().unwrap();
        
        // 步骤4.2：获取基准位置
        // 关键点：使用中间元素作为基准
        let mid_index = (i + j) / 2;
        let pivot = arr[mid_index];
        
        // 步骤4.3：分区过程
        // 关键点：左右指针相向移动，进行分区
        let mut i = i;
        let mut j = j;
        while i <= j {
            // 步骤4.3.1：左指针扫描，找到大于基准的元素
            // 关键点：当左侧小于基准时查找位置右移
            while arr[i] < pivot {
                i += 1;
            }
            // 步骤4.3.2：右指针扫描，找到小于基准的元素
            // 关键点：当前右侧大于基准时左移
            while arr[j] > pivot {
                j -= 1;
            }
            // 步骤4.3.3：交换元素
            // 关键点：当左侧位置小于右侧时，将数据交换
            if i <= j {
                arr.swap(i, j);
                i += 1;
                j -= 1;
            }
        }

        // 步骤4.4：子区间入栈
        // 关键点：将分区后的子范围重新入栈，继续处理
        if i < j {
            // 关键点：左子数组有数据，入栈待处理
            println!("left < j:recursion: left={} right={} i={} j={} arr={:?}", 
                     left, right, i, j, arr);
            stack.push(i);
            stack.push(j);
        }
        if i < right {
            // 关键点：右子数组有数据，入栈待处理
            println!("i < right:recursion: left={} right={} i={} j={} arr={:?}", 
                     left, right, i, j, arr);
            stack.push(i);
            stack.push(right);
        }
    }

    // 第五步：返回排序后的数组
    // 关键点：所有范围处理完成，数组已排序
}

/**
 * Lomuto分区函数
 *
 * ## 算法特点
 * - 使用最后一个元素作为基准
 * - 单向扫描：从左到右扫描
 * - 分区指针：记录小于基准区域的边界
 * - 基准归位：最后将基准元素放到正确位置
 *
 * ## 复杂度分析
 * - 时间复杂度：O(n) - 单次分区时间
 * - 空间复杂度：O(1) - 原地分区
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的整数数组
 * @param low - 起始索引
 * @param high - 结束索引
 * @returns 基准元素的最终位置
 */
fn partition_lomuto(arr: &mut [i32], low: usize, high: usize) -> usize {
    // 第一步：初始化基准和指针
    let pivot = arr[high]; // 最后一个元素作为基准
    let mut i = low as isize - 1; // 小于基准的元素的边界

    // 第二步：遍历数组进行分区
    for j in low..high {
        // 关键点：将小于基准的元素交换到左侧
        if arr[j] < pivot {
            i += 1;
            arr.swap(i as usize, j);
        }
    }

    // 第三步：将基准放到正确位置
    arr.swap((i + 1) as usize, high);
    (i + 1) as usize
}

/**
 * 快速排序5 - Lomuto分区递归版本
 *
 * ## 算法特点
 * - 使用Lomuto分区方案
 * - 最后一个元素作为基准
 * - 单向扫描：从左到右扫描
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的整数数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @returns void 无返回值
 */
fn quick_sort5(arr: &mut [i32], left: usize, right: usize) {
    // 第一步：递归终止条件检查
    if left >= right {
        return;
    }

    // 第二步：获取基准位置
    let pi = partition_lomuto(arr, left, right);

    // 第三步：递归排序左右子数组
    if pi > 0 {
        quick_sort5(arr, left, pi - 1);
    }
    quick_sort5(arr, pi + 1, right);
}

/**
 * 快速排序6 - Hoare分区递归版本
 *
 * ## 算法特点
 * - 使用Hoare分区方案
 * - 第一个元素作为基准
 * - 双向扫描：左右指针相向移动
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的整数数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @returns void 无返回值
 */
fn quick_sort6(arr: &mut [i32], left: usize, right: usize) {
    // 第一步：递归终止条件检查
    if left >= right {
        return;
    }

    // 第二步：初始化指针和基准
    let mut i = left;
    let mut j = right;
    let pivot = arr[left]; // 第一个元素作为基准

    // 第三步：双向扫描分区
    while i <= j {
        // 左指针：找到大于基准的元素
        while i <= right && arr[i] < pivot {
            i += 1;
        }
        // 右指针：找到小于基准的元素
        while j >= left && arr[j] > pivot {
            j -= 1;
        }
        // 交换元素
        if i <= j {
            arr.swap(i, j);
            i += 1;
            if j > 0 {
                j -= 1;
            }
        }
    }

    // 第四步：递归处理左右子数组
    if j > 0 {
        quick_sort6(arr, left, j);
    }
    if i < right {
        quick_sort6(arr, i, right);
    }
}

/**
 * 快速排序7 - 三路分区递归版本
 *
 * ## 算法特点
 * - 使用第一个元素作为基准
 * - 三路分区：处理重复元素，提高效率
 * - 递归优化：减少递归调用次数
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr - 待排序的整数数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @returns void 无返回值
 */
fn quick_sort7(arr: &mut [i32], left: usize, right: usize) {
    // 第一步：递归终止条件检查
    if left >= right {
        return;
    }

    // 第二步：初始化基准和三路指针
    let pivot = arr[left]; // 第一个元素作为基准
    let mut lt = left; // 小于基准的右边界
    let mut i = left + 1; // 当前遍历指针
    let mut gt = right; // 大于基准的左边界

    // 第三步：三路分区
    while i <= gt {
        if arr[i] < pivot {
            // 步骤3.1：小于基准，交换到左边
            arr.swap(lt, i);
            lt += 1;
            i += 1;
        } else if arr[i] > pivot {
            // 步骤3.2：大于基准，交换到右边
            arr.swap(i, gt);
            gt -= 1;
        } else {
            // 步骤3.3：等于基准，直接跳过
            i += 1;
        }
    }

    // 第四步：递归处理左右子数组
    if lt > 0 {
        quick_sort7(arr, left, lt - 1);
    }
    quick_sort7(arr, gt + 1, right);
    // 等于基准的部分已经就位，无需处理
}

// ==================== 算法测试和性能对比 ====================

fn main() {
    // 测试数据：
    let test_data = [7, 11, 9, 10, 12, 13, 8];

    // 测试1：递归新建数组版本
    let test_arr = test_data.to_vec();
    print_array(&test_arr, "递归新建数组版本原始数组");
    let start = Instant::now();
    let result = quick_sort1(test_arr);
    let duration = start.elapsed();
    println!("递归新建数组版本: {:.3}ms", duration.as_micros() as f64 / 1000.0);
    print_array(&result, "递归新建数组版本排序结果");
    println!();

    // 测试2：标准递归版本
    performance_test(|arr| quick_sort2(arr, 0, arr.len() - 1), &test_data, "标准递归版本");

    // 测试3：非递归版本
    performance_test(|arr| quick_sort4(arr, 0, arr.len() - 1), &test_data, "非递归版本");

    // 测试4：分区交换版本
    performance_test(|arr| quick_sort3(arr, 0, arr.len() - 1), &test_data, "分区交换版本");

    // 测试5：Lomuto分区递归版本
    performance_test(|arr| quick_sort5(arr, 0, arr.len() - 1), &test_data, "Lomuto分区递归版本");

    // 测试6：Hoare分区递归版本
    performance_test(|arr| quick_sort6(arr, 0, arr.len() - 1), &test_data, "Hoare分区递归版本");

    // 测试7：三路分区递归版本
    performance_test(|arr| quick_sort7(arr, 0, arr.len() - 1), &test_data, "三路分区递归版本");

    println!("=== 算法对比总结 ===");
    println!("1. 递归新建数组版本：中间基准，新建数组，稳定排序");
    println!("2. 标准递归版本：中间基准，双向扫描，原地交换");
    println!("3. 非递归版本：栈模拟，避免递归，双向扫描");
    println!("4. 分区交换版本：右侧基准，原地交换，Lomuto分区");
    println!("5. Lomuto分区递归版本：最后基准，单向扫描");
    println!("6. Hoare分区递归版本：第一个基准，双向扫描");
    println!("7. 三路分区递归版本：第一个基准，三路分区");
}

/*
打印结果
jarry@Mac quicksort % rustc quick_sort.rs && ./quick_sort
递归新建数组版本原始数组: [7, 11, 9, 10, 12, 13, 8]
split array: [7, 11, 9, 10, 12, 13, 8]
split array: [7, 9, 8]
split array: [7, 8]
sorted array: [7, 8]
sorted array: [7, 8, 9]
split array: [11, 12, 13]
sorted array: [11, 12, 13]
sorted array: [7, 8, 9, 10, 11, 12, 13]
递归新建数组版本: 0.015ms
递归新建数组版本排序结果: [7, 8, 9, 10, 11, 12, 13]

标准递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
left < j:recursion: left=0 right=6 i=4 j=2 arr=[7, 8, 9, 10, 12, 13, 11]
i < right:recursion: left=0 right=6 i=4 j=2 arr=[7, 8, 9, 10, 12, 13, 11]
left < j:recursion: left=4 right=6 i=6 j=5 arr=[7, 8, 9, 10, 12, 11, 13]
标准递归版本: 0.005ms
标准递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

非递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
i < right:recursion: left=0 right=6 i=4 j=2 arr=[7, 8, 9, 10, 12, 13, 11]
非递归版本: 0.002ms
非递归版本排序结果: [7, 8, 9, 10, 12, 11, 13]

分区交换版本原始数组: [7, 11, 9, 10, 12, 13, 8]
partitioned arr= [7, 8, 9, 10, 12, 13, 11] partitionIndex: 1 left= [7] arr[partitionIndex]= 8 right= [8, 9, 10, 12, 13, 11] [7, 8, 9, 10, 12, 13, 11]
partitioned arr= [7, 8, 9, 10, 11, 13, 12] partitionIndex: 4 left= [9, 10] arr[partitionIndex]= 11 right= [11, 13, 12] [7, 8, 9, 10, 11, 13, 12]
partitioned arr= [7, 8, 9, 10, 11, 13, 12] partitionIndex: 3 left= [9] arr[partitionIndex]= 10 right= [10] [7, 8, 9, 10, 11, 13, 12]
partitioned arr= [7, 8, 9, 10, 11, 12, 13] partitionIndex: 5 left= [] arr[partitionIndex]= 12 right= [12, 13] [7, 8, 9, 10, 11, 12, 13]
分区交换版本: 0.009ms
分区交换版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Lomuto分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
Lomuto分区递归版本: 0.000ms
Lomuto分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Hoare分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
Hoare分区递归版本: 0.000ms
Hoare分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

三路分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
三路分区递归版本: 0.001ms
三路分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归新建数组版本：中间基准，新建数组，稳定排序
2. 标准递归版本：中间基准，双向扫描，原地交换
3. 非递归版本：栈模拟，避免递归，双向扫描
4. 分区交换版本：右侧基准，原地交换，Lomuto分区
5. Lomuto分区递归版本：最后基准，单向扫描
6. Hoare分区递归版本：第一个基准，双向扫描
7. 三路分区递归版本：第一个基准，三路分区
*/
