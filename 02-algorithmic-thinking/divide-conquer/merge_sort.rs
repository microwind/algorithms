/**
 * 归并排序 - 分治法的典型应用
 *
 * 分治法三个步骤：
 * 1. 分解：将数组分成两个子数组
 * 2. 求解：递归对子数组进行归并排序
 * 3. 合并：将两个已排序的子数组合并
 *
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(n)
 */

/// 合并两个已排序的数组段
fn merge(arr: &mut [i32], left: usize, mid: usize, right: usize) {
    // 创建临时向量
    let mut temp = Vec::with_capacity(right - left + 1);

    let mut i = left;
    let mut j = mid + 1;

    // 比较两个子数组的元素
    while i <= mid && j <= right {
        if arr[i] <= arr[j] {
            temp.push(arr[i]);
            i += 1;
        } else {
            temp.push(arr[j]);
            j += 1;
        }
    }

    // 复制左侧剩余元素
    while i <= mid {
        temp.push(arr[i]);
        i += 1;
    }

    // 复制右侧剩余元素
    while j <= right {
        temp.push(arr[j]);
        j += 1;
    }

    // 将临时数组复制回原数组
    for (i, &val) in temp.iter().enumerate() {
        arr[left + i] = val;
    }
}

/// 递归进行归并排序
fn merge_sort_helper(arr: &mut [i32], left: usize, right: usize) {
    if left < right {
        let mid = left + (right - left) / 2;

        // 递归排序左半部分
        merge_sort_helper(arr, left, mid);

        // 递归排序右半部分
        merge_sort_helper(arr, mid + 1, right);

        // 合并两个已排序的部分
        merge(arr, left, mid, right);
    }
}

/// 归并排序入口函数
pub fn merge_sort(arr: &mut [i32]) {
    if arr.len() <= 1 {
        return;
    }
    merge_sort_helper(arr, 0, arr.len() - 1);
}

fn main() {
    println!("=== 归并排序 ===\n");

    // 测试用例1：随机数组
    let mut arr1 = vec![64, 34, 25, 12, 22, 11, 90];
    println!("原数组: {:?}", arr1);
    merge_sort(&mut arr1);
    println!("排序后: {:?}\n", arr1);

    // 测试用例2：已排序数组
    let mut arr2 = vec![1, 2, 3, 4, 5];
    println!("已排序数组: {:?}", arr2);
    merge_sort(&mut arr2);
    println!("排序后: {:?}\n", arr2);

    // 测试用例3：反序数组
    let mut arr3 = vec![5, 4, 3, 2, 1];
    println!("反序数组: {:?}", arr3);
    merge_sort(&mut arr3);
    println!("排序后: {:?}\n", arr3);

    // 测试用例4：包含重复元素
    let mut arr4 = vec![3, 1, 4, 1, 5, 9, 2, 6];
    println!("包含重复: {:?}", arr4);
    merge_sort(&mut arr4);
    println!("排序后: {:?}", arr4);
}
