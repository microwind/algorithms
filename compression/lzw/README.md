# LZW压缩算法完整教学资源

## 概述

LZW (Lempel-Ziv-Welch) 是一种无损数据压缩算法，由 Abraham Lempel、Jacob Ziv 和 Terry Welch 发明。它通过动态构建字典来压缩数据，广泛应用于 GIF 图像压缩和 Unix 的 compress 命令中。

### LZW 的三个关键要素

LZW 算法包含：
1. **动态字典**：在压缩过程中动态构建编码字典
2. **字符串匹配**：查找输入数据中的最长匹配字符串
3. **字典更新**：将新发现的字符串加入字典

## 目录结构

```
lzw/
├── lzw.c              # C 语言实现
├── LZW.java           # Java 语言实现
├── lzw.go             # Go 语言实现
├── lzw.py             # Python 语言实现
├── lzw.js             # JavaScript 语言实现
├── lzw.rs             # Rust 语言实现
├── LZW.ts             # TypeScript 语言实现
└── README.md          # 本文档
```

## 核心思想

### 压缩过程

1. 初始化字典，包含所有单字符（ASCII 0-255）
2. 读取输入字符串，查找当前字典中的最长匹配
3. 输出匹配字符串的字典索引
4. 将匹配字符串 + 下一个字符作为新条目加入字典
5. 重复直到输入结束

### 解压过程

1. 初始化字典，包含所有单字符
2. 读取编码索引，输出对应字符串
3. 将前一个输出字符串 + 当前输出字符串的首字符加入字典
4. 重复直到编码结束

### 核心特点

- 自适应字典：字典在压缩过程中动态构建
- 无损压缩：解压后可以完全恢复原始数据
- 字典同步：解压端可以重建相同的字典

## 复杂度分析

- **时间复杂度**: O(n)，其中 n 是输入长度
- **空间复杂度**: O(n)，用于存储字典
- **字典大小**: 通常限制为 4096 或 8192 个条目

## 应用场景

- GIF 图像压缩
- 文本文件压缩
- 数据传输压缩
- 归档工具

## 简单例子

### Python 示例
```python
def lzw_compress(text):
    """LZW压缩"""
    dictionary = {chr(i): i for i in range(256)}
    next_code = 256
    compressed = []
    current_string = ""
    
    for char in text:
        combined = current_string + char
        if combined in dictionary:
            current_string = combined
        else:
            compressed.append(dictionary[current_string])
            dictionary[combined] = next_code
            next_code += 1
            current_string = char
    
    if current_string:
        compressed.append(dictionary[current_string])
    
    return compressed

def lzw_decompress(compressed):
    """LZW解压"""
    dictionary = {i: chr(i) for i in range(256)}
    next_code = 256
    decompressed = ""
    previous_string = ""
    
    for code in compressed:
        if code in dictionary:
            current_string = dictionary[code]
        elif code == next_code:
            current_string = previous_string + previous_string[0]
        else:
            raise ValueError("Invalid compressed data")
        
        decompressed += current_string
        
        if previous_string:
            dictionary[next_code] = previous_string + current_string[0]
            next_code += 1
        
        previous_string = current_string
    
    return decompressed

# 示例使用
text = "TOBEORNOTTOBEORTOBEORNOT"
compressed = lzw_compress(text)
print(f"压缩后: {compressed}")

decompressed = lzw_decompress(compressed)
print(f"解压后: {decompressed}")
print(f"验证: {text == decompressed}")
```

### Java 示例
```java
import java.util.*;

public class LZW {
    
    public static List<Integer> compress(String text) {
        Map<String, Integer> dictionary = new HashMap<>();
        for (int i = 0; i < 256; i++) {
            dictionary.put(String.valueOf((char) i), i);
        }
        
        int nextCode = 256;
        List<Integer> compressed = new ArrayList<>();
        String currentString = "";
        
        for (char c : text.toCharArray()) {
            String combined = currentString + c;
            if (dictionary.containsKey(combined)) {
                currentString = combined;
            } else {
                compressed.add(dictionary.get(currentString));
                dictionary.put(combined, nextCode++);
                currentString = String.valueOf(c);
            }
        }
        
        if (!currentString.isEmpty()) {
            compressed.add(dictionary.get(currentString));
        }
        
        return compressed;
    }
    
    public static String decompress(List<Integer> compressed) {
        Map<Integer, String> dictionary = new HashMap<>();
        for (int i = 0; i < 256; i++) {
            dictionary.put(i, String.valueOf((char) i));
        }
        
        int nextCode = 256;
        StringBuilder decompressed = new StringBuilder();
        String previousString = "";
        
        for (int code : compressed) {
            String currentString;
            if (dictionary.containsKey(code)) {
                currentString = dictionary.get(code);
            } else if (code == nextCode) {
                currentString = previousString + previousString.charAt(0);
            } else {
                throw new IllegalArgumentException("Invalid compressed data");
            }
            
            decompressed.append(currentString);
            
            if (!previousString.isEmpty()) {
                dictionary.put(nextCode++, previousString + currentString.charAt(0));
            }
            
            previousString = currentString;
        }
        
        return decompressed.toString();
    }
    
    public static void main(String[] args) {
        String text = "TOBEORNOTTOBEORTOBEORNOT";
        System.out.println("原始文本: " + text);
        
        List<Integer> compressed = compress(text);
        System.out.println("压缩后: " + compressed);
        
        String decompressed = decompress(compressed);
        System.out.println("解压后: " + decompressed);
        
        System.out.println("验证: " + text.equals(decompressed));
    }
}
```

## 特点

### 优点
- 自适应性强：根据输入数据自动构建字典
- 压缩效果好：对于有重复模式的数据压缩率高
- 解压简单：解压端可以重建相同的字典
- 无损压缩：完全恢复原始数据

### 缺点
- 字典大小限制：需要限制字典大小避免内存溢出
- 随机数据效果差：对于随机数据压缩效果不佳
- 专利问题：早期版本有专利限制（已过期）

## 变体与优化

### 固定字典大小
- 当字典达到最大大小时，停止添加新条目
- 简单实现，但可能影响压缩率

### 可变字典大小
- 动态调整字典大小
- 根据压缩效果优化

### 自适应字典
- 定期清理不常用的字典条目
- 适应数据模式变化

## 学习建议

1. 理解字典构建过程：掌握动态字典的构建方法
2. 熟悉编码解码：理解编码和解码的对称性
3. 练习边界条件：处理字典满、特殊字符等情况
4. 分析压缩效果：了解不同类型数据的压缩率
5. 实际应用：了解 LZW 在 GIF 等格式中的应用
