"""
布隆过滤器系统 - 单元测试
"""

import sys
sys.path.insert(0, '../src/python')

from bloom_filter import (
    BloomFilter,
    URLCrawlerFilter,
    IpBlocklistFilter
)


def test_bloom_filter_basic():
    """测试基础布隆过滤器"""
    bf = BloomFilter(expected_elements=1000, false_positive_rate=0.01)

    items = [f"item_{i}" for i in range(100)]
    for item in items:
        bf.add(item)

    # 验证所有添加的元素都能找到
    for item in items:
        assert bf.contains(item), f"应该找到 {item}"

    # 验证不存在的元素
    assert not bf.contains("nonexistent"), "不存在的元素应该返回False"


def test_bloom_filter_false_positive():
    """测试误判率"""
    bf = BloomFilter(expected_elements=1000, false_positive_rate=0.01)

    # 添加100个元素
    for i in range(100):
        bf.add(f"item_{i}")

    # 检查1000个不存在的元素
    false_positives = 0
    for i in range(100, 1100):
        if bf.contains(f"item_{i}"):
            false_positives += 1

    fpr = false_positives / 1000
    # 误判率应该在预期范围内（允许2倍误差）
    assert fpr < 0.02, f"误判率 {fpr:.3%} 应该 < 2%"


def test_url_crawler():
    """测试URL爬虫去重"""
    crawler = URLCrawlerFilter(expected_urls=10000)

    urls = [f"http://example.com/page_{i}" for i in range(100)]

    # 第一次爬取
    for url in urls:
        crawler.mark_crawled(url)

    # 第二次爬取（应该都被检测为重复）
    duplicates = 0
    for url in urls:
        if crawler.is_crawled(url):
            duplicates += 1

    assert duplicates == 100, "应该检测到所有重复"


def test_ip_blocklist():
    """测试IP黑名单"""
    ip_filter = IpBlocklistFilter(expected_ips=10000)

    blacklist = ["192.168.1.1", "192.168.1.2", "192.168.1.3"]
    for ip in blacklist:
        ip_filter.add_blocked_ip(ip)

    # 验证黑名单IP被检测
    for ip in blacklist:
        assert ip_filter.is_blocked(ip), f"{ip} 应该被阻止"

    # 验证白名单IP不被检测
    assert not ip_filter.is_blocked("192.168.1.100"), "白名单IP应该通过"


if __name__ == "__main__":
    print("运行布隆过滤器系统测试...\n")

    test_bloom_filter_basic()
    print("✅ test_bloom_filter_basic 通过")

    test_bloom_filter_false_positive()
    print("✅ test_bloom_filter_false_positive 通过")

    test_url_crawler()
    print("✅ test_url_crawler 通过")

    test_ip_blocklist()
    print("✅ test_ip_blocklist 通过")

    print("\n✅ 所有测试通过！")
