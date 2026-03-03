"""
实际应用：Hash签名验证
场景：文件完整性检验、数据校验、数字签名、内容去重

使用场景：
- 文件下载后完整性验证
- Git中内容的唯一标识
- 数据库中的去重存储
- CDN缓存密钥
- 内容寻址存储 (Content Addressable Storage)
"""

import hashlib
from collections import defaultdict
from datetime import datetime


class FileVerification:
    """文件完整性验证"""

    @staticmethod
    def calculate_file_hash(filepath, algorithm='sha256'):
        """计算文件Hash值，支持大文件"""
        hash_obj = hashlib.new(algorithm)
        with open(filepath, 'rb') as f:
            for chunk in iter(lambda: f.read(4096), b''):
                hash_obj.update(chunk)
        return hash_obj.hexdigest()

    @staticmethod
    def calculate_content_hash(content, algorithm='sha256'):
        """计算内容Hash值"""
        if isinstance(content, str):
            content = content.encode()
        return hashlib.new(algorithm, content).hexdigest()


class ContentDeduplication:
    """内容去重存储系统"""

    def __init__(self):
        # hash -> content 映射
        self.storage = {}
        # hash -> metadata 映射
        self.metadata = {}

    def add_content(self, content, filename=None):
        """添加内容，自动去重"""
        content_hash = hashlib.sha256(
            content.encode() if isinstance(content, str) else content
        ).hexdigest()

        if content_hash not in self.storage:
            # 首次存储此内容
            self.storage[content_hash] = content
            self.metadata[content_hash] = {
                'size': len(content),
                'added_date': datetime.now().isoformat(),
                'filenames': []
            }

        # 记录文件名
        if filename:
            if filename not in self.metadata[content_hash]['filenames']:
                self.metadata[content_hash]['filenames'].append(filename)

        return content_hash

    def get_content(self, content_hash):
        """根据Hash获取内容"""
        return self.storage.get(content_hash)

    def get_dedup_stats(self):
        """获取去重统计"""
        total_files = sum(
            len(meta['filenames'])
            for meta in self.metadata.values()
        )
        unique_content = len(self.storage)
        saved_space = sum(
            meta['size'] * (len(meta['filenames']) - 1)
            for meta in self.metadata.values()
        )
        return {
            'total_files': total_files,
            'unique_content': unique_content,
            'saved_space_bytes': saved_space,
            'compression_ratio': f"{(1 - unique_content/total_files if total_files > 0 else 0) * 100:.2f}%"
        }


class DataIntegrityValidator:
    """数据完整性验证器"""

    def __init__(self):
        self.checksums = {}

    def register_data(self, data_id, content):
        """注册数据及其Hash"""
        checksum = hashlib.sha256(
            content.encode() if isinstance(content, str) else content
        ).hexdigest()
        self.checksums[data_id] = checksum
        return checksum

    def verify_data(self, data_id, content):
        """验证数据是否被修改"""
        current_checksum = hashlib.sha256(
            content.encode() if isinstance(content, str) else content
        ).hexdigest()
        stored_checksum = self.checksums.get(data_id)

        if stored_checksum is None:
            return None, "数据未注册"

        if current_checksum == stored_checksum:
            return True, "数据完整"
        else:
            return False, "数据已被修改"


class GitLikeVersionControl:
    """类Git的内容寻址版本控制"""

    def __init__(self):
        self.objects = {}  # hash -> content
        self.refs = defaultdict(list)  # branch -> [commits]

    def add_object(self, content):
        """添加对象，返回其Hash"""
        obj_hash = hashlib.sha256(
            content.encode() if isinstance(content, str) else content
        ).hexdigest()[:12]  # 使用短Hash

        if obj_hash not in self.objects:
            self.objects[obj_hash] = content

        return obj_hash

    def create_commit(self, branch, message, content):
        """创建提交"""
        content_hash = self.add_object(content)
        commit_info = {
            'message': message,
            'content_hash': content_hash,
            'timestamp': datetime.now().isoformat()
        }
        self.refs[branch].append(commit_info)
        return content_hash

    def get_history(self, branch):
        """获取分支历史"""
        return self.refs.get(branch, [])


class DuplicateFileDetector:
    """重复文件检测"""

    def __init__(self):
        self.hash_to_files = defaultdict(list)

    def scan_files(self, file_list):
        """扫描文件列表，找出重复"""
        for filepath in file_list:
            try:
                with open(filepath, 'rb') as f:
                    file_hash = hashlib.sha256(f.read()).hexdigest()
                    self.hash_to_files[file_hash].append(filepath)
            except Exception as e:
                print(f"扫描失败 {filepath}: {e}")

    def get_duplicates(self):
        """获取所有重复文件"""
        return {
            hash_val: files
            for hash_val, files in self.hash_to_files.items()
            if len(files) > 1
        }

    def get_duplicate_stats(self):
        """获取重复统计"""
        duplicates = self.get_duplicates()
        return {
            'duplicate_groups': len(duplicates),
            'total_duplicate_files': sum(len(files) - 1 for files in duplicates.values()),
            'duplicate_details': duplicates
        }


if __name__ == "__main__":
    print("=== Hash签名验证实际应用 ===\n")

    # 1. 内容Hash计算
    print("--- 内容Hash计算 ---")
    content1 = "Hello, World!"
    content2 = "Hello, World!"
    content3 = "Hello, Python!"

    hash1 = FileVerification.calculate_content_hash(content1)
    hash2 = FileVerification.calculate_content_hash(content2)
    hash3 = FileVerification.calculate_content_hash(content3)

    print(f"内容1 Hash: {hash1[:16]}...")
    print(f"内容2 Hash: {hash2[:16]}...")
    print(f"内容1和2相同: {hash1 == hash2}")
    print(f"内容3 Hash: {hash3[:16]}...")
    print(f"内容1和3相同: {hash1 == hash3}\n")

    # 2. 内容去重存储
    print("--- 内容去重存储 ---")
    dedup = ContentDeduplication()
    dedup.add_content("Python is great", "file1.txt")
    dedup.add_content("Python is great", "file2.txt")  # 相同内容
    dedup.add_content("Java is also good", "file3.txt")

    stats = dedup.get_dedup_stats()
    print(f"总文件数: {stats['total_files']}")
    print(f"唯一内容数: {stats['unique_content']}")
    print(f"节省空间: {stats['saved_space_bytes']} 字节")
    print(f"压缩率: {stats['compression_ratio']}\n")

    # 3. 数据完整性验证
    print("--- 数据完整性验证 ---")
    validator = DataIntegrityValidator()
    original_data = "Important database record"
    data_id = "record_001"

    validator.register_data(data_id, original_data)
    print(f"数据已注册: {data_id}")

    # 验证未修改的数据
    is_valid, msg = validator.verify_data(data_id, original_data)
    print(f"验证结果: {is_valid} - {msg}")

    # 验证被修改的数据
    modified_data = "Important database record (modified)"
    is_valid, msg = validator.verify_data(data_id, modified_data)
    print(f"修改后验证: {is_valid} - {msg}\n")

    # 4. Git式版本控制
    print("--- Git式版本控制 ---")
    git = GitLikeVersionControl()
    git.create_commit("main", "Initial commit", "print('Hello')")
    git.create_commit("main", "Add feature", "print('Hello with feature')")

    history = git.get_history("main")
    print(f"提交历史:")
    for i, commit in enumerate(history, 1):
        print(f"  提交{i}: {commit['message']}")
        print(f"    内容Hash: {commit['content_hash']}")
