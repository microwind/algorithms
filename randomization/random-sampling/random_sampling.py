# 随机采样 - Python 实现

"""
随机采样（Reservoir Sampling）
时间复杂度: O(n)
空间复杂度: O(k)
应用: 流式数据采样，无需预知数据总量
"""

import random
from collections import deque

def reservoir_sampling(data, k):
    """
    标准水库采样：从流中随机选择 k 个元素
    每个元素被选中的概率相等 = k/n
    时间: O(n), 空间: O(k)
    """
    reservoir = []
    
    for i, item in enumerate(data):
        if i < k:
            # 前 k 个元素直接放入水池
            reservoir.append(item)
        else:
            # 对于第 i (i >= k) 个元素
            # 以 k/(i+1) 的概率替换水池中的某个元素
            j = random.randint(0, i)
            if j < k:
                reservoir[j] = item
    
    return reservoir

def reservoir_sampling_weighted(data, k, weight_func):
    """
    加权水库采样
    根据权重随机选择元素
    使用 Efraimidis-Spirakis 算法
    """
    # 计算每个元素的随机键
    # key = random() ^ (1/weight)
    heap = []
    
    for i, item in enumerate(data):
        weight = weight_func(item)
        if weight > 0:
            random_key = random.random() ** (1.0 / weight)
            
            if len(heap) < k:
                heapq.heappush(heap, (random_key, i, item))
            elif random_key > heap[0][0]:
                heapq.heapreplace(heap, (random_key, i, item))
    
    # 提取结果
    result = [item for _, _, item in heap]
    return result

def reservoir_sampling_timestamp(stream, k, window_duration):
    """
    时间窗口水库采样
    只采样最近 window_duration 时间内的元素
    （假设流中有 (timestamp, data) 元组）
    """
    import time
    
    current_time = time.time()
    reservoir = []
    
    for timestamp, item in stream:
        # 跳过过期元素
        if timestamp < current_time - window_duration:
            continue
        
        if len(reservoir) < k:
            reservoir.append((timestamp, item))
        else:
            j = random.randint(0, len(reservoir) - 1)
            reservoir[j] = (timestamp, item)
    
    return reservoir

def random_sample_without_replacement(population, k):
    """
    无放回随机采样
    从总体中随机选择 k 个不同的元素
    基于水库采样
    """
    if k > len(population):
        raise ValueError("k 不能大于总体大小")
    
    # 对于小规模，直接使用 random.sample
    if k <= len(population) // 2:
        return random.sample(population, k)
    
    # 对于大规模流数据
    return reservoir_sampling(population, k)

def random_sample_with_replacement(population, k):
    """
    有放回随机采样
    从总体中随机选择 k 个元素（可重复）
    """
    return [random.choice(population) for _ in range(k)]

def online_median_finder(stream):
    """
    在线中位数计算（使用水库采样）
    时间: O(n), 空间: O(k)
    k 越大，精度越高
    """
    import statistics
    
    k = 100  # 样本大小
    sample = reservoir_sampling(stream, k)
    
    if len(sample) > 0:
        sample.sort()
        return statistics.median(sample)
    return None

def stratified_sampling(data, k, strata_func):
    """
    分层采样
    将数据分层后在每层内进行采样
    """
    # 按层分组
    strata = {}
    for item in data:
        stratum = strata_func(item)
        if stratum not in strata:
            strata[stratum] = []
        strata[stratum].append(item)
    
    # 从每层等比采样
    total = sum(len(items) for items in strata.values())
    samples = {}
    
    for stratum, items in strata.items():
        # 该层应采集的样本数
        layer_k = max(1, int(k * len(items) / total))
        samples[stratum] = random.sample(items, min(layer_k, len(items)))
    
    # 合并结果
    result = []
    for items in samples.values():
        result.extend(items)
    
    return result

if __name__ == "__main__":
    print("=" * 50)
    print("随机采样 - Python 实现")
    print("=" * 50)
    
    # 测试 1：基础水库采样
    print("\n测试 1: 基础水库采样")
    data = range(1, 11)  # 1 到 10
    k = 3
    print(f"从 {list(data)} 中随机采样 {k} 个:")
    for i in range(3):
        sample = reservoir_sampling(data, k)
        print(f"  采样 {i+1}: {sample}")
    
    # 测试 2：大规模流采样
    print("\n测试 2: 大规模数据采样")
    large_stream = range(1000000)
    k = 10
    sample = reservoir_sampling(large_stream, k)
    print(f"从 100万 个数据中采样 {k} 个: {sorted(sample)}")
    
    # 测试 3：无放回采样
    print("\n测试 3: 无放回随机采样")
    population = ['A', 'B', 'C', 'D', 'E', 'F']
    k = 3
    print(f"从 {population} 中无放回采样 {k} 个:")
    for i in range(2):
        sample = random_sample_without_replacement(population, k)
        print(f"  采样 {i+1}: {sample}")
    
    # 测试 4：有放回采样
    print("\n测试 4: 有放回随机采样")
    population = [1, 2, 3, 4, 5]
    k = 5
    print(f"从 {population} 中有放回采样 {k} 个:")
    sample = random_sample_with_replacement(population, k)
    print(f"  采样结果: {sample}")
    
    # 测试 5：分层采样
    print("\n测试 5: 分层采样")
    # 模拟学生数据：(name, grade)
    students = [
        ('张三', 'A级'), ('李四', 'B级'), ('王五', 'A级'),
        ('赵六', 'C级'), ('孙七', 'B级'), ('周八', 'A级'),
        ('吴九', 'B级'), ('郑十', 'C级')
    ]
    
    # 按等级分层采样，每层采样 1-2 个
    samples = stratified_sampling(students, 3, lambda x: x[1])
    print(f"学生数据: {students}")
    print(f"分层采样结果: {samples}")
    
    # 测试 6：验证采样均匀性
    print("\n测试 6: 采样分布验证")
    data = range(5)
    counts = {i: 0 for i in range(5)}
    trials = 10000
    
    for _ in range(trials):
        sample = reservoir_sampling(data, 2)
        for item in sample:
            counts[item] += 1
    
    print(f"从 [0,1,2,3,4] 中采样 2 个，重复 {trials} 次:")
    expected = trials * 2 / 5
    for item, count in counts.items():
        print(f"  元素 {item}: {count} 次 (期望 {expected:.0f})")
    
    print("\n" + "=" * 50)
