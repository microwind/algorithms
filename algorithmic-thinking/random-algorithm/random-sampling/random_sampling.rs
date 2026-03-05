use rand::Rng;

/// 随机采样（Reservoir Sampling）- Rust 版本
///
/// 从一个可迭代数据源中随机选择 k 个元素，
/// 保证每个元素被选中的概率相等（k/n）。
///
/// 时间复杂度：O(n)
/// 空间复杂度：O(k)
pub fn reservoir_sampling<T: Clone, I: IntoIterator<Item = T>>(iter: I, k: usize) -> Vec<T> {
    let mut reservoir: Vec<T> = Vec::with_capacity(k);
    let mut rng = rand::thread_rng();
    let mut i: usize = 0;

    for item in iter {
        if i < k {
            // 前 k 个元素直接进入水库
            reservoir.push(item);
        } else {
            // 对于第 i 个元素，以 k/(i+1) 的概率替换已有元素
            let j = rng.gen_range(0..=i); // 0..=i
            if j < k {
                reservoir[j] = item;
            }
        }
        i += 1;
    }

    reservoir
}

fn main() {
    println!("========== Random Sampling (Rust) ==========");

    let data: Vec<i32> = (1..=10).collect();
    println!("数据: {:?}", data);

    let k = 3;
    for t in 1..=3 {
        let sample = reservoir_sampling(data.clone(), k);
        println!("第 {} 次采样: {:?}", t, sample);
    }
}

