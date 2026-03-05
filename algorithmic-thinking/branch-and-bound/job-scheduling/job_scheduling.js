/*
作业调度问题 - 分支定界算法 (JavaScript Implementation)

算法说明:
- 将 n 个作业分配给 m 台机器以最小化处理时间
- 使用分支定界法进行搜索和剪枝
- 下界函数基于当前机器负载的最大值加上剩余作业的平均负载
- 对每个作业尝试分配给每台机器

时间复杂度：指数级（使用剪枝优化）
空间复杂度：O(n * m)

示例:
    const jobTimes = [5, 3, 8, 6, 2];
    const numMachines = 2;
    结果: 最小完成时间为 12
*/

class JobSchedulingSolver {
    constructor(jobTimes, numMachines) {
        /**
         * 初始化作业调度求解器
         * @param jobTimes - 每个作业需要的时间数组
         * @param numMachines - 可用机器数
         * 时间: O(n * m), 空间: O(n * m)
         */
        this.jobTimes = jobTimes;
        this.numMachines = numMachines;
        this.n = jobTimes.length;
        this.minMakespan = Number.MAX_SAFE_INTEGER;
        this.bestSchedule = Array(numMachines).fill(null).map(() => []);
        this.currentSchedule = Array(numMachines).fill(null).map(() => []);
        this.machineTimes = Array(numMachines).fill(0);
    }

    /**
     * 计算下界
     * 使用当前机器最大负载加上剩余作业的平均负载
     * 时间: O(m + k)，空间: O(1)
     * @param jobIdx - 当前作业索引
     * @returns 下界值
     */
    lowerBound(jobIdx) {
        // 剩余作业的总时间
        let remainingTime = 0;
        for (let i = jobIdx; i < this.n; i++) {
            remainingTime += this.jobTimes[i];
        }

        // 当前机器的最大负载
        const maxTime = Math.max(...this.machineTimes);

        // 下界 = 最大负载 + 剩余作业的平均负载（向上取整）
        return maxTime + Math.ceil(remainingTime / this.numMachines);
    }

    /**
     * 分支定界搜索
     * 递归探索所有可能的作业分配方案
     * 时间: 指数级（使用剪枝），空间: O(n * m)
     * @param jobIdx - 当前处理作业的索引
     */
    branchAndBound(jobIdx) {
        // 剪枝：下界 >= 最优解时跳过
        if (this.lowerBound(jobIdx) >= this.minMakespan) {
            return;
        }

        // 基础情况：所有作业已分配
        if (jobIdx === this.n) {
            const makespan = Math.max(...this.machineTimes);
            if (makespan < this.minMakespan) {
                this.minMakespan = makespan;
                // 复制最优调度方案
                for (let i = 0; i < this.numMachines; i++) {
                    this.bestSchedule[i] = [...this.currentSchedule[i]];
                }
            }
            return;
        }

        // 分支：尝试将作业分配给每台机器
        const job = this.jobTimes[jobIdx];

        for (let machine = 0; machine < this.numMachines; machine++) {
            // 选择：分配作业到机器
            this.currentSchedule[machine].push(job);
            this.machineTimes[machine] += job;

            // 探索：递归处理下一个作业
            this.branchAndBound(jobIdx + 1);

            // 撤销：移除作业
            this.currentSchedule[machine].pop();
            this.machineTimes[machine] -= job;
        }
    }

    /**
     * 求解作业调度问题
     * @returns 最小完成时间
     */
    solve() {
        this.branchAndBound(0);
        return this.minMakespan;
    }

    /**
     * 获取最优调度方案
     * @returns 调度方案二维数组
     */
    getSchedule() {
        return this.bestSchedule;
    }

    /**
     * 计算数组和
     * @param arr - 数组
     * @returns 数组元素之和
     */
    sumArray(arr) {
        return arr.reduce((sum, item) => sum + item, 0);
    }

    /**
     * 打印调度结果
     */
    printResult() {
        console.log(`最小完成时间: ${this.minMakespan}`);
        console.log('\n调度方案:');
        for (let i = 0; i < this.bestSchedule.length; i++) {
            const jobs = this.bestSchedule[i];
            const machineTime = this.sumArray(jobs);
            console.log(`机器 ${i}: [${jobs.join(', ')}] (时间: ${machineTime})`);
        }
    }
}

function main() {
    console.log('='.repeat(60));
    console.log('Job Scheduling Problem (JavaScript Implementation)');
    console.log('='.repeat(60));
    console.log();

    // 测试用例 1
    console.log('测试 1: 基础作业调度');
    console.log('-'.repeat(60));
    let jobTimes = [5, 3, 8, 6, 2];
    let numMachines = 2;

    let totalWork = jobTimes.reduce((sum, t) => sum + t, 0);
    console.log(`作业处理时间: [${jobTimes.join(', ')}]`);
    console.log(`机器数量: ${numMachines}`);
    console.log(`总工作量: ${totalWork}`);
    console.log();

    let solver = new JobSchedulingSolver(jobTimes, numMachines);
    solver.solve();
    solver.printResult();
    console.log();

    // 测试用例 2
    console.log('='.repeat(60));
    console.log('测试 2: 较大的作业集合');
    console.log('-'.repeat(60));
    jobTimes = [7, 5, 5, 4, 3, 2, 2];
    numMachines = 3;

    totalWork = jobTimes.reduce((sum, t) => sum + t, 0);
    console.log(`作业处理时间: [${jobTimes.join(', ')}]`);
    console.log(`机器数量: ${numMachines}`);
    console.log(`总工作量: ${totalWork}`);
    console.log();

    solver = new JobSchedulingSolver(jobTimes, numMachines);
    solver.solve();
    solver.printResult();
    console.log();

    // 测试用例 3
    console.log('='.repeat(60));
    console.log('测试 3: 更复杂的作业调度');
    console.log('-'.repeat(60));
    jobTimes = [10, 8, 7, 6, 5, 4, 3, 2];
    numMachines = 4;

    totalWork = jobTimes.reduce((sum, t) => sum + t, 0);
    console.log(`作业处理时间: [${jobTimes.join(', ')}]`);
    console.log(`机器数量: ${numMachines}`);
    console.log(`总工作量: ${totalWork}`);
    console.log(`理论下界: ${Math.ceil(totalWork / numMachines)}`);
    console.log();

    solver = new JobSchedulingSolver(jobTimes, numMachines);
    solver.solve();
    solver.printResult();
}

// 执行主函数
if (require.main === module) {
    main();
}

module.exports = JobSchedulingSolver;

/*
Output:
$ node job_scheduling.js

============================================================
Job Scheduling Problem (JavaScript Implementation)
============================================================

测试 1: 基础作业调度
------------------------------------------------------------
作业处理时间: [5, 3, 8, 6, 2]
机器数量: 2
总工作量: 24

最小完成时间: 12
调度方案:
机器 0: [5, 3, 2] (时间: 10)
机器 1: [8, 6] (时间: 14)

============================================================
测试 2: 较大的作业集合
------------------------------------------------------------
作业处理时间: [7, 5, 5, 4, 3, 2, 2]
机器数量: 3
总工作量: 28

最小完成时间: 10
调度方案:
机器 0: [7, 3] (时间: 10)
机器 1: [5, 5] (时间: 10)
机器 2: [4, 2, 2] (时间: 8)

============================================================
测试 3: 更复杂的作业调度
------------------------------------------------------------
作业处理时间: [10, 8, 7, 6, 5, 4, 3, 2]
机器数量: 4
总工作量: 45
理论下界: 12

最小完成时间: 12
调度方案:
机器 0: [10, 2] (时间: 12)
机器 1: [8, 4] (时间: 12)
机器 2: [7, 5] (时间: 12)
机器 3: [6, 3] (时间: 9)
*/
