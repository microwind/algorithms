// 任务分配问题 - 分支定界法 (Rust)
// Author: jarry

use std::cmp;

struct TaskAssignment {
    cost: Vec<Vec<i32>>,
    n: usize,
    min_cost: i32,
    best_assignment: Vec<usize>,
    current_assignment: Vec<usize>,
    assigned_workers: Vec<bool>,
}

impl TaskAssignment {
    fn new(cost_matrix: Vec<Vec<i32>>) -> Self {
        let n = cost_matrix.len();
        TaskAssignment {
            cost: cost_matrix,
            n,
            min_cost: i32::MAX,
            best_assignment: vec![0; n],
            current_assignment: vec![0; n],
            assigned_workers: vec![false; n],
        }
    }

    // 下界估计（贪心）
    fn lower_bound(&self, task_idx: usize) -> i32 {
        let mut bound = 0;
        for i in task_idx..self.n {
            let mut min_cost = i32::MAX;
            for j in 0..self.n {
                if !self.assigned_workers[j] && self.cost[i][j] < min_cost {
                    min_cost = self.cost[i][j];
                }
            }
            if min_cost != i32::MAX {
                bound += min_cost;
            }
        }
        bound
    }

    // 分支定界搜索
    fn branch_and_bound(&mut self, task_idx: usize, current_cost: i32) {
        if current_cost + self.lower_bound(task_idx) >= self.min_cost {
            return;
        }
        if task_idx == self.n {
            if current_cost < self.min_cost {
                self.min_cost = current_cost;
                self.best_assignment.copy_from_slice(&self.current_assignment);
            }
            return;
        }
        for worker in 0..self.n {
            if !self.assigned_workers[worker] {
                self.current_assignment[task_idx] = worker;
                self.assigned_workers[worker] = true;
                self.branch_and_bound(task_idx + 1, current_cost + self.cost[task_idx][worker]);
                self.assigned_workers[worker] = false;
            }
        }
    }

    fn solve(&mut self) -> (i32, Vec<usize>) {
        self.branch_and_bound(0, 0);
        (self.min_cost, self.best_assignment.clone())
    }
}

fn main() {
    println!("============================================================");
    println!("Task Assignment Problem (Rust)");
    println!("============================================================\n");

    // 测试用例1
    let cost_matrix = vec![
        vec![5, 7, 9],
        vec![6, 8, 4],
        vec![3, 5, 7],
    ];
    println!("Test Case 1:");
    println!("Cost Matrix:");
    for (i, row) in cost_matrix.iter().enumerate() {
        println!("Task {}: {:?}", i, row);
    }
    let mut solver = TaskAssignment::new(cost_matrix.clone());
    let (min_cost, assignment) = solver.solve();
    println!("\nMinimum Cost: {}", min_cost);
    println!("Assignment:");
    for (task, &worker) in assignment.iter().enumerate() {
        println!("Task {} -> Worker {} (cost: {})", task, worker, cost_matrix[task][worker]);
    }

    // 测试用例2
    println!("\n============================================================");
    let cost_matrix2 = vec![
        vec![10, 2, 3, 4],
        vec![4, 13, 8, 9],
        vec![14, 4, 13, 10],
        vec![4, 7, 5, 12],
    ];
    println!("Test Case 2:");
    println!("Cost Matrix:");
    for (i, row) in cost_matrix2.iter().enumerate() {
        println!("Task {}: {:?}", i, row);
    }
    let mut solver2 = TaskAssignment::new(cost_matrix2.clone());
    let (min_cost2, assignment2) = solver2.solve();
    println!("\nMinimum Cost: {}", min_cost2);
    println!("Assignment:");
    for (task, &worker) in assignment2.iter().enumerate() {
        println!("Task {} -> Worker {} (cost: {})", task, worker, cost_matrix2[task][worker]);
    }
}
