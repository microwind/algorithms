/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树搜索算法 - 矩阵节点路径查找
 * 实现BFS和DFS用于二维矩阵中的最短路径查找
 * 用于路径查找、迷宫求解、图遍历等
 * 支持4方向移动和多条最短路径
 */

// 具有4方向连接的矩阵节点
class MatrixNode {
    public data: number;    // 节点存储的数据
    public up?: MatrixNode;   // 上方节点连接
    public down?: MatrixNode; // 下方节点连接
    public left?: MatrixNode; // 左侧节点连接
    public right?: MatrixNode; // 右侧节点连接

    /**
     * 构造函数 - 初始化矩阵节点
     * @param data 节点数据值
     */
    constructor(data: number) {
        this.data = data; // 初始化节点数据
    }

    /**
     * 将节点转换为字符串表示
     * @returns 节点的字符串表示
     */
    toString(): string {
        return `MatrixNode(${this.data})`; // 节点的字符串表示
    }
}

// 用于存储路径的路径结构
class Path {
    public nodes: MatrixNode[]; // 路径中的节点数组
    public length: number;     // 路径长度

    /**
     * 构造函数 - 初始化空路径
     */
    constructor() {
        this.nodes = []; // 初始化空节点数组
        this.length = 0; // 初始化路径长度为0
    }

    /**
     * 向路径添加节点
     * @param node 要添加的节点
     */
    add(node: MatrixNode): void {
        this.nodes.push(node); // 将节点添加到路径
        this.length++;        // 增加路径长度
    }

    /**
     * 创建当前路径的副本
     * @returns 复制的路径对象
     */
    copy(): Path {
        const copy = new Path();
        copy.nodes = [...this.nodes]; // 复制节点数组
        copy.length = this.length;     // 复制路径长度
        return copy;
    }

    /**
     * 检查节点是否存在于路径中
     * @param node 要检查的节点
     * @returns 如果节点在路径中返回true，否则返回false
     */
    contains(node: MatrixNode): boolean {
        return this.nodes.includes(node); // 检查节点是否在路径中
    }

    /**
     * 将路径转换为字符串表示
     * @returns 路径的字符串表示
     */
    toString(): string {
        return this.nodes.map(node => node.data).join(' -> '); // 将路径转换为字符串表示
    }
}

// 矩阵搜索算法实现
class MatrixSearch {
    /**
     * 创建具有互连节点的n x n矩阵
     * 
     * 算法:
     * 1. 创建n x n节点矩阵
     * 2. 用顺序数据初始化每个节点
     * 3. 建立水平连接（左右）
     * 4. 建立垂直连接（上下）
     * 
     * 时间复杂度: O(n²) - 处理n²个节点
     * 空间复杂度: O(n²) - 存储n²个节点
     * 
     * @param n 矩阵维度 (n x n)
     * @returns 矩阵的左上角节点
     */
    static createMatrix(n: number): MatrixNode {
        const matrix: MatrixNode[][] = [];
        let counter = 1;

        // 初始化n x n矩阵
        for (let i = 0; i < n; i++) {
            matrix[i] = [];
            for (let j = 0; j < n; j++) {
                matrix[i][j] = new MatrixNode(counter++);
            }
        }

        // 连接左右（水平连接）
        for (let i = 0; i < n; i++) {
            for (let j = 0; j < n - 1; j++) {
                matrix[i][j + 1].left = matrix[i][j];
                matrix[i][j].right = matrix[i][j + 1];
            }
        }

        // 连接上下（垂直连接）
        for (let i = 0; i < n - 1; i++) {
            for (let j = 0; j < n; j++) {
                matrix[i + 1][j].up = matrix[i][j];
                matrix[i][j].down = matrix[i + 1][j];
            }
        }

        return matrix[0][0];
    }

    /**
     * 从头节点开始打印矩阵
     * 
     * 算法:
     * 1. 使用down指针逐行遍历
     * 2. 使用right指针遍历每行
     * 3. 打印每个节点的数据值
     * 
     * @param head 左上角节点
     * @param n 矩阵维度
     */
    static printMatrix(head: MatrixNode, n: number): void {
        let currentRow = head; // 当前行指针

        for (let i = 0; i < n; i++) {
            let current = currentRow; // 当前列指针
            const row: string[] = [];
            for (let j = 0; j < n; j++) {
                row.push(current.data.toString()); // 将节点数据添加到行数组
                current = current.right!; // 移动到右侧节点
            }
            console.log(row.join(' ')); // 打印行
            currentRow = currentRow.down!; // 移动到下一行
        }
    }

    /**
     * 通过从头节点导航查找特定节点
     * 
     * 算法:
     * 1. 逐行遍历矩阵
     * 2. 检查每个节点的数据值
     * 3. 找到时返回节点
     * 
     * 时间复杂度: O(n²) - 最坏情况检查所有节点
     * 空间复杂度: O(1) - 常数额外空间
     * 
     * @param head 左上角节点
     * @param targetData 目标节点数据值
     * @param n 矩阵维度
     * @returns 找到的节点或null（如果未找到）
     */
    static findNode(head: MatrixNode, targetData: number, n: number): MatrixNode | null {
        let currentRow = head; // 当前行指针

        for (let i = 0; i < n; i++) {
            let current = currentRow; // 当前列指针
            for (let j = 0; j < n; j++) {
                if (current.data === targetData) {
                    return current; // 找到目标节点
                }
                current = current.right!; // 移动到右侧节点
            }
            currentRow = currentRow.down!; // 移动到下一行
        }

        return null; // 未找到节点
    }

    /**
     * 使用BFS查找所有最短路径
     * 
     * 算法:
     * 1. 使用队列进行层次遍历
     * 2. 跟踪最短路径长度
     * 3. 探索所有最小长度的路径
     * 4. 使用路径跟踪避免循环
     * 
     * 时间复杂度: O(V + E) - V=顶点数, E=边数
     * 空间复杂度: O(V) - 用于队列和路径存储
     * 
     * @param start 起始节点
     * @param end 目标节点
     * @returns 最短路径数组
     */
    static findShortestPathsBFS(start: MatrixNode, end: MatrixNode): Path[] {
        console.log(`BFS最短路径从 ${start.data} 到 ${end.data}:`);

        const queue: Path[] = []; // BFS队列
        const paths: Path[] = []; // 存储找到的路径
        let shortestLength = -1; // 最短路径长度

        // 从初始路径开始
        const initialPath = new Path(); // 创建初始路径对象
        initialPath.add(start); // 将起始节点添加到初始路径
        queue.push(initialPath); // 将初始路径入队

        while (queue.length > 0) {
            const currentPath = queue.shift()!; // 出队当前路径
            const current = currentPath.nodes[currentPath.length - 1]; // 获取当前节点

            // 检查是否到达目的地
            if (current === end) {
                if (shortestLength === -1 || currentPath.length < shortestLength) {
                    shortestLength = currentPath.length; // 更新最短长度
                    paths.length = 0; // 清除之前的路径
                    paths.push(currentPath.copy()); // 添加新的最短路径
                } else if (currentPath.length === shortestLength) {
                    paths.push(currentPath.copy()); // 添加另一条最短路径
                }
                continue;
            }

            // 如果已经找到最短路径且当前路径更长，跳过
            if (shortestLength !== -1 && currentPath.length >= shortestLength) {
                continue; // 跳过更长的路径
            }

            // 探索邻居
            const neighbors = [current.left, current.up, current.down, current.right]; // 获取所有邻居

            for (const neighbor of neighbors) {
                if (neighbor && !currentPath.contains(neighbor)) {
                    const newPath = currentPath.copy(); // 复制当前路径
                    newPath.add(neighbor); // 将邻居添加到路径
                    queue.push(newPath); // 将新路径入队
                }
            }
        }

        return paths;
    }

    /**
     * 使用DFS查找所有最短路径
     * 
     * 算法:
     * 1. 使用递归深度优先搜索
     * 2. 跟踪访问过的节点以避免循环
     * 3. 探索每条路径后回溯
     * 4. 收集找到的所有最短路径
     * 
     * 时间复杂度: O(V + E) - V=顶点数, E=边数
     * 空间复杂度: O(V) - 用于递归栈和访问集合
     * 
     * @param start 起始节点
     * @param end 目标节点
     * @returns 最短路径数组
     */
    static findShortestPathsDFS(start: MatrixNode, end: MatrixNode): Path[] {
        console.log(`DFS最短路径从 ${start.data} 到 ${end.data}:`);

        const foundPaths: Path[] = []; // 存储找到的路径数组
        let shortestLength = -1; // 初始化最短长度

        const dfs = (current: MatrixNode | undefined, path: Path, visited: Set<MatrixNode>): void => {
            if (!current) {
                return; // 如果当前节点未定义则返回
            }

            path.add(current); // 将当前节点添加到路径
            visited.add(current); // 将当前节点添加到访问集合

            // 检查是否到达目的地
            if (current === end) {
                if (shortestLength === -1 || path.length < shortestLength) {
                    shortestLength = path.length; // 更新最短长度
                    foundPaths.length = 0; // 清除之前的路径
                    foundPaths.push(path.copy()); // 存储新的最短路径
                } else if (path.length === shortestLength) {
                    foundPaths.push(path.copy()); // 添加另一条最短路径
                }
            } else {
                // 如果已经找到最短路径且当前路径更长，跳过
                if (shortestLength !== -1 && path.length >= shortestLength) {
                    path.length--; // 移除当前节点
                    visited.delete(current); // 从访问集合中移除
                    return;
                }

                // 探索邻居
                const neighbors = [current.left, current.up, current.down, current.right]; // 获取所有邻居

                for (const neighbor of neighbors) {
                    if (neighbor && !visited.has(neighbor)) {
                        dfs(neighbor, path, visited); // 递归DFS调用
                    }
                }
            }

            path.length--; // 移除当前节点（回溯）
            visited.delete(current); // 从访问集合中移除
        };

        dfs(start, new Path(), new Set<MatrixNode>()); // 使用空路径和访问集合开始DFS
        return foundPaths;
    }

    /**
     * 打印所有找到的路径
     * 
     * @param paths 要打印的路径数组
     */
    static printPaths(paths: Path[]): void {
        if (paths.length === 0) {
            console.log("未找到路径"); // 未找到路径消息
            return;
        }

        console.log(`最短路径（长度 ${paths[0].length}）:`); // 显示路径长度
        for (let i = 0; i < paths.length; i++) {
            console.log(`  路径 ${i + 1}: ${paths[i].toString()}`); // 显示每条路径
        }
    }

    /**
     * 测试矩阵搜索算法
     * 
     * 测试用例:
     * 1. 创建3x3矩阵网络
     * 2. 演示矩阵结构
     * 3. 使用BFS查找最短路径
     * 4. 使用DFS查找最短路径
     * 5. 比较算法特性
     */
    static test(): void {
        console.log("=".repeat(60));
        console.log("树搜索算法 - 矩阵节点路径查找"); // 显示标题
        console.log("=".repeat(60));
        console.log();

        const n = 3;
        const head = this.createMatrix(n);

        console.log(`矩阵结构 (${n}x${n}):`);
        this.printMatrix(head, n);
        console.log();

        // 查找特定节点用于演示
        const node2 = this.findNode(head, 2, n); // 查找值为2的节点
        const node9 = this.findNode(head, 9, n); // 查找值为9的节点

        if (node2 && node9) {
            // 广度优先搜索
            const bfsPaths = this.findShortestPathsBFS(node2, node9); // 查找BFS最短路径
            this.printPaths(bfsPaths); // 打印BFS路径
            console.log();

            // 深度优先搜索
            const dfsPaths = this.findShortestPathsDFS(node2, node9); // 查找DFS最短路径
            this.printPaths(dfsPaths); // 打印DFS路径
        } else {
            console.log("无法找到所需节点"); // 错误消息
        }

        console.log();
        console.log("=== 算法特性 ===");
        console.log("BFS（广度优先搜索）:");
        console.log("  - 在无权图中保证找到最短路径");
        console.log("  - 使用队列进行层次遍历");
        console.log("  - 适用于查找最短路径");
        
        console.log("\nDFS（深度优先搜索）:");
        console.log("  - 可能先找到较长的路径，但能找到所有路径");
        console.log("  - 使用递归和回溯");
        console.log("  - 适用于探索所有可能的路径");
        
        console.log("\n复杂度分析:");
        console.log("  - 时间复杂度: O(V + E)，其中V是顶点数，E是边数");
        console.log("  - 空间复杂度: O(V)，用于队列/递归栈");
        console.log("  - 矩阵导航: 4方向移动（上、下、左、右）");
        
        console.log("\n=== 应用场景 ===");
        console.log("矩阵路径查找用于:");
        console.log("  - 迷宫求解和益智游戏");
        console.log("  - 网络路由和导航");
        console.log("  - 游戏AI和路径查找");
        console.log("  - 电路板设计");
        console.log("  - 图像处理和分析");
    }
}

// 如果直接执行此文件则运行测试
if (require.main === module) {
    MatrixSearch.test(); // 运行测试函数
}

export { MatrixNode, Path, MatrixSearch }; // 导出类

/*打印结果
jarry@Mac tree-search % ts-node TreeSearch.ts 
============================================================
树搜索算法 - 矩阵节点路径查找
============================================================

矩阵结构 (3x3):
1 2 3
4 5 6
7 8 9

BFS最短路径从 2 到 9:
最短路径（长度 4）:
  路径 1: 2 -> 5 -> 8 -> 9
  路径 2: 2 -> 5 -> 6 -> 9
  路径 3: 2 -> 3 -> 6 -> 9

DFS最短路径从 2 到 9:
最短路径（长度 4）:
  路径 1: 2 -> 1 -> 4 -> 7 -> 8 -> 5 -> 6 -> 3 -> 9 -> 9 -> 5 -> 8 -> 7 -> 9 -> 6 -> 3 -> 9 -> 5 -> 4 -> 1 -> 7 -> 8 -> 9 -> 8 -> 7 -> 4 -> 1 -> 9
  路径 2: 2 -> 1 -> 4 -> 7 -> 8 -> 5 -> 6 -> 3 -> 9 -> 9 -> 5 -> 8 -> 7 -> 9 -> 6 -> 3 -> 9 -> 5 -> 4 -> 1 -> 7 -> 8 -> 9 -> 8 -> 7 -> 4 -> 1 -> 9 -> 6 -> 3 -> 9
  路径 3: 2 -> 1 -> 4 -> 7 -> 8 -> 5 -> 6 -> 3 -> 9 -> 9 -> 5 -> 8 -> 7 -> 9 -> 6 -> 3 -> 9 -> 5 -> 4 -> 1 -> 7 -> 8 -> 9 -> 8 -> 7 -> 4 -> 1 -> 9 -> 6 -> 3 -> 9 -> 3 -> 6 -> 5 -> 9

=== 算法特性 ===
BFS（广度优先搜索）:
  - 在无权图中保证找到最短路径
  - 使用队列进行层次遍历
  - 适用于查找最短路径

DFS（深度优先搜索）:
  - 可能先找到较长的路径，但能找到所有路径
  - 使用递归和回溯
  - 适用于探索所有可能的路径

复杂度分析:
  - 时间复杂度: O(V + E)，其中V是顶点数，E是边数
  - 空间复杂度: O(V)，用于队列/递归栈
  - 矩阵导航: 4方向移动（上、下、左、右）

=== 应用场景 ===
矩阵路径查找用于:
  - 迷宫求解和益智游戏
  - 网络路由和导航
  - 游戏AI和路径查找
  - 电路板设计
  - 图像处理和分析
*/
