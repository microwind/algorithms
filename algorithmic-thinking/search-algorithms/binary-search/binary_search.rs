/// 二分搜索（Binary Search）- Rust 版本
///
/// 要求切片按升序排序。
/// 时间复杂度：O(log n)
/// 空间复杂度：O(1)

/// 迭代版二分搜索，返回任意一个等于 target 的下标
pub fn binary_search_iterative(arr: &[i32], target: i32) -> Option<usize> {
    let mut left: isize = 0;
    let mut right: isize = arr.len() as isize - 1;

    while left <= right {
        let mid = left + (right - left) / 2;
        let mid_val = arr[mid as usize];
        if mid_val == target {
            return Some(mid as usize);
        } else if mid_val < target {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    None
}

/// 查找第一个等于 target 的位置（左边界）
pub fn find_first_occurrence(arr: &[i32], target: i32) -> Option<usize> {
    let mut left: isize = 0;
    let mut right: isize = arr.len() as isize - 1;
    let mut result: Option<usize> = None;

    while left <= right {
        let mid = left + (right - left) / 2;
        let mid_val = arr[mid as usize];
        if mid_val == target {
            result = Some(mid as usize);
            right = mid - 1;
        } else if mid_val < target {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    result
}

/// 查找最后一个等于 target 的位置（右边界）
pub fn find_last_occurrence(arr: &[i32], target: i32) -> Option<usize> {
    let mut left: isize = 0;
    let mut right: isize = arr.len() as isize - 1;
    let mut result: Option<usize> = None;

    while left <= right {
        let mid = left + (right - left) / 2;
        let mid_val = arr[mid as usize];
        if mid_val == target {
            result = Some(mid as usize);
            left = mid + 1;
        } else if mid_val < target {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    result
}

fn main() {
    println!("========== Binary Search (Rust) ==========");
    let arr = vec![1, 3, 5, 7, 9, 11, 13];
    println!("数组: {:?}", arr);
    println!(
        "迭代查找 7 -> {:?}",
        binary_search_iterative(&arr, 7)
    );

    let arr2 = vec![1, 3, 5, 5, 5, 7, 9];
    println!("\n数组2: {:?}", arr2);
    println!("第一个 5 的位置 -> {:?}", find_first_occurrence(&arr2, 5));
    println!("最后一个 5 的位置 -> {:?}", find_last_occurrence(&arr2, 5));
}

