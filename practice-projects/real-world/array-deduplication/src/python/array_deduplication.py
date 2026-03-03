"""
实际应用：数组去重
场景：数据统计、日志去重、用户去重、IP去重

使用场景：
- 统计活跃用户数
- 日志系统中去重错误日志
- 推荐系统中去重用户浏览记录
- 流量统计中去重IP地址
"""

class ArrayDeduplication:
    """数组去重实现"""

    @staticmethod
    def remove_duplicates_by_set(arr):
        """使用Set去重，时间O(n)，空间O(n)"""
        return list(set(arr))

    @staticmethod
    def remove_duplicates_preserve_order(arr):
        """保持顺序的去重，使用字典"""
        seen = {}
        result = []
        for item in arr:
            if item not in seen:
                seen[item] = True
                result.append(item)
        return result

    @staticmethod
    def count_unique(arr):
        """统计唯一元素数量"""
        return len(set(arr))

    @staticmethod
    def find_duplicates(arr):
        """找出所有重复的元素"""
        seen = set()
        duplicates = set()
        for item in arr:
            if item in seen:
                duplicates.add(item)
            seen.add(item)
        return list(duplicates)


# 实际场景1：日志系统去重
class LogDeduplication:
    """日志系统中的去重"""

    def __init__(self):
        self.error_logs = set()
        self.log_count = {}

    def add_error_log(self, error_msg):
        """添加错误日志，自动去重"""
        if error_msg not in self.error_logs:
            self.error_logs.add(error_msg)
            self.log_count[error_msg] = 1
        else:
            self.log_count[error_msg] += 1

    def get_unique_errors(self):
        """获取唯一的错误"""
        return list(self.error_logs)

    def get_error_frequency(self):
        """获取错误频率"""
        return sorted(self.log_count.items(), key=lambda x: x[1], reverse=True)


# 实际场景2：活跃用户统计
class UserAnalytics:
    """用户活跃度统计"""

    def __init__(self):
        self.daily_active_users = {}

    def record_user_activity(self, date, user_id):
        """记录用户活动"""
        if date not in self.daily_active_users:
            self.daily_active_users[date] = set()
        self.daily_active_users[date].add(user_id)

    def get_dau(self, date):
        """获取日活跃用户数 (DAU)"""
        return len(self.daily_active_users.get(date, set()))

    def get_mau(self, month):
        """获取月活跃用户数 (MAU)"""
        all_users = set()
        for date, users in self.daily_active_users.items():
            if date.startswith(month):
                all_users.update(users)
        return len(all_users)


# 实际场景3：IP去重和统计
class IPTracker:
    """IP地址去重和统计"""

    def __init__(self):
        self.ip_count = {}
        self.unique_ips = set()

    def record_ip(self, ip):
        """记录IP访问"""
        self.unique_ips.add(ip)
        self.ip_count[ip] = self.ip_count.get(ip, 0) + 1

    def get_unique_ip_count(self):
        """获取唯一IP数"""
        return len(self.unique_ips)

    def get_top_ips(self, n=10):
        """获取访问最频繁的IP"""
        return sorted(self.ip_count.items(), key=lambda x: x[1], reverse=True)[:n]


if __name__ == "__main__":
    print("=== 数组去重实际应用 ===\n")

    # 基础去重
    arr = [1, 2, 2, 3, 3, 3, 4]
    print(f"原数组: {arr}")
    print(f"去重后: {ArrayDeduplication.remove_duplicates_by_set(arr)}")
    print(f"保序去重: {ArrayDeduplication.remove_duplicates_preserve_order(arr)}")
    print(f"唯一元素数: {ArrayDeduplication.count_unique(arr)}")
    print(f"重复元素: {ArrayDeduplication.find_duplicates(arr)}\n")

    # 日志去重
    print("--- 日志系统去重 ---")
    logger = LogDeduplication()
    errors = [
        "Connection timeout",
        "Database error",
        "Connection timeout",
        "File not found",
        "Database error",
        "Database error"
    ]
    for error in errors:
        logger.add_error_log(error)

    print(f"唯一错误数: {len(logger.get_unique_errors())}")
    print("错误频率:")
    for error, count in logger.get_error_frequency():
        print(f"  {error}: {count}次")

    # 用户统计
    print("\n--- 活跃用户统计 ---")
    analytics = UserAnalytics()
    users = [1, 2, 2, 3, 3, 3, 4, 5, 5]
    for user_id in users:
        analytics.record_user_activity("2024-03-01", user_id)
    print(f"日活跃用户数 (DAU): {analytics.get_dau('2024-03-01')}")

    # IP统计
    print("\n--- IP去重统计 ---")
    ip_tracker = IPTracker()
    ips = ["192.168.1.1", "192.168.1.2", "192.168.1.1", "192.168.1.3", "192.168.1.1"]
    for ip in ips:
        ip_tracker.record_ip(ip)
    print(f"唯一IP数: {ip_tracker.get_unique_ip_count()}")
    print(f"总访问次数: {len(ips)}")
