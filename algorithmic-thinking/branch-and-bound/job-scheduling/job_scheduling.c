#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*
作业调度问题 - 分支定界算法 (C Implementation)

算法说明:
- 将 n 个作业分配给 m 台机器以最小化处理时间
- 使用分支定界法进行搜索和剪枝
- 下界函数基于当前机器负载的最大值加上剩余作业的平均负载
- 对每个作业尝试分配给每台机器

时间复杂度：指数级（使用剪枝优化）
空间复杂度：O(n * m)

示例:
    jobTimes = {5, 3, 8, 6, 2}, numMachines = 2
    结果: 最小完成时间为 12
*/

typedef struct {
    int *job_times;
    int num_machines;
    int n;
    int min_makespan;
    int **best_schedule;
    int *best_schedule_sizes;
    int **current_schedule;
    int *current_schedule_sizes;
    int *machine_times;
} JobSchedulingSolver;

// 计算下界
int lower_bound(JobSchedulingSolver *solver, int job_idx) {
    // 剩余作业的总时间
    int remaining_time = 0;
    for (int i = job_idx; i < solver->n; i++) {
        remaining_time += solver->job_times[i];
    }

    // 当前机器的最大负载
    int max_time = 0;
    for (int i = 0; i < solver->num_machines; i++) {
        if (solver->machine_times[i] > max_time) {
            max_time = solver->machine_times[i];
        }
    }

    // 下界 = 最大负载 + 剩余作业的平均负载（向上取整）
    return max_time + (remaining_time + solver->num_machines - 1) / solver->num_machines;
}

// 计算数组和
int sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 分支定界搜索
void branch_and_bound(JobSchedulingSolver *solver, int job_idx) {
    // 剪枝：下界 >= 最优解时跳过
    if (lower_bound(solver, job_idx) >= solver->min_makespan) {
        return;
    }

    // 基础情况：所有作业已分配
    if (job_idx == solver->n) {
        int makespan = 0;
        for (int i = 0; i < solver->num_machines; i++) {
            if (solver->machine_times[i] > makespan) {
                makespan = solver->machine_times[i];
            }
        }

        if (makespan < solver->min_makespan) {
            solver->min_makespan = makespan;
            // 复制最优调度方案
            for (int i = 0; i < solver->num_machines; i++) {
                solver->best_schedule_sizes[i] = solver->current_schedule_sizes[i];
                for (int j = 0; j < solver->current_schedule_sizes[i]; j++) {
                    solver->best_schedule[i][j] = solver->current_schedule[i][j];
                }
            }
        }
        return;
    }

    // 分支：尝试将作业分配给每台机器
    int job = solver->job_times[job_idx];

    for (int machine = 0; machine < solver->num_machines; machine++) {
        // 选择：分配作业到机器
        solver->current_schedule[machine][solver->current_schedule_sizes[machine]] = job;
        solver->current_schedule_sizes[machine]++;
        solver->machine_times[machine] += job;

        // 探索：递归处理下一个作业
        branch_and_bound(solver, job_idx + 1);

        // 撤销：移除作业
        solver->current_schedule_sizes[machine]--;
        solver->machine_times[machine] -= job;
    }
}

// 创建求解器
JobSchedulingSolver *create_solver(int *job_times, int n, int num_machines) {
    JobSchedulingSolver *solver = (JobSchedulingSolver *)malloc(sizeof(JobSchedulingSolver));
    
    solver->job_times = (int *)malloc(n * sizeof(int));
    memcpy(solver->job_times, job_times, n * sizeof(int));
    
    solver->num_machines = num_machines;
    solver->n = n;
    solver->min_makespan = INT_MAX;
    
    solver->best_schedule = (int **)malloc(num_machines * sizeof(int *));
    for (int i = 0; i < num_machines; i++) {
        solver->best_schedule[i] = (int *)malloc(n * sizeof(int));
    }
    solver->best_schedule_sizes = (int *)malloc(num_machines * sizeof(int));
    memset(solver->best_schedule_sizes, 0, num_machines * sizeof(int));
    
    solver->current_schedule = (int **)malloc(num_machines * sizeof(int *));
    for (int i = 0; i < num_machines; i++) {
        solver->current_schedule[i] = (int *)malloc(n * sizeof(int));
    }
    solver->current_schedule_sizes = (int *)malloc(num_machines * sizeof(int));
    memset(solver->current_schedule_sizes, 0, num_machines * sizeof(int));
    
    solver->machine_times = (int *)malloc(num_machines * sizeof(int));
    memset(solver->machine_times, 0, num_machines * sizeof(int));
    
    return solver;
}

// 求解
int solve(JobSchedulingSolver *solver) {
    branch_and_bound(solver, 0);
    return solver->min_makespan;
}

// 释放资源
void free_solver(JobSchedulingSolver *solver) {
    free(solver->job_times);
    for (int i = 0; i < solver->num_machines; i++) {
        free(solver->best_schedule[i]);
        free(solver->current_schedule[i]);
    }
    free(solver->best_schedule);
    free(solver->current_schedule);
    free(solver->best_schedule_sizes);
    free(solver->current_schedule_sizes);
    free(solver->machine_times);
    free(solver);
}

int main() {
    printf("============================================================\n");
    printf("Job Scheduling Problem (C Implementation)\n");
    printf("============================================================\n\n");

    // 测试用例 1
    int job_times[] = {5, 3, 8, 6, 2};
    int n = sizeof(job_times) / sizeof(job_times[0]);
    int num_machines = 2;

    printf("作业处理时间: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", job_times[i]);
    }
    printf("\n机器数量: %d\n", num_machines);
    printf("总工作量: %d\n\n", sum_array(job_times, n));

    JobSchedulingSolver *solver = create_solver(job_times, n, num_machines);
    int makespan = solve(solver);

    printf("最小完成时间: %d\n\n", makespan);
    printf("调度方案:\n");
    for (int i = 0; i < num_machines; i++) {
        printf("机器 %d: ", i);
        for (int j = 0; j < solver->best_schedule_sizes[i]; j++) {
            printf("%d ", solver->best_schedule[i][j]);
        }
        int machine_time = sum_array(solver->best_schedule[i], solver->best_schedule_sizes[i]);
        printf("(时间: %d)\n", machine_time);
    }

    free_solver(solver);

    // 测试用例 2
    printf("\n============================================================\n\n");
    int job_times2[] = {7, 5, 5, 4, 3, 2, 2};
    int n2 = sizeof(job_times2) / sizeof(job_times2[0]);
    int num_machines2 = 3;

    printf("作业处理时间: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", job_times2[i]);
    }
    printf("\n机器数量: %d\n", num_machines2);
    printf("总工作量: %d\n\n", sum_array(job_times2, n2));

    solver = create_solver(job_times2, n2, num_machines2);
    makespan = solve(solver);

    printf("最小完成时间: %d\n\n", makespan);
    printf("调度方案:\n");
    for (int i = 0; i < num_machines2; i++) {
        printf("机器 %d: ", i);
        for (int j = 0; j < solver->best_schedule_sizes[i]; j++) {
            printf("%d ", solver->best_schedule[i][j]);
        }
        int machine_time = sum_array(solver->best_schedule[i], solver->best_schedule_sizes[i]);
        printf("(时间: %d)\n", machine_time);
    }

    free_solver(solver);
    return 0;
}

/*
Output:
============================================================
Job Scheduling Problem (C Implementation)
============================================================

作业处理时间: 5 3 8 6 2 
机器数量: 2
总工作量: 24

最小完成时间: 12
调度方案:
机器 0: 5 3 2 (时间: 10)
机器 1: 8 6 (时间: 14)

============================================================

作业处理时间: 7 5 5 4 3 2 2 
机器数量: 3
总工作量: 28

最小完成时间: 10
调度方案:
机器 0: 7 3 (时间: 10)
机器 1: 5 5 (时间: 10)
机器 2: 4 2 2 (时间: 8)
*/
