"""
一致哈希系统 - 单元测试
"""

import sys
sys.path.insert(0, '../src/python')

from consistent_hashing import (
    ConsistentHash,
    DistributedCache,
    LoadBalancer
)


def test_consistent_hash_basic():
    """测试基础一致哈希"""
    ch = ConsistentHash(replicas=3)

    ch.add_node("server1")
    ch.add_node("server2")
    ch.add_node("server3")

    # 同一key总是映射到同一服务器
    node1 = ch.get_node("user_123")
    node2 = ch.get_node("user_123")
    assert node1 == node2, "同一key应该映射到同一服务器"


def test_consistent_hash_distribution():
    """测试哈希分布"""
    ch = ConsistentHash(replicas=3)

    for i in range(1, 4):
        ch.add_node(f"server{i}")

    # 测试100个key的分布
    distribution = {}
    for i in range(100):
        node = ch.get_node(f"key_{i}")
        distribution[node] = distribution.get(node, 0) + 1

    # 应该相对均匀分布
    avg = 100 / 3
    for count in distribution.values():
        # 允许 ±50% 的偏差
        assert 30 < count < 70, f"分布应该相对均匀，期望~{avg:.0f}，实际{count}"


def test_distributed_cache():
    """测试分布式缓存"""
    cache = DistributedCache(replicas=3)

    cache.add_server("cache1")
    cache.add_server("cache2")
    cache.add_server("cache3")

    # 存储数据
    for i in range(30):
        cache.set(f"user_{i}", f"data_{i}")

    # 验证数据
    for i in range(30):
        assert cache.get(f"user_{i}") == f"data_{i}"


def test_load_balancer():
    """测试负载均衡"""
    lb = LoadBalancer(replicas=3)

    lb.add_server("server1")
    lb.add_server("server2")
    lb.add_server("server3")

    # 1000个请求
    for i in range(1000):
        server = lb.route_request(f"req_{i}")
        assert server is not None

    stats = lb.get_load_balance_stats()
    total = sum(s['requests'] for s in stats.values())
    assert total == 1000, "应该处理1000个请求"


if __name__ == "__main__":
    print("运行一致哈希系统测试...\n")

    test_consistent_hash_basic()
    print("✅ test_consistent_hash_basic 通过")

    test_consistent_hash_distribution()
    print("✅ test_consistent_hash_distribution 通过")

    test_distributed_cache()
    print("✅ test_distributed_cache 通过")

    test_load_balancer()
    print("✅ test_load_balancer 通过")

    print("\n✅ 所有测试通过！")
