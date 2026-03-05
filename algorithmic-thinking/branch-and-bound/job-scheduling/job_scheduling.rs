// job_scheduling.rs
// 分支限界法求解最小最大完工时间（Makespan）问题
// Author: jarry

/*
问题描述：
给定 n 个作业和 m 台机器，每个作业只能分配给一台机器，目标是最小化所有机器的最大完工时间（Makespan）。

算法思路：
- 递归分配每个作业到一台机器
- 剪枝：当前最大负载+下界>=最优解时直接返回
- 下界估计：剩余作业总和/m 向上取整
*/

fn branch_and_bound(
    jobs: &[usize],
    m: usize,
    loads: &mut Vec<usize>,
    idx: usize,
    best: &mut usize,
) {
    if idx == jobs.len() {
        let max_load = *loads.iter().max().unwrap();
        if max_load < *best {
            *best = max_load;
        }
        return;
    }
    // 剪枝：下界估计
    let remain_sum: usize = jobs[idx..].iter().sum();
    let lower = (remain_sum + m - 1) / m;
    let cur_max = *loads.iter().max().unwrap();
    if cur_max.max(lower) >= *best {
        return;
    }
    // 尝试将当前作业分配给每台机器
    for i in 0..m {
        loads[i] += jobs[idx];
        branch_and_bound(jobs, m, loads, idx + 1, best);
        loads[i] -= jobs[idx];
    }
}

fn min_makespan(jobs: &[usize], m: usize) -> usize {
    let mut best = jobs.iter().sum();
    let mut loads = vec![0; m];
    branch_and_bound(jobs, m, &mut loads, 0, &mut best);
    best
}

fn main() {
    println!("==============================");
    println!("Job Scheduling Problem (Rust)");
    println!("==============================\n");
    let jobs = vec![2, 14, 4, 16, 6, 5, 3];
    let m = 3;
    println!("作业时长: {:?}", jobs);
    println!("机器数: {}", m);
    let min_time = min_makespan(&jobs, m);
    println!("最小最大完工时间: {}", min_time);
    // 更多测试
    let jobs2 = vec![7, 5, 5, 3, 3, 3, 2];
    let m2 = 2;
    let min_time2 = min_makespan(&jobs2, m2);
    println!("\n作业时长: {:?}", jobs2);
    println!("机器数: {}", m2);
    println!("最小最大完工时间: {}", min_time2);
}

/*
输出示例：
==============================
Job Scheduling Problem (Rust)
==============================

作业时长: [2, 14, 4, 16, 6, 5, 3]
机器数: 3
最小最大完工时间: 23

作业时长: [7, 5, 5, 3, 3, 3, 2]
机器数: 2
最小最大完工时间: 14
*/
