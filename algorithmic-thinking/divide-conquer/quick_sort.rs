/*
*
 * 快速排序 - 分治法的高效应用
 *
 * 分治法三个步骤：
 * 1. 分解：选择一个基准元素，将数组分为三部分
 * 2. 求解：递归对左右两部分进行快速排序
 * 3. 合并：基准元素已经在最终位置，无需额外合并
 *
 * 时间复杂度: O(n log n) 平均，O(n²) 最坏
 * 空间复杂度: O(log n)
*/

// / 分割函数：使用 Hoare 分割方案
fn partition(arr: &mut [i32], low: usize, high: usize) -> usize {
    let pivot = arr[high];
    let mut i = (low as i32) - 1;

    for j in low..high {
        if arr[j] < pivot {
            i += 1;
            arr.swap(i as usize, j);
        }
    }

    arr.swap((i + 1) as usize, high);
    (i + 1) as usize
}

// / 递归进行快速排序
fn quick_sort_helper(arr: &mut [i32], low: usize, high: usize) {
    if low < high {
        // 分割
        let pi = partition(arr, low, high);

        // 递归排序左右两部分
        if pi > 0 {
            quick_sort_helper(arr, low, pi - 1);
        }
        quick_sort_helper(arr, pi + 1, high);
    }
}

// / 快速排序入口函数
pub fn quick_sort(arr: &mut [i32]) {
    if arr.len() <= 1 {
        return;
    }
    quick_sort_helper(arr, 0, arr.len() - 1);
}

fn main() {
    println!("=== 快速排序 ===\n");

    // 测试用例1：随机数组
    let mut arr1 = vec![64, 34, 25, 12, 22, 11, 90];
    println!("原数组: {:?}", arr1);
    quick_sort(&mut arr1);
    println!("排序后: {:?}\n", arr1);

    // 测试用例2：已排序数组
    let mut arr2 = vec![1, 2, 3, 4, 5];
    println!("已排序数组: {:?}", arr2);
    quick_sort(&mut arr2);
    println!("排序后: {:?}\n", arr2);

    // 测试用例3：反序数组
    let mut arr3 = vec![5, 4, 3, 2, 1];
    println!("反序数组: {:?}", arr3);
    quick_sort(&mut arr3);
    println!("排序后: {:?}\n", arr3);

    // 测试用例4：包含重复元素
    let mut arr4 = vec![3, 1, 4, 1, 5, 9, 2, 6];
    println!("包含重复: {:?}", arr4);
    quick_sort(&mut arr4);
    println!("排序后: {:?}", arr4);
}
