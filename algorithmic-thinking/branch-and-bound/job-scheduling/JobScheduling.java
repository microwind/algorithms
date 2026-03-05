/**
 * 作业调度问题 - 分支定界算法 (Java)
 */

import java.util.*;

public class JobScheduling {
    private int[] jobTimes;
    private int numMachines;
    private int n;
    private int minMakespan;
    private List<List<Integer>> bestSchedule;
    private List<List<Integer>> currentSchedule;
    private int[] machineTimes;
    
    public JobScheduling(int[] jobTimes, int numMachines) {
        this.jobTimes = jobTimes;
        this.numMachines = numMachines;
        this.n = jobTimes.length;
        this.minMakespan = Integer.MAX_VALUE;
        this.bestSchedule = new ArrayList<>();
        this.currentSchedule = new ArrayList<>();
        this.machineTimes = new int[numMachines];
        
        for (int i = 0; i < numMachines; i++) {
            currentSchedule.add(new ArrayList<>());
        }
    }
    
    private int lowerBound(int jobIdx) {
        int remainingTime = 0;
        for (int i = jobIdx; i < n; i++) {
            remainingTime += jobTimes[i];
        }
        
        int maxTime = 0;
        for (int time : machineTimes) {
            maxTime = Math.max(maxTime, time);
        }
        
        return maxTime + remainingTime / numMachines;
    }
    
    private void branchAndBound(int jobIdx) {
        if (lowerBound(jobIdx) >= minMakespan) {
            return;
        }
        
        if (jobIdx == n) {
            int makespan = 0;
            for (int time : machineTimes) {
                makespan = Math.max(makespan, time);
            }
            
            if (makespan < minMakespan) {
                minMakespan = makespan;
                bestSchedule.clear();
                for (List<Integer> schedule : currentSchedule) {
                    bestSchedule.add(new ArrayList<>(schedule));
                }
            }
            return;
        }
        
        int job = jobTimes[jobIdx];
        
        for (int machine = 0; machine < numMachines; machine++) {
            currentSchedule.get(machine).add(job);
            machineTimes[machine] += job;
            
            branchAndBound(jobIdx + 1);
            
            machineTimes[machine] -= job;
            currentSchedule.get(machine).remove(currentSchedule.get(machine).size() - 1);
        }
    }
    
    public int solve() {
        branchAndBound(0);
        return minMakespan;
    }
    
    public List<List<Integer>> getSchedule() {
        return bestSchedule;
    }
    
    public static void main(String[] args) {
        int[] jobTimes = {5, 3, 8, 6, 2};
        int numMachines = 2;
        
        System.out.println("============================================================");
        System.out.println("Job Scheduling Problem (Java)");
        System.out.println("============================================================");
        
        System.out.println("\nJob Times: " + Arrays.toString(jobTimes));
        System.out.println("Number of Machines: " + numMachines);
        
        int totalTime = 0;
        for (int time : jobTimes) totalTime += time;
        System.out.println("Total Work: " + totalTime);
        
        JobScheduling solver = new JobScheduling(jobTimes, numMachines);
        int makespan = solver.solve();
        List<List<Integer>> schedule = solver.getSchedule();
        
        System.out.println("\nMinimum Makespan: " + makespan);
        System.out.println("\nSchedule:");
        for (int i = 0; i < schedule.size(); i++) {
            List<Integer> jobs = schedule.get(i);
            int totalJobTime = 0;
            for (int time : jobs) totalJobTime += time;
            System.out.printf("Machine %d: %s (time: %d)\n", i, jobs, totalJobTime);
        }
    }
}
