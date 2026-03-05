"""
作业调度问题 - 分支定界算法
将n个作业分配给m台機器以最小化处理時間
"""

class JobScheduling:
    def __init__(self, job_times, num_machines):
        """
        初始化作业调度求解器
        job_times: 每个作业需要的时間列表
        num_machines: 可用機器整数
        时间: O(n), 空间: O(n + m)
        """
        self.job_times = job_times
        self.num_machines = num_machines
        self.n = len(job_times)
        
        self.min_makespan = float('inf')
        self.best_schedule = [[] for _ in range(num_machines)]
        self.current_schedule = [[] for _ in range(num_machines)]
        self.machine_times = [0] * num_machines
    
    def lower_bound(self, job_idx):
        """
        使用平均负载和当前载载的最大值计算下界
        时间: O(m), 空间: O(1)
        """
        # 剩余作业的平均负载
        remaining_time = sum(self.job_times[job_idx:])
        avg_load = remaining_time / self.num_machines
        
        # 下界至少为max(当前機器负载) + 平均负载
        bound = max(self.machine_times) + avg_load
        
        return int(bound)
    
    def branch_and_bound(self, job_idx=0):
        """
        分支定界及剪枝
        时间: 指数级及剪枝, 空间: O(n)
        """
        # 剪枝：下界 >= 当前最优解，跳过
        if self.lower_bound(job_idx) >= self.min_makespan:
            return
        
        # 基础情况：所有作业已分顯
        if job_idx == self.n:
            makespan = max(self.machine_times)
            if makespan < self.min_makespan:
                self.min_makespan = makespan
                self.best_schedule = [machine[:] for machine in self.current_schedule]
            return
        
        # 分支：尝试将作业割派给每台機器
        job = self.job_times[job_idx]
        
        for machine in range(self.num_machines):
            # Assign job to machine
            self.current_schedule[machine].append(job)
            self.machine_times[machine] += job
            
            self.branch_and_bound(job_idx + 1)
            
            # Backtrack
            self.current_schedule[machine].pop()
            self.machine_times[machine] -= job
    
    def solve(self):
        """
        求解并返回最小处理時間和调度方案
        """
        self.branch_and_bound()
        return self.min_makespan, self.best_schedule
    
    def get_schedule_details(self):
        """
        获取详细的调度信息
        """
        details = []
        for machine_id, jobs in enumerate(self.best_schedule):
            details.append({
                'machine': machine_id,
                'jobs': jobs,
                'total_time': sum(jobs)
            })
        return details


# 测试和例子
if __name__ == "__main__":
    print("=" * 60)
    print("Job Scheduling Problem - Branch and Bound")
    print("=" * 60)
    
    # Test case 1
    job_times = [5, 3, 8, 6, 2]
    num_machines = 2
    
    print(f"\nJobs (processing times): {job_times}")
    print(f"Number of Machines: {num_machines}")
    print(f"Total Work: {sum(job_times)}")
    
    solver = JobScheduling(job_times, num_machines)
    makespan, schedule = solver.solve()
    
    print(f"\nMinimum Makespan (completion time): {makespan}")
    print("\nSchedule:")
    for machine_id, jobs in enumerate(schedule):
        total_time = sum(jobs)
        print(f"Machine {machine_id}: {jobs} (time: {total_time})")
    
    # Test case 2
    print("\n" + "=" * 60)
    job_times2 = [7, 5, 5, 4, 3, 2, 2]
    num_machines2 = 3
    
    print(f"\nJobs: {job_times2}")
    print(f"Number of Machines: {num_machines2}")
    print(f"Total Work: {sum(job_times2)}")
    
    solver2 = JobScheduling(job_times2, num_machines2)
    makespan2, schedule2 = solver2.solve()
    
    print(f"\nMinimum Makespan: {makespan2}")
    print("\nSchedule:")
    for machine_id, jobs in enumerate(schedule2):
        total_time = sum(jobs)
        print(f"Machine {machine_id}: {jobs} (time: {total_time})")
