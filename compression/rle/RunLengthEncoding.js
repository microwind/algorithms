/**
 * 游程编码(RLE)实现 - JavaScript
 * 核心：连续重复字符转为"字符+计数"
 */
class RunLengthEncoding {
    // 压缩：连续相同字符编码为字符+计数
    static compress(text) {
        if (!text) return text;
        
        let compressed = "";
        let currentChar = text[0];
        let count = 1;
        
        // 遍历统计连续字符
        for (let i = 1; i < text.length; i++) {
            if (text[i] === currentChar) {
                count++;  // 连续字符，计数+1
            } else {
                compressed += currentChar;
                if (count > 1) {
                    compressed += count;
                }
                currentChar = text[i];
                count = 1;
            }
        }
        
        // 处理最后一个字符
        compressed += currentChar;
        if (count > 1) {
            compressed += count;
        }
        
        return compressed;
    }
    
    // 解压：解析"字符+计数"还原字符串
    static decompress(compressed) {
        if (!compressed) return compressed;
        
        let decompressed = "";
        let i = 0;
        
        while (i < compressed.length) {
            const currentChar = compressed[i++];
            let countStr = "";
            
            // 解析连续数字（计数）
            while (i < compressed.length && /\d/.test(compressed[i])) {
                countStr += compressed[i++];
            }
            
            const count = countStr ? parseInt(countStr) : 1;
            
            // 重复字符count次
            decompressed += currentChar.repeat(count);
        }
        
        return decompressed;
    }
    
    static compressionRatio(original, compressed) {
        return compressed.length / original.length;
    }
}

// 示例使用
const text = "AAAABBBCCDAA";
console.log("原始文本:", text);

const compressed = RunLengthEncoding.compress(text);
console.log("压缩后:", compressed);

const decompressed = RunLengthEncoding.decompress(compressed);
console.log("解压后:", decompressed);

console.log("压缩比:", RunLengthEncoding.compressionRatio(text, compressed));
console.log("验证:", text === decompressed);
