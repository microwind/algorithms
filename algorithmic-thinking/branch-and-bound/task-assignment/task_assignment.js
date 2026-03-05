// 任务分配 - 分支定界算法 (JavaScript)
class TaskAssignment {
    constructor(costMatrix) {
        this.cost = costMatrix;
        this.n = costMatrix.length;
        this.minCost = Infinity;
        this.bestAssignment = new Array(this.n);
        this.currentAssignment = new Array(this.n);
        this.assignedWorkers = new Array(this.n).fill(false);
    }

    lowerBound(taskIdx) {
        let bound = 0;
        // 对于每个未分配任务，添加最小成本下界
        for (let i = taskIdx; i < this.n; i++) {
            let minCost = Infinity;
            for (let j = 0; j < this.n; j++) {
                if (!this.assignedWorkers[j]) {
                    minCost = Math.min(minCost, this.cost[i][j]);
                }
            }
            if (minCost !== Infinity) {
                bound += minCost;
            }
        }
        return bound;
    }

    branchAndBound(taskIdx = 0, currentCost = 0) {
        // 剪枝
        if (currentCost + this.lowerBound(taskIdx) >= this.minCost) {
            return;
        }

        // 基础情况
        if (taskIdx === this.n) {
            if (currentCost < this.minCost) {
                this.minCost = currentCost;
                this.bestAssignment = [...this.currentAssignment];
            }
            return;
        }

        // 分支
        for (let worker = 0; worker < this.n; worker++) {
            if (!this.assignedWorkers[worker]) {
                this.currentAssignment[taskIdx] = worker;
                this.assignedWorkers[worker] = true;

                this.branchAndBound(taskIdx + 1, currentCost + this.cost[taskIdx][worker]);

                this.assignedWorkers[worker] = false;
            }
        }
    }

    solve() {
        this.branchAndBound();
        return {
            cost: this.minCost,
            assignment: this.bestAssignment
        };
    }
}

// Test
const costMatrix = [
    [5, 7, 9],
    [6, 8, 4],
    [3, 5, 7]
];

console.log("Task Assignment Problem (JavaScript)");
console.log("=====================================\n");

console.log("Cost Matrix:");
costMatrix.forEach((row, i) => {
    console.log(`Task ${i}: ${row.join(' ')}`);
});

const solver = new TaskAssignment(costMatrix);
const result = solver.solve();

console.log(`\nMinimum Cost: ${result.cost}`);
console.log("\nOptimal Assignment:");
result.assignment.forEach((worker, task) => {
    console.log(`Task ${task} -> Worker ${worker} (cost: ${costMatrix[task][worker]})`);
});
