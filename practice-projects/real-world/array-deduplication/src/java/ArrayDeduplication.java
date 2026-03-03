import java.util.*;

/**
 * 实际应用：数组去重
 * 场景：数据统计、日志去重、用户去重、IP去重
 */
public class ArrayDeduplication {

    // 基础去重方法
    public static List<Integer> removeDuplicates(int[] arr) {
        Set<Integer> set = new HashSet<>(Arrays.asList(
            Arrays.stream(arr).boxed().toArray(Integer[]::new)
        ));
        return new ArrayList<>(set);
    }

    // 保持顺序的去重
    public static List<Integer> removeDuplicatesPreserveOrder(int[] arr) {
        Set<Integer> seen = new LinkedHashSet<>();
        for (int num : arr) {
            seen.add(num);
        }
        return new ArrayList<>(seen);
    }

    // 找出重复元素
    public static Set<Integer> findDuplicates(int[] arr) {
        Set<Integer> seen = new HashSet<>();
        Set<Integer> duplicates = new HashSet<>();
        for (int num : arr) {
            if (!seen.add(num)) {
                duplicates.add(num);
            }
        }
        return duplicates;
    }

    // 日志去重系统
    static class LogDeduplication {
        private Set<String> errorLogs;
        private Map<String, Integer> logCount;

        public LogDeduplication() {
            this.errorLogs = new HashSet<>();
            this.logCount = new HashMap<>();
        }

        public void addErrorLog(String errorMsg) {
            if (!errorLogs.contains(errorMsg)) {
                errorLogs.add(errorMsg);
                logCount.put(errorMsg, 1);
            } else {
                logCount.put(errorMsg, logCount.get(errorMsg) + 1);
            }
        }

        public int getUniqueErrorCount() {
            return errorLogs.size();
        }

        public void printErrorFrequency() {
            logCount.entrySet().stream()
                .sorted((a, b) -> b.getValue() - a.getValue())
                .forEach(e -> System.out.println("  " + e.getKey() + ": " + e.getValue() + "次"));
        }
    }

    // 用户活跃度统计
    static class UserAnalytics {
        private Map<String, Set<Integer>> dailyActiveUsers;

        public UserAnalytics() {
            this.dailyActiveUsers = new HashMap<>();
        }

        public void recordUserActivity(String date, int userId) {
            dailyActiveUsers.computeIfAbsent(date, k -> new HashSet<>()).add(userId);
        }

        public int getDau(String date) {
            return dailyActiveUsers.getOrDefault(date, new HashSet<>()).size();
        }

        public int getMau(String month) {
            Set<Integer> allUsers = new HashSet<>();
            dailyActiveUsers.forEach((date, users) -> {
                if (date.startsWith(month)) {
                    allUsers.addAll(users);
                }
            });
            return allUsers.size();
        }
    }

    // IP去重和统计
    static class IPTracker {
        private Set<String> uniqueIps;
        private Map<String, Integer> ipCount;

        public IPTracker() {
            this.uniqueIps = new HashSet<>();
            this.ipCount = new HashMap<>();
        }

        public void recordIp(String ip) {
            uniqueIps.add(ip);
            ipCount.put(ip, ipCount.getOrDefault(ip, 0) + 1);
        }

        public int getUniqueIpCount() {
            return uniqueIps.size();
        }

        public void printTopIps(int n) {
            ipCount.entrySet().stream()
                .sorted((a, b) -> b.getValue() - a.getValue())
                .limit(n)
                .forEach(e -> System.out.println("  " + e.getKey() + ": " + e.getValue() + "次"));
        }
    }

    public static void main(String[] args) {
        System.out.println("=== 数组去重实际应用 ===\n");

        // 基础去重
        int[] arr = {1, 2, 2, 3, 3, 3, 4};
        System.out.println("原数组: " + Arrays.toString(arr));
        System.out.println("去重后: " + removeDuplicates(arr));
        System.out.println("保序去重: " + removeDuplicatesPreserveOrder(arr));
        System.out.println("重复元素: " + findDuplicates(arr) + "\n");

        // 日志去重
        System.out.println("--- 日志系统去重 ---");
        LogDeduplication logger = new LogDeduplication();
        String[] errors = {
            "Connection timeout",
            "Database error",
            "Connection timeout",
            "File not found",
            "Database error",
            "Database error"
        };
        for (String error : errors) {
            logger.addErrorLog(error);
        }
        System.out.println("唯一错误数: " + logger.getUniqueErrorCount());
        System.out.println("错误频率:");
        logger.printErrorFrequency();

        // 用户统计
        System.out.println("\n--- 活跃用户统计 ---");
        UserAnalytics analytics = new UserAnalytics();
        int[] users = {1, 2, 2, 3, 3, 3, 4, 5, 5};
        for (int userId : users) {
            analytics.recordUserActivity("2024-03-01", userId);
        }
        System.out.println("日活跃用户数 (DAU): " + analytics.getDau("2024-03-01"));

        // IP统计
        System.out.println("\n--- IP去重统计 ---");
        IPTracker ipTracker = new IPTracker();
        String[] ips = {"192.168.1.1", "192.168.1.2", "192.168.1.1", "192.168.1.3", "192.168.1.1"};
        for (String ip : ips) {
            ipTracker.recordIp(ip);
        }
        System.out.println("唯一IP数: " + ipTracker.getUniqueIpCount());
        System.out.println("总访问次数: " + ips.length);
        System.out.println("IP访问频率 (Top 3):");
        ipTracker.printTopIps(3);
    }
}
