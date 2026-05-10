// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 数组去重算法 - Rust 实现，20 种不同思路
//
// 算法原理：扫描数组，保留每个值的首次出现，丢弃后续重复
//
// 20 种实现按 5 类组织：
// - 第1类 基础循环（方法1-6）：纯下标遍历，O(n²)
// - 第2类 哈希集合（方法7-11）：HashSet/HashMap/BTreeSet
// - 第3类 排序后去重（方法12-14）：sort+dedup / 双指针
// - 第4类 迭代器与函数式（方法15-17）：fold / filter / 泛型
// - 第5类 递归与位图（方法18-20）：递归实现 + BitSet
//
// Rust 的特殊点：
// - 所有权与借用：原地修改的方法用 `mut Vec<T>`，只读的用 `&[T]`
// - HashSet/HashMap 来自 std::collections，无需第三方
// - 单文件编译：`rustc unique.rs`，不需要 Cargo 项目
//
// 应用场景：数据清洗、统计唯一值、数据库去重

use std::collections::{BTreeSet, HashMap, HashSet};
use std::hash::Hash;

// ==================== 第1类：基础循环（方法1-6） ====================
//
// 策略：不依赖任何额外数据结构，纯靠下标、嵌套循环完成判重。
// 每一步判重都是 O(n)，整体 O(n²)。
// 适用：教学、小数据、内存敏感场景。

/// 方法1：双循环 i == j 索引比较法
/// 核心原理：对每个元素向前扫描；前面没出现过则首次保留
///
/// 时间复杂度：O(n²)
/// 空间复杂度：O(n)
fn unique1(arr: &[i32]) -> Vec<i32> {
    let mut result = Vec::with_capacity(arr.len());
    for i in 0..arr.len() {
        let mut first = true;
        // 与 [0, i) 区间逐个比较，发现相同则不是首次
        for j in 0..i {
            if arr[i] == arr[j] {
                first = false;
                break;
            }
        }
        if first {
            result.push(arr[i]);
        }
    }
    result
}

/// 方法2：标记数组 frequent 法
/// 核心原理：给每个元素一个频次标记，frequent[i]==1 表示此前未出现
///
/// 时间复杂度：O(n²)
/// 空间复杂度：O(n)
fn unique2(arr: &[i32]) -> Vec<i32> {
    let n = arr.len();
    let mut freq = vec![1usize; n];
    for i in 1..n {
        for j in 0..i {
            if arr[i] == arr[j] {
                freq[i] += 1;
                break;
            }
        }
    }
    // 仅 freq==1 的位置（首次出现）才进入结果
    arr.iter()
        .zip(freq.iter())
        .filter_map(|(&v, &f)| if f == 1 { Some(v) } else { None })
        .collect()
}

/// 方法3：新建 Vec + contains 检查
/// 核心原理：维护结果切片，遍历时用线性查找判重
/// 这是最直观的"新手版"
///
/// 时间复杂度：O(n²)
/// 空间复杂度：O(n)
fn unique3(arr: &[i32]) -> Vec<i32> {
    let mut result = Vec::with_capacity(arr.len());
    for &item in arr {
        // Vec::contains 是 O(n) 线性查找
        if !result.contains(&item) {
            result.push(item);
        }
    }
    result
}

/// 方法4：原地从后往前删除
/// 核心原理：倒序扫描，与左侧任一相同则删除自身
/// 倒序的好处：删除点之后元素已处理，不影响下标
///
/// 时间复杂度：O(n²) - Vec::remove 是 O(n)
/// 空间复杂度：O(1) - 原地修改
fn unique4(mut arr: Vec<i32>) -> Vec<i32> {
    let mut l = arr.len();
    while l > 0 {
        l -= 1;
        for i in 0..l {
            if arr[l] == arr[i] {
                arr.remove(l);
                break;
            }
        }
    }
    arr
}

/// 方法5：原地从前往后删除
/// 核心原理：正序扫描，与右侧相同则删除右侧重复项
/// 删除后 j 不前进，避免漏判
///
/// 时间复杂度：O(n²)
/// 空间复杂度：O(1)
fn unique5(mut arr: Vec<i32>) -> Vec<i32> {
    let mut i = 0;
    while i < arr.len() {
        let mut j = i + 1;
        while j < arr.len() {
            if arr[i] == arr[j] {
                arr.remove(j);
                // j 不前进；删除后新的 arr[j] 是原 arr[j+1]
            } else {
                j += 1;
            }
        }
        i += 1;
    }
    arr
}

/// 方法6：iter().position 首次位置法
/// 核心原理：扫描时用 position 找该值首次出现位置，等于当前下标即首次
/// 策略：避免维护额外结果切片，靠"首次位置"性质判重
///
/// 时间复杂度：O(n²) - position 每次 O(n)
/// 空间复杂度：O(n) - 结果切片
fn unique6(arr: &[i32]) -> Vec<i32> {
    arr.iter()
        .enumerate()
        .filter_map(|(i, &v)| {
            // position 返回首次出现位置，等于 i 表示是首次
            if arr.iter().position(|&x| x == v) == Some(i) {
                Some(v)
            } else {
                None
            }
        })
        .collect()
}

// ==================== 第2类：哈希集合（方法7-11） ====================
//
// 策略：用键唯一性 O(1) 判重。
// std::collections 提供了 HashSet/HashMap/BTreeSet，工程首选。

/// 方法7：HashSet 简洁版（不保序）
/// 核心原理：HashSet 自动去重，一行 collect 完事
/// 缺点：HashSet 不保序，每次运行结果顺序可能不同
///
/// 时间复杂度：O(n) 平均
/// 空间复杂度：O(n)
fn unique7(arr: &[i32]) -> Vec<i32> {
    let set: HashSet<i32> = arr.iter().copied().collect();
    set.into_iter().collect()
}

/// 方法8：HashSet + Vec 保序遍历
/// 核心原理：HashSet 仅用作判重，输出顺序由 Vec 控制
/// 推荐场景：需要 O(n) 又要保序的工程标准写法
///
/// 时间复杂度：O(n) 平均
/// 空间复杂度：O(n)
fn unique8(arr: &[i32]) -> Vec<i32> {
    let mut seen = HashSet::with_capacity(arr.len());
    let mut result = Vec::with_capacity(arr.len());
    for &item in arr {
        // HashSet::insert 返回 true 表示新插入（首次出现）
        if seen.insert(item) {
            result.push(item);
        }
    }
    result
}

/// 方法9：BTreeSet（自动排序）
/// 核心原理：BTreeSet 是基于红黑树的有序集合
/// 等价于"去重 + 升序排序"
///
/// 时间复杂度：O(n log n)
/// 空间复杂度：O(n)
fn unique9(arr: &[i32]) -> Vec<i32> {
    let set: BTreeSet<i32> = arr.iter().copied().collect();
    set.into_iter().collect()
}

/// 方法10：HashMap 键去重 + 保序
/// 核心原理：HashMap 仅用键，值可以是 () 占位
/// 与方法8 等价，但展示 HashMap 的 entry API
///
/// 时间复杂度：O(n) 平均
/// 空间复杂度：O(n)
fn unique10(arr: &[i32]) -> Vec<i32> {
    let mut map: HashMap<i32, ()> = HashMap::with_capacity(arr.len());
    let mut result = Vec::with_capacity(arr.len());
    for &item in arr {
        // entry().or_insert_with 仅在键不存在时执行回调
        if !map.contains_key(&item) {
            map.insert(item, ());
            result.push(item);
        }
    }
    result
}

/// 方法11：HashMap 频次统计 + 保序
/// 核心原理：去重的同时统计每个值的出现次数
/// 推荐场景：去重同时需要业务统计（如"按 user_id 累计金额"）
///
/// 时间复杂度：O(n) 平均
/// 空间复杂度：O(n)
///
/// 返回：(去重后的元素列表, 与之一一对应的频次)
fn unique11(arr: &[i32]) -> (Vec<i32>, Vec<usize>) {
    let mut map: HashMap<i32, usize> = HashMap::with_capacity(arr.len());
    let mut order = Vec::with_capacity(arr.len());
    for &item in arr {
        let entry = map.entry(item).or_insert(0);
        if *entry == 0 {
            // 首次出现：记录顺序
            order.push(item);
        }
        *entry += 1;
    }
    let counts: Vec<usize> = order.iter().map(|k| map[k]).collect();
    (order, counts)
}

// ==================== 第3类：排序后去重（方法12-14） ====================
//
// 策略：先排序让相同元素相邻，再扫一遍删除相邻相同项。
// 复杂度由排序决定。

/// 方法12：sort + dedup（标准库）
/// 核心原理：标准库 Vec::dedup 删除相邻重复元素，要求先排序
/// 推荐场景：现代 Rust 工程首选写法
///
/// 时间复杂度：O(n log n) - 排序主导
/// 空间复杂度：O(1) - 原地修改（dedup 是 O(1)）
fn unique12(arr: &[i32]) -> Vec<i32> {
    let mut sorted = arr.to_vec();
    sorted.sort();           // 稳定排序，O(n log n)
    sorted.dedup();          // 原地删相邻重复，O(n)
    sorted
}

/// 方法13：sort_unstable + dedup
/// 核心原理：与方法12 相同，但用不稳定排序换更高速度
/// sort_unstable 是 introsort，基本快于 sort（稳定排序，归并）
/// 适用：不关心相同 key 的相对顺序
///
/// 时间复杂度：O(n log n) - 比 sort 常数更小
/// 空间复杂度：O(1) - 原地
fn unique13(arr: &[i32]) -> Vec<i32> {
    let mut sorted = arr.to_vec();
    sorted.sort_unstable();
    sorted.dedup();
    sorted
}

/// 方法14：手写双指针法（LeetCode 26）
/// 核心原理：原地排序后双指针扫描，慢指针指向最后一个唯一元素
/// 策略：快指针发现新值，慢指针前进并写入；O(1) 额外空间
///
/// 时间复杂度：O(n log n) - 排序主导
/// 空间复杂度：O(1)
fn unique14(arr: &[i32]) -> Vec<i32> {
    if arr.is_empty() {
        return Vec::new();
    }
    let mut sorted = arr.to_vec();
    sorted.sort();
    let mut slow = 0;
    for fast in 1..sorted.len() {
        if sorted[fast] != sorted[slow] {
            slow += 1;
            sorted[slow] = sorted[fast];
        }
    }
    sorted.truncate(slow + 1);
    sorted
}

// ==================== 第4类：迭代器与函数式（方法15-17） ====================
//
// 策略：充分利用 Rust 的 Iterator trait 与闭包，写出函数式风格。

/// 方法15：fold 折叠法
/// 核心原理：用 fold 累积一个 Vec，遇到未出现的就追加
/// 函数式风格，无显式可变状态
///
/// 时间复杂度：O(n²) - contains 每次 O(n)
/// 空间复杂度：O(n)
fn unique15(arr: &[i32]) -> Vec<i32> {
    arr.iter().fold(Vec::new(), |mut acc, &x| {
        if !acc.contains(&x) {
            acc.push(x);
        }
        acc
    })
}

/// 方法16：filter + 闭包捕获 HashSet
/// 核心原理：用闭包捕获 HashSet 状态，模拟"惰性"去重过滤器
/// 类似 itertools::unique 的实现
///
/// 时间复杂度：O(n) 平均
/// 空间复杂度：O(n)
fn unique16(arr: &[i32]) -> Vec<i32> {
    let mut seen = HashSet::with_capacity(arr.len());
    // 闭包捕获 seen，副作用谓词：首次见到返回 true
    arr.iter()
        .copied()
        .filter(|x| seen.insert(*x))
        .collect()
}

/// 方法17：泛型函数 unique<T: Eq + Hash + Clone>
/// 核心原理：trait bound 把"任意可哈希可比较的类型"统一处理
/// Rust 单态化（monomorphization）让泛型在编译期展开为具体类型
/// 推荐场景：需要支持 i32 / String / 自定义类型的通用工具
///
/// 时间复杂度：O(n) 平均
/// 空间复杂度：O(n)
fn unique17<T: Eq + Hash + Clone>(arr: &[T]) -> Vec<T> {
    let mut seen = HashSet::with_capacity(arr.len());
    let mut result = Vec::with_capacity(arr.len());
    for item in arr {
        if seen.insert(item.clone()) {
            result.push(item.clone());
        }
    }
    result
}

// ==================== 第5类：递归与位图（方法18-20） ====================
//
// 策略：递归把"线性扫描"换成"自我调用"；位图把"指针节点"换成"bit 标记"。

/// 方法18：递归原地删除法
/// 核心原理：递归从末尾取元素，重复则丢，递归处理前 length-1 项
/// 自后往前递归，相同就删除自身
///
/// 时间复杂度：O(n²) - 递归 n 层，每层扫前面 O(n) 加 remove O(n)
/// 空间复杂度：O(n) - 递归栈深度 n
fn unique18(arr: &[i32]) -> Vec<i32> {
    fn rec(mut data: Vec<i32>, length: usize) -> Vec<i32> {
        // 递归出口：长度小于等于 1
        if length <= 1 {
            return data;
        }
        let last = length - 1;
        let mut is_repeat = false;
        // 在 [0, last) 区间内查找是否存在与 data[last] 相同的元素
        for i in (0..last).rev() {
            if data[last] == data[i] {
                is_repeat = true;
                break;
            }
        }
        if is_repeat {
            data.remove(last);
        }
        rec(data, length - 1)
    }
    rec(arr.to_vec(), arr.len())
}

/// 方法19：递归拼接返回法（纯函数式）
/// 核心原理：递归处理前 length-1 项，末项不重复则拼到结果末尾
/// 不修改原切片，纯函数式风格
///
/// 时间复杂度：O(n²)
/// 空间复杂度：O(n²) - 每层都返回新 Vec
fn unique19(arr: &[i32]) -> Vec<i32> {
    fn rec(data: &[i32], length: usize) -> Vec<i32> {
        if length == 0 {
            return Vec::new();
        }
        let last = length - 1;
        let last_item = data[last];
        let mut is_repeat = false;
        // 在 [0, last) 内找一遍是否已出现过
        for i in (0..last).rev() {
            if last_item == data[i] {
                is_repeat = true;
                break;
            }
        }
        // 递归处理前 length-1 项
        let mut head = rec(data, length - 1);
        if !is_repeat {
            head.push(last_item);
        }
        head
    }
    rec(arr, arr.len())
}

/// 方法20：BitSet 位图法
/// 核心原理：每个非负整数用一位标记是否出现过
/// 用 Vec<u64> 实现位图，遇未置位则视为首次出现
/// 推荐场景：海量非负整数（10亿规模仅需约 128MB）
///
/// 时间复杂度：O(n) - 位运算 O(1)
/// 空间复杂度：O(max_value / 64)
fn unique20(arr: &[i32]) -> Vec<i32> {
    if arr.iter().any(|&v| v < 0) {
        panic!("BitSet 不支持负数，需要先做偏移");
    }
    let max_val = *arr.iter().max().unwrap_or(&0) as usize;
    let n_words = max_val / 64 + 1;
    let mut bits = vec![0u64; n_words];
    let mut result = Vec::with_capacity(arr.len());
    for &v in arr {
        let v = v as usize;
        let mask = 1u64 << (v % 64);
        // 第 v 位为 0 表示首次出现
        if bits[v / 64] & mask == 0 {
            bits[v / 64] |= mask;
            result.push(v as i32);
        }
    }
    result
}

// ==================== main 函数 ====================

fn main() {
    let base = vec![1, 3, -1, 1, 2, 2, 4, 2, 2, -1];
    println!("base: {:?}\n", base);

    // ---- 第1类：基础循环（O(n²)，保序） ----
    println!("---- 第1类：基础循环（O(n²)，保序） ----");
    println!("unique1  (双循环 i==j):       {:?}", unique1(&base));
    println!("unique2  (frequent 标记):     {:?}", unique2(&base));
    println!("unique3  (Vec::contains):     {:?}", unique3(&base));
    println!("unique4  (原地反向删除):      {:?}", unique4(base.clone()));
    println!("unique5  (原地正向删除):      {:?}", unique5(base.clone()));
    println!("unique6  (position 首次):     {:?}", unique6(&base));
    println!();

    // ---- 第2类：哈希集合（O(n)） ----
    println!("---- 第2类：哈希集合（O(n)） ----");
    // HashSet 输出无序：排序后再打印，便于对照
    let mut h7 = unique7(&base);
    h7.sort();
    println!("unique7  (HashSet 不保序+排): {:?}", h7);
    println!("unique8  (HashSet 保序):      {:?}", unique8(&base));
    println!("unique9  (BTreeSet 自动排):   {:?}", unique9(&base));
    println!("unique10 (HashMap 键去重):    {:?}", unique10(&base));
    let (order, counts) = unique11(&base);
    println!("unique11 (HashMap 频次):      {:?}  freq={:?}", order, counts);
    println!();

    // ---- 第3类：排序后去重（输出升序） ----
    println!("---- 第3类：排序后去重（O(n log n)，输出升序） ----");
    println!("unique12 (sort+dedup):        {:?}", unique12(&base));
    println!("unique13 (sort_unstable):     {:?}", unique13(&base));
    println!("unique14 (双指针 LeetCode26): {:?}", unique14(&base));
    println!();

    // ---- 第4类：迭代器与函数式 ----
    println!("---- 第4类：迭代器与函数式 ----");
    println!("unique15 (fold 折叠):         {:?}", unique15(&base));
    println!("unique16 (filter+HashSet):    {:?}", unique16(&base));
    // 方法17 是泛型，演示 i32 与 &str 两种类型
    println!("unique17 (泛型 i32):          {:?}", unique17(&base));
    let strs = vec!["apple", "banana", "apple", "cherry", "banana"];
    println!("unique17 (泛型 &str):         {:?}", unique17(&strs));
    println!();

    // ---- 第5类：递归与位图 ----
    println!("---- 第5类：递归与位图 ----");
    println!("unique18 (递归原地删除):      {:?}", unique18(&base));
    println!("unique19 (递归拼接返回):      {:?}", unique19(&base));
    // 方法20 仅支持非负值
    let pos = vec![1, 3, 1, 2, 2, 4, 2, 2];
    println!("unique20 (BitSet 仅非负):     {:?}  [输入: {:?}]", unique20(&pos), pos);
}

/*
 * 编译运行：
 *   rustc unique.rs -o ./unique_rs && ./unique_rs
 *
 * 预期输出（已实测，rustc 1.84+）：
 *
 * base: [1, 3, -1, 1, 2, 2, 4, 2, 2, -1]
 *
 * ---- 第1类：基础循环（O(n²)，保序） ----
 * unique1  (双循环 i==j):       [1, 3, -1, 2, 4]
 * unique2  (frequent 标记):     [1, 3, -1, 2, 4]
 * unique3  (Vec::contains):     [1, 3, -1, 2, 4]
 * unique4  (原地反向删除):      [1, 3, -1, 2, 4]
 * unique5  (原地正向删除):      [1, 3, -1, 2, 4]
 * unique6  (position 首次):     [1, 3, -1, 2, 4]
 *
 * ---- 第2类：哈希集合（O(n)） ----
 * unique7  (HashSet 不保序+排): [-1, 1, 2, 3, 4]
 * unique8  (HashSet 保序):      [1, 3, -1, 2, 4]
 * unique9  (BTreeSet 自动排):   [-1, 1, 2, 3, 4]
 * unique10 (HashMap 键去重):    [1, 3, -1, 2, 4]
 * unique11 (HashMap 频次):      [1, 3, -1, 2, 4]  freq=[2, 1, 2, 4, 1]
 *
 * ---- 第3类：排序后去重（O(n log n)，输出升序） ----
 * unique12 (sort+dedup):        [-1, 1, 2, 3, 4]
 * unique13 (sort_unstable):     [-1, 1, 2, 3, 4]
 * unique14 (双指针 LeetCode26): [-1, 1, 2, 3, 4]
 *
 * ---- 第4类：迭代器与函数式 ----
 * unique15 (fold 折叠):         [1, 3, -1, 2, 4]
 * unique16 (filter+HashSet):    [1, 3, -1, 2, 4]
 * unique17 (泛型 i32):          [1, 3, -1, 2, 4]
 * unique17 (泛型 &str):         ["apple", "banana", "cherry"]
 *
 * ---- 第5类：递归与位图 ----
 * unique18 (递归原地删除):      [1, 3, -1, 2, 4]
 * unique19 (递归拼接返回):      [1, 3, -1, 2, 4]
 * unique20 (BitSet 仅非负):     [1, 3, 2, 4]  [输入: [1, 3, 1, 2, 2, 4, 2, 2]]
 */
