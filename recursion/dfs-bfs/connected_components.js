/**
 * 图的DFS - 连通分量检测
 * 使用递归DFS找出图中的所有连通分量
 */

const MAX_VERTICES = 100;

// 邻接矩阵表示图
let graph = Array(MAX_VERTICES).fill().map(() => Array(MAX_VERTICES).fill(0));
let visited = Array(MAX_VERTICES).fill(false);
let numVertices;

/**
 * DFS递归遍历
 * @param {number} vertex 当前顶点
 */
function dfs(vertex) {
    // 标记当前顶点为已访问
    visited[vertex] = true;
    process.stdout.write(vertex + " ");
    
    // 递归访问所有未访问的邻居
    for (let i = 0; i < numVertices; i++) {
        if (graph[vertex][i] === 1 && !visited[i]) {
            dfs(i);
        }
    }
}

/**
 * 查找所有连通分量
 */
function findConnectedComponents() {
    let componentCount = 0;
    
    console.log("连通分量检测:\n");
    
    // 初始化访问数组
    for (let i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    
    // 遍历所有顶点，对每个未访问的顶点进行DFS
    for (let i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            componentCount++;
            process.stdout.write("连通分量 " + componentCount + ": ");
            dfs(i);
            console.log();
        }
    }
    
    console.log("\n总共找到 " + componentCount + " 个连通分量");
}

/**
 * 添加边
 * @param {number} from 起始顶点
 * @param {number} to 目标顶点
 */
function addEdge(from, to) {
    graph[from][to] = 1;
    graph[to][from] = 1;
}

// 主程序
function main() {
    // 创建一个示例图（两个连通分量）
    // 分量1: 0-1-2
    // 分量2: 3-4
    numVertices = 5;
    
    // 添加边
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(3, 4);
    
    console.log("图结构:");
    console.log("  分量1: 0 -- 1 -- 2");
    console.log("  分量2: 3 -- 4\n");
    
    findConnectedComponents();
}

main();
