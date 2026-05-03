
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组去重算法 - Java实现，20种不同思路
 *
 * 算法原理：扫描数组，保留每个值的首次出现，丢弃后续重复
 *
 * 20种实现按5类组织：
 * - 第1类 基础循环（方法1-6）：纯下标遍历，O(n²)
 * - 第2类 集合容器（方法7-11）：利用Set/Map键唯一性，O(n)
 * - 第3类 排序后去重（方法12-14）：相同元素相邻后扫描，O(n log n)
 * - 第4类 Stream函数式（方法15-17）：现代Java写法，O(n)
 * - 第5类 递归与位图（方法18-20）：教学经典与位图法
 *
 * 应用场景：数据清洗、统计唯一值、数据库去重
 */
import java.util.*;
import java.util.stream.Collectors;

public class UniqueArray {

  // ==================== 第1类：基础循环（方法1-6） ====================

  /**
   * 方法1：双循环索引比较法
   * 核心原理：对每个元素向前查找，若找到相同值则为重复，否则为唯一值
   * 策略：遍历全部成员，将当前项与左边项逐个对比
   * 如果值相同且下标相同表示唯一，其他则认为是重复项
   *
   * 时间复杂度：O(n²) - 双层循环，最坏所有元素都不重复
   * 空间复杂度：O(n) - 新建数组存储结果
   *
   * @param arr 输入数组
   * @return 去重后的数组，保留首次出现顺序
   */
  static int[] unique1(int[] arr) {
    int[] newArr = new int[arr.length];
    int x = 0;
    // 当前项跟左侧全量对比，是否首次出现
    for (int i = 0; i < arr.length; i++) {
      for (int j = 0; j <= i; j++) {
        if (arr[i] == arr[j]) {
          // i == j 表示前面没有相同值，是首次出现
          if (i == j) {
            newArr[x++] = arr[i];
          }
          break;
        }
      }
    }
    return Arrays.copyOf(newArr, x);
  }

  /**
   * 方法2：List.indexOf 索引法
   * 核心原理：indexOf 返回首次出现下标，等于当前下标即为首次出现
   * 策略：遍历列表，对每一项调用 indexOf 判断是否首次出现
   *
   * 时间复杂度：O(n²) - indexOf 是 O(n) 线性查找
   * 空间复杂度：O(n) - 新建结果列表
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique2(Integer[] arr) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    List<Integer> result = new ArrayList<>();
    for (int i = 0; i < list.size(); i++) {
      // indexOf 内部仍是 O(n) 线性查找
      if (list.indexOf(list.get(i)) == i) {
        result.add(list.get(i));
      }
    }
    return result.toArray(new Integer[0]);
  }

  /**
   * 方法3：从后往前原地删除法
   * 核心原理：倒序遍历，与左侧任一元素相同则删除自身
   * 策略：自后往前扫，删除点之后元素已处理，不影响下标
   *
   * 时间复杂度：O(n²) - 双循环加 List.remove 每次 O(n)
   * 空间复杂度：O(n) - List 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique3(Integer[] arr) {
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
    return list.toArray(new Integer[0]);
  }

  /**
   * 方法4：从前往后原地删除法（删除后面相同项）
   * 核心原理：正序遍历，与右侧相同则删除右侧重复项
   * 策略：删除后 j 不前进、长度同步减一，避免漏判
   *
   * 时间复杂度：O(n²) - 双循环加 List.remove 每次 O(n)
   * 空间复杂度：O(n) - List 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique4(Integer[] arr) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    int l = list.size();
    for (int i = 0; i < l; i++) {
      for (int j = i + 1; j < l; j++) {
        if (list.get(i).equals(list.get(j))) {
          list.remove(j);
          j--; // 删除后下标回退
          l--; // 长度同步减一
        }
      }
    }
    return list.toArray(new Integer[0]);
  }

  /**
   * 方法5：Iterator 遍历法
   * 核心原理：Iterator 遍历原数组，结果列表用 contains 判重
   * 策略：判重在结果列表中进行，未出现的才添加
   *
   * 时间复杂度：O(n²) - ArrayList.contains 每次 O(n)
   * 空间复杂度：O(n) - 结果列表
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique5(Integer[] arr) {
    List<Integer> source = Arrays.asList(arr);
    List<Integer> result = new ArrayList<>();
    Iterator<Integer> it = source.iterator();
    while (it.hasNext()) {
      Integer item = it.next();
      if (!result.contains(item)) {
        result.add(item);
      }
    }
    return result.toArray(new Integer[0]);
  }

  /**
   * 方法6：从右往左跳过重复法
   * 核心原理：倒序扫描，遇相同时把 i 整体左移跳过这一段重复区
   * 策略：保留下来的 i 是非重复项，倒序写入结果数组
   *
   * 时间复杂度：O(n²) - 双循环
   * 空间复杂度：O(n) - 结果数组
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique6(Integer[] arr) {
    int len = arr.length;
    Integer[] result = new Integer[len];
    int x = len;
    for (int i = len - 1; i >= 0; i--) {
      for (int j = i - 1; j >= 0; j--) {
        if (arr[i].equals(arr[j])) {
          i--; // 跳过当前重复项
          j = i; // j 复位到 i 左侧重新比较
        }
      }
      result[--x] = arr[i];
    }
    return Arrays.copyOfRange(result, x, len);
  }

  // ==================== 第2类：集合容器（方法7-11） ====================

  /**
   * 方法7：HashSet 去重法
   * 核心原理：哈希表键唯一，O(1) 判重
   * 策略：将数组转为 HashSet，自动完成去重
   * 优势：时间最快；缺点：底层散列后顺序不可预测
   *
   * 时间复杂度：O(n) - HashSet 添加 O(1) 平均
   * 空间复杂度：O(n) - HashSet 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（无序）
   */
  static Integer[] unique7(Integer[] arr) {
    Set<Integer> set = new HashSet<>(Arrays.asList(arr));
    return set.toArray(new Integer[0]);
  }

  /**
   * 方法8：LinkedHashSet 去重法
   * 核心原理：哈希表加双向链表，O(1) 判重并保留插入顺序
   * 策略：直接转 LinkedHashSet，去重与保序一气呵成
   * 推荐场景：日常工程最常用方案
   *
   * 时间复杂度：O(n) - 集合插入 O(1)
   * 空间复杂度：O(n) - LinkedHashSet 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique8(Integer[] arr) {
    Set<Integer> set = new LinkedHashSet<>(Arrays.asList(arr));
    return set.toArray(new Integer[0]);
  }

  /**
   * 方法9：TreeSet 自动排序去重法
   * 核心原理：红黑树实现的有序集合，自动排序且自动去重
   * 策略：将数组转为 TreeSet，利用其排序与去重的双重特性
   * 推荐场景：需要顺便排序的去重
   *
   * 时间复杂度：O(n log n) - 红黑树插入 O(log n)
   * 空间复杂度：O(n) - TreeSet 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（升序）
   */
  static Integer[] unique9(Integer[] arr) {
    Set<Integer> set = new TreeSet<>(Arrays.asList(arr));
    return set.toArray(new Integer[0]);
  }

  /**
   * 方法10：HashMap 显式判重法
   * 核心原理：利用 HashMap 键的唯一性自动去重
   * 策略：putIfAbsent 内部判 containsKey 加 put，紧凑等价
   * 优势：值可携带统计信息（如频次、首次位置）
   *
   * 时间复杂度：O(n) - HashMap 操作 O(1) 平均
   * 空间复杂度：O(n) - HashMap 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique10(Integer[] arr) {
    Map<Integer, Integer> map = new HashMap<>();
    List<Integer> result = new ArrayList<>();
    for (Integer item : arr) {
      // putIfAbsent 返回 null 表示首次插入
      if (map.putIfAbsent(item, item) == null) {
        result.add(item);
      }
    }
    return result.toArray(new Integer[0]);
  }

  /**
   * 方法11：LinkedHashMap merge 去重法
   * 核心原理：LinkedHashMap 保插入顺序，merge 处理冲突
   * 策略：键去重，值用 merge 累加，顺便统计频次
   * 推荐场景：去重同时需要业务统计的场景
   *
   * 时间复杂度：O(n) - HashMap 操作 O(1) 平均
   * 空间复杂度：O(n) - LinkedHashMap 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique11(Integer[] arr) {
    Map<Integer, Integer> map = new LinkedHashMap<>();
    for (Integer item : arr) {
      // 键不存在则放 1，存在则累加（相当于做了频次统计）
      map.merge(item, 1, Integer::sum);
    }
    return map.keySet().toArray(new Integer[0]);
  }

  // ==================== 第3类：排序后去重（方法12-14） ====================

  /**
   * 方法12：排序后从后往前删法
   * 核心原理：先排序让相同元素相邻，再倒序删除重复
   * 策略：升序排序后从末尾扫，相邻相同则删后者
   *
   * 时间复杂度：O(n²) - 排序 O(n log n)，每次 remove O(n)
   * 空间复杂度：O(n) - List 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（升序）
   */
  static Integer[] unique12(Integer[] arr) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    Collections.sort(list);
    for (int l = list.size() - 1; l > 0; l--) {
      if (list.get(l).equals(list.get(l - 1))) {
        list.remove(l);
      }
    }
    return list.toArray(new Integer[0]);
  }

  /**
   * 方法13：排序后从前往后删法
   * 核心原理：降序排序后正序扫，相邻相同则删前者
   * 策略：删除后 i 回退、长度减一，避免漏判
   *
   * 时间复杂度：O(n²) - 排序 O(n log n)，每次 remove O(n)
   * 空间复杂度：O(n) - List 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（降序）
   */
  static Integer[] unique13(Integer[] arr) {
    List<Integer> list = new ArrayList<>(Arrays.asList(arr));
    Collections.sort(list, Collections.reverseOrder());
    int l = list.size() - 1;
    int i = 0;
    while (i < l) {
      if (list.get(i).equals(list.get(i + 1))) {
        list.remove(i);
        i--;
        l--;
      }
      i++;
    }
    return list.toArray(new Integer[0]);
  }

  /**
   * 方法14：经典双指针法（LeetCode原题）
   * 核心原理：原地排序后双指针扫描，慢指针指向最后一个唯一元素
   * 策略：快指针发现新值，慢指针前进并写入；O(1) 额外空间
   * 推荐场景：数组原地去重，不允许额外存储
   *
   * 时间复杂度：O(n log n) - 排序主导
   * 空间复杂度：O(1) - 原地修改
   *
   * @param arr 输入数组（会被原地修改）
   * @return 去重后的数组（升序）
   */
  static int[] unique14(int[] arr) {
    if (arr.length == 0)
      return arr;
    Arrays.sort(arr);
    int slow = 0;
    for (int fast = 1; fast < arr.length; fast++) {
      // 快指针发现新值，慢指针前进一步并写入
      if (arr[fast] != arr[slow]) {
        arr[++slow] = arr[fast];
      }
    }
    return Arrays.copyOf(arr, slow + 1);
  }

  // ==================== 第4类：Stream 与函数式（方法15-17） ====================

  /**
   * 方法15：Stream.distinct 去重法
   * 核心原理：Stream 中间操作，内部基于 LinkedHashSet 实现
   * 策略：链式调用，一行解决，保序、O(n)
   * 推荐场景：现代 Java 工程首选写法
   *
   * 时间复杂度：O(n) - distinct 内部 O(1) 判重
   * 空间复杂度：O(n) - 中间 LinkedHashSet
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique15(Integer[] arr) {
    return Arrays.stream(arr).distinct().toArray(Integer[]::new);
  }

  /**
   * 方法16：Stream.filter 加外部 Set 法
   * 核心原理：filter 谓词带副作用，seen.add 返回 true 表示首次见到
   * 策略：在函数式管道里携带"已见"状态，仅保留首次出现
   * 推荐场景：自定义过滤条件加去重的组合
   *
   * 时间复杂度：O(n) - HashSet.add 是 O(1) 平均
   * 空间复杂度：O(n) - HashSet 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique16(Integer[] arr) {
    Set<Integer> seen = new HashSet<>();
    return Arrays.stream(arr).filter(seen::add).toArray(Integer[]::new);
  }

  /**
   * 方法17：Collectors.toMap 去重法
   * 核心原理：toMap 第三参数为冲突合并函数，保留首项
   * 策略：用值本身做键，LinkedHashMap 保序
   * 推荐场景：自定义对象按某字段去重
   *
   * 时间复杂度：O(n) - HashMap 操作 O(1) 平均
   * 空间复杂度：O(n) - LinkedHashMap 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static Integer[] unique17(Integer[] arr) {
    Map<Integer, Integer> map = Arrays.stream(arr).collect(
        Collectors.toMap(
            item -> item, // keyMapper：用值本身做键
            item -> item, // valueMapper
            (existing, replacement) -> existing, // 冲突保留首项
            LinkedHashMap::new // 保序工厂
        ));
    return map.values().toArray(new Integer[0]);
  }

  // ==================== 第5类：递归与位图（方法18-20） ====================

  /**
   * 方法18：递归--从后往前构建去重列表
   * 核心原理：递归检查末尾元素是否在前面出现过，若不重复则插入到结果列表头部，最终保持原顺序
   * 策略：result 头插保持原顺序，递归出口为 length<=1
   *
   * 时间复杂度：O(n²) - 递归 n 层，每层扫前面 O(n)
   * 空间复杂度：O(n) - 递归栈深度 n
   *
   * @param arr    输入数组
   * @param length 当前处理长度（递归参数）
   * @param result 结果列表（递归积累）
   * @return 去重后的数组（保序）
   */
  static Integer[] unique18(Integer[] arr, int length, List<Integer> result) {
    // 递归终止：只剩一项或为空
    if (length <= 1) {
      if (length == 1)
        result.add(0, arr[0]);
      return result.toArray(new Integer[0]);
    }
    int last = length - 1;
    Integer lastItem = arr[last];
    boolean isRepeat = false;
    // 在 [0, last) 区间检查是否已出现 lastItem
    for (int i = last - 1; i >= 0; i--) {
      if (lastItem.equals(arr[i])) {
        isRepeat = true;
        break;
      }
    }
    // 不重复则往前插入以保持原顺序
    if (!isRepeat) {
      result.add(0, lastItem);
    }
    return unique18(arr, length - 1, result);
  }

  /**
   * 方法19：递归--拼接返回（纯函数式，不修改原数组和外部集合）
   * 核心原理：先递归处理前 n-1 个元素得到去重结果，再判断第 n 个元素是否在它前面出现过。
   * 若未出现过，则追加到结果末尾；否则直接返回。最终保持原数组的首次出现顺序。
   * 策略：纯函数式风格，不修改原列表
   *
   * 时间复杂度：O(n²) - 递归 n 层，每层扫前面 O(n)
   * 空间复杂度：O(n) - 递归栈加 List 占用
   *
   * @param list   输入列表
   * @param length 当前处理长度（递归参数）
   * @return 去重后的列表（保序）
   */
  static List<Integer> unique19(List<Integer> list, int length) {
    if (length <= 1) {
      // 长度≤1时，直接返回原列表的前 length 个元素（避免后续越界）
      return new ArrayList<>(list.subList(0, length));
    }

    int last = length - 1;
    Integer lastItem = list.get(last);
    boolean isRepeat = false;
    // 检查当前项 lastItem 是否在它前面的子数组中出现过
    for (int i = last - 1; i >= 0; i--) {
      if (lastItem.equals(list.get(i))) {
        isRepeat = true;
        break;
      }
    }

    // 递归深入：此时尚未得到前 length-1 项的去重结果，暂停当前层，进入子问题求解
    List<Integer> head = unique19(list, length - 1);
    // 递归回溯：子问题已返回结果（head 中已包含前 length-1 项的去重结果，且保序）

    // 当前项不重复则追加到结果末尾（保持原顺序）
    if (!isRepeat) {
      head.add(lastItem);
    }
    return head;
  }

  /**
   * 方法20：BitSet 位图法
   * 核心原理：BitSet 是用一个 long[] 数组来模拟一个无限长的位序列。
   * 每个 int 用一位标记是否出现过，仅适用非负整数
   * 策略：BitSet.set 标记，遇未置位则视为首次出现并写入结果
   * 推荐场景：海量非负整数（10亿规模仅需约 128MB）
   *
   * 时间复杂度：O(n) - BitSet 操作 O(1)
   * 空间复杂度：O(max_value/8) - 取决于最大值
   *
   * @param arr 输入数组（非负整数）
   * @return 去重后的数组（保序）
   */
  static int[] unique20(int[] arr) {
    // 初始化 BitSet 为 0，所有位都为 false/未出现
    BitSet bitSet = new BitSet();
    int[] result = new int[arr.length];
    int x = 0;
    for (int item : arr) {
      // BitSet 下标必须非负，负数需先做偏移
      if (item < 0) {
        throw new IllegalArgumentException("BitSet 不支持负数，需要先偏移");
      }
      // 第 item 位为 0 表示首次出现，标记为 1 并写入结果
      // 原理：BitSet.set(item) 会将第 item 位设为 true，后续遇到相同值时会直接跳过
      // 写入结果时，只写入首次出现的项，后续重复项会直接跳过
      if (!bitSet.get(item)) {
        bitSet.set(item);   // 标记为已出现
        result[x++] = item; // 写入结果数组
      }
    }
    return Arrays.copyOf(result, x);
  }

  // ==================== main 函数 ====================

  public static void main(String[] args) {
    int[] base = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    Integer[] baseI = { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 };
    long startTime;

    // 1. 双循环索引比较
    System.out.println("unique1 start:" + Arrays.toString(base));
    startTime = System.currentTimeMillis();
    int[] result1 = unique1(base.clone());
    System.out.println("unique1 result:" + Arrays.toString(result1));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 2. List.indexOf
    System.out.println("unique2 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result2 = unique2(baseI.clone());
    System.out.println("unique2 result:" + Arrays.toString(result2));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 3. 从后往前删
    System.out.println("unique3 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result3 = unique3(baseI.clone());
    System.out.println("unique3 result:" + Arrays.toString(result3));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 4. 从前往后删（删后面项）
    System.out.println("unique4 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result4 = unique4(baseI.clone());
    System.out.println("unique4 result:" + Arrays.toString(result4));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 5. Iterator 遍历
    System.out.println("unique5 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result5 = unique5(baseI.clone());
    System.out.println("unique5 result:" + Arrays.toString(result5));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 6. 从右往左跳过
    System.out.println("unique6 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result6 = unique6(baseI.clone());
    System.out.println("unique6 result:" + Arrays.toString(result6));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 7. HashSet
    System.out.println("unique7 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result7 = unique7(baseI.clone());
    System.out.println("unique7 result:" + Arrays.toString(result7));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 8. LinkedHashSet
    System.out.println("unique8 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result8 = unique8(baseI.clone());
    System.out.println("unique8 result:" + Arrays.toString(result8));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 9. TreeSet
    System.out.println("unique9 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result9 = unique9(baseI.clone());
    System.out.println("unique9 result:" + Arrays.toString(result9));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 10. HashMap 显式判重
    System.out.println("unique10 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result10 = unique10(baseI.clone());
    System.out.println("unique10 result:" + Arrays.toString(result10));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 11. LinkedHashMap merge
    System.out.println("unique11 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result11 = unique11(baseI.clone());
    System.out.println("unique11 result:" + Arrays.toString(result11));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 12. 排序后从后往前删
    System.out.println("unique12 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result12 = unique12(baseI.clone());
    System.out.println("unique12 result:" + Arrays.toString(result12));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 13. 排序后从前往后删
    System.out.println("unique13 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result13 = unique13(baseI.clone());
    System.out.println("unique13 result:" + Arrays.toString(result13));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 14. 经典双指针 LeetCode 26
    System.out.println("unique14 start:" + Arrays.toString(base));
    startTime = System.currentTimeMillis();
    int[] result14 = unique14(base.clone());
    System.out.println("unique14 result:" + Arrays.toString(result14));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 15. Stream.distinct
    System.out.println("unique15 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result15 = unique15(baseI.clone());
    System.out.println("unique15 result:" + Arrays.toString(result15));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 16. Stream.filter + 外部 Set
    System.out.println("unique16 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result16 = unique16(baseI.clone());
    System.out.println("unique16 result:" + Arrays.toString(result16));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 17. Collectors.toMap
    System.out.println("unique17 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result17 = unique17(baseI.clone());
    System.out.println("unique17 result:" + Arrays.toString(result17));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 18. 递归原地删除
    System.out.println("unique18 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    Integer[] result18 = unique18(baseI.clone(), baseI.length, new ArrayList<>());
    System.out.println("unique18 result:" + Arrays.toString(result18));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 19. 递归拼接返回
    System.out.println("unique19 start:" + Arrays.toString(baseI));
    startTime = System.currentTimeMillis();
    List<Integer> result19 = unique19(new ArrayList<>(Arrays.asList(baseI)), baseI.length);
    System.out.println("unique19 result:" + result19);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 20. BitSet 位图法（仅非负整数）
    int[] base20 = { 1, 3, 1, 2, 2, 4, 2, 2 };
    System.out.println("unique20 start:" + Arrays.toString(base20));
    startTime = System.currentTimeMillis();
    int[] result20 = unique20(base20.clone());
    System.out.println("unique20 result:" + Arrays.toString(result20));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  }
}

/*
 * 打印结果
 * jarry@Mac unique % java UniqueArray.java
 * unique1 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique1 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique2 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique2 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique3 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique3 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique4 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique4 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique5 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique5 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique6 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique6 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique7 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique7 result:[-1, 1, 2, 3, 4]
 * 
 * time:1 ms.
 * unique8 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique8 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique9 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique9 result:[-1, 1, 2, 3, 4]
 * 
 * time:0 ms.
 * unique10 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique10 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique11 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique11 result:[1, 3, -1, 2, 4]
 * 
 * time:1 ms.
 * unique12 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique12 result:[-1, 1, 2, 3, 4]
 * 
 * time:1 ms.
 * unique13 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique13 result:[4, 3, 2, 1, -1]
 * 
 * time:0 ms.
 * unique14 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique14 result:[-1, 1, 2, 3, 4]
 * 
 * time:2 ms.
 * unique15 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique15 result:[1, 3, -1, 2, 4]
 * 
 * time:1 ms.
 * unique16 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique16 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique17 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique17 result:[1, 3, -1, 2, 4]
 * 
 * time:1 ms.
 * unique18 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique18 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique19 start:[1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique19 result:[1, 3, -1, 2, 4]
 * 
 * time:0 ms.
 * unique20 start:[1, 3, 1, 2, 2, 4, 2, 2]
 * unique20 result:[1, 3, 2, 4]
 * 
 * time:0 ms.
 */
