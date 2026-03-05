/// 线性搜索（Linear Search）- Rust 版本
///
/// 依次扫描切片中的元素，找到目标值所在的下标。
/// 时间复杂度：O(n)
/// 空间复杂度：O(1)

/// 返回第一个等于 target 的下标，未找到返回 None
pub fn linear_search<T: PartialEq>(arr: &[T], target: &T) -> Option<usize> {
    for (i, v) in arr.iter().enumerate() {
        if v == target {
            return Some(i);
        }
    }
    None
}

/// 返回所有等于 target 的下标
pub fn linear_search_all<T: PartialEq>(arr: &[T], target: &T) -> Vec<usize> {
    let mut indices = Vec::new();
    for (i, v) in arr.iter().enumerate() {
        if v == target {
            indices.push(i);
        }
    }
    indices
}

fn main() {
    println!("========== Linear Search (Rust) ==========");
    let arr = vec![5, 2, 8, 1, 9, 3, 7];
    println!("数组: {:?}", arr);
    println!("查找 8 -> {:?}", linear_search(&arr, &8));
    println!("查找 10 -> {:?}", linear_search(&arr, &10));

    let arr2 = vec![1, 2, 3, 2, 4, 2];
    println!("数组2: {:?}", arr2);
    let indices = linear_search_all(&arr2, &2);
    println!("查找所有 2 -> {:?}", indices);
}

