
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
import java.util.*;

public class MergeSortedArray {

  /** 
   * @desc 新建数组，两两比较移动指针实现已排序数组合并
   */
  static int[] mergeSorted1(int[] one, int[] two) {
    // 新数组长度是两个数组长度之和
    int[] result = new int[one.length + two.length];
    // 数组1下标
    int i = 0;
    // 数组2下标
    int j = 0;
    // 新数组下标
    int k = 0;
    // 两个数组同时遍历，直到一个遍历完成
    while (i < one.length && j < two.length) {
      // 两两比较，把小的项追加到新数组中，同时移动小的那个数组指针
      if (one[i] < two[j]) {
        result[k++] = one[i++];
      } else {
        result[k++] = two[j++];
      }
    }

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
   * @desc 逐个取出1项插入到另外1个已排序数组中去，相当于选择最小项插入到已排序数组中
   * 从第1个数组里依次取出项插入到第2个数组合适位置中，这里采用List以便动态调整
   */
  static List<Integer> mergeSorted2(List<Integer> one, List<Integer> two) {
    int twoLen = two.size();
    for (int i = 0; i < one.size(); i++) {
      int j = 0;
      // 从第1个列表依次取出比较项，与第2个列表项自前往后逐个比较
      while (j < twoLen) {
        // 如果比较项小于第2个数组的某项，则插入到该项前面
        if (one.get(i) < two.get(j)) {
          // 第2个数组扩容1位，将最后1位复制添加到最后，并增加第2个数组长度
          two.add(two.get(twoLen - 1));
          twoLen++;
          int itemIndex = twoLen - 1;
          // 并将第2个数组自j位整体后移1位
          while (itemIndex-- > j) {
            two.set(itemIndex, two.get(itemIndex - 1));
          }
          // 将比较项插入到第2个列表的j位置中
          two.set(j, one.get(i));
          break;
        } else {
          // 如果全部比较完成，数组2里面没有比它还大的，则添加到最后
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
    // 第2个列表是合并了第1个数组的结果
    return two;
  }

  public static void main(String args[]) {
    int arr1[] = { 3, 7, 9, 10, 11, 15, 16 };
    int arr2[] = { 1, 5, 6, 9, 12 };
    System.out.println("mergeSorted1 start:");
    System.out.println("mergeSorted1 origin arr1: " + 
    Arrays.toString(arr1) + " arr2: " + Arrays.toString(arr2));
    long startTime = System.currentTimeMillis();
    System.out.println(Arrays.toString(mergeSorted1(arr1, arr2)));
    System.out.println("\r\ntime:" +
     (System.currentTimeMillis() - startTime) + " ms.");


    List list1 = new ArrayList<>(Arrays.asList(3, 7, 9, 10, 11, 15, 16));
    List list2 = new ArrayList<>(Arrays.asList(1, 5, 6, 9, 12));
    System.out.println("mergeSorted2 start:");
    System.out.println("mergeSorted2 origin list1: " + list1.toString()
     + " list2:" + list2.toString());
    startTime = System.currentTimeMillis();
    System.out.println(mergeSorted2(list1, list2).toString());
    System.out.println("\r\ntime:" + (System.currentTimeMillis() 
    - startTime) + " ms.");

  }

}
