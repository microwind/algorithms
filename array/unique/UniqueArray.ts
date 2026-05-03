/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组去重算法 - TypeScript实现，20种不同思路
 *
 * 算法原理：扫描数组，保留每个值的首次出现，丢弃后续重复
 *
 * 20种实现按5类组织：
 * - 第1类 基础循环（方法1-6）：纯下标遍历，O(n²)
 * - 第2类 内置数组方法（方法7-11）：filter / reduce 等函数式 API
 * - 第3类 集合容器（方法12-14）：Set / Map / Object，O(n)
 * - 第4类 排序后去重（方法15-17）：相同元素相邻后扫描，O(n log n)
 * - 第5类 递归与特殊（方法18-20）：递归与对象/嵌套数组的深度判重
 *
 * 应用场景：数据清洗、统计唯一值、数据库去重
 */

class UniqueArray {

  // ==================== 第1类：基础循环（方法1-6） ====================

  /**
   * 方法1：双循环索引比较法
   * 核心原理：对每个元素向前查找，若找到相同值则为重复，否则为唯一值
   * 策略：当前项与左侧逐个对比，下标相同表示首次出现
   *
   * 时间复杂度：O(n²) - 双层循环
   * 空间复杂度：O(n) - 新建数组存储结果
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique1<T>(arr: T[]): T[] {
    const result: T[] = [];
    for (let i = 0, l = arr.length; i < l; i++) {
      for (let j = 0; j <= i; j++) {
        if (arr[i] === arr[j]) {
          // i === j 表示前面没有相同值，是首次出现
          if (i === j) result.push(arr[i]);
          break;
        }
      }
    }
    return result;
  }

  /**
   * 方法2：新建数组 + includes 法
   * 核心原理：维护结果数组，遍历时用 includes 判断是否已存在
   * 策略：未出现的才追加，最直观的新手写法
   *
   * 时间复杂度：O(n²) - includes 是 O(n) 线性扫描
   * 空间复杂度：O(n) - 结果数组
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique2<T>(arr: T[]): T[] {
    const result: T[] = [];
    for (const item of arr) {
      if (!result.includes(item)) result.push(item);
    }
    return result;
  }

  /**
   * 方法3：从后往前原地 splice 法
   * 核心原理：倒序遍历，与左侧任一元素相同则删除自身
   * 策略：自后往前扫，删除点之后元素已处理，不影响下标
   *
   * 时间复杂度：O(n²) - 双循环加 splice 每次 O(n)
   * 空间复杂度：O(1) - 原地修改
   *
   * @param arr 输入数组（会被原地修改）
   * @return 去重后的数组（保序）
   */
  static unique3<T>(arr: T[]): T[] {
    let l = arr.length;
    while (l-- > 0) {
      for (let i = 0; i < l; i++) {
        if (arr[l] === arr[i]) {
          arr.splice(l, 1);
          break;
        }
      }
    }
    return arr;
  }

  /**
   * 方法4：从前往后原地 splice 法（删除后面相同项）
   * 核心原理：正序遍历，与右侧相同则删除右侧重复项
   * 策略：删除后 j 不前进、长度同步减一，避免漏判
   *
   * 时间复杂度：O(n²) - 双循环加 splice 每次 O(n)
   * 空间复杂度：O(1) - 原地修改
   *
   * @param arr 输入数组（会被原地修改）
   * @return 去重后的数组（保序）
   */
  static unique4<T>(arr: T[]): T[] {
    let l = arr.length;
    for (let i = 0; i < l; i++) {
      for (let j = i + 1; j < l; j++) {
        if (arr[i] === arr[j]) {
          arr.splice(j, 1);
          j--; // 删除后下标回退
          l--; // 长度同步减一
        }
      }
    }
    return arr;
  }

  /**
   * 方法5：forEach + indexOf 法
   * 核心原理：indexOf 返回首次出现下标，等于当前下标即为首次
   * 策略：用回调形式遍历，indexOf 提供"是否首次"的判断
   *
   * 时间复杂度：O(n²) - indexOf 每次 O(n)
   * 空间复杂度：O(n) - 结果数组
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique5<T>(arr: T[]): T[] {
    const result: T[] = [];
    arr.forEach((item, i) => {
      if (arr.indexOf(item) === i) result.push(item);
    });
    return result;
  }

  /**
   * 方法6：双重 while 倒序 splice 法
   * 核心原理：外层 while 倒序，内层 while 倒序扫前面
   * 策略：与方法3思路相同，但用嵌套 while 强调反向比较
   *
   * 时间复杂度：O(n²) - 双循环加 splice 每次 O(n)
   * 空间复杂度：O(1) - 原地修改
   *
   * @param arr 输入数组（会被原地修改）
   * @return 去重后的数组（保序）
   */
  static unique6<T>(arr: T[]): T[] {
    let l = arr.length;
    while (l-- > 0) {
      let i = l;
      while (i-- > 0) {
        if (arr[l] === arr[i]) {
          arr.splice(l, 1);
          break;
        }
      }
    }
    return arr;
  }

  // ==================== 第2类：内置数组方法（方法7-11） ====================

  /**
   * 方法7：filter + indexOf 一行法
   * 核心原理：indexOf 返回首次出现下标，filter 保留首次出现项
   * 策略：函数式风格，写法最短，但仍是 O(n²)
   *
   * 时间复杂度：O(n²) - indexOf 每次 O(n)
   * 空间复杂度：O(n) - 新数组
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique7<T>(arr: T[]): T[] {
    return arr.filter((item, i) => arr.indexOf(item) === i);
  }

  /**
   * 方法8：filter + Set 闭包法
   * 核心原理：filter 谓词带副作用，首次见到才返回 true
   * 策略：闭包内 Set 提供 O(1) 判重，比方法7快得多
   * 推荐场景：函数式风格中需要 O(n) 性能的去重
   *
   * 时间复杂度：O(n) - Set.has/add 是 O(1) 平均
   * 空间复杂度：O(n) - Set 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique8<T>(arr: T[]): T[] {
    const seen = new Set<T>();
    return arr.filter(item => !seen.has(item) && !!seen.add(item));
  }

  /**
   * 方法9：reduce 累加法
   * 核心原理：用 reduce 把"已见数组"作为累加器，逐步构建结果
   * 策略：includes 判重，函数式风格但 O(n²)
   *
   * 时间复杂度：O(n²) - includes 每次 O(n)
   * 空间复杂度：O(n) - 累加器数组
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique9<T>(arr: T[]): T[] {
    return arr.reduce<T[]>((acc, item) => {
      if (!acc.includes(item)) acc.push(item);
      return acc;
    }, []);
  }

  /**
   * 方法10：reduce + Set 闭包法
   * 核心原理：用 Set 替代 includes 判重，O(n²) 降到 O(n)
   * 策略：累加器维护数组顺序，外部 Set 维护判重
   *
   * 时间复杂度：O(n) - Set.has 是 O(1) 平均
   * 空间复杂度：O(n) - Set 加结果数组
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique10<T>(arr: T[]): T[] {
    const seen = new Set<T>();
    return arr.reduce<T[]>((acc, item) => {
      if (!seen.has(item)) {
        seen.add(item);
        acc.push(item);
      }
      return acc;
    }, []);
  }

  /**
   * 方法11：Object + typeof 键法
   * 核心原理：用 typeof + value 拼成字符串作为对象键，避免 1 与 '1' 冲突
   * 策略：filter + hasOwnProperty 判重，区分类型
   * 推荐场景：数组同时含有数字和字符串字面量时
   *
   * 时间复杂度：O(n) - 对象属性访问 O(1) 平均
   * 空间复杂度：O(n) - 对象占用
   *
   * @param arr 输入数组（基本类型）
   * @return 去重后的数组（保序）
   */
  static unique11<T extends string | number | boolean>(arr: T[]): T[] {
    const obj: Record<string, true> = {};
    return arr.filter(item => {
      const key = typeof item + String(item);
      return Object.prototype.hasOwnProperty.call(obj, key) ? false : (obj[key] = true);
    });
  }

  // ==================== 第3类：集合容器（方法12-14） ====================

  /**
   * 方法12：new Set 转数组法
   * 核心原理：Set 自动键唯一，spread 转回数组
   * 策略：写法最短，O(n) 性能，保留插入顺序
   * 推荐场景：日常工程首选
   *
   * 时间复杂度：O(n) - Set 添加 O(1) 平均
   * 空间复杂度：O(n) - Set 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique12<T>(arr: T[]): T[] {
    return [...new Set(arr)];
  }

  /**
   * 方法13：Map.set 法
   * 核心原理：Map 键唯一且保插入顺序，重复键自动覆盖
   * 策略：键去重，值可携带额外信息（频次、首次位置等）
   * 推荐场景：去重同时需要保留 value 的场景
   *
   * 时间复杂度：O(n) - Map 添加 O(1) 平均
   * 空间复杂度：O(n) - Map 占用
   *
   * @param arr 输入数组
   * @return 去重后的数组（保序）
   */
  static unique13<T>(arr: T[]): T[] {
    const map = new Map<T, T>();
    arr.forEach(item => map.set(item, item));
    return [...map.keys()];
  }

  /**
   * 方法14：Object 字面量哈希法
   * 核心原理：对象键唯一性自动去重，但所有键会被字符串化
   * 策略：直接以元素为键存入对象，最后取所有键
   * 缺点：1 与 '1' 会被合并；引用类型变成 [object Object]
   *
   * 时间复杂度：O(n) - 对象属性访问 O(1) 平均
   * 空间复杂度：O(n) - 对象占用
   *
   * @param arr 输入数组（基本类型）
   * @return 去重后的数组（数字键被引擎升序重排）
   */
  static unique14<T extends string | number>(arr: T[]): T[] {
    const obj = {} as Record<string, T>;
    for (const item of arr) obj[String(item)] = item;
    return Object.values(obj);
  }

  // ==================== 第4类：排序后去重（方法15-17） ====================

  /**
   * 方法15：sort + splice 升序去重法
   * 核心原理：先排序让相同元素相邻，再倒序删除重复
   * 策略：升序排序后从末尾扫，相邻相同则删后者
   *
   * 时间复杂度：O(n²) - 排序 O(n log n)，每次 splice O(n)
   * 空间复杂度：O(1) - 原地修改
   *
   * @param arr 输入数组（会被原地修改）
   * @return 去重后的数组（升序）
   */
  static unique15(arr: number[]): number[] {
    arr.sort((a, b) => a - b);
    let l = arr.length;
    while (l-- > 1) {
      if (arr[l] === arr[l - 1]) arr.splice(l, 1);
    }
    return arr;
  }

  /**
   * 方法16：sort + filter 相邻判重法
   * 核心原理：排序后用 filter 保留与前一项不同的元素
   * 策略：相邻判等是最便宜的判重方式
   *
   * 时间复杂度：O(n log n) - 排序主导
   * 空间复杂度：O(n) - 新数组
   *
   * @param arr 输入数组（会被原地排序修改）
   * @return 去重后的数组（升序）
   */
  static unique16(arr: number[]): number[] {
    arr.sort((a, b) => a - b);
    return arr.filter((item, i) => i === 0 || item !== arr[i - 1]);
  }

  /**
   * 方法17：经典双指针法（LeetCode 26）
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
  static unique17(arr: number[]): number[] {
    if (arr.length === 0) return arr;
    arr.sort((a, b) => a - b);
    let slow = 0;
    for (let fast = 1; fast < arr.length; fast++) {
      if (arr[fast] !== arr[slow]) arr[++slow] = arr[fast];
    }
    return arr.slice(0, slow + 1);
  }

  // ==================== 第5类：递归与特殊（方法18-20） ====================

  /**
   * 方法18：递归原地删除法
   * 核心原理：递归从末尾取元素，重复则丢，递归处理前 length-1 项
   * 策略：自后往前递归，相同则用 splice 删掉自身
   *
   * 时间复杂度：O(n²) - 递归 n 层，每层扫前面 O(n)
   * 空间复杂度：O(n) - 递归栈深度 n
   *
   * @param arr 输入数组（会被原地修改）
   * @param length 当前处理长度（递归参数）
   * @return 去重后的数组（保序）
   */
  static unique18<T>(arr: T[], length: number): T[] {
    if (length <= 1) return arr;
    const last = length - 1;
    for (let i = last - 1; i >= 0; i--) {
      if (arr[last] === arr[i]) {
        arr.splice(last, 1);
        break;
      }
    }
    return UniqueArray.unique18(arr, length - 1);
  }

  /**
   * 方法19：递归拼接返回法
   * 核心原理：递归处理前 length-1 项，末项不重复则拼到结果末尾
   * 策略：纯函数式风格，不修改原数组
   *
   * 时间复杂度：O(n²) - 递归 n 层，每层扫前面 O(n)
   * 空间复杂度：O(n) - 递归栈加多次数组复制
   *
   * @param arr 输入数组
   * @param length 当前处理长度（递归参数）
   * @return 去重后的数组（保序）
   */
  static unique19<T>(arr: T[], length: number): T[] {
    if (length <= 1) return arr.slice(0, length);
    const last = length - 1;
    const lastItem = arr[last];
    let isRepeat = false;
    for (let i = last - 1; i >= 0; i--) {
      if (lastItem === arr[i]) {
        isRepeat = true;
        break;
      }
    }
    const head = UniqueArray.unique19(arr, length - 1);
    return isRepeat ? head : head.concat(lastItem);
  }

  /**
   * 方法20：JSON 字符串判重法（深度去重）
   * 核心原理：JSON.stringify 把任意对象映射为字符串，作为 Set 的键
   * 策略：处理对象、嵌套数组等不可哈希元素
   * 推荐场景：数组里含有对象/数组，常规 Set 无法直接判重
   *
   * 时间复杂度：O(n × m) - n 项，每项 stringify O(m) 取决于对象大小
   * 空间复杂度：O(n × m) - 字符串集合
   *
   * @param arr 输入数组（可含对象/数组等引用类型）
   * @return 去重后的数组（保序）
   */
  static unique20<T>(arr: T[]): T[] {
    const seen = new Set<string>();
    const result: T[] = [];
    for (const item of arr) {
      const key = JSON.stringify(item);
      if (!seen.has(key)) {
        seen.add(key);
        result.push(item);
      }
    }
    return result;
  }
}

// ==================== main 测试 ====================

(function main() {
  const base: number[] = [1, 3, -1, 1, 2, 2, 4, 2, 2, -1];
  const clone = (): number[] => [...base];

  // 1-14, 18-19 用泛型方法（number[]），15-17 仅接受 number[]
  const numericMethods: Array<(arr: number[]) => number[]> = [
    UniqueArray.unique1, UniqueArray.unique2, UniqueArray.unique3,
    UniqueArray.unique4, UniqueArray.unique5, UniqueArray.unique6,
    UniqueArray.unique7, UniqueArray.unique8, UniqueArray.unique9,
    UniqueArray.unique10, UniqueArray.unique11, UniqueArray.unique12,
    UniqueArray.unique13, UniqueArray.unique14, UniqueArray.unique15,
    UniqueArray.unique16, UniqueArray.unique17,
  ];

  numericMethods.forEach((fn, idx) => {
    const i = idx + 1;
    console.log(`unique${i} start: [${base.join(", ")}]`);
    console.time(`unique${i}`);
    const r = fn(clone());
    console.log(`unique${i} result: [${r.join(", ")}]`);
    console.timeEnd(`unique${i}`);
  });

  // 18. 递归原地删除
  console.log(`unique18 start: [${base.join(", ")}]`);
  console.time("unique18");
  const r18 = UniqueArray.unique18(clone(), base.length);
  console.log(`unique18 result: [${r18.join(", ")}]`);
  console.timeEnd("unique18");

  // 19. 递归拼接返回
  console.log(`unique19 start: [${base.join(", ")}]`);
  console.time("unique19");
  const r19 = UniqueArray.unique19(clone(), base.length);
  console.log(`unique19 result: [${r19.join(", ")}]`);
  console.timeEnd("unique19");

  // 20. JSON 深度去重（演示对象数组）
  const base20 = [{ id: 1 }, { id: 2 }, { id: 1 }, { id: 3 }, { id: 2 }];
  console.log(`unique20 start:`, base20);
  console.time("unique20");
  const r20 = UniqueArray.unique20(base20);
  console.log(`unique20 result:`, r20);
  console.timeEnd("unique20");
})();

/**
 * 编译运行：
 *   tsc UniqueArray.ts -t es2020 && node UniqueArray.js
 *   或直接：npx ts-node UniqueArray.ts
 *
 * 预期输出（time 数值会因机器而异，结果数据稳定）：
 *
 * unique1 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique1 result: [1, 3, -1, 2, 4]
 * unique2 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique2 result: [1, 3, -1, 2, 4]
 * unique3 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique3 result: [1, 3, -1, 2, 4]
 * unique4 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique4 result: [1, 3, -1, 2, 4]
 * unique5 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique5 result: [1, 3, -1, 2, 4]
 * unique6 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique6 result: [1, 3, -1, 2, 4]
 * unique7 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique7 result: [1, 3, -1, 2, 4]
 * unique8 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique8 result: [1, 3, -1, 2, 4]
 * unique9 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique9 result: [1, 3, -1, 2, 4]
 * unique10 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique10 result: [1, 3, -1, 2, 4]
 * unique11 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique11 result: [1, 3, -1, 2, 4]
 * unique12 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique12 result: [1, 3, -1, 2, 4]
 * unique13 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique13 result: [1, 3, -1, 2, 4]
 * unique14 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique14 result: [1, 2, 3, 4, -1]   // 数字键被引擎按升序重排，-1 作为字符串键放在最后
 * unique15 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique15 result: [-1, 1, 2, 3, 4]
 * unique16 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique16 result: [-1, 1, 2, 3, 4]
 * unique17 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique17 result: [-1, 1, 2, 3, 4]
 * unique18 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique18 result: [1, 3, -1, 2, 4]
 * unique19 start: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 * unique19 result: [1, 3, -1, 2, 4]
 * unique20 start: [ { id: 1 }, { id: 2 }, { id: 1 }, { id: 3 }, { id: 2 } ]
 * unique20 result: [ { id: 1 }, { id: 2 }, { id: 3 } ]
 */
