/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 树搜索算法 - 综合路径查找实现
 * 实现BFS、DFS、A*、Dijkstra等搜索算法
 * 用于矩阵导航、图遍历、最短路径问题
 * 包含详细的中文注释和全面的说明
 */

// 具有4方向连接的矩阵节点
class MatrixNode {
    constructor(data) {
        this.data = data; // 节点存储的数据
        this.up = null; // 上方节点
        this.down = null; // 下方节点
        this.left = null; // 左侧节点
        this.right = null; // 右侧节点
    }
    
    toString() {
        return `MatrixNode(${this.data})`; // 返回节点的字符串表示
    }
    
    getNeighbors() {
        const neighbors = []; // 存储所有邻居节点
        
        // 检查并添加各个方向的邻居
        if (this.up) neighbors.push(this.up); // 添加上方邻居
        if (this.down) neighbors.push(this.down); // 添加下方邻居
        if (this.left) neighbors.push(this.left); // 添加左侧邻居
        if (this.right) neighbors.push(this.right); // 添加右侧邻居
        
        return neighbors;
    }
    
    getNeighborData() {
        return this.getNeighbors().map(neighbor => neighbor.data); // 返回所有邻居节点的数据
    }
}

// 用于存储和操作路径的路径结构
class Path {
    constructor() {
        this.nodes = []; // 路径中的节点序列
        this.length = 0; // 路径长度
    }
    
    add(node) {
        this.nodes.push(node); // 向路径末尾添加节点
        this.length++; // 增加路径长度
    }
    
    copy() {
        const newPath = new Path(); // 创建新路径对象
        newPath.nodes = [...this.nodes]; // 复制节点数组
        newPath.length = this.length; // 复制路径长度
        return newPath;
    }
    
    contains(node) {
        return this.nodes.includes(node); // 检查路径是否包含指定节点
    }
    
    getDataSequence() {
        return this.nodes.map(node => node.data); // 返回路径中所有节点的数据序列
    }
    
    calculateCost() {
        return this.length === 0 ? 0 : this.length - 1; // 计算路径成本（边数）
    }
    
    toString() {
        return this.getDataSequence().join(' -> '); // 返回路径的字符串表示
    }
}

// 矩阵搜索算法用于路径查找
class MatrixSearch {
    
    /**
     * 创建n x n矩阵，节点相互连接
     * 
     * 算法:
     * 1. 创建n x n节点网格
     * 2. 连接左右邻居
     * 3. 连接上下邻居
     * 
     * 时间复杂度: O(n²)
     * 空间复杂度: O(n²)
     * 
     * 返回: 左上角节点作为矩阵入口点
     */
    static createMatrix(n) {
        const matrix = [];
        let counter = 1;
        
        // 初始化节点
        for (let i = 0; i < n; i++) {
            matrix[i] = [];
            for (let j = 0; j < n; j++) {
                matrix[i][j] = new MatrixNode(counter++);
            }
        }
        
        // 连接左右节点
        for (let i = 0; i < n; i++) {
            for (let j = 0; j < n - 1; j++) {
                matrix[i][j + 1].left = matrix[i][j];
                matrix[i][j].right = matrix[i][j + 1];
            }
        }
        
        // 连接上下节点
        for (let i = 0; i < n - 1; i++) {
            for (let j = 0; j < n; j++) {
                matrix[i + 1][j].up = matrix[i][j];
                matrix[i][j].down = matrix[i + 1][j];
            }
        }
        
        return matrix[0][0];
    }
    
    /**
     * 从头节点开始打印矩阵结构
     */
    static printMatrix(head, n) {
        let currentRow = head;
        
        for (let i = 0; i < n; i++) {
            let current = currentRow;
            const row = [];
            
            for (let j = 0; j < n; j++) {
                row.push(current.data.toString());
                current = current.right;
            }
            
            console.log(row.join(' '));
            currentRow = currentRow.down;
        }
    }
    
    /**
     * 通过从头节点导航查找特定节点
     * 
     * 时间复杂度: O(n²) - 最坏情况搜索整个矩阵
     * 空间复杂度: O(1)
     */
    static findNode(head, targetData, n) {
        let currentRow = head;
        
        for (let i = 0; i < n; i++) {
            let current = currentRow;
            
            for (let j = 0; j < n; j++) {
                if (current.data === targetData) {
                    return current;
                }
                current = current.right;
            }
            
            currentRow = currentRow.down;
        }
        
        return null;
    }
    
    /**
     * 使用BFS查找所有最短路径
     * 
     * 算法:
     * 1. 使用队列进行逐层探索
     * 2. 跟踪到每个节点的所有路径
     * 3. 在最小深度到达目标时停止
     * 4. 收集所有最短路径
     * 
     * 时间复杂度: O(b^d) 其中b是分支因子，d是深度
     * 空间复杂度: O(b^d) 用于存储路径
     * 
     * 保证:
     * - 找到所有最短路径
     * - 路径具有最小长度
     * - 按距离顺序探索节点
     */
    static bfsShortestPaths(start, end) {
        console.log(`BFS shortest paths from ${start.data} to ${end.data}:`);
        
        const queue = [];
        const foundPaths = [];
        let shortestLength = null;
        
        // 从初始路径开始
        const initialPath = new Path();
        initialPath.add(start);
        queue.push(initialPath);
        
        while (queue.length > 0) {
            const currentPath = queue.shift();
            const current = currentPath.nodes[currentPath.length - 1];
            
            // 检查是否到达目的地
            if (current === end) {
                if (shortestLength === null || currentPath.length < shortestLength) {
                    shortestLength = currentPath.length;
                    foundPaths.length = 0;
                    foundPaths.push(currentPath.copy());
                } else if (currentPath.length === shortestLength) {
                    foundPaths.push(currentPath.copy());
                }
                continue;
            }
            
            // 如果已经找到最短路径且当前路径更长，跳过
            if (shortestLength !== null && currentPath.length >= shortestLength) {
                continue;
            }
            
            // 探索邻居
            for (const neighbor of current.getNeighbors()) {
                if (!currentPath.contains(neighbor)) {
                    const newPath = currentPath.copy();
                    newPath.add(neighbor);
                    queue.push(newPath);
                }
            }
        }
        
        return foundPaths;
    }
    
    /**
     * 使用DFS和深度限制查找所有路径
     * 
     * 算法:
     * 1. 在回溯前尽可能深入探索
     * 2. 跟踪到达目的地的所有路径
     * 3. 通过跟踪访问节点避免循环
     * 4. 限制深度以防止无限递归
     * 
     * 时间复杂度: O(b^d) 其中b是分支因子，d是最大深度
     * 空间复杂度: O(d) 用于递归栈
     */
    static dfsAllPaths(start, end, maxDepth = 20) {
        console.log(`DFS all paths from ${start.data} to ${end.data}:`);
        
        const allPaths = [];
        
        const dfs = (current, path, depth) => {
            // 检查深度限制
            if (depth > maxDepth) {
                return;
            }
            
            // 创建新路径并添加当前节点
            const newPath = path.copy();
            newPath.add(current);
            
            // 检查是否到达目的地
            if (current === end) {
                allPaths.push(newPath);
                return;
            }
            
            // 探索邻居
            for (const neighbor of current.getNeighbors()) {
                if (!path.contains(neighbor)) {
                    dfs(neighbor, newPath, depth + 1);
                }
            }
        };
        
        dfs(start, new Path(), 0);
        return allPaths;
    }
    
    /**
     * 使用A*算法查找最短路径
     * 
     * 算法:
     * 1. 使用启发式函数估计到目标的距离
     * 2. 维护开放和关闭节点集合
     * 3. 选择f = g + h最小的节点
     * 4. 重建路径
     * 
     * 时间复杂度: O(b^d) 但通常比BFS快
     * 空间复杂度: O(b^d)
     */
    static aStarShortestPath(start, end) {
        console.log(`A* shortest path from ${start.data} to ${end.data}:`);
        
        const openSet = [start];
        const closedSet = new Set();
        const gScore = new Map();
        const fScore = new Map();
        const cameFrom = new Map();
        
        // 初始化分数
        gScore.set(start, 0);
        fScore.set(start, this.heuristic(start, end));
        
        while (openSet.length > 0) {
            // 找到f分数最小的节点
            let current = openSet[0];
            let currentIndex = 0;
            
            for (let i = 1; i < openSet.length; i++) {
                if (fScore.get(openSet[i]) < fScore.get(current)) {
                    current = openSet[i];
                    currentIndex = i;
                }
            }
            
            // 检查是否到达目的地
            if (current === end) {
                return this.reconstructPath(cameFrom, current);
            }
            
            // 从开放集合移到关闭集合
            openSet.splice(currentIndex, 1);
            closedSet.add(current);
            
            // 检查邻居
            for (const neighbor of current.getNeighbors()) {
                if (closedSet.has(neighbor)) {
                    continue;
                }
                
                const tentativeGScore = gScore.get(current) + 1;
                
                if (!gScore.has(neighbor) || tentativeGScore < gScore.get(neighbor)) {
                    cameFrom.set(neighbor, current);
                    gScore.set(neighbor, tentativeGScore);
                    fScore.set(neighbor, tentativeGScore + this.heuristic(neighbor, end));
                    
                    if (!openSet.includes(neighbor)) {
                        openSet.push(neighbor);
                    }
                }
            }
        }
        
        return null; // 未找到路径
    }
    
    /**
     * 启发式函数 - 曼哈顿距离
     */
    static heuristic(node, end) {
        // 简单的曼哈顿距离启发式
        // 在实际应用中，这里应该根据节点的实际坐标计算
        return Math.abs(node.data - end.data);
    }
    
    /**
     * 从cameFrom映射重建路径
     */
    static reconstructPath(cameFrom, current) {
        const path = new Path();
        path.add(current);
        
        while (cameFrom.has(current)) {
            current = cameFrom.get(current);
            path.nodes.unshift(current);
        }
        
        return path;
    }
    
    /**
     * Dijkstra算法查找最短路径
     * 
     * 算法:
     * 1. 初始化所有节点的距离为无穷大
     * 2. 设置起始节点距离为0
     * 3. 选择未访问节点中距离最小的
     * 4. 更新邻居节点的距离
     * 
     * 时间复杂度: O((V + E) log V)
     * 空间复杂度: O(V)
     */
    static dijkstraShortestPath(start, end) {
        console.log(`Dijkstra shortest path from ${start.data} to ${end.data}:`);
        
        const distances = new Map();
        const visited = new Set();
        const previous = new Map();
        const unvisited = new Set();
        
        // 收集所有节点
        const allNodes = this.collectAllNodes(start);
        for (const node of allNodes) {
            distances.set(node, Infinity);
            unvisited.add(node);
        }
        
        distances.set(start, 0);
        
        while (unvisited.size > 0) {
            // 找到未访问节点中距离最小的
            let current = null;
            let minDistance = Infinity;
            
            for (const node of unvisited) {
                if (distances.get(node) < minDistance) {
                    current = node;
                    minDistance = distances.get(node);
                }
            }
            
            if (current === null || current === end) {
                break;
            }
            
            unvisited.delete(current);
            visited.add(current);
            
            // 更新邻居距离
            for (const neighbor of current.getNeighbors()) {
                if (visited.has(neighbor)) {
                    continue;
                }
                
                const alt = distances.get(current) + 1;
                if (alt < distances.get(neighbor)) {
                    distances.set(neighbor, alt);
                    previous.set(neighbor, current);
                }
            }
        }
        
        // 重建路径
        if (!previous.has(end)) {
            return null; // 未找到路径
        }
        
        const path = new Path();
        let current = end;
        path.add(current);
        
        while (previous.has(current)) {
            current = previous.get(current);
            path.nodes.unshift(current);
        }
        
        return path;
    }
    
    /**
     * 收集从起始节点可达的所有节点
     */
    static collectAllNodes(start) {
        const visited = new Set();
        const allNodes = [];
        
        const dfs = (node) => {
            if (visited.has(node)) {
                return;
            }
            
            visited.add(node);
            allNodes.push(node);
            
            for (const neighbor of node.getNeighbors()) {
                dfs(neighbor);
            }
        };
        
        dfs(start);
        return allNodes;
    }
    
    /**
     * 运行所有搜索算法的演示
     */
    static demonstrate() {
        console.log('='.repeat(70));
        console.log('矩阵搜索算法演示');
        console.log('='.repeat(70));
        
        // 创建5x5矩阵
        const head = this.createMatrix(5);
        console.log('\n创建的5x5矩阵:');
        this.printMatrix(head, 5);
        
        // 查找特定节点
        const targetNode = this.findNode(head, 13, 5);
        console.log(`\n查找节点13: ${targetNode ? '找到' : '未找到'}`);
        
        // BFS最短路径
        const startNode = this.findNode(head, 1, 5);
        const endNode = this.findNode(head, 25, 5);
        
        if (startNode && endNode) {
            console.log('\n=== BFS最短路径 ===');
            const bfsPaths = this.bfsShortestPaths(startNode, endNode);
            console.log(`找到 ${bfsPaths.length} 条最短路径:`);
            bfsPaths.forEach((path, index) => {
                console.log(`路径 ${index + 1}: ${path.toString()}`);
            });
            
            console.log('\n=== DFS所有路径 ===');
            const dfsPaths = this.dfsAllPaths(startNode, endNode, 10);
            console.log(`找到 ${dfsPaths.length} 条路径:`);
            dfsPaths.forEach((path, index) => {
                console.log(`路径 ${index + 1}: ${path.toString()}`);
            });
            
            console.log('\n=== A*最短路径 ===');
            const aStarPath = this.aStarShortestPath(startNode, endNode);
            if (aStarPath) {
                console.log(`A*路径: ${aStarPath.toString()}`);
                console.log(`路径长度: ${aStarPath.calculateCost()}`);
            } else {
                console.log('A*未找到路径');
            }
            
            console.log('\n=== Dijkstra最短路径 ===');
            const dijkstraPath = this.dijkstraShortestPath(startNode, endNode);
            if (dijkstraPath) {
                console.log(`Dijkstra路径: ${dijkstraPath.toString()}`);
                console.log(`路径长度: ${dijkstraPath.calculateCost()}`);
            } else {
                console.log('Dijkstra未找到路径');
            }
        }
        
        console.log('\n=== 算法特性 ===');
        console.log('1. BFS: 保证找到最短路径，适合无权图');
        console.log('2. DFS: 可以找到所有路径，适合回溯问题');
        console.log('3. A*: 使用启发式，通常比BFS快');
        console.log('4. Dijkstra: 适合带权重的图，保证最优');
        console.log('5. 所有算法都可以用于路径查找和图遍历');
        
        console.log('\n=== 应用场景 ===');
        console.log('游戏AI寻路、网络路由、社交网络分析、');
        console.log('地图导航、依赖关系分析、最优化问题等。');
    }
}

// 运行演示
if (require.main === module) {
    MatrixSearch.demonstrate();
}

module.exports = { MatrixNode, Path, MatrixSearch };
