// 0-1 背包优化 - 分支定界算法 (JavaScript)
class KnapsackOptimization {
    constructor(weights, values, capacity) {
        this.weights = weights;
        this.values = values;
        this.capacity = capacity;
        this.n = weights.length;
        this.maxProfit = 0;
        this.bestItems = new Array(this.n).fill(false);
        this.currentItems = new Array(this.n).fill(false);
    }

    upperBound(idx, weight, profit) {
        // 处理容量已满的情况
        if (weight >= this.capacity) {
            return profit;
        }

        let bound = profit;
        let remainCapacity = this.capacity - weight;

        // 贪心选择
        for (let i = idx; i < this.n; i++) {
            if (this.weights[i] <= remainCapacity) {
                bound += this.values[i];
                remainCapacity -= this.weights[i];
            } else {
                bound += Math.floor(this.values[i] * remainCapacity / this.weights[i]);
                break;
            }
        }

        return bound;
    }

    branchAndBound(idx = 0, weight = 0, profit = 0) {
        // 剪枝
        if (this.upperBound(idx, weight, profit) <= this.maxProfit) {
            return;
        }

        // 基础情况
        if (idx === this.n) {
            if (profit > this.maxProfit) {
                this.maxProfit = profit;
                this.bestItems = [...this.currentItems];
            }
            return;
        }

        // 包含当前物品
        if (weight + this.weights[idx] <= this.capacity) {
            this.currentItems[idx] = true;
            this.branchAndBound(idx + 1, weight + this.weights[idx], profit + this.values[idx]);
            this.currentItems[idx] = false;
        }

        // 排除当前物品
        this.branchAndBound(idx + 1, weight, profit);
    }

    solve() {
        this.branchAndBound();
        return {
            profit: this.maxProfit,
            items: this.bestItems
                .map((selected, idx) => selected ? idx : -1)
                .filter(idx => idx !== -1)
        };
    }
}

// Test
console.log("============================================================");
console.log("0-1 Knapsack Optimization - Branch and Bound (JavaScript)");
console.log("============================================================");

const weights = [2, 3, 4, 5];
const values = [3, 4, 5, 6];
const capacity = 8;

console.log(`\nCapacity: ${capacity}`);
console.log(`Weights: ${weights.join(' ')}`);
console.log(`Values: ${values.join(' ')}`);

const solver = new KnapsackOptimization(weights, values, capacity);
const result = solver.solve();

console.log(`\nMaximum Profit: ${result.profit}`);
console.log(`Selected Items: ${result.items.join(' ')}`);
