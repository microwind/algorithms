# 贡献指南 Contributing Guide

感谢你对本项目的关注！我是 Jarry，来自中国的软件工程师。

Thank you for your interest in this project! We welcome all forms of contributions.

## 🎯 如何贡献 How to Contribute

### 1. 报告问题 Report Issues
- 发现 Bug？请创建 Issue
- 有改进建议？请创建 Issue
- 文档有误？请创建 Issue

### 2. 提交代码 Submit Code

#### 贡献新算法 Add New Algorithm
1. Fork 本仓库
2. 创建新分支：`git checkout -b feature/new-algorithm`
3. 按照标准结构添加算法
4. 确保代码通过测试
5. 提交 Pull Request

#### 标准算法结构
```
algorithm-name/
├── README.md                    # 算法说明（必需）
├── implementations/             # 实现代码（至少3种语言）
│   ├── c/
│   ├── java/
│   ├── python/
│   ├── javascript/
│   ├── go/
│   └── typescript/
├── examples/                    # 使用示例（推荐）
└── visuals/                     # 可视化图片（推荐）
```

### 3. 改进文档 Improve Documentation
- 修正拼写错误
- 改进说明文字
- 添加更多示例
- 翻译文档

### 4. 优化现有代码 Optimize Existing Code
- 性能优化
- 代码重构
- 添加注释
- 修复 Bug

## 📝 代码规范 Code Standards

### C 语言规范
```c
/**
 * 函数功能简述
 * @param arr 参数说明
 * @param n 参数说明
 * @return 返回值说明
 */
void bubble_sort(int arr[], int n) {
    // 代码实现
    // 添加详细注释
}
```

### Java 规范
```java
/**
 * 类功能简述
 */
public class BubbleSort {
    /**
     * 方法功能简述
     * @param arr 参数说明
     */
    public static void sort(int[] arr) {
        // 代码实现
        // 添加详细注释
    }
}
```

### Python 规范
```python
def bubble_sort(arr):
    """
    函数功能简述

    Args:
        arr: 参数说明

    Returns:
        返回值说明
    """
    # 代码实现
    # 添加详细注释
```

### JavaScript/TypeScript 规范
```javascript
/**
 * 函数功能简述
 * @param {Array} arr - 参数说明
 * @returns {Array} 返回值说明
 */
function bubbleSort(arr) {
    // 代码实现
    // 添加详细注释
}
```

### Go 规范
```go
// BubbleSort 函数功能简述
// arr: 参数说明
func BubbleSort(arr []int) {
    // 代码实现
    // 添加详细注释
}
```

## 🧪 测试要求 Testing Requirements

每个算法实现都应包含测试代码：

### C 测试示例
```c
// test.c
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, n);

    // 验证结果
    assert(arr[0] == 11);
    assert(arr[n-1] == 90);

    printf("Test passed!\n");
    return 0;
}
```

### Python 测试示例
```python
# test_algorithm.py
import unittest

class TestBubbleSort(unittest.TestCase):
    def test_basic(self):
        arr = [64, 34, 25, 12, 22, 11, 90]
        result = bubble_sort(arr)
        self.assertEqual(result, [11, 12, 22, 25, 34, 64, 90])

    def test_empty(self):
        arr = []
        result = bubble_sort(arr)
        self.assertEqual(result, [])

if __name__ == '__main__':
    unittest.main()
```

## 📚 文档要求 Documentation Requirements

### README.md 必需内容
1. **算法名称** - 中英文
2. **算法描述** - 用通俗语言解释
3. **算法原理** - 详细说明工作原理
4. **时间复杂度** - 最好/平均/最坏情况
5. **空间复杂度** - 分析内存使用
6. **代码示例** - 各语言实现链接
7. **应用场景** - 实际使用场景
8. **注意事项** - 常见问题和优化

### 示例 README 模板
```markdown
# 冒泡排序 Bubble Sort

## 简介
冒泡排序是一种简单的排序算法...

## 算法原理
通过重复遍历要排序的数列...

## 复杂度分析
- 时间复杂度：O(n²)
- 空间复杂度：O(1)

## 实现代码
- [C 语言实现](./c/bubble_sort.c)
- [Java 实现](./java/BubbleSort.java)
- [Python 实现](./python/bubble_sort.py)
...

## 使用示例
...

## 注意事项
...
```

## 🎨 命名规范 Naming Conventions

### 文件命名
- C: `algorithm_name.c`, `algorithm_name.h`
- Java: `AlgorithmName.java`
- Python: `algorithm_name.py`
- JavaScript: `algorithmName.js` 或 `algorithm-name.js`
- Go: `algorithm_name.go`
- TypeScript: `AlgorithmName.ts`

### 函数/方法命名
- C: `snake_case` - `bubble_sort()`
- Java: `camelCase` - `bubbleSort()`
- Python: `snake_case` - `bubble_sort()`
- JavaScript: `camelCase` - `bubbleSort()`
- Go: `PascalCase` - `BubbleSort()`
- TypeScript: `camelCase` - `bubbleSort()`

## ✅ 提交检查清单 Submission Checklist

提交 Pull Request 前，请确保：

- [ ] 代码遵循项目的编码规范
- [ ] 添加了充分的代码注释
- [ ] 包含了测试用例
- [ ] 测试全部通过
- [ ] 更新了相关文档
- [ ] README.md 包含了所有必需内容
- [ ] 提交信息清晰明确
- [ ] 代码没有编译警告或错误

## 🔍 Code Review 流程

1. 提交 Pull Request
2. 维护者会在 3-5 个工作日内审查
3. 根据反馈修改代码
4. 审查通过后合并

## 💬 交流方式 Communication

- GitHub Issues：报告问题、提出建议
- GitHub Discussions：技术讨论、使用咨询
- Email：jarryli@gmail.com

## 📜 行为准则 Code of Conduct

- 尊重所有贡献者
- 保持友好和专业
- 接受建设性批评
- 专注于对项目最有利的方面

## 🎓 学分 Credits

所有贡献者都将被列入项目的贡献者名单。

Thank you for contributing! 感谢你的贡献！

please concat jarryli@gmail.com or lichunping@buaa.edu.cn if you have any question.
