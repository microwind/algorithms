use rand::prelude::*;

/// 洗牌算法（Shuffle）- Rust 版本
///
/// 使用 Fisher–Yates 洗牌算法，对切片进行等概率随机打乱。
/// 提供两个函数：
/// - `shuffle_in_place`：原地洗牌，直接修改切片
/// - `shuffled_vec`：返回打乱后的新向量，原数据不变

/// 原地洗牌：对可变切片进行 Fisher–Yates 随机打乱
pub fn shuffle_in_place<T>(arr: &mut [T]) {
    let mut rng = thread_rng();
    // 从最后一个元素开始，逐个与前面随机位置交换
    for i in (1..arr.len()).rev() {
        // 在 [0, i] 范围内生成随机下标
        let j = rng.gen_range(0..=i);
        arr.swap(i, j);
    }
}

/// 返回打乱后的新向量，原切片不变
pub fn shuffled_vec<T: Clone>(arr: &[T]) -> Vec<T> {
    let mut v = arr.to_vec();
    shuffle_in_place(&mut v);
    v
}

fn main() {
    println!("========== Shuffle (Rust) ==========");
    let original = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
    println!("原向量: {:?}", original);

    let mut in_place = original.clone();
    shuffle_in_place(&mut in_place);
    println!("原地洗牌结果: {:?}", in_place);

    let shuffled = shuffled_vec(&original);
    println!("新向量洗牌结果: {:?}", shuffled);
    println!("原向量保持不变: {:?}", original);
}

