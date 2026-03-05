// 深度优先搜索（DFS）实现 (Rust)
//
// 特点：
// - 优先往纵深方向探索
// - 使用栈或递归
// - 回溯机制
// - 时间复杂度：O(V + E)
// - 空间复杂度：O(V)

use std::collections::VecDeque;

// 图结构（邻接表）
#[derive(Debug, Clone)]
pub struct Graph {
    adj_lists: Vec<Vec<usize>>,
    num_vertices: usize,
}

impl Graph {
    // 初始化图
    pub fn new(vertices: usize) -> Self {
        Graph {
            adj_lists: vec![Vec::new(); vertices],
            num_vertices: vertices,
        }
    }

    // 添加边（无向图）
    pub fn add_edge(&mut self, src: usize, dest: usize) {
        self.adj_lists[src].push(dest);
        self.adj_lists[dest].push(src); // 无向图
    }

    // DFS递归实现
    fn dfs_recursive(&self, vertex: usize, visited: &mut [bool], result: &mut Vec<usize>) {
        // 标记当前顶点为已访问
        visited[vertex] = true;
        result.push(vertex);

        // 递归访问所有未访问的邻接顶点
        for &adj_vertex in &self.adj_lists[vertex] {
            if !visited[adj_vertex] {
                self.dfs_recursive(adj_vertex, visited, result);
            }
        }
    }

    // DFS递归遍历（包装函数）
    pub fn dfs_recursive_traversal(&self, start_vertex: usize) -> Vec<usize> {
        let mut visited = vec![false; self.num_vertices];
        let mut result = Vec::new();
        
        self.dfs_recursive(start_vertex, &mut visited, &mut result);
        result
    }

    // DFS迭代实现（使用栈）
    pub fn dfs_iterative(&self, start_vertex: usize) -> Vec<usize> {
        let mut visited = vec![false; self.num_vertices];
        let mut stack = Vec::new();
        let mut result = Vec::new();

        // 将起始顶点入栈
        stack.push(start_vertex);

        while let Some(current_vertex) = stack.pop() {
            // 如果该顶点未被访问
            if !visited[current_vertex] {
                visited[current_vertex] = true;
                result.push(current_vertex);

                // 将所有未访问的邻接顶点入栈
                // 注意：为了保持与递归相似的顺序，需要反向入栈
                for &adj_vertex in self.adj_lists[current_vertex].iter().rev() {
                    if !visited[adj_vertex] {
                        stack.push(adj_vertex);
                    }
                }
            }
        }

        result
    }

    // DFS查找路径
    fn dfs_find_path(
        &self,
        current: usize,
        target: usize,
        visited: &mut [bool],
        path: &mut Vec<usize>,
    ) -> bool {
        // 标记当前顶点为已访问
        visited[current] = true;
        path.push(current);

        // 如果找到目标
        if current == target {
            return true;
        }

        // 递归访问所有邻接顶点
        for &adj_vertex in &self.adj_lists[current] {
            if !visited[adj_vertex] {
                if self.dfs_find_path(adj_vertex, target, visited, path) {
                    return true;
                }
            }
        }

        // 回溯：从路径中移除当前顶点
        path.pop();
        false
    }

    // 查找两点之间的路径
    pub fn find_path(&self, start: usize, end: usize) -> Option<Vec<usize>> {
        let mut visited = vec![false; self.num_vertices];
        let mut path = Vec::new();

        if self.dfs_find_path(start, end, &mut visited, &mut path) {
            Some(path)
        } else {
            None
        }
    }

    // DFS检测环
    fn dfs_detect_cycle(&self, vertex: usize, parent: usize, visited: &mut [bool]) -> bool {
        visited[vertex] = true;

        for &adj_vertex in &self.adj_lists[vertex] {
            // 如果邻接顶点未被访问，递归检查
            if !visited[adj_vertex] {
                if self.dfs_detect_cycle(adj_vertex, vertex, visited) {
                    return true;
                }
            }
            // 如果邻接顶点已被访问且不是父节点，则存在环
            else if adj_vertex != parent {
                return true;
            }
        }

        false
    }

    // 检测图中是否存在环
    pub fn has_cycle(&self) -> bool {
        let mut visited = vec![false; self.num_vertices];

        for i in 0..self.num_vertices {
            if !visited[i] {
                if self.dfs_detect_cycle(i, self.num_vertices, &mut visited) {
                    return true;
                }
            }
        }

        false
    }

    // DFS计算连通分量
    pub fn dfs_connected_components(&self) -> Vec<Vec<usize>> {
        let mut visited = vec![false; self.num_vertices];
        let mut components = Vec::new();

        for i in 0..self.num_vertices {
            if !visited[i] {
                let mut component = Vec::new();
                self.dfs_recursive(i, &mut visited, &mut component);
                components.push(component);
            }
        }

        components
    }

    // DFS拓扑排序（用于有向无环图）
    pub fn dfs_topological_sort(&self) -> Vec<usize> {
        let mut visited = vec![false; self.num_vertices];
        let mut stack = Vec::new();

        // 对每个未访问的顶点进行DFS
        for i in 0..self.num_vertices {
            if !visited[i] {
                self.topological_sort_util(i, &mut visited, &mut stack);
            }
        }

        // 弹出栈中的元素得到拓扑排序
        stack.reverse();
        stack
    }

    // 拓扑排序的辅助函数
    fn topological_sort_util(&self, vertex: usize, visited: &mut [bool], stack: &mut Vec<usize>) {
        visited[vertex] = true;

        for &adj_vertex in &self.adj_lists[vertex] {
            if !visited[adj_vertex] {
                self.topological_sort_util(adj_vertex, visited, stack);
            }
        }

        // 将顶点入栈
        stack.push(vertex);
    }

    // 获取转置图（用于强连通分量）
    fn get_transpose(&self) -> Graph {
        let mut transposed = Graph::new(self.num_vertices);

        for v in 0..self.num_vertices {
            for &adj_vertex in &self.adj_lists[v] {
                transposed.adj_lists[adj_vertex].push(v);
            }
        }

        transposed
    }

    // 填充顺序的辅助函数
    fn fill_order(&self, vertex: usize, visited: &mut [bool], stack: &mut Vec<usize>) {
        visited[vertex] = true;

        for &adj_vertex in &self.adj_lists[vertex] {
            if !visited[adj_vertex] {
                self.fill_order(adj_vertex, visited, stack);
            }
        }

        stack.push(vertex);
    }

    // DFS检测强连通分量（用于有向图）
    pub fn dfs_strongly_connected_components(&self) -> Vec<Vec<usize>> {
        // Kosaraju算法
        let mut visited = vec![false; self.num_vertices];
        let mut stack = Vec::new();

        // 第一步：对原图进行DFS，将顶点按完成时间入栈
        for i in 0..self.num_vertices {
            if !visited[i] {
                self.fill_order(i, &mut visited, &mut stack);
            }
        }

        // 第二步：创建转置图
        let transposed = self.get_transpose();

        // 第三步：按栈中顺序对转置图进行DFS
        visited = vec![false; self.num_vertices];
        let mut components = Vec::new();

        while let Some(vertex) = stack.pop() {
            if !visited[vertex] {
                let mut component = Vec::new();
                transposed.dfs_recursive(vertex, &mut visited, &mut component);
                components.push(component);
            }
        }

        components
    }

    // 检查是否为二分图
    pub fn is_bipartite(&self) -> bool {
        let mut color = vec![0; self.num_vertices]; // 0: 未染色, 1: 染色A, -1: 染色B

        for i in 0..self.num_vertices {
            if color[i] == 0 {
                let mut stack = Vec::new();
                color[i] = 1;
                stack.push(i);

                while let Some(current_vertex) = stack.pop() {
                    for &adj_vertex in &self.adj_lists[current_vertex] {
                        if color[adj_vertex] == 0 {
                            color[adj_vertex] = -color[current_vertex];
                            stack.push(adj_vertex);
                        } else if color[adj_vertex] == color[current_vertex] {
                            return false;
                        }
                    }
                }
            }
        }

        true
    }
}

fn main() {
    println!("=== 深度优先搜索（DFS）演示 ===\n");

    // 创建图
    let mut graph = Graph::new(8);

    // 添加边
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);
    graph.add_edge(2, 5);
    graph.add_edge(2, 6);
    graph.add_edge(3, 7);
    graph.add_edge(4, 7);
    graph.add_edge(5, 6);

    println!("图结构:");
    println!("0 -- 1 -- 3 -- 7");
    println!("|    |         |");
    println!("|    |         |");
    println!("2 -- 4 --------|");
    println!("|    |");
    println!("|    |");
    println!("5 -- 6\n");

    // 1. DFS递归遍历
    println!("1. DFS递归遍历（从顶点0开始）");
    let recursive_result = graph.dfs_recursive_traversal(0);
    println!("结果: {:?}", recursive_result);
    println!();

    // 2. DFS迭代遍历
    println!("2. DFS迭代遍历（从顶点0开始）");
    let iterative_result = graph.dfs_iterative(0);
    println!("结果: {:?}", iterative_result);
    println!();

    // 3. 查找路径
    println!("3. 查找路径");
    match graph.find_path(0, 7) {
        Some(path) => println!("从 0 到 7 的路径: {:?}", path),
        None => println!("未找到从 0 到 7 的路径"),
    }
    println!();

    // 4. 检测环
    println!("4. 检测环");
    if graph.has_cycle() {
        println!("图中存在环");
    } else {
        println!("图中不存在环");
    }
    println!();

    // 5. 计算连通分量
    println!("5. 计算连通分量");
    let components = graph.dfs_connected_components();
    println!("连通分量数: {}", components.len());
    for (i, component) in components.iter().enumerate() {
        println!("分量 {}: {:?}", i + 1, component);
    }
    println!();

    // 6. 从不同起点开始DFS
    println!("6. 从不同起点开始DFS");
    println!("从顶点3开始（递归）: {:?}", graph.dfs_recursive_traversal(3));
    println!("从顶点3开始（迭代）: {:?}", graph.dfs_iterative(3));

    // 7. 检查是否为二分图
    println!("\n7. 检查是否为二分图");
    if graph.is_bipartite() {
        println!("该图是二分图");
    } else {
        println!("该图不是二分图");
    }
}
