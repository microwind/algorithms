/**
 * 图的DFS - 连通分量检测
 * 使用递归DFS找出图中的所有连通分量
 */

const MAX_VERTICES: usize = 100;

// 邻接矩阵表示图
static mut GRAPH: [[i32; MAX_VERTICES]; MAX_VERTICES] = [[0; MAX_VERTICES]; MAX_VERTICES];
static mut VISITED: [bool; MAX_VERTICES] = [false; MAX_VERTICES];
static mut NUM_VERTICES: usize = 0;

/**
 * DFS递归遍历
 */
unsafe fn dfs(vertex: usize) {
    // 标记当前顶点为已访问
    VISITED[vertex] = true;
    print!("{} ", vertex);
    
    // 递归访问所有未访问的邻居
    for i in 0..NUM_VERTICES {
        if GRAPH[vertex][i] == 1 && !VISITED[i] {
            dfs(i);
        }
    }
}

/**
 * 查找所有连通分量
 */
unsafe fn find_connected_components() {
    let mut component_count = 0;
    
    println!("连通分量检测:\n");
    
    // 初始化访问数组
    for i in 0..NUM_VERTICES {
        VISITED[i] = false;
    }
    
    // 遍历所有顶点，对每个未访问的顶点进行DFS
    for i in 0..NUM_VERTICES {
        if !VISITED[i] {
            component_count += 1;
            print!("连通分量 {}: ", component_count);
            dfs(i);
            println!();
        }
    }
    
    println!("\n总共找到 {} 个连通分量", component_count);
}

/**
 * 添加边
 */
unsafe fn add_edge(from: usize, to: usize) {
    GRAPH[from][to] = 1;
    GRAPH[to][from] = 1;
}

fn main() {
    unsafe {
        // 创建一个示例图（两个连通分量）
        // 分量1: 0-1-2
        // 分量2: 3-4
        NUM_VERTICES = 5;
        
        // 添加边
        add_edge(0, 1);
        add_edge(1, 2);
        add_edge(3, 4);
        
        println!("图结构:");
        println!("  分量1: 0 -- 1 -- 2");
        println!("  分量2: 3 -- 4\n");
        
        find_connected_components();
    }
}
