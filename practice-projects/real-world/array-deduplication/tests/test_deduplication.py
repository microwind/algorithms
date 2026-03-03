"""
数组去重系统 - 单元测试
"""

import sys
sys.path.insert(0, '../src/python')

from deduplication import (
    ArrayDeduplication,
    LogDeduplication,
    UserAnalytics,
    IPTracker
)


def test_array_deduplication():
    """测试基础去重"""
    arr = [1, 2, 2, 3, 3, 3, 4]
    result = ArrayDeduplication.remove_duplicates_by_set(arr)
    assert set(result) == {1, 2, 3, 4}
    assert len(result) == 4


def test_find_duplicates():
    """测试找出重复元素"""
    arr = [1, 2, 2, 3, 3, 3, 4]
    duplicates = ArrayDeduplication.find_duplicates(arr)
    assert set(duplicates) == {2, 3}


def test_log_deduplication():
    """测试日志去重"""
    logger = LogDeduplication()
    errors = ["Error A", "Error B", "Error A", "Error B", "Error B"]
    for error in errors:
        logger.add_error_log(error)

    assert logger.get_unique_errors() == ["Error A", "Error B"] or \
           logger.get_unique_errors() == ["Error B", "Error A"]
    assert len(logger.get_unique_errors()) == 2


def test_user_analytics():
    """测试用户统计"""
    analytics = UserAnalytics()
    users = [1, 2, 2, 3, 3, 3]
    for user_id in users:
        analytics.record_user_activity("2024-03-01", user_id)

    assert analytics.get_dau("2024-03-01") == 3


def test_ip_tracker():
    """测试IP统计"""
    tracker = IPTracker()
    ips = ["192.168.1.1", "192.168.1.2", "192.168.1.1"]
    for ip in ips:
        tracker.record_ip(ip)

    assert tracker.get_unique_ip_count() == 2
    top_ips = tracker.get_top_ips(1)
    assert top_ips[0][0] == "192.168.1.1"


if __name__ == "__main__":
    print("运行数组去重系统测试...\n")

    test_array_deduplication()
    print("✅ test_array_deduplication 通过")

    test_find_duplicates()
    print("✅ test_find_duplicates 通过")

    test_log_deduplication()
    print("✅ test_log_deduplication 通过")

    test_user_analytics()
    print("✅ test_user_analytics 通过")

    test_ip_tracker()
    print("✅ test_ip_tracker 通过")

    print("\n✅ 所有测试通过！")
