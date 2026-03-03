/**
 * 实际应用：数组去重
 * 场景：数据统计、日志去重、用户去重、IP去重
 */

class ArrayDeduplication {
    // 使用Set去重
    static removeDuplicates(arr) {
        return [...new Set(arr)];
    }

    // 保持顺序的去重
    static removeDuplicatesPreserveOrder(arr) {
        const seen = new Set();
        return arr.filter(item => {
            if (seen.has(item)) return false;
            seen.add(item);
            return true;
        });
    }

    // 找出重复元素
    static findDuplicates(arr) {
        const seen = new Set();
        const duplicates = new Set();
        for (const item of arr) {
            if (seen.has(item)) {
                duplicates.add(item);
            } else {
                seen.add(item);
            }
        }
        return [...duplicates];
    }

    // 统计唯一元素数量
    static countUnique(arr) {
        return new Set(arr).size;
    }
}

// 日志去重系统
class LogDeduplication {
    constructor() {
        this.errorLogs = new Set();
        this.logCount = new Map();
    }

    addErrorLog(errorMsg) {
        if (!this.errorLogs.has(errorMsg)) {
            this.errorLogs.add(errorMsg);
            this.logCount.set(errorMsg, 1);
        } else {
            this.logCount.set(errorMsg, this.logCount.get(errorMsg) + 1);
        }
    }

    getUniqueErrorCount() {
        return this.errorLogs.size;
    }

    getErrorFrequency() {
        return [...this.logCount.entries()]
            .sort((a, b) => b[1] - a[1]);
    }

    printErrorFrequency() {
        this.getErrorFrequency().forEach(([error, count]) => {
            console.log(`  ${error}: ${count}次`);
        });
    }
}

// 用户活跃度统计
class UserAnalytics {
    constructor() {
        this.dailyActiveUsers = new Map();
    }

    recordUserActivity(date, userId) {
        if (!this.dailyActiveUsers.has(date)) {
            this.dailyActiveUsers.set(date, new Set());
        }
        this.dailyActiveUsers.get(date).add(userId);
    }

    getDAU(date) {
        return this.dailyActiveUsers.get(date)?.size || 0;
    }

    getMAU(month) {
        const allUsers = new Set();
        for (const [date, users] of this.dailyActiveUsers.entries()) {
            if (date.startsWith(month)) {
                for (const userId of users) {
                    allUsers.add(userId);
                }
            }
        }
        return allUsers.size;
    }
}

// IP去重和统计
class IPTracker {
    constructor() {
        this.uniqueIps = new Set();
        this.ipCount = new Map();
    }

    recordIP(ip) {
        this.uniqueIps.add(ip);
        this.ipCount.set(ip, (this.ipCount.get(ip) || 0) + 1);
    }

    getUniqueIPCount() {
        return this.uniqueIps.size;
    }

    getTopIPs(n = 10) {
        return [...this.ipCount.entries()]
            .sort((a, b) => b[1] - a[1])
            .slice(0, n);
    }

    printTopIPs(n = 10) {
        this.getTopIPs(n).forEach(([ip, count]) => {
            console.log(`  ${ip}: ${count}次`);
        });
    }
}

// 测试代码
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        ArrayDeduplication,
        LogDeduplication,
        UserAnalytics,
        IPTracker
    };
}

// 运行示例
console.log("=== 数组去重实际应用 ===\n");

// 基础去重
const arr = [1, 2, 2, 3, 3, 3, 4];
console.log(`原数组: [${arr}]`);
console.log(`去重后: [${ArrayDeduplication.removeDuplicates(arr)}]`);
console.log(`保序去重: [${ArrayDeduplication.removeDuplicatesPreserveOrder(arr)}]`);
console.log(`唯一元素数: ${ArrayDeduplication.countUnique(arr)}`);
console.log(`重复元素: [${ArrayDeduplication.findDuplicates(arr)}]\n`);

// 日志去重
console.log("--- 日志系统去重 ---");
const logger = new LogDeduplication();
const errors = [
    "Connection timeout",
    "Database error",
    "Connection timeout",
    "File not found",
    "Database error",
    "Database error"
];
errors.forEach(error => logger.addErrorLog(error));
console.log(`唯一错误数: ${logger.getUniqueErrorCount()}`);
console.log("错误频率:");
logger.printErrorFrequency();

// 用户统计
console.log("\n--- 活跃用户统计 ---");
const analytics = new UserAnalytics();
const users = [1, 2, 2, 3, 3, 3, 4, 5, 5];
users.forEach(userId => analytics.recordUserActivity("2024-03-01", userId));
console.log(`日活跃用户数 (DAU): ${analytics.getDAU("2024-03-01")}`);

// IP统计
console.log("\n--- IP去重统计 ---");
const ipTracker = new IPTracker();
const ips = ["192.168.1.1", "192.168.1.2", "192.168.1.1", "192.168.1.3", "192.168.1.1"];
ips.forEach(ip => ipTracker.recordIP(ip));
console.log(`唯一IP数: ${ipTracker.getUniqueIPCount()}`);
console.log(`总访问次数: ${ips.length}`);
console.log("IP访问频率 (Top 3):");
ipTracker.printTopIPs(3);
