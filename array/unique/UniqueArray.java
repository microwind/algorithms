/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组去重算法 - Java实现
 *
 * 算法原理：
 * - 通过比较元素，找出数组中只出现一次的元素
 * - 移除或跳过重复出现的元素
 * - 保留元素的相对顺序（取决于具体实现）
 *
 * 本文件提供18种不同的去重实现：
 * - 方法1-5: 双循环比较，在原数组或新数组上操作
 * - 方法6: 使用HashMap去重
 * - 方法7: 使用Stream filter
 * - 方法8-10: 使用Set数据结构（HashSet、LinkedHashSet、TreeSet）
 * - 方法11-12: 排序后去重
 * - 方法13: 使用Stream distinct
 * - 方法14-15: 特殊遍历方式
 * - 方法16-17: 递归方法
 * - 方法18: 优化的双循环
 *
 * 时间复杂度:
 * - 双循环方法: O(n²)
 * - 排序方法: O(n log n)
 * - 哈希表/Set方法: O(n)
 * 空间复杂度: O(n) - 需要额外集合或数组存储
 *
 * 应用场景：
 * - 数据清洗
 * - 统计唯一值
 * - 数据库去重
 */
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class UniqueArray {

  /**
   * 方法1：双循环索引比较法
   * 遍历全部成员，将当前项与左边项逐个对比
   * 如果值相同且下标相同表示唯一，其他则认为是重复项
   *
   * 时间复杂度：O(n²)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static int[] unique1(int arr[]) {
    int newArr[] = new int[arr.length];
    int x = 0;
    for (int i = 0; i < arr.length; i++) {
      for (int j = 0; j <= i; j++) {
        if (arr[i] == arr[j]) {
          // 值相同且下标相同，表示第一次出现
          if (i == j) {
            newArr[x] = arr[i];
            x++;
          }
          break; // 找到相同值后跳出
        }
      }
    }
    int result[] = Arrays.copyOf(newArr, x);
    return result;
  }

  /**
   * 方法2：indexOf索引法
   * 将数组转换为List，利用List的indexOf方法查找下标
   * 当下标匹配时表示唯一，添加到新列表中
   *
   * 时间复杂度：O(n²) - indexOf是O(n)，循环n次
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique2(Integer arr[]) {
    int x = 0;
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    int l = list.size();
    for (int i = 0; i < l; i++) {
      // indexOf返回第一次出现的索引，如果等于当前索引说明是第一次出现
      if (list.indexOf(arr[i]) == i) {
        list.add(arr[i]);
        x++;
      }
    }
    // 返回取出的非重复项
    Integer[] result = new Integer[x];
    return list.subList(list.size() - x, list.size()).toArray(result);
  }

  /**
   * 方法3：从后往前删除法
   * 在原有列表上移除重复项目，自后往前遍历
   * 逐个与前面项比较，如果值相同则移除当前项
   *
   * 时间复杂度：O(n²)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique3(Integer arr[]) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    int l = list.size();
    while (l-- > 0) {
      int i = l;
      while (i-- > 0) {
        if (list.get(l).equals(list.get(i))) {
          list.remove(l);
          break;
        }
      }
    }
    return list.toArray(new Integer[list.size()]);
  }

  /**
   * 方法4：从前往后删除法（删除前面项）
   * 在原有列表上移除重复项目，自前往后遍历
   * 逐个与前面项比较，如果值相同则移除当前项
   *
   * 时间复杂度：O(n²)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique4(Integer arr[]) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    int l = list.size();

    for (int i = 1; i < l; i++) {
      for (int j = 0; j < i; j++) {
        if (list.get(i).equals(list.get(j))) {
          list.remove(i);
          i--; // 调整索引
          l--;
          break;
        }
      }
    }
    return list.toArray(new Integer[list.size()]);
  }

  /**
   * 方法5：从前往后删除法（删除后面项）
   * 在原有列表上移除重复项目，自前往后遍历
   * 逐个与后面项比较，如果值相同则移除后面项
   *
   * 时间复杂度：O(n²)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique5(Integer arr[]) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    int l = list.size();
    for (int i = 0; i < l; i++) {
      for (int j = i + 1; j < l; j++) {
        if (list.get(i).equals(list.get(j))) {
          list.remove(j);
          i--; // 调整索引
          l--;
          break;
        }
      }
    }
    return list.toArray(new Integer[list.size()]);
  }

  /**
   * 方法6：HashMap去重法
   * 利用HashMap键的唯一性来实现去重
   *
   * 时间复杂度：O(n) - HashMap的put和containsKey是O(1)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique6(Integer arr[]) {
    Map<Object, Integer> map = new HashMap<Object, Integer>();

    for (Integer item : arr) {
      if (map.containsKey(item)) {
        continue; // 已存在则跳过
      }
      map.put(item, item);
    }

    List<Integer> list = new ArrayList<>(map.values());
    return list.toArray(new Integer[list.size()]);
  }

  /**
   * 方法7：Stream filter去重法
   * 利用Stream的filter表达式过滤掉重复项
   * 需要借助外部列表存储不重复项
   *
   * 时间复杂度：O(n²) - indexOf是O(n)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static List<Integer> unique7newArr = new ArrayList<>();

  static boolean unique7contains(Integer item) {
    if (unique7newArr.indexOf(item) < 0) {
      unique7newArr.add(item);
      return true;
    }
    return false;
  }

  static Integer[] unique7(Integer arr[]) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    return list.stream().filter(UniqueArray::unique7contains).collect(Collectors.toList())
        .toArray(new Integer[UniqueArray.unique7newArr.size()]);
  }

  /**
   * 方法8：HashSet去重法
   * 利用HashSet数据结构直接去重，无序非同步
   *
   * 时间复杂度：O(n)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组（无序）
   */
  static Integer[] unique8(Integer arr[]) {
    System.out.print("covert to steam first then to set: ");
    Arrays.asList(arr).stream().collect(Collectors.toSet()).forEach(System.out::print);
    System.out.println("\ndirectly convert to set:");
    Set<Integer> set = new HashSet<>(Arrays.asList(arr));
    return new ArrayList<>(set).toArray(new Integer[set.size()]);
  }

  /**
   * 方法9：LinkedHashSet去重法
   * 利用LinkedHashSet数据结构直接去重，保持插入顺序
   *
   * 时间复杂度：O(n)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组（保持原顺序）
   */
  static Integer[] unique9(Integer arr[]) {
    Set<Integer> linkedHashSet = new LinkedHashSet<>(Arrays.asList(arr));
    return new ArrayList<>(linkedHashSet).toArray(new Integer[linkedHashSet.size()]);
  }

  /**
   * 方法10：TreeSet去重法
   * 利用TreeSet数据结构直接去重，自动排序（降序）
   *
   * 时间复杂度：O(n log n)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组（降序排序）
   */
  static Integer[] unique10(Integer arr[]) {
    Set<Integer> treeSet = new TreeSet<>(Arrays.asList(arr)).descendingSet();
    return new ArrayList<>(treeSet).toArray(new Integer[treeSet.size()]);
  }

  /**
   * 方法11：排序后从后往前删除法
   * 提前排序，从后向前遍历，将当前项与前一项对比
   * 如果重复则移除当前项
   *
   * 时间复杂度：O(n log n) - 排序是O(n log n)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组（升序）
   */
  static Integer[] unique11(Integer arr[]) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    Collections.sort(list);
    for (int l = list.size() - 1; l > 0; l--) {
      if (list.get(l).equals(list.get(l - 1))) {
        list.remove(l);
      }
    }
    return new ArrayList<>(list).toArray(new Integer[list.size()]);
  }

  /**
   * 方法12：排序后从前往后删除法（降序）
   * 提前降序排序，自前往后遍历
   * 将当前项与后一项对比，如果重复则移除当前项
   *
   * 时间复杂度：O(n log n) - 排序是O(n log n)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组（降序）
   */
  static Integer[] unique12(Integer arr[]) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    Collections.sort(list, Collections.reverseOrder());
    int l = list.size() - 1;
    for (int i = 0; i < l; i++) {
      if (list.get(i).equals(list.get(i + 1))) {
        list.remove(i);
        i--; // 调整索引
        l--;
      }
    }
    return new ArrayList<>(list).toArray(new Integer[list.size()]);
  }

  /**
   * 方法13：Stream distinct去重法
   * 转为Stream，利用distinct方法去重
   *
   * 时间复杂度：O(n)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique13(Integer arr[]) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    list = list.stream().distinct().collect(Collectors.toList());
    return new ArrayList<>(list).toArray(new Integer[list.size()]);
  }

  /**
   * 方法14：从右往左跳过重复法
   * 双循环自右往左逐个与左侧项对比
   * 如遇相同则跳过当前项，下一项为当前项，继续逐个与左侧项对比
   *
   * 时间复杂度：O(n²)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique14(Integer arr[]) {
    int len = arr.length;
    Integer[] result = new Integer[len];
    int x = len;
    for (int i = len - 1; i >= 0; i--) {
      for (int j = i - 1; j >= 0; j--) {
        if (arr[i].equals(arr[j])) {
          i--; // 跳过重复项
          j = i;
        }
      }
      // 非重复项为唯一，追加到新数组
      result[--x] = arr[i];
    }
    return Arrays.copyOfRange(result, x, len);
  }

  /**
   * 方法15：Iterator遍历法
   * 利用Iterator来遍历List，如果不在新列表中则添加
   *
   * 时间复杂度：O(n²) - contains是O(n)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique15(Integer arr[]) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    List<Integer> result = new ArrayList<>();
    Iterator<Integer> it = list.iterator();
    while (it.hasNext()) {
      Integer item = it.next();
      if (!result.contains(item)) {
        result.add(item);
      }
    }
    return new ArrayList<>(result).toArray(new Integer[result.size()]);
  }

  /**
   * 方法16：递归去重法（删除原数组）
   * 利用递归调用来去重，递归自后往前逐个调用，当长度为1时终止
   * 当后一项与前任一项相同说明有重复，则删除当前项
   * 相当于利用自我调用来替换循环
   *
   * 时间复杂度：O(n²)
   * 空间复杂度：O(n) - 递归栈深度
   *
   * @param arr 输入数组
   * @param len 当前处理长度
   * @param result 结果列表
   * @return 去重后的数组
   */
  static Integer[] uniqueRecursion1(Integer arr[], 
    int len, List<Integer> result) {
    int last = len - 1;
    Integer lastItem = arr[last];
    int l = last;
    boolean isRepeat = false;
    if (len <= 1) {
      result.add(0, lastItem);
      return new ArrayList<>(result).toArray(new Integer[result.size()]);
    }
    while (l-- > 0) {
      if (lastItem.equals(arr[l])) {
        isRepeat = true;
        break;
      }
    }
    // 如果不重复表示唯一，则添加到新数组中
    if (!isRepeat) {
      result.add(0, lastItem);
    }
    return uniqueRecursion1(arr, len - 1, result);
  }

  /**
   * 方法17：递归去重法（拼接结果）
   * 利用递归调用来去重的另一种方式，递归自后往前逐个调用
   * 与上一个递归不同，这里将不重复的项目作为结果拼接起来
   *
   * 时间复杂度：O(n²)
   * 空间复杂度：O(n) - 递归栈深度
   *
   * @param arr 输入列表
   * @param len 当前处理长度
   * @return 去重后的列表
   */
  static List<Integer> uniqueRecursion2(List<Integer> arr, int len) {
    if (len <= 1) {
      System.out.println("last arr:" + arr);
      return arr;
    }

    int last = len - 1;
    int l = last - 1;
    boolean isRepeat = false;
    Integer lastItem = arr.get(last);
    while (l >= 0) {
      if (lastItem.equals(arr.get(l))) {
        isRepeat = true;
        break;
      }
      l--;
    }

    // 如果不重复则添加到临时列表，最后将全部结果拼接
    List<Integer> result = new ArrayList<>();
    arr.remove(last);
    if (!isRepeat) {
      result.add(lastItem);
    }
    return Stream.concat(uniqueRecursion2(arr, len - 1).stream(), 
      result.stream()).collect(Collectors.toList());
  }


  /**
   * 方法18：优化的双循环索引比较法
   * 双重循环，将左侧项逐个与当前项比较
   * 如果遇到值相等则跳出循环比较下标
   * 若下标相同表示第一次出现则追加到新数组
   * 与方法1类似，但实现略有不同
   *
   * 时间复杂度：O(n²)
   * 空间复杂度：O(n)
   *
   * @param arr 输入数组
   * @return 去重后的数组
   */
  static Integer[] unique18(Integer arr[]) {
    Integer newArr[] = new Integer[arr.length];
    int x = 0;
    for (int i = 0; i < arr.length; i++) {
      int j = 0;;
      for (; j < i; j++) {
        if (arr[i].equals(arr[j])) {
          break; // 找到相同值后跳出
        }
      }
      // j == i 表示没有找到重复值，是第一次出现
      if (i == j) {
        newArr[x] = arr[i];
        x++;
      }
    }
    return Arrays.copyOf(newArr, x);
  }

  public static void main(final String args[]) {
    int arr1[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    int[] result;
    long startTime;
    // 1.
    System.out.println("unique1 start:" + Arrays.toString(arr1));
    startTime = System.currentTimeMillis();
    result = UniqueArray.unique1(arr1);
    System.out.println("unique1 result:" + Arrays.toString(result));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 2.
    Integer arr2[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique2 start:" + Arrays.toString(arr2));
    startTime = System.currentTimeMillis();
    Integer result2[] = UniqueArray.unique2(arr2);
    System.out.println("unique2 result:" + Arrays.toString(result2));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 3.
    Integer arr3[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique3 start:" + Arrays.toString(arr2));
    startTime = System.currentTimeMillis();
    Integer result3[] = UniqueArray.unique3(arr3);
    System.out.println("unique3 result:" + Arrays.toString(result3));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 4.
    Integer arr4[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique4 start:" + Arrays.toString(arr4));
    startTime = System.currentTimeMillis();
    Integer result4[] = UniqueArray.unique4(arr4);
    System.out.println("unique4 result:" + Arrays.toString(result4));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 5.
    Integer arr5[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique5 start:" + Arrays.toString(arr5));
    startTime = System.currentTimeMillis();
    Integer result5[] = UniqueArray.unique5(arr5);
    System.out.println("unique5 result:" + Arrays.toString(result5));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 6.
    Integer arr6[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique6 start:" + Arrays.toString(arr6));
    startTime = System.currentTimeMillis();
    Integer result6[] = UniqueArray.unique6(arr6);
    System.out.println("unique6 result:" + Arrays.toString(result6));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 7.
    Integer arr7[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique7 start:" + Arrays.toString(arr7));
    startTime = System.currentTimeMillis();
    Integer result7[] = UniqueArray.unique7(arr7);
    System.out.println("unique7 result:" + Arrays.toString(result7));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 8.
    Integer arr8[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique8 start:" + Arrays.toString(arr8));
    startTime = System.currentTimeMillis();
    Integer result8[] = UniqueArray.unique8(arr8);
    System.out.println("unique8 result:" + Arrays.toString(result8));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 9.
    Integer arr9[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique9 start:" + Arrays.toString(arr9));
    startTime = System.currentTimeMillis();
    Integer result9[] = UniqueArray.unique9(arr9);
    System.out.println("unique9 result:" + Arrays.toString(result9));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 10.
    Integer arr10[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique10 start:" + Arrays.toString(arr10));
    startTime = System.currentTimeMillis();
    Integer result10[] = UniqueArray.unique10(arr10);
    System.out.println("unique10 result:" + Arrays.toString(result10));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 11.
    Integer arr11[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique11 start:" + Arrays.toString(arr11));
    startTime = System.currentTimeMillis();
    Integer result11[] = UniqueArray.unique11(arr11);
    System.out.println("unique11 result:" + Arrays.toString(result11));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 12.
    Integer arr12[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique12 start:" + Arrays.toString(arr12));
    startTime = System.currentTimeMillis();
    Integer result12[] = UniqueArray.unique12(arr12);
    System.out.println("unique12 result:" + Arrays.toString(result12));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 13.
    Integer arr13[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique13 start:" + Arrays.toString(arr13));
    startTime = System.currentTimeMillis();
    Integer result13[] = UniqueArray.unique13(arr13);
    System.out.println("unique13 result:" + Arrays.toString(result13));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 14.
    Integer arr14[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique14 start:" + Arrays.toString(arr14));
    startTime = System.currentTimeMillis();
    Integer result14[] = UniqueArray.unique14(arr14);
    System.out.println("unique14 result:" + Arrays.toString(result14));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 15.
    Integer arr15[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique15 start:" + Arrays.toString(arr15));
    startTime = System.currentTimeMillis();
    Integer result15[] = UniqueArray.unique15(arr15);
    System.out.println("unique15 result:" + Arrays.toString(result15));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 16.
    Integer arr16[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("uniqueRecursion1 start:" + Arrays.toString(arr16));
    startTime = System.currentTimeMillis();
    Integer result16[] = UniqueArray.uniqueRecursion1(arr16, arr16.length, new ArrayList<>());
    System.out.println("uniqueRecursion1 result:" + Arrays.toString(result16));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 17.
    Integer arr17[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("uniqueRecursion2 start:" + Arrays.toString(arr17));
    startTime = System.currentTimeMillis();
    List<Integer> result17 = UniqueArray.uniqueRecursion2(new ArrayList<>(Arrays.asList(arr17)), arr17.length);
    System.out.println("uniqueRecursion2 result:" + result17);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 18.
    Integer arr18[] = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    System.out.println("unique18 start:" + Arrays.toString(arr18));
    startTime = System.currentTimeMillis();
    Integer result18[] = UniqueArray.unique18(arr18);
    System.out.println("unique18 result:" + Arrays.toString(result18));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

  }
}

/*
 jarrys-MacBook-Pro:unique jarry$ java --version java 10.0.1 2018-04-17
 Java(TM) SE Runtime Environment 18.3 (build 10.0.1+10) Java HotSpot(TM)
 64-Bit Server VM 18.3 (build 10.0.1+10, mixed mode)

jarrys-MacBook-Pro:unique jarry$ javac UniqueArray.java 
jarrys-MacBook-Pro:unique jarry$ java UniqueArray
unique1 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique1 result:[1, 3, -1, 2, 4]

time:0 ms.
unique2 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique2 result:[1, 3, -1, 2, 4]

time:0 ms.
unique3 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique3 result:[1, 3, -1, 2, 4]

time:1 ms.
unique4 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique4 result:[1, 3, -1, 2, 4]

time:0 ms.
unique5 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique5 result:[1, 3, -1, 2, 4]

time:1 ms.
unique6 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique6 result:[-1, 1, 2, 3, 4]

time:0 ms.
unique7 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique7 result:[1, 3, -1, 2, 4]

time:6 ms.
unique8 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
covert to steam first then to set: -11234
directly convert to set:
unique8 result:[-1, 1, 2, 3, 4]

time:2 ms.
unique9 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique9 result:[1, 3, -1, 2, 4]

time:1 ms.
unique10 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique10 result:[4, 3, 2, 1, -1]

time:1 ms.
unique11 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique11 result:[-1, 1, 2, 3, 4]

time:1 ms.
unique12 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique12 result:[4, 3, 2, 1, -1]

time:0 ms.
unique13 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique13 result:[1, 3, -1, 2, 4]

time:0 ms.
unique14 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique14 result:[1, 3, -1, 2, 4]

time:0 ms.
unique15 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique15 result:[1, 3, -1, 2, 4]

time:0 ms.
uniqueRecursion1 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
uniqueRecursion1 result:[1, 3, -1, 2, 4]

time:0 ms.
uniqueRecursion2 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
last arr:[1]
uniqueRecursion2 result:[1, 3, -1, 2, 4]

time:1 ms.
unique18 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
unique18 result:[1, 3, -1, 2, 4]

time:0 ms.
 */