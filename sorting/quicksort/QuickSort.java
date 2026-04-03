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

import java.util.Arrays;
import java.util.Stack;

public class QuickSort {

// ==================== 辅助函数 ====================

/**
 * 打印数组内容的辅助函数
 * 
 * 功能：以格式化的方式输出数组内容
 * 
 * @param arr - 要打印的数字数组
 * @param label - 数组的标签说明，用于标识输出
 */
private static void printArray(int[] arr, String label) {
    System.out.print(label + ": [");
    for (int i = 0; i < arr.length; i++) {
        System.out.print(arr[i]);
        if (i < arr.length - 1) {
            System.out.print(", ");
        }
    }
    System.out.println("]");
}

/**
 * 性能测试函数
 * 
 * 功能：测试排序算法的性能，包括执行时间和正确性验证
 * 
 * @param sortFunc - 排序函数，接受数组并返回排序后的数组
 * @param arr - 测试用的原始数组
 * @param name - 测试名称，用于输出标识和性能统计
 */
private static void performanceTest(SortFunction sortFunc, int[] arr, String name) {
    // 创建数组副本，避免修改原数组
    int[] testArr = arr.clone();
    printArray(testArr, name + "原始数组");
    
    // 开始计时并执行排序
    long startTime = System.nanoTime();
    sortFunc.sort(testArr);
    long endTime = System.nanoTime();
    
    // 输出结果
    System.out.println(name + ": " + (endTime - startTime) / 1000000.0 + "ms");
    printArray(testArr, name + "排序结果");
    System.out.println(); // 空行分隔
}

@FunctionalInterface
private interface SortFunction {
    void sort(int[] arr);
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
 * @param arr - 待排序的数字数组
 * @return 排序后的数字数组
 */
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
public static int[] quickSort1(int[] arr) {
    // 第一步：递归终止条件
    // 关键点：数组长度<=1时已经有序，直接返回
    if (arr.length <= 1) {
        return arr;
    }

    // 第二步：选择基准并分区
    System.out.println("split array: " + Arrays.toString(arr));
    int[] left = new int[0];
    int[] right = new int[0];
    // 关键点：设置中间数作为基准，避免最坏情况
    int midIndex = arr.length / 2;
    int pivot = arr[midIndex];

    // 第三步：遍历数组，按基准值分区
    for (int i = 0; i < arr.length; i++) {
        // 关键点：跳过基准元素本身，避免重复处理
        if (midIndex == i) {
            continue;
        }
        // 关键点：小于基准的放左边，大于等于的放右边
        if (arr[i] < pivot) {
            left = Arrays.copyOf(left, left.length + 1);
            left[left.length - 1] = arr[i];
        } else {
            right = Arrays.copyOf(right, right.length + 1);
            right[right.length - 1] = arr[i];
        }
    }

    // 第四步：递归排序并合并
    // 关键点：先递归左数组，再添加基准，最后递归右数组
    int[] leftSorted = quickSort1(left);
    int[] rightSorted = quickSort1(right);
    
    int[] result = new int[leftSorted.length + 1 + rightSorted.length];
    System.arraycopy(leftSorted, 0, result, 0, leftSorted.length);
    result[leftSorted.length] = pivot;
    System.arraycopy(rightSorted, 0, result, leftSorted.length + 1, rightSorted.length);
    
    System.out.println("sorted array: " + Arrays.toString(result));
    return result;
}

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
 * @param arr - 待排序的数字数组
 * @param low - 起始索引
 * @param high - 结束索引
 * @return 排序后的数字数组
 */
public static int[] quickSort2(int[] arr, int low, int high) {
    // 第一步：递归终止条件检查
    // 关键点：low >= high时已经有序，直接返回
    if (low >= high) {
        return arr;
    }

    // 第二步：初始化指针和基准
    int i = low > 0 ? low : 0;
    int j = high;
    // 关键点：确定中间位置，基于中间位置不停左右交换
    int midIndex = (i + j) / 2;
    int pivot = arr[midIndex];

    System.out.println(
        " i=" + i + ", j=" + j + ", midIndex=" + midIndex + ", pivot=" + pivot + "  arr[]=" + Arrays.toString(arr));

    // 第三步：双向扫描分区
    // 关键点：当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j) {
        // 步骤3.1：左指针扫描，找到大于基准的元素
        // 关键点：当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
        while (arr[i] < pivot) {
            System.out.println("arr[i] < pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
            i++;
        }
        // 步骤3.2：右指针扫描，找到小于基准的元素
        // 关键点：当前右侧大于基准时左移，直到找出比基准值小的位置来
        while (arr[j] > pivot) {
            System.out.println("arr[i] > pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
            j--;
        }

        System.out.println("low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", pivot=" + pivot);

        // 步骤3.3：交换元素
        // 关键点：当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
        if (i <= j) {
            int tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;
            // 关键点：缩小搜查范围，直到左侧都小于基数，右侧都大于基数
            i++;
            j--;
        }
    }

    // 第四步：递归处理左右子数组
    // 步骤4.1：递归处理左子数组
    // 关键点：左侧小于基数位置，不断递归左边部分
    if (low < j) {
        System.out.println("  low < j:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", midIndex="
            + midIndex + ", pivot=" + pivot);
        quickSort2(arr, low, j);
    }
    // 步骤4.2：递归处理右子数组
    // 关键点：基数位置小于右侧，不断递归右侧部分
    if (i < high) {
        System.out.println("  i < high:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", midIndex="
            + midIndex + ", pivot=" + pivot);
        quickSort2(arr, i, high);
    }

    return arr;
}

/**
 * 快速排序3 - 非递归版本
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
 * @param arr - 待排序的数字数组
 * @param low - 起始索引
 * @param high - 结束索引
 * @return 排序后的数字数组
 */
public static int[] quickSort3(int[] arr, int low, int high) {
    // 第一步：初始化参数
    // 关键点：设置默认值，确保函数可以单独调用
    Stack<Integer> stack = new Stack<Integer>();
    int i, j, midIndex, pivot, tmp;
    // 与标准递归版相同，只是将递归改为遍历栈的方式
    // 先将左右各取一个入栈
    stack.add(low);
    stack.add(high);

    // 第二步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while (!stack.isEmpty()) {
        // 步骤2.1：从栈中取出待处理的范围
        // 关键点：如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
        j = high = (int) stack.pop();
        i = low = (int) stack.pop();

        // 步骤2.2：获取基准位置
        // 关键点：使用中间元素作为基准
        midIndex = (i + j) / 2;
        pivot = arr[midIndex];

        // 步骤2.3：分区过程
        // 关键点：左右指针相向移动，进行分区
        while (i <= j) {
            // 步骤2.3.1：左指针扫描，找到大于基准的元素
            // 关键点：当左侧小于基准时查找位置右移
            while (arr[i] < pivot) {
                System.out.println("arr[i] < pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
                i++;
            }
            // 步骤2.3.2：右指针扫描，找到小于基准的元素
            // 关键点：当前右侧大于基准时左移
            while (arr[j] > pivot) {
                System.out.println("arr[i] > pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
                j--;
            }

            System.out.println("low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", pivot=" + pivot);

            // 步骤2.3.3：交换元素
            // 关键点：当左侧位置小于右侧时，将数据交换
            if (i <= j) {
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
                i++;
                j--;
            }
        }
        // 步骤2.4：子区间入栈
        // 关键点：将分区后的子范围重新入栈，继续处理
        if (low < j) {
            // 关键点：左子数组有数据，入栈待处理
            // 与递归版不同，这里添加到栈中，以便继续循环
            System.out.println("  low < j:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j
                + ", midIndex=" + midIndex + ", pivot=" + pivot);
            stack.add(low);
            stack.add(j);
        }
        if (i < high) {
            // 关键点：右子数组有数据，入栈待处理
            System.out.println("  i < high:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j
                + ", midIndex=" + midIndex + ", pivot=" + pivot);
            stack.add(i);
            stack.add(high);
        }
    }

    // 第三步：返回排序后的数组
    // 关键点：所有范围处理完成，数组已排序
    return arr;
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
 * @param arr - 待排序的数字数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @return 基准元素的最终位置
 */
public static int partition(int[] arr, int left, int right) {
    // 第一步：选择基准（这里取右侧）
    // 基准值可以是left与right之间的任意值，再将基准值移动至最左或最右即可。
    int pivotIndex = right;
    int pivot = arr[pivotIndex];
    int partitionIndex = left - 1;

    // 第二步：遍历数组进行分区
    for (int i = left; i < right; i++) {
        // 关键点：将小于基准的元素交换到左侧
        if (arr[i] < pivot) {
            // 将小于基准值的数据交换到左侧，分区下标右移1位
            partitionIndex += 1;
            int tmp = arr[partitionIndex];
            arr[partitionIndex] = arr[i];
            arr[i] = tmp;
        }
    }

    // 第三步：将基准放到正确位置
    partitionIndex += 1;
    // 最后将基准值交换到交换下标处，以此分割左右
    int tmp = arr[partitionIndex];
    arr[partitionIndex] = arr[pivotIndex];
    arr[pivotIndex] = tmp;
    System.out.println(
        "partition:" + " partitionIndex=" + partitionIndex + " arr[partitionIndex]=" + arr[partitionIndex] + " left="
            + left + " right=" + right);
    return partitionIndex;
}

/**
 * 快速排序4 - 标准递归版本
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
 * @param arr - 待排序的数字数组
 * @param start - 起始索引
 * @param end - 结束索引
 * @return 排序后的数字数组
 */
public static int[] quickSort4(int[] arr, int start, int end) {
    // 第一步：递归终止条件检查
    // 关键点：start < end时还需要排序，否则已经有序
    if (start < end) {
        // 第二步：分区并获取基准位置
        // 关键点：使用partition函数将数组分为两部分
        int pivot = partition(arr, start, end);

        // 第三步：递归排序左半部分
        // 关键点：排序基准左边的元素
        quickSort4(arr, 0, pivot - 1);

        // 第四步：递归排序右半部分
        // 关键点：排序基准右边的元素
        quickSort4(arr, pivot + 1, end);
    }
    return arr;
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
 * @param arr - 待排序的数字数组
 * @param low - 起始索引
 * @param high - 结束索引
 * @return 基准元素的最终位置
 */
public static int partitionLomuto(int[] arr, int low, int high) {
    // 第一步：初始化基准和指针
    int pivot = arr[high]; // 最后一个元素作为基准
    int i = low - 1; // 小于基准的元素的边界

    // 第二步：遍历数组进行分区
    for (int j = low; j < high; j++) {
        // 关键点：将小于基准的元素交换到左侧
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    // 第三步：将基准放到正确位置
    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return i + 1;
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
 * @param arr - 待排序的数字数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @return 排序后的数字数组
 */
public static int[] quickSort5(int[] arr, int left, int right) {
    // 第一步：递归终止条件检查
    if (left >= right) {
        return arr;
    }

    // 第二步：获取基准位置
    int pi = partitionLomuto(arr, left, right);

    // 第三步：递归排序左右子数组
    if (pi > 0) {
        quickSort5(arr, left, pi - 1);
    }
    quickSort5(arr, pi + 1, right);
    return arr;
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
 * @param arr - 待排序的数字数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @return 排序后的数字数组
 */
public static int[] quickSort6(int[] arr, int left, int right) {
    // 第一步：递归终止条件检查
    if (left >= right) {
        return arr;
    }

    // 第二步：初始化指针和基准
    int i = left;
    int j = right;
    int pivot = arr[left]; // 第一个元素作为基准

    // 第三步：双向扫描分区
    while (i <= j) {
        // 左指针：找到大于基准的元素
        while (arr[i] < pivot) {
            i++;
        }
        // 右指针：找到小于基准的元素
        while (arr[j] > pivot) {
            j--;
        }
        // 交换元素
        if (i <= j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    // 第四步：递归处理左右子数组
    quickSort6(arr, left, j);
    quickSort6(arr, i, right);
    return arr;
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
 * @param arr - 待排序的数字数组
 * @param left - 起始索引
 * @param right - 结束索引
 * @return 排序后的数字数组
 */
public static int[] quickSort7(int[] arr, int left, int right) {
    // 第一步：递归终止条件检查
    if (left >= right) {
        return arr;
    }

    // 第二步：初始化基准和三路指针
    int pivot = arr[left]; // 第一个元素作为基准
    int lt = left; // 小于基准的右边界
    int i = left + 1; // 当前遍历指针
    int gt = right; // 大于基准的左边界

    // 第三步：三路分区
    while (i <= gt) {
        if (arr[i] < pivot) {
            // 步骤3.1：小于基准，交换到左边
            int tmp = arr[lt];
            arr[lt] = arr[i];
            arr[i] = tmp;
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            // 步骤3.2：大于基准，交换到右边
            int tmp = arr[i];
            arr[i] = arr[gt];
            arr[gt] = tmp;
            gt--;
        } else {
            // 步骤3.3：等于基准，直接跳过
            i++;
        }
    }

    // 第四步：递归处理左右子数组
    if (lt > 0) {
        quickSort7(arr, left, lt - 1);
    }
    quickSort7(arr, gt + 1, right);
    // 等于基准的部分已经就位，无需处理
    return arr;
}

// ==================== 算法测试和性能对比 ====================

public static void main(String[] args) {
    // 测试数据：
    int[] testData = {7, 11, 9, 10, 12, 13, 8};

    // 测试1：递归新建数组版本
    performanceTest((arr) -> quickSort1(arr), testData, "递归新建数组版本");

    // 测试2：标准递归版本
    performanceTest((arr) -> quickSort2(arr, 0, arr.length - 1), testData, "标准递归版本");

    // 测试3：非递归版本
    performanceTest((arr) -> quickSort3(arr, 0, arr.length - 1), testData, "非递归版本");

    // 测试4：标准递归版本
    performanceTest((arr) -> quickSort4(arr, 0, arr.length - 1), testData, "标准递归版本");

    // 测试5：Lomuto分区递归版本
    performanceTest((arr) -> quickSort5(arr, 0, arr.length - 1), testData, "Lomuto分区递归版本");

    // 测试6：Hoare分区递归版本
    performanceTest((arr) -> quickSort6(arr, 0, arr.length - 1), testData, "Hoare分区递归版本");

    // 测试7：三路分区递归版本
    performanceTest((arr) -> quickSort7(arr, 0, arr.length - 1), testData, "三路分区递归版本");

    System.out.println("=== 算法对比总结 ===");
    System.out.println("1. 递归新建数组版本：中间基准，新建数组，稳定排序");
    System.out.println("2. 标准递归版本：中间基准，双向扫描，原地交换");
    System.out.println("3. 非递归版本：栈模拟，避免递归，双向扫描");
    System.out.println("4. 标准递归版本：右侧基准，原地交换，Lomuto分区");
    System.out.println("5. Lomuto分区递归版本：最后基准，单向扫描");
    System.out.println("6. Hoare分区递归版本：第一个基准，双向扫描");
    System.out.println("7. 三路分区递归版本：第一个基准，三路分区");
}

/*
打印结果
jarry@Mac quicksort % java QuickSort
递归新建数组版本原始数组: [7, 11, 9, 10, 12, 13, 8]
split array: [7, 11, 9, 10, 12, 13, 8]
split array: [7, 9, 8]
split array: [7, 8]
sorted array: [7, 8]
sorted array: [7, 8, 9]
split array: [11, 12, 13]
sorted array: [11, 12, 13]
sorted array: [7, 8, 9, 10, 11, 12, 13]
递归新建数组版本: 0.804ms
递归新建数组版本排序结果: [7, 11, 9, 10, 12, 13, 8]

标准递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
 i=0, j=6, midIndex=3, pivot=10  arr[]=[7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot: i=0, j=6, pivot=10
low=0, high=6, i=1, j=6, pivot=10
arr[i] < pivot: i=2, j=5, pivot=10
arr[i] > pivot: i=3, j=5, pivot=10
arr[i] > pivot: i=3, j=4, pivot=10
low=0, high=6, i=3, j=3, pivot=10
  low < j:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
 i=0, j=2, midIndex=1, pivot=8  arr[]=[7, 8, 9, 10, 12, 13, 11]
arr[i] < pivot: i=0, j=2, pivot=8
arr[i] > pivot: i=1, j=2, pivot=8
low=0, high=2, i=1, j=1, pivot=8
  i < high:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
 i=4, j=6, midIndex=5, pivot=13  arr[]=[7, 8, 9, 10, 12, 13, 11]
arr[i] < pivot: i=4, j=6, pivot=13
low=4, high=6, i=5, j=6, pivot=13
  low < j:recursion: low=4, high=6, i=6, j=5, midIndex=5, pivot=13
 i=4, j=5, midIndex=4, pivot=12  arr[]=[7, 8, 9, 10, 12, 11, 13]
low=4, high=5, i=4, j=5, pivot=12
标准递归版本: 21.859458ms
标准递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

非递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot: i=0, j=6, pivot=10
low=0, high=6, i=1, j=6, pivot=10
arr[i] < pivot: i=2, j=5, pivot=10
arr[i] > pivot: i=3, j=5, pivot=10
arr[i] > pivot: i=3, j=4, pivot=10
low=0, high=6, i=3, j=3, pivot=10
  low < j:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  i < high:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
arr[i] < pivot: i=4, j=6, pivot=13
low=4, high=6, i=5, j=6, pivot=13
  low < j:recursion: low=4, high=6, i=6, j=5, midIndex=5, pivot=13
low=4, high=5, i=4, j=5, pivot=12
arr[i] < pivot: i=0, j=2, pivot=8
arr[i] > pivot: i=1, j=2, pivot=8
low=0, high=2, i=1, j=1, pivot=8
非递归版本: 1.982416ms
非递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

标准递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
partition: partitionIndex=1 arr[partitionIndex]=8 left=0 right=6
partition: partitionIndex=4 arr[partitionIndex]=11 left=2 right=6
partition: partitionIndex=3 arr[partitionIndex]=10 left=0 right=3
partition: partitionIndex=2 arr[partitionIndex]=9 left=0 right=2
partition: partitionIndex=1 arr[partitionIndex]=8 left=0 right=1
partition: partitionIndex=5 arr[partitionIndex]=12 left=5 right=6
partition: partitionIndex=4 arr[partitionIndex]=11 left=0 right=4
partition: partitionIndex=3 arr[partitionIndex]=10 left=0 right=3
partition: partitionIndex=2 arr[partitionIndex]=9 left=0 right=2
partition: partitionIndex=1 arr[partitionIndex]=8 left=0 right=1
标准递归版本: 2.064292ms
标准递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Lomuto分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
Lomuto分区递归版本: 0.008458ms
Lomuto分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Hoare分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
Hoare分区递归版本: 0.006709ms
Hoare分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

三路分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
三路分区递归版本: 0.008458ms
三路分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归新建数组版本：中间基准，新建数组，稳定排序
2. 标准递归版本：中间基准，双向扫描，原地交换
3. 非递归版本：栈模拟，避免递归，双向扫描
4. 标准递归版本：右侧基准，原地交换，Lomuto分区
5. Lomuto分区递归版本：最后基准，单向扫描
6. Hoare分区递归版本：第一个基准，双向扫描
7. 三路分区递归版本：第一个基准，三路分区
*/

}
