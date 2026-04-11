/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/*
*
 * LZ77压缩算法 - 滑动窗口压缩
 *
 * 问题：使用滑动窗口技术进行无损数据压缩
 *
 * 核心思想：
 * - 维护一个滑动窗口
 * - 在窗口中查找最长匹配
 * - 使用(偏移, 长度, 下一个字符)三元组表示
 *
 * 时间复杂度: O(n * m) 其中n是输入长度，m是窗口大小
 * 空间复杂度: O(n)
*/

/*
*
 * LZ77令牌结构
*/
interface Token {
    offset: number;
    length: number;
    character: string;
}

/*
*
 * 创建LZ77令牌
*/
function createToken(offset: number, length: number, character: string): Token {
    return { offset, length, character };
}

/*
*
 * LZ77压缩算法
*/
function lz77Compress(input: string): { tokens: Token[], tokenCount: number } {
    console.log("LZ77压缩开始...");
    const windowSize = 256;
    let position = 0;
    const inputLength = input.length;

    const tokens: Token[] = [];

    while (position < inputLength) {
        const maxLength = windowSize < position ? windowSize : position;
        let windowStart = position - maxLength;
        if (windowStart < 0) windowStart = 0;

        let bestLength = 0;
        let bestOffset = 0;

        // 在窗口中搜索最长匹配
        for (let i = 0; i < maxLength; i++) {
            let matchLength = 0;
            while (
                position + matchLength < inputLength &&
                i + matchLength < maxLength &&
                input[position + matchLength] === input[windowStart + i + matchLength]
            ) {
                matchLength++;
            }

            if (matchLength > bestLength) {
                bestLength = matchLength;
                bestOffset = maxLength - i;
            }
        }

        if (bestLength >= 3) { // 最小匹配长度
            const nextChar = position + bestLength < inputLength ?
                           input[position + bestLength] : '\0';
            tokens.push(createToken(bestOffset, bestLength, nextChar));
            console.log(`找到匹配: 偏移=${bestOffset}, 长度=${bestLength}`);
            position += bestLength + 1;
        } else {
            tokens.push(createToken(0, 0, input[position]));
            console.log(`字面量: ${input[position]}`);
            position++;
        }
    }

    console.log(`LZ77压缩完成，令牌数: ${tokens.length}`);
    return { tokens, tokenCount: tokens.length };
}

/*
*
 * LZ77解压算法
*/
function lz77Decompress(tokens: Token[]): { output: string, outputLength: number } {
    console.log("LZ77解压开始...");
    let output = "";

    for (let i = 0; i < tokens.length; i++) {
        const token = tokens[i];
        console.log(`处理令牌 ${i}: 偏移=${token.offset}, 长度=${token.length}, 字符=${token.character}`);

        if (token.length > 0) {
            const start = output.length - token.offset;
            for (let j = 0; j < token.length; j++) {
                output += output[start + j];
            }
            if (token.character !== '\0') {
                output += token.character;
            }
        } else {
            output += token.character;
        }
    }

    console.log(`LZ77解压完成，长度: ${output.length}`);
    return { output, outputLength: output.length };
}

/*
*
 * 计算压缩比
*/
function compressionRatio(original: string, compressed: Token[]): number {
    const originalSize = original.length * 8; // 假设每个字符8位
    let compressedSize = 0;
    for (const token of compressed) {
        compressedSize += 16; // 偏移和长度各8位
        if (token.length > 0) compressedSize += 8; // 字符8位
    }
    return compressedSize / originalSize;
}

/*
*
 * 打印令牌
*/
function printTokens(tokens: Token[]): void {
    console.log("压缩结果: ");
    for (const token of tokens) {
        if (token.length > 0) {
            console.log(`(${token.offset},${token.length})`);
        } else {
            console.log(`(${token.character})`);
        }
    }
}

/*
*
 * 主函数，演示LZ77压缩和解压
*/
function main(): void {
    const input = "ABABABABABAABABABABA";
    console.log("=== LZ77算法演示 ===");
    console.log(`原始文本: ${input}`);
    console.log(`原始长度: ${input.length}`);

    // 压缩
    const { tokens } = lz77Compress(input);
    printTokens(tokens);

    // 计算压缩比
    const ratio = compressionRatio(input, tokens);
    console.log(`压缩比: ${ratio.toFixed(2)}`);

    // 解压
    const { output } = lz77Decompress(tokens);
    console.log(`解压结果: ${output}`);
    console.log(`解压长度: ${output.length}`);

    // 验证
    const isValid = input === output;
    console.log(`验证结果: ${isValid ? '✓ 成功' : '✗ 失败'}`);
    console.log("=== 演示结束 ===");
}

// 运行测试
main();
