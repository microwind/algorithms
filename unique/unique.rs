use std::collections::{HashMap, HashSet};
use std::time::Instant;

/// 结构体 UniqueArray 用于实现多种数组去重方法
struct UniqueArray {
    arr: Vec<i32>, // 存储需要去重的数组
}

impl UniqueArray {
    /// 构造函数，初始化数组
    fn new(arr: Vec<i32>) -> Self {
        UniqueArray { arr }
    }

    /// 方法1: 使用嵌套循环实现去重
    /// 思路: 遍历数组，使用新数组保存不重复的元素
    fn unique1(&self) -> Vec<i32> {
        let start = Instant::now(); // 记录起始时间
        let mut new_arr = Vec::new();
        for &item in &self.arr {
            // 如果新数组中不存在当前元素，则添加
            if !new_arr.contains(&item) {
                new_arr.push(item);
            }
        }
        println!("Unique1 result: {:?}", new_arr); // 打印结果
        println!("Time: {:?}", start.elapsed()); // 打印执行时间
        new_arr
    }

    /// 方法2: 使用 HashSet 实现去重
    /// 思路: 利用 HashSet 的唯一性特性快速去重
    fn unique2(&self) -> Vec<i32> {
        let start = Instant::now();
        let set: HashSet<_> = self.arr.iter().cloned().collect(); // 将数组元素插入 HashSet
        let result: Vec<i32> = set.into_iter().collect(); // 转换为 Vec
        println!("Unique2 (HashSet) result: {:?}", result);
        println!("Time: {:?}", start.elapsed());
        result
    }

    /// 方法3: 使用 HashMap 实现去重
    /// 思路: 使用 HashMap 的键唯一性，同时保留插入顺序
    fn unique3(&self) -> Vec<i32> {
        let start = Instant::now();
        let mut map = HashMap::new();
        for &item in &self.arr {
            // 将元素作为键插入 HashMap
            map.entry(item).or_insert(true);
        }
        let result: Vec<i32> = map.keys().cloned().collect(); // 提取键并转换为 Vec
        println!("Unique3 (HashMap) result: {:?}", result);
        println!("Time: {:?}", start.elapsed());
        result
    }

    /// 方法4: 双循环遍历数组，自后往前删除重复元素
    /// 思路: 将数组最后一个元素与前面的元素比较，如果重复则删除
    fn unique4(&self) -> Vec<i32> {
        // 4. one array last -> first
        let mut arr = self.arr.clone(); // 克隆原数组
        let mut l = arr.len();
        // 使用 while 循环遍历数组
        while l > 0 {
            let mut i = 0;
            while i < l {
                if arr[l - 1] == arr[i] {
                    // 如果当前元素在前面已经出现过，则删除当前元素
                    arr.remove(l - 1);
                    break;  // 一旦移除元素，退出内层循环
                }
                i += 1;
            }
            l -= 1;
        }
    
        // 打印结果
        println!("one array last -> first result: {:?}", arr);
        arr
    }

    /// 方法5: 使用排序和去重
    /// 思路: 排序后删除相邻重复的元素
    fn unique5(&self) -> Vec<i32> {
        let start = Instant::now();
        let mut sorted_arr = self.arr.clone(); // 克隆原数组
        sorted_arr.sort(); // 排序
        sorted_arr.dedup(); // 去重
        println!("Unique4 (Sorted + Dedup) result: {:?}", sorted_arr);
        println!("Time: {:?}", start.elapsed());
        sorted_arr
    }

    /// 方法6: 使用手动遍历模拟 reduce 逻辑
    /// 思路: 遍历数组，将不重复的元素添加到结果数组中
    fn unique6(&self) -> Vec<i32> {
        let start = Instant::now();
        let mut result = Vec::new();
        for &item in &self.arr {
            // 如果结果数组中不存在当前元素，则添加
            if !result.contains(&item) {
                result.push(item);
            }
        }
        println!("Unique5 (Reduce-like) result: {:?}", result);
        println!("Time: {:?}", start.elapsed());
        result
    }

    /// 方法7: 使用递归实现去重
    /// 思路: 每次递归检查最后一个元素是否与之前的元素重复，如果重复则删除
    fn recursion_unique(&self, arr: Vec<i32>) -> Vec<i32> {
        if arr.len() <= 1 {
            return arr; // 如果数组长度小于等于1，直接返回
        }
        let last = arr.last().cloned().unwrap(); // 获取数组最后一个元素
        let mut rest = arr[..arr.len() - 1].to_vec(); // 截取数组的前部分
        rest = self.recursion_unique(rest); // 对前部分递归去重
        if !rest.contains(&last) {
            rest.push(last); // 如果最后一个元素不重复，则添加
        }
        rest
    }

    /// 测试递归去重方法
    fn test_recursion(&self) {
        let start = Instant::now();
        let result = self.recursion_unique(self.arr.clone());
        println!("Recursion Unique result: {:?}", result);
        println!("Time: {:?}", start.elapsed());
    }

    /// 运行所有去重测试
    fn run_all_tests(&self) {
        println!("Starting tests:");
        self.unique1(); // 方法1
        self.unique2(); // 方法2
        self.unique3(); // 方法3
        self.unique4(); // 方法4
        self.unique5(); // 方法5
        self.unique6(); // 方法6
        self.test_recursion(); // 递归去重
    }
}

fn main() {
    // 初始化测试数组
    let arr = vec![1, 1, 3, -1, 1, 2, 2, 4, 2, 2, -1];
    let unique_array = UniqueArray::new(arr);
    // 运行所有去重测试
    unique_array.run_all_tests();
}

/*
jarry@MacBook-Pro unique % rustc -V         
rustc 1.84.0 (9fc6b4312 2025-01-07)
jarry@MacBook-Pro unique % rustc ./unique.rs
jarry@MacBook-Pro unique % ./unique         
Starting tests:
Unique1 result: [1, 3, -1, 2, 4]
Time: 28.667µs
Unique2 (HashSet) result: [3, 4, 1, 2, -1]
Time: 12.042µs
Unique3 (HashMap) result: [4, -1, 3, 1, 2]
Time: 9.584µs
one array last -> first result: []
Unique4 (Sorted + Dedup) result: [-1, 1, 2, 3, 4]
Time: 3.667µs
Unique5 (Reduce-like) result: [1, 3, -1, 2, 4]
Time: 3.625µs
Recursion Unique result: [1, 3, -1, 2, 4]
Time: 5.958µs
*/