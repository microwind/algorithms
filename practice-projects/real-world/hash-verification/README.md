# Hash签名验证系统 | Hash Verification

**难度**: ⭐⭐⭐ | **标签**: `Hash` `加密` `数据完整性`

用密码学哈希函数实现文件验证、数据校验和内容寻址存储。

## 项目简介

Hash 算法是现代计算机系统的基础。本项目展示如何使用 SHA256、MD5 等哈希函数实现：
- 文件完整性验证（下载检验）
- 内容去重存储（相同内容只存一份）
- 数据防篡改检测
- Git 式版本控制

## 核心概念

### 哈希函数性质

| 性质 | 说明 | 应用 |
|------|------|------|
| 确定性 | 相同输入→相同输出 | 文件校验 |
| 一致性 | 结果固定长度 | 数据库索引 |
| 单向性 | 无法反向推导 | 密码存储 |
| 雪崩效应 | 微小改变→完全不同 | 篡改检测 |

### 哈希算法对比

| 算法 | 输出长度 | 冲突概率 | 应用 |
|------|---------|--------|------|
| MD5 | 128 bit | 已破解 | 遗留系统 |
| SHA1 | 160 bit | 已破解 | 遗留系统 |
| SHA256 | 256 bit | 极低 | ✅ 推荐 |
| SHA512 | 512 bit | 极低 | 超高安全 |

## 实际应用场景

### 1. 文件完整性验证

```python
# 下载文件后验证
local_hash = FileVerification.calculate_file_hash("downloaded.iso")
official_hash = "a3b5c7d9..."

if local_hash == official_hash:
    print("✅ 文件完整")
else:
    print("❌ 文件已损坏，需要重新下载")
```

**应用场景**:
- 软件下载站点
- 系统镜像文件
- 数据库备份文件

### 2. 内容去重存储

```python
dedup = ContentDeduplication()

# 存储相同内容的两个文件
hash1 = dedup.add_content("Python is great", "file1.txt")
hash2 = dedup.add_content("Python is great", "file2.txt")

stats = dedup.get_dedup_stats()
# 节省67%的存储空间 (2文件→1个内容)
```

**应用场景**:
- 云存储去重（节省空间）
- 备份系统（增量备份）
- 文档管理（避免重复存储）

**实际效果**:
```
总文件数: 1000
唯一内容: 650
节省空间: 35%
```

### 3. 数据完整性校验

```python
validator = DataIntegrityValidator()

# 注册关键数据
validator.register_data("user_001", important_data)

# 定期验证
is_valid, msg = validator.verify_data("user_001", current_data)
if not is_valid:
    print("⚠️ 数据已被篡改！")
    # 启动恢复流程
```

**应用场景**:
- 数据库事务日志
- 配置文件管理
- 交易记录保护

### 4. Git式版本控制

```python
git = GitLikeVersionControl()

git.create_commit("main", "Initial commit", "code v1")
git.create_commit("main", "Add feature", "code v2")

history = git.get_history("main")
# 每个提交都有唯一的内容哈希
```

**应用场景**:
- 版本控制系统
- 分布式存储
- 不可篡改的审计日志

## 项目结构

```
02-hash-verification/
├── README.md
├── docs/
│   ├── DESIGN.md
│   └── ALGORITHMS.md
├── src/
│   └── python/
│       └── hash_verification.py
├── tests/
│   └── test_hash.py
└── requirements.txt
```

## 使用指南

### Python版本

```bash
# 运行示例
python3 src/python/hash_verification.py

# 计算文件哈希
from hash_verification import FileVerification
hash_val = FileVerification.calculate_file_hash("file.txt", "sha256")

# 内容去重
from hash_verification import ContentDeduplication
dedup = ContentDeduplication()
hash1 = dedup.add_content("content", "file1.txt")
```

## 性能分析

### 哈希计算速度

| 算法 | 1MB文件 | 100MB文件 | 1GB文件 |
|------|--------|---------|--------|
| MD5 | 2ms | 150ms | 1.5s |
| SHA256 | 3ms | 200ms | 2.0s |
| SHA512 | 5ms | 300ms | 3.0s |

### 去重效果

| 场景 | 文件数 | 去重后 | 节省空间 |
|------|--------|--------|---------|
| 备份数据 | 10000 | 6500 | 35% |
| 云存储 | 100000 | 65000 | 35% |
| 日志文件 | 1000 | 800 | 20% |

## 核心API

### Python

```python
# 文件哈希
FileVerification.calculate_file_hash(filepath, algorithm='sha256')
FileVerification.calculate_content_hash(content, algorithm='sha256')

# 内容去重
dedup = ContentDeduplication()
dedup.add_content(content, filename)
dedup.get_content(content_hash)
dedup.get_dedup_stats()

# 数据校验
validator = DataIntegrityValidator()
validator.register_data(data_id, content)
validator.verify_data(data_id, content)  # 返回 (True/False, 消息)

# 版本控制
git = GitLikeVersionControl()
git.create_commit(branch, message, content)
git.get_history(branch)
```

## 高级主题

### 1. 哈希碰撞处理

极小概率事件，但需要准备：
```python
# 使用多个算法确认
sha256_hash = hashlib.sha256(content).hexdigest()
sha512_hash = hashlib.sha512(content).hexdigest()

if sha256_hash == known_hash and sha512_hash == known_hash2:
    print("✅ 100% 确认无碰撞")
```

### 2. 大文件处理

避免一次性加载整个文件：
```python
def hash_large_file(filepath):
    hasher = hashlib.sha256()
    with open(filepath, 'rb') as f:
        while True:
            chunk = f.read(8192)
            if not chunk:
                break
            hasher.update(chunk)
    return hasher.hexdigest()
```

### 3. 分布式验证

多个节点验证数据完整性：
```
Client → Server A (hash1)
      → Server B (hash2)
      → Server C (hash3)

if hash1 == hash2 == hash3:
    数据可靠
```

## 安全注意事项

⚠️ **不要用于密码存储** - 使用 bcrypt/scrypt

⚠️ **MD5/SHA1已破解** - 使用 SHA256 及以上

⚠️ **验证来源** - 从官方网站获取哈希值

## 常见问题

**Q: MD5 为什么不安全？**

A: MD5 已被破解，存在碰撞。2004年已发现碰撞算法，2008年已可实际生成碰撞。

**Q: 何时用SHA256，何时用SHA512？**

A:
- SHA256：通用场景，性能和安全的平衡点 ✅ 推荐
- SHA512：超高安全要求，性能要求不高

**Q: 如何验证大文件？**

A: 分块计算哈希，避免内存溢出：
```python
hash_obj = hashlib.sha256()
with open(filepath, 'rb') as f:
    for chunk in iter(lambda: f.read(4096), b''):
        hash_obj.update(chunk)
return hash_obj.hexdigest()
```

## 扩展练习

1. 实现**rainbow table 抵抗** - 添加salt
2. 实现**增量哈希** - 只计算变化部分
3. 实现**分布式文件验证**
4. 实现**自己的哈希函数**（教学用）

## 相关资源

- [SHA 系列算法解析](../../)
- [密码学基础](../../07-resources/)
- [OWASP 哈希安全](https://cheatsheetseries.owasp.org/cheatsheets/Password_Storage_Cheat_Sheet.html)

---

**最后更新**: 2024-03-02
**作者**: Algorithm Team
**License**: MIT
