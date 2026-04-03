/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 合并两个已排序数组算法实现
 * 提供三种不同的合并策略，适合不同场景和性能需求
 * 
 * 算法思路：
 * 1. 双指针法：同时遍历两个数组，逐个比较并合并
 * 2. 插入法：将一个数组的元素逐个插入到另一个数组中
 * 3. 合并排序法：先合并数组再进行排序
 * 
 * 时间复杂度：O(n+m) - 双指针法最优
 * 空间复杂度：O(n+m) - 需要额外空间存储结果
 * 稳定性：稳定 - 保持相等元素的相对位置
 */
import java.util.*;

public class MergeSortedArray {

  /**
   * 合并两个已排序数组 - 双指针法
   * 
   * 算法思路：
   * 使用两个指针分别指向两个数组的起始位置，同时遍历比较
   * 将较小的元素放入结果数组，并移动相应指针，直到其中一个数组遍历完成
   * 最后将剩余数组元素直接复制到结果数组中
   * 
   * 步骤1：初始化结果数组和指针
   * 步骤2：同时遍历两个数组，比较并合并
   * 步骤3：处理剩余元素
   * 
   * 关键点：
   * - 使用三个指针分别跟踪两个输入数组和一个结果数组
   * - 比较当前元素，选择较小的放入结果数组
   * - 保持算法的稳定性
   * 
   * 时间复杂度：O(n+m) - 每个元素只被访问一次
   * 空间复杂度：O(n+m) - 需要额外空间存储结果
   * 稳定性：稳定 - 保持相等元素的相对位置
   */
  static int[] mergeSorted1(int[] one, int[] two) {
    // 步骤1：初始化结果数组和指针
    // 关键点：结果数组长度为两个数组长度之和
    int[] result = new int[one.length + two.length];
    int i = 0;  // 数组1下标
    int j = 0;  // 数组2下标
    int k = 0;  // 新数组下标
    
    // 步骤2：同时遍历两个数组，比较并合并
    // 关键点：当两个数组都还有元素时继续比较
    while (i < one.length && j < two.length) {
      // 关键点：两两比较，把小的项追加到新数组中，同时移动小的那个数组指针
      if (one[i] < two[j]) {
        result[k++] = one[i++];
      } else {
        result[k++] = two[j++];
      }
    }

    // 步骤3：处理剩余元素
    // 关键点：将未处理完的数组元素直接复制到结果数组
    // 复制数组1剩余的项目
    while (i < one.length) {
      result[k++] = one[i++];
    }
    // 复制数组2剩余的项目
    while (j < two.length) {
      result[k++] = two[j++];
    }
    return result;
  }

  /**
   * 合并两个已排序数组 - 插入法
   * 
   * 算法思路：
   * 逐个取出第一个数组的元素，插入到第二个数组合适的位置中
   * 使用List数据结构便于动态插入操作
   * 
   * 步骤1：遍历第一个数组的每个元素
   * 步骤2：在第二个数组中找到合适的插入位置
   * 步骤3：插入元素并调整数组结构
   * 
   * 关键点：
   * - 使用List的动态插入特性
   * - 需要移动后续元素为新元素腾出空间
   * - 时间复杂度较高，但空间复杂度较低
   * 
   * 时间复杂度：O(n*m) - 最坏情况下需要遍历所有元素
   * 空间复杂度：O(1) - 在原数组基础上操作
   * 稳定性：稳定 - 保持相等元素的相对位置
   */
  static List<Integer> mergeSorted2(List<Integer> one, List<Integer> two) {
    // 关键点：记录第二个数组的当前长度，避免重复计算
    int twoLen = two.size();
    
    // 步骤1：遍历第一个数组的每个元素
    for (int i = 0; i < one.size(); i++) {
      int j = 0;
      
      // 步骤2：在第二个数组中找到合适的插入位置
      // 关键点：从第1个列表依次取出比较项，与第2个列表项自前往后逐个比较
      while (j < twoLen) {
        // 关键点：如果比较项小于第2个数组的某项，则插入到该项前面
        if (one.get(i) < two.get(j)) {
          // 步骤3：插入元素并调整数组结构
          // 关键点：第2个数组扩容1位，将最后1位复制添加到最后
          two.add(two.get(twoLen - 1));
          twoLen++;
          int itemIndex = twoLen - 1 - 1;

          // 关键点：并将第2个数组自j位整体后移1位
          while (itemIndex > j) {
            two.set(itemIndex, two.get(itemIndex - 1));
            itemIndex--;
          }

          // 关键点：将比较项插入到第2个列表的j位置中
          two.set(j, one.get(i));
          break;
        } else {
          // 关键点：如果全部比较完成，数组2里面没有比它还大的，则添加到最后
          // 也可以一次性添加数组1里面全部剩余项，终止外部的循环
          if (j == twoLen - 1) {
            two.add(one.get(i));
            twoLen++;
            break;
          }
        }
        j++;
      }
    }
    // 关键点：第2个列表是合并了第1个数组的结果
    return two;
  }

  /**
   * 合并两个已排序数组 - 合并排序法
   * 
   * 算法思路：
   * 先将两个数组合并为一个数组，然后使用插入排序算法进行排序
   * 利用第一个数组已经有序的特性，从第二个数组开始排序
   * 
   * 步骤1：合并两个数组到一个新数组
   * 步骤2：使用插入排序算法排序
   * 步骤3：返回排序后的结果
   * 
   * 关键点：
   * - 先合并再排序，逻辑简单
   * - 利用插入排序对部分有序数据的优势
   * - 从第二个数组开始排序，减少不必要的比较
   * 
   * 时间复杂度：O((n+m)²) - 插入排序的时间复杂度
   * 空间复杂度：O(n+m) - 需要额外空间存储合并结果
   * 稳定性：稳定 - 插入排序是稳定算法
   */
  static int[] mergeSorted3(int[] one, int[] two) {
    int oneLen = one.length;
    int twoLen = two.length;
    int[] output = new int[oneLen + twoLen];
    
    // 步骤1：合并两个数组到一个新数组
    // 关键点：直接复制数组元素，无需排序
    for (int i = 0; i < output.length; i++) {
      if (i < oneLen) {
        output[i] = one[i];
      } else {
        output[i] = two[i - oneLen];
      }
    }
    
    // 步骤2：使用插入排序算法排序
    // 关键点：采用任意一种排序算法，这里采用插入算法
    // 前面已排序的无需再排，i从第2个数组开始
    for (int i = oneLen; i < output.length; i++) {
      int j = i;
      int current = output[j];
      
      // 关键点：用未排序的项逐个与左侧已排序项进行对比
      while (j-- > 0 && current < output[j]) {
        // 关键点：如果比较项小于已排序的项，需要将已排序项整体右移
        output[j + 1] = output[j];
      }
      // 关键点：将比较项插入到空出的位置
      output[j + 1] = current;
    }

    // 步骤3：返回排序后的结果
    return output;
  }

  /**
   * 主函数 - 演示三种合并算法
   * 
   * 测试数据：
   * - 第一个数组：[-3, 7, 9, 10, 11, 15, 16]
   * - 第二个数组：[-1, 5, 6, 9, 12]
   * 
   * 预期结果：[-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16]
   */
  public static void main(String args[]) {
    // 测试数据
    int arr1[] = { -3, 7, 9, 10, 11, 15, 16 };
    int arr2[] = { -1, 5, 6, 9, 12 };
    
    // 测试1：双指针法
    System.out.println("=== mergeSorted1 双指针法 ===");
    System.out.println("原始数组1: " + Arrays.toString(arr1));
    System.out.println("原始数组2: " + Arrays.toString(arr2));
    long startTime = System.currentTimeMillis();
    int[] result1 = mergeSorted1(arr1, arr2);
    System.out.println("合并结果: " + Arrays.toString(result1));
    System.out.println("执行时间: " + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println();

    // 测试2：插入法
    List<Integer> list1 = new ArrayList<>(Arrays.asList(-3, 7, 9, 10, 11, 15, 16));
    List<Integer> list2 = new ArrayList<>(Arrays.asList(-1, 5, 6, 9, 12));
    System.out.println("=== mergeSorted2 插入法 ===");
    System.out.println("原始列表1: " + list1.toString());
    System.out.println("原始列表2: " + list2.toString());
    startTime = System.currentTimeMillis();
    List<Integer> result2 = mergeSorted2(list1, list2);
    System.out.println("合并结果: " + result2.toString());
    System.out.println("执行时间: " + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println();

    // 测试3：合并排序法
    int arr3[] = { -3, 7, 9, 10, 11, 15, 16 };
    int arr4[] = { -1, 5, 6, 9, 12 };
    System.out.println("=== mergeSorted3 合并排序法 ===");
    System.out.println("原始数组3: " + Arrays.toString(arr3));
    System.out.println("原始数组4: " + Arrays.toString(arr4));
    startTime = System.currentTimeMillis();
    int[] result3 = mergeSorted3(arr3, arr4);
    System.out.println("合并结果: " + Arrays.toString(result3));
    System.out.println("执行时间: " + (System.currentTimeMillis() - startTime) + " ms.");
    
    // 算法对比总结
    System.out.println();
    System.out.println("=== 算法对比总结 ===");
    System.out.println("1. 双指针法：时间复杂度O(n+m)，空间复杂度O(n+m)，最优选择");
    System.out.println("2. 插入法：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量");
    System.out.println("3. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单");
  }

}

/*打印结果
 jarry@Mac mergesort % java MergeSortedArray.java 
=== mergeSorted1 双指针法 ===
原始数组1: [-3, 7, 9, 10, 11, 15, 16]
原始数组2: [-1, 5, 6, 9, 12]
合并结果: [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16]
执行时间: 0 ms.

=== mergeSorted2 插入法 ===
原始列表1: [-3, 7, 9, 10, 11, 15, 16]
原始列表2: [-1, 5, 6, 9, 12]
合并结果: [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16]
执行时间: 0 ms.

=== mergeSorted3 合并排序法 ===
原始数组3: [-3, 7, 9, 10, 11, 15, 16]
原始数组4: [-1, 5, 6, 9, 12]
合并结果: [-3, -1, 5, 6, 7, 9, 9, 10, 11, 12, 15, 16]
执行时间: 0 ms.

=== 算法对比总结 ===
1. 双指针法：时间复杂度O(n+m)，空间复杂度O(n+m)，最优选择
2. 插入法：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量
3. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单
 */