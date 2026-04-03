class RunLengthEncoding {
    static compress(text: string): string {
        if (!text) return text;
        
        let compressed = "";
        let currentChar = text[0];
        let count = 1;
        
        for (let i = 1; i < text.length; i++) {
            if (text[i] === currentChar) {
                count++;
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
    
    static decompress(compressed: string): string {
        if (!compressed) return compressed;
        
        let decompressed = "";
        let i = 0;
        
        while (i < compressed.length) {
            const currentChar = compressed[i++];
            let countStr = "";
            
            // 解析数字
            while (i < compressed.length && /\d/.test(compressed[i])) {
                countStr += compressed[i++];
            }
            
            const count = countStr ? parseInt(countStr) : 1;
            
            // 添加字符
            decompressed += currentChar.repeat(count);
        }
        
        return decompressed;
    }
    
    static compressionRatio(original: string, compressed: string): number {
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
