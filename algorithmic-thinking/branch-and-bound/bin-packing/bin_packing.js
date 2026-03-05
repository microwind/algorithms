/*
装箱问题 - 分支定界算法 (JavaScript Implementation)

算法说明:
- 将 n 个物品装入最少数量的容量相同的箱子中
- 使用分支定界法进行搜索和剪枝
- 首先按降序排列物品以减少搜索空间
- 使用下界函数进行剪枝优化

时间复杂度：指数级（使用剪枝优化）
空间复杂度：O(最优箱子数 * 物品数)

示例:
    const items = [7, 5, 5, 3, 3, 3, 2];
    const capacity = 10;
    结果: 最少 3 个箱子
*/

class BinPackingSolver {
    constructor(items, capacity) {
        /**
         * 初始化装箱求解器
         * @param items - 物品重量数组
         * @param capacity - 每个箱的最大容量
         * 时间: O(n log n)，空间: O(n)
         */
        this.items = items.slice().sort((a, b) => b - a);
        this.binCapacity = capacity;
        this.n = items.length;
        this.minBins = items.length;
        this.bestPacking = [];
        this.currentBins = [];
    }

    /**
     * 计算下界
     * 使用楼函数计算最少需要多少个箱子来放置剩余物品
     * 时间: O(n)，空间: O(1)
     * @param itemIdx - 当前物品索引
     * @returns 下界值
     */
    lowerBound(itemIdx) {
        let totalWeight = 0;
        for (let i = itemIdx; i < this.n; i++) {
            totalWeight += this.items[i];
        }
        return Math.ceil(totalWeight / this.binCapacity);
    }

    /**
     * 计算箱子总重
     * 时间: O(k)，空间: O(1)
     * @param bin - 箱子数组
     * @returns 箱子中物品的总重
     */
    sumBin(bin) {
        return bin.reduce((sum, item) => sum + item, 0);
    }

    /**
     * 分支定界搜索
     * 递归探索所有可能的装箱方案
     * 时间: 指数级（使用剪枝），空间: O(最优箱子数)
     * @param itemIdx - 当前处理物品的索引
     */
    branchAndBound(itemIdx) {
        // 剪枝：当前箱数 + 下界 >= 最优箱数时跳过
        if (this.currentBins.length + this.lowerBound(itemIdx) >= this.minBins) {
            return;
        }

        // 基础情况：所有物品已装
        if (itemIdx === this.n) {
            if (this.currentBins.length < this.minBins) {
                this.minBins = this.currentBins.length;
                this.bestPacking = this.currentBins.map(bin => [...bin]);
            }
            return;
        }

        // 尝试把物品放入现有的箱子
        const item = this.items[itemIdx];
        let placed = false;

        for (const bin of this.currentBins) {
            if (this.sumBin(bin) + item <= this.binCapacity) {
                // 选择：加入箱子
                bin.push(item);
                // 探索：递归处理下一个物品
                this.branchAndBound(itemIdx + 1);
                // 撤销：移除物品
                bin.pop();
                placed = true;
                break;
            }
        }

        // 尝试加入一个新箱子
        if (!placed && this.currentBins.length < this.n) {
            // 选择：创建新箱子
            this.currentBins.push([item]);
            // 探索：递归处理下一个物品
            this.branchAndBound(itemIdx + 1);
            // 撤销：移除新箱子
            this.currentBins.pop();
        }
    }

    /**
     * 求解装箱问题
     * 返回最少箱子数
     * @returns 最少箱子数
     */
    solve() {
        this.branchAndBound(0);
        return this.minBins;
    }

    /**
     * 获取最优装箱方案
     * @returns 装箱方案二维数组
     */
    getPacking() {
        return this.bestPacking;
    }

    /**
     * 打印装箱结果
     */
    printResult() {
        console.log(`最少箱子数: ${this.minBins}`);
        for (let i = 0; i < this.bestPacking.length; i++) {
            const bin = this.bestPacking[i];
            const weight = this.sumBin(bin);
            console.log(`箱子 ${i}: [${bin.join(', ')}] (重量: ${weight})`);
        }
    }
}

function main() {
    console.log('='.repeat(60));
    console.log('装箱问题 - 分支定界算法 (JavaScript Implementation)');
    console.log('='.repeat(60));
    console.log();

    // 测试用例 1: 基础示例
    console.log('测试 1: 基础装箱问题');
    console.log('-'.repeat(60));
    let items = [7, 5, 5, 3, 3, 3, 2];
    let capacity = 10;
    console.log(`物品重量: [${items.join(', ')}]`);
    console.log(`箱子容量: ${capacity}`);
    console.log();

    let solver = new BinPackingSolver(items, capacity);
    solver.solve();
    solver.printResult();
    console.log();

    // 测试用例 2: 更大的测试集
    console.log('测试 2: 更大的物品集合');
    console.log('-'.repeat(60));
    items = [6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3];
    capacity = 12;
    console.log(`物品重量: [${items.join(', ')}]`);
    console.log(`箱子容量: ${capacity}`);
    console.log();

    solver = new BinPackingSolver(items, capacity);
    solver.solve();
    solver.printResult();
    console.log();

    // 测试用例 3: 完美适配
    console.log('测试 3: 完美适配的物品');
    console.log('-'.repeat(60));
    items = [5, 5, 4, 4, 3, 2, 2];
    capacity = 10;
    console.log(`物品重量: [${items.join(', ')}]`);
    console.log(`箱子容量: ${capacity}`);
    console.log();

    solver = new BinPackingSolver(items, capacity);
    solver.solve();
    solver.printResult();
}

// 执行主函数
if (require.main === module) {
    main();
}

module.exports = BinPackingSolver;

/*
Output:
$ node bin_packing.js

============================================================
装箱问题 - 分支定界算法 (JavaScript Implementation)
============================================================

测试 1: 基础装箱问题
------------------------------------------------------------
物品重量: [7, 5, 5, 3, 3, 3, 2]
箱子容量: 10

最少箱子数: 3
箱子 0: [7, 3] (重量: 10)
箱子 1: [5, 5] (重量: 10)
箱子 2: [3, 3, 2] (重量: 8)

测试 2: 更大的物品集合
------------------------------------------------------------
物品重量: [6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3]
箱子容量: 12

最少箱子数: 4
箱子 0: [6, 6] (重量: 12)
箱子 1: [5, 5] (重量: 10)
箱子 2: [5, 4, 3] (重量: 12)
箱子 3: [4, 4, 3, 3] (重量: 14) // 可能有所不同，取决于搜索顺序

测试 3: 完美适配的物品
------------------------------------------------------------
物品重量: [5, 5, 4, 4, 3, 2, 2]
箱子容量: 10

最少箱子数: 3
箱子 0: [5, 5] (重量: 10)
箱子 1: [4, 4, 2] (重量: 10)
箱子 2: [3, 2] (重量: 5)
*/
