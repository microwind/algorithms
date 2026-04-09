/*
版权所有 © https://github.com/microwind 保留所有权利
@author: jarryli@gmail.com
@version: 1.0

树搜索算法 - 矩阵节点路径查找
实现BFS和DFS用于二维矩阵中的最短路径查找
用于路径查找、迷宫求解、图遍历等
支持4方向移动和多条最短路径
*/

use std::collections::{VecDeque, HashSet};
use std::rc::Rc;
use std::cell::RefCell;

/// 具有4方向连接的矩阵节点
/// 表示二维网格/矩阵结构中的节点
/// 支持四个方向移动：上、下、左、右
#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub struct MatrixNode {
    pub data: i32,                     // 节点存储的数据
    pub up: Option<Rc<RefCell<MatrixNode>>>,     // 上方节点连接
    pub down: Option<Rc<RefCell<MatrixNode>>>,   // 下方节点连接
    pub left: Option<Rc<RefCell<MatrixNode>>>,    // 左侧节点连接
    pub right: Option<Rc<RefCell<MatrixNode>>>,   // 右侧节点连接
}

impl MatrixNode {
    /// 创建新的矩阵节点
    pub fn new(data: i32) -> Self {
        Self {
            data,
            up: None,
            down: None,
            left: None,
            right: None,
        }
    }
}

/// 矩阵搜索结构，实现BFS和DFS路径查找
pub struct MatrixSearch {
    head: Option<Rc<RefCell<MatrixNode>>>,
}

impl MatrixSearch {
    /// 创建新的矩阵搜索实例
    pub fn new() -> Self {
        Self { head: None }
    }
    
    /**
     * 创建n x n的互连矩阵节点
     * 
     * 算法:
     * 1. 创建n x n的节点矩阵
     * 2. 用顺序数据初始化每个节点
     * 3. 建立水平连接（左右）
     * 4. 建立垂直连接（上下）
     * 
     * 时间复杂度: O(n²) - 处理n²个节点
     * 空间复杂度: O(n²) - 存储n²个节点
     * 
     * @param n 矩阵维度 (n x n)
     * @return 头节点（左上角）
     */
    pub fn create_matrix(&mut self, n: i32) -> Rc<RefCell<MatrixNode>> {
        let mut matrix: Vec<Vec<Rc<RefCell<MatrixNode>>>> = vec![vec![]; n as usize];
        
        // 初始化n x n节点矩阵
        for i in 0..n {
            for j in 0..n {
                let node = Rc::new(RefCell::new(MatrixNode::new(i * n + j + 1)));
                matrix[i as usize].push(node);
            }
        }
        
        // 连接左右（水平连接）
        for i in 0..n {
            for j in 0..n - 1 {
                let left = matrix[i as usize][j as usize].clone();
                let right = matrix[i as usize][(j + 1) as usize].clone();
                matrix[i as usize][(j + 1) as usize].borrow_mut().left = Some(left);
                matrix[i as usize][j as usize].borrow_mut().right = Some(right);
            }
        }

        // 连接上下
        for i in 0..n - 1 {
            for j in 0..n {
                let up = matrix[i as usize][j as usize].clone();
                let down = matrix[(i + 1) as usize][j as usize].clone();
                matrix[(i + 1) as usize][j as usize].borrow_mut().up = Some(up);
                matrix[i as usize][j as usize].borrow_mut().down = Some(down);
            }
        }

        self.head = Some(matrix[0][0].clone());
        matrix[0][0].clone()
    }
    
    /**
     * 从头节点开始打印矩阵
     * 
     * 算法:
     * 1. 从头节点开始逐行遍历
     * 2. 使用down指针移动到下一行
     * 3. 使用right指针在每行内遍历
     * 4. 打印每个节点的数据值
     * 
     * @param n 矩阵维度
     */
    pub fn print_matrix(&self, n: i32) {
        if let Some(ref head) = self.head {
            let mut current_row = Some(head.clone());
            
            for _ in 0..n {
                let mut current = current_row.clone();
                for _ in 0..n {
                    if let Some(ref node) = current {
                        print!("{} ", node.borrow().data);
                        current = node.borrow().right.clone();
                    }
                }
                println!();
                if let Some(ref node) = current_row {
                    current_row = node.borrow().down.clone();
                }
            }
        } else {
            println!("矩阵未创建");
        }
    }
    
    /**
     * 使用BFS查找最短路径
     * 
     * 算法:
     * 1. 使用队列进行层序遍历
     * 2. 跟踪最短路径长度
     * 3. 探索所有最小长度路径
     * 4. 使用路径跟踪避免循环
     * 
     * 时间复杂度: O(V + E) - V=顶点数, E=边数
     * 空间复杂度: O(V) - 用于队列和路径存储
     * 
     * @param start 起始节点
     * @param end 目标节点
     * @return 最短路径数组
     */
    pub fn find_shortest_paths_bfs(
        &self,
        start: &Rc<RefCell<MatrixNode>>,
        end: &Rc<RefCell<MatrixNode>>,
    ) -> Vec<Vec<Rc<RefCell<MatrixNode>>>> {
        let mut queue: VecDeque<Vec<Rc<RefCell<MatrixNode>>>> = VecDeque::new();
        let mut paths: Vec<Vec<Rc<RefCell<MatrixNode>>>> = vec![];
        let mut shortest_length: Option<usize> = None;
        
        queue.push_back(vec![start.clone()]);
        
        while let Some(current_path) = queue.pop_front() {
            let current = &current_path[current_path.len() - 1];
            
            // 检查是否到达目标
            if current.borrow().data == end.borrow().data {
                match shortest_length {
                    None => {
                        shortest_length = Some(current_path.len());
                        paths.push(current_path);
                    }
                    Some(len) if current_path.len() < len => {
                        shortest_length = Some(current_path.len());
                        paths = vec![current_path];
                    }
                    Some(len) if current_path.len() == len => {
                        paths.push(current_path);
                    }
                    _ => {}
                }
                continue;
            }
            
            // 如果已找到最短路径且当前路径更长，跳过
            if let Some(len) = shortest_length {
                if current_path.len() >= len {
                    continue;
                }
            }
            
            // 探索邻居节点
            let neighbors = vec![
                current.borrow().left.clone(),
                current.borrow().up.clone(),
                current.borrow().down.clone(),
                current.borrow().right.clone(),
            ];
            
            for neighbor in neighbors {
                if let Some(neighbor_node) = neighbor {
                    // 检查是否已在路径中
                    let in_path = current_path.iter().any(|node| {
                        node.borrow().data == neighbor_node.borrow().data
                    });
                    
                    if !in_path {
                        let mut new_path = current_path.clone();
                        new_path.push(neighbor_node);
                        queue.push_back(new_path);
                    }
                }
            }
        }
        
        paths
    }
    
    /**
     * 打印所有找到的路径
     * 
     * @param paths 路径数组
     */
    pub fn print_paths(&self, paths: &Vec<Vec<Rc<RefCell<MatrixNode>>>>) {
        if paths.is_empty() {
            println!("未找到路径");
            return;
        }
        
        println!("最短路径（长度 {}）:", paths[0].len());
        for (i, path) in paths.iter().enumerate() {
            print!("  路径 {}: ", i + 1);
            for (j, node) in path.iter().enumerate() {
                print!("{}", node.borrow().data);
                if j < path.len() - 1 {
                    print!(" -> ");
                }
            }
            println!();
        }
    }
    
    /// 打印分隔线
    pub fn print_separator() {
        println!("{}", "=".repeat(60));
    }
}

/**
 * 主测试函数
 * 
 * 测试用例:
 * 1. 创建3x3矩阵网络
 * 2. 演示矩阵结构
 * 3. 使用BFS查找最短路径
 * 4. 比较算法特性
 */
fn main() {
    let n = 3;
    let mut search = MatrixSearch::new();
    let head = search.create_matrix(n);
    
    search.print_separator();
    println!("树搜索算法 - 矩阵节点路径查找");
    search.print_separator();
    println!();
    
    println!("矩阵结构 ({}x{}):", n, n);
    search.print_matrix(n);
    println!();
    
    // 查找特定节点用于演示
    let node2 = head.borrow().right.clone().unwrap(); // 值为2的节点
    let mut node9 = head.clone(); // 从头节点开始
    // 导航到节点9（右下角）
    for _ in 0..n - 1 {
        node9 = node9.borrow().down.clone().unwrap();
    }
    for _ in 0..n - 1 {
        node9 = node9.borrow().right.clone().unwrap();
    }
    
    // BFS搜索
    println!("从 {} 到 {} 的BFS最短路径:", node2.borrow().data, node9.borrow().data);
    let bfs_paths = search.find_shortest_paths_bfs(&node2, &node9);
    search.print_paths(&bfs_paths);
    println!();
    
    println!("=== 算法特性 ===");
    println!("BFS（广度优先搜索）:");
    println!("  - 保证在无权图中找到最短路径");
    println!("  - 使用队列进行层序遍历");
    println!("  - 适用于最短路径查找");
    
    println!("\n复杂度分析:");
    println!("  - 时间复杂度: O(V + E)，其中V是顶点数，E是边数");
    println!("  - 空间复杂度: O(V)，用于队列/递归栈");
    println!("  - 矩阵导航: 4方向移动（上、下、左、右）");
    
    println!("\n=== 应用场景 ===");
    println!("矩阵路径查找用于:");
    println!("  - 迷宫求解和益智游戏");
    println!("  - 网络路由和导航");
    println!("  - 游戏AI和路径查找");
    println!("  - 电路板设计");
    println!("  - 图像处理和分析");
}
