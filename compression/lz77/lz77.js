/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class Token {
    /**
     * LZ77压缩令牌构造函数
     * @param {number} offset 偏移量
     * @param {number} length 匹配长度
     * @param {string} character 下一个字符
     */
    constructor(offset = 0, length = 0, character = null) {
        this.offset = offset;
        this.length = length;
        this.character = character;
    }
    
    toString() {
        if (this.length > 0) {
            return `(${this.offset},${this.length})`;
        } else {
            return `(${this.character})`;
        }
    }
}

/**
 * LZ77压缩算法
 * @param {string} input 输入字符串
 * @return {Array<Token>} 压缩后的令牌列表
 */
function lz77Compress(input) {
    console.log("LZ77压缩开始...");
    const tokens = [];
    const windowSize = 256;
    let position = 0;
    
    while (position < input.length) {
        const maxLength = Math.min(windowSize, position);
        const window = input.substring(position - maxLength, position);
            
        let bestLength = 0;
        let bestOffset = 0;
        
        // 在窗口中搜索最长匹配
        for (let i = 0; i < window.length; i++) {
            let matchLength = 0;
            while (position + matchLength < input.length &&
                   i + matchLength < window.length &&
                   input[position + matchLength] === window[i + matchLength]) {
                matchLength++;
            }
            
            if (matchLength > bestLength) {
                bestLength = matchLength;
                bestOffset = window.length - i;
            }
        }
        
        if (bestLength >= 3) { // 最小匹配长度
            const nextChar = position + bestLength < input.length ? 
                              input[position + bestLength] : null;
            tokens.push(new Token(bestOffset, bestLength, nextChar));
            console.log(`找到匹配: 偏移=${bestOffset}, 长度=${bestLength}`);
            position += bestLength + 1;
        } else {
            tokens.push(new Token(0, 0, input[position]));
            console.log(`字面量: ${input[position]}`);
            position++;
        }
    }
    
    console.log(`LZ77压缩完成，令牌数: ${tokens.length}`);
    return tokens;
}

/**
 * LZ77解压算法
 * @param {Array<Token>} tokens 压缩令牌列表
 * @return {string} 解压后的字符串
 */
function lz77Decompress(tokens) {
    console.log("LZ77解压开始...");
    let output = '';
    
    for (let i = 0; i < tokens.length; i++) {
        const token = tokens[i];
        console.log(`处理令牌 ${i}: ${token}`);
        
        if (token.length > 0) {
            const start = output.length - token.offset;
            for (let j = 0; j < token.length; j++) {
                output += output[start + j];
            }
            if (token.character !== null) {
                output += token.character;
            }
        } else {
            output += token.character;
        }
    }
    
    console.log(`LZ77解压完成，长度: ${output.length}`);
    return output;
}

/**
 * 计算压缩比
 * @param {string} original 原始字符串
 * @param {Array<Token>} compressed 压缩令牌列表
 * @return {number} 压缩比
 */
function compressionRatio(original, compressed) {
    const originalSize = original.length * 8; // 假设每个字符8位
    let compressedSize = 0;
    for (const token of compressed) {
        compressedSize += 16; // 偏移和长度各8位
        if (token.length > 0) compressedSize += 8; // 字符8位
    }
    return compressedSize / originalSize;
}

/**
 * 主函数，演示LZ77压缩和解压
 */
function main() {
    const input = "ABABABABABAABABABABA";
    console.log("=== LZ77算法演示 ===");
    console.log(`原始文本: ${input}`);
    console.log(`原始长度: ${input.length}`);
    
    // 压缩
    const compressed = lz77Compress(input);
    console.log(`压缩结果: ${compressed}`);
    
    // 计算压缩比
    const ratio = compressionRatio(input, compressed);
    console.log(`压缩比: ${ratio.toFixed(2)}`);
    
    // 解压
    const decompressed = lz77Decompress(compressed);
    console.log(`解压结果: ${decompressed}`);
    console.log(`解压长度: ${decompressed.length}`);
    
    // 验证
    const isValid = input === decompressed;
    console.log(`验证结果: ${isValid ? '✓ 成功' : '✗ 失败'}`);
    console.log("=== 演示结束 ===");
}

// 执行主函数
main();
