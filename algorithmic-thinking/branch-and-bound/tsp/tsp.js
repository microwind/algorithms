// 旅行商问题 - 分支定界算法 (JavaScript)
class TSPSolver {
    constructor(distMatrix) {
        this.dist = distMatrix;
        this.n = distMatrix.length;
        this.minCost = Infinity;
        this.bestPath = [];
        this.currentPath = [0];
        this.visited = new Array(this.n).fill(false);
        this.visited[0] = true;
    }

    lowerBound(node, level, currentCost) {
        let bound = currentCost;
        let minEdge = Infinity;

        // 从当前节点到未访问城市找最小边
        for (let i = 0; i < this.n; i++) {
            if (!this.visited[i]) {
                minEdge = Math.min(minEdge, this.dist[node][i]);
            }
        }

        if (minEdge !== Infinity) {
            bound += minEdge;
        }

        // 估计剩余城市的最小成本
        for (let i = 0; i < this.n; i++) {
            if (!this.visited[i]) {
                let min1 = Infinity, min2 = Infinity;
                for (let j = 0; j < this.n; j++) {
                    if (!this.visited[j] && i !== j) {
                        if (this.dist[i][j] < min1) {
                            min2 = min1;
                            min1 = this.dist[i][j];
                        } else if (this.dist[i][j] < min2) {
                            min2 = this.dist[i][j];
                        }
                    }
                }
                if (min2 !== Infinity) {
                    bound += min1;
                }
            }
        }

        return bound;
    }

    branchAndBound(node, level, cost) {
        // 基础情况：找到完整路径
        if (level === this.n) {
            const totalCost = cost + this.dist[node][0];
            if (totalCost < this.minCost) {
                this.minCost = totalCost;
                this.bestPath = [...this.currentPath];
            }
            return;
        }

        // 剪枝
        if (this.lowerBound(node, level, cost) >= this.minCost) {
            return;
        }

        // 分支
        for (let i = 0; i < this.n; i++) {
            if (!this.visited[i]) {
                this.visited[i] = true;
                this.currentPath.push(i);

                this.branchAndBound(i, level + 1, cost + this.dist[node][i]);

                this.currentPath.pop();
                this.visited[i] = false;
            }
        }
    }

    solve() {
        this.branchAndBound(0, 1, 0);
        return {
            cost: this.minCost,
            path: [...this.bestPath, 0]
        };
    }
}

// Test
const graph = [
    [0, 10, 15, 20],
    [10, 0, 35, 25],
    [15, 35, 0, 30],
    [20, 25, 30, 0]
];

console.log("TSP - Traveling Salesman Problem (JavaScript)");
console.log("=============================================\n");

console.log("Test Case 1:");
console.log("Distance Matrix:");
graph.forEach(row => console.log(row.map(x => x.toString().padStart(3)).join(' ')));

const solver = new TSPSolver(graph);
const result = solver.solve();

console.log(`\nMinimum Tour Cost: ${result.cost}`);
console.log(`Tour: ${result.path.join(' -> ')}`);

// Test Case 2
console.log("\n" + "=============================================");
console.log("\nTest Case 2: 5 Cities\n");

const graph2 = [
    [0, 29, 20, 32, 23],
    [29, 0, 21, 37, 18],
    [20, 21, 0, 28, 23],
    [32, 37, 28, 0, 34],
    [23, 18, 23, 34, 0]
];

console.log("Distance Matrix:");
graph2.forEach(row => console.log(row.map(x => x.toString().padStart(3)).join(' ')));

const solver2 = new TSPSolver(graph2);
const result2 = solver2.solve();

console.log(`\nMinimum Tour Cost: ${result2.cost}`);
console.log(`Tour: ${result2.path.join(' -> ')}`);
