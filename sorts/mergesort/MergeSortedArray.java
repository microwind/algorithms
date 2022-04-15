
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
import java.util.*;
public class MergeSortedArray {

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
      // 两两比较，把小的追加到新数组中，同时移动指针
      if (one[i] < two[j]) {
        result[k] = one[i];
        i++;
        k++;
      } else {
        result[k] = two[i];
        j++;
        k++;
      }
    }

    // 复制数组1剩余的项目
    while (i < one.length) {
      result[k] = one[i];
      k++;
      i++;
    }
    // 复制数组2剩余的项目
    while (j < one.length) {
      result[k] = one[j];
      k++;
      j++;
    }
    return result;
  }

  static List<int> mergeSorted2(List<int> one, List<int> two) {
    int twoLen = two.size();
    for (int i = 0; i < one.length; i++) {
      int j = twoLen - 1;
      // 从第1个列表取出一个最小的作为比较项，与第2个列表项自后前往逐个比较
      // 从第2个列表的项如果大于比较项，则统一往后移动一位
      while (one[i] < two[j]) {
        // two.add(j++) = two.add(two[j]);
        j--;
      }

      // 如果比较项比第2列表里的任何一项都要大
      if (j == two.size() - 1) {
        // 则复制列表1的剩余项到列表2，并终止循环
        // two[j++] = one[i];
        // break;
      }

      // 找到第2个列表里比比较项小的位置，把比较项插入到该位置
      two[j+1] = one[i];
      twoLen++;
    }
    // 第2个列表是合并了第1个数组的结果
    return two;
  }

  public static void main(String args[]) {
    int arr1[] = {1, 5, 6, 7, 10};
    int arr2[] = {2, 3, 4, 8, 9};
    System.out.println("mergeSorted1 start:");
    long startTime = System.currentTimeMillis();
    System.out.println(Arrays.toString(mergeSorted1(arr1, arr2)));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    List list1 = Arrays.asList(1, 5, 6, 7, 10);
    List list2 = Arrays.asList(2, 3, 4, 8, 9);
    System.out.println("mergeSorted2 start:");
    long startTime = System.currentTimeMillis();
    System.out.println(mergeSorted2(list1, list2).toString());
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");


  }
  
}
