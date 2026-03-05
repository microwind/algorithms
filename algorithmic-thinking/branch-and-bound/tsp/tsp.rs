// 旅行商问题 - 分支定界法 (Rust)
// Author: jarry

struct TSPSolver {
    dist: Vec<Vec<i32>>,
    n: usize,
    min_cost: i32,
    best_path: Vec<usize>,
    current_path: Vec<usize>,
    visited: Vec<bool>,
}

impl TSPSolver {
    fn new(dist: Vec<Vec<i32>>) -> Self {
        let n = dist.len();
        let mut visited = vec![false; n];
        visited[0] = true;
        TSPSolver {
            dist,
            n,
            min_cost: i32::MAX,
            best_path: Vec::new(),
            current_path: vec![0],
            visited,
        }
    }

    // 下界估计
    fn lower_bound(&self, node: usize, _level: usize, cost: i32) -> i32 {
        let mut bound = cost;
        // 当前节点到未访问城市的最小边
        let mut min_edge = i32::MAX;
        for i in 0..self.n {
            if !self.visited[i] && self.dist[node][i] < min_edge {
                min_edge = self.dist[node][i];
            }
        }
        if min_edge != i32::MAX {
            bound += min_edge;
        }
        // 估计剩余路径的最小成本
        for i in 0..self.n {
            if !self.visited[i] {
                let mut min1 = i32::MAX;
                let mut min2 = i32::MAX;
                for j in 0..self.n {
                    if !self.visited[j] && i != j {
                        if self.dist[i][j] < min1 {
                            min2 = min1;
                            min1 = self.dist[i][j];
                        } else if self.dist[i][j] < min2 {
                            min2 = self.dist[i][j];
                        }
                    }
                }
                if min2 != i32::MAX {
                    bound += min1;
                }
            }
        }
        bound
    }

    // 分支定界递归
    fn branch_and_bound(&mut self, node: usize, level: usize, cost: i32) {
        if level == self.n {
            let total_cost = cost + self.dist[node][0];
            if total_cost < self.min_cost {
                self.min_cost = total_cost;
                self.best_path = self.current_path.clone();
            }
            return;
        }
        if self.lower_bound(node, level, cost) >= self.min_cost {
            return;
        }
        for i in 0..self.n {
            if !self.visited[i] {
                self.visited[i] = true;
                self.current_path.push(i);
                self.branch_and_bound(i, level + 1, cost + self.dist[node][i]);
                self.current_path.pop();
                self.visited[i] = false;
            }
        }
    }

    fn solve(&mut self) -> (i32, Vec<usize>) {
        self.branch_and_bound(0, 1, 0);
        let mut path = self.best_path.clone();
        path.push(0);
        (self.min_cost, path)
    }
}

fn main() {
    println!("============================================================");
    println!("TSP - Traveling Salesman Problem (Rust)");
    println!("============================================================\n");
    // 测试用例1
    let graph = vec![
        vec![0, 10, 15, 20],
        vec![10, 0, 35, 25],
        vec![15, 35, 0, 30],
        vec![20, 25, 30, 0],
    ];
    println!("Distance Matrix:");
    for row in &graph {
        println!("{:?}", row);
    }
    let mut solver = TSPSolver::new(graph.clone());
    let (min_cost, path) = solver.solve();
    println!("\nMinimum Tour Cost: {}", min_cost);
    print!("Tour: ");
    for (i, city) in path.iter().enumerate() {
        if i > 0 { print!(" -> "); }
        print!("{}", city);
    }
    println!("");

    // 测试用例2
    println!("\n============================================================");
    let graph2 = vec![
        vec![0, 29, 20, 32, 23],
        vec![29, 0, 21, 37, 18],
        vec![20, 21, 0, 28, 23],
        vec![32, 37, 28, 0, 34],
        vec![23, 18, 23, 34, 0],
    ];
    println!("Distance Matrix:");
    for row in &graph2 {
        println!("{:?}", row);
    }
    let mut solver2 = TSPSolver::new(graph2.clone());
    let (min_cost2, path2) = solver2.solve();
    println!("\nMinimum Tour Cost: {}", min_cost2);
    print!("Tour: ");
    for (i, city) in path2.iter().enumerate() {
        if i > 0 { print!(" -> "); }
        print!("{}", city);
    }
    println!("");
}
