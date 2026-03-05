/*
*
 * 二分查找 - 分治法的查询应用
 *
 * 前置条件：数组必须已排序
 *
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1) 迭代版本，O(log n) 递归版本
*/

// / 二分查找（迭代版本）
pub fn binary_search(arr: &[i32], target: i32) -> i32 {
    let mut left = 0i32;
    let mut right = (arr.len() as i32) - 1;

    while left <= right {
        let mid = left + (right - left) / 2;

        match arr[mid as usize].cmp(&target) {
            std::cmp::Ordering::Equal => return mid,
            std::cmp::Ordering::Less => left = mid + 1,
            std::cmp::Ordering::Greater => right = mid - 1,
        }
    }

    -1
}

// / 二分查找（递归版本）
pub fn binary_search_recursive(arr: &[i32], left: i32, right: i32, target: i32) -> i32 {
    if left > right {
        return -1;
    }

    let mid = left + (right - left) / 2;

    match arr[mid as usize].cmp(&target) {
        std::cmp::Ordering::Equal => mid,
        std::cmp::Ordering::Less => binary_search_recursive(arr, mid + 1, right, target),
        std::cmp::Ordering::Greater => binary_search_recursive(arr, left, mid - 1, target),
    }
}

// / 查找第一个 >= target 的元素位置（左边界）
pub fn binary_search_left(arr: &[i32], target: i32) -> i32 {
    let mut left = 0i32;
    let mut right = (arr.len() as i32) - 1;
    let mut result = -1;

    while left <= right {
        let mid = left + (right - left) / 2;

        if arr[mid as usize] >= target {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    result
}

fn main() {
    println!("=== 二分查找 ===\n");

    let arr = vec![1, 3, 5, 7, 9, 11, 13, 15, 17, 19];
    println!("数组: {:?}\n", arr);

    // 测试用例1：迭代版本
    println!("1. 迭代版本:");
    println!("  查找 7: {}", binary_search(&arr, 7));
    println!("  查找 20: {}\n", binary_search(&arr, 20));

    // 测试用例2：递归版本
    println!("2. 递归版本:");
    println!("  查找 9: {}", binary_search_recursive(&arr, 0, (arr.len() - 1) as i32, 9));
    println!("  查找 2: {}\n", binary_search_recursive(&arr, 0, (arr.len() - 1) as i32, 2));

    // 测试用例3：查找边界
    let arr_dup = vec![1, 2, 2, 2, 3, 4, 5, 5, 5, 6];
    println!("3. 查找边界 (数组: {:?}):", arr_dup);
    println!("  左边界 2: {}", binary_search_left(&arr_dup, 2));
    println!("  左边界 5: {}\n", binary_search_left(&arr_dup, 5));

    // 测试用例4：查找不存在的元素
    println!("4. 查找不存在的元素:");
    println!("  查找 100: {}", binary_search(&arr, 100));
    println!("  查找 0: {}", binary_search(&arr, 0));
}
