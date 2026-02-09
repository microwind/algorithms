"""
实际应用：限流算法
"""

import time
from collections import deque

class TokenBucket:
    """令牌桶限流"""
    def __init__(self, capacity, refill_rate):
        self.capacity = capacity
        self.tokens = capacity
        self.refill_rate = refill_rate
        self.last_refill = time.time()
    
    def is_allowed(self):
        now = time.time()
        elapsed = now - self.last_refill
        self.tokens = min(self.capacity, self.tokens + elapsed * self.refill_rate)
        self.last_refill = now
        
        if self.tokens >= 1:
            self.tokens -= 1
            return True
        return False

class SlidingWindow:
    """滑动窗口限流"""
    def __init__(self, window_size, max_requests):
        self.window_size = window_size
        self.max_requests = max_requests
        self.requests = deque()
    
    def is_allowed(self):
        now = time.time()
        
        # 移除窗口外的请求
        while self.requests and self.requests[0] < now - self.window_size:
            self.requests.popleft()
        
        # 检查是否超出限制
        if len(self.requests) < self.max_requests:
            self.requests.append(now)
            return True
        return False

if __name__ == "__main__":
    print("=== 限流算法示例 ===\n")
    
    # 令牌桶
    bucket = TokenBucket(10, 2)
    for i in range(15):
        if bucket.is_allowed():
            print(f"请求 {i+1}: 允许")
        else:
            print(f"请求 {i+1}: 拒绝")
        time.sleep(0.1)
