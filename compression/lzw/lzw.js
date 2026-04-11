/*
*
 * LZW压缩算法 - 字典压缩
 *
 * 问题：使用动态字典进行无损数据压缩
 *
 * 核心思想：
 * - 动态构建编码字典
 * - 查找最长匹配字符串
 * - 输出字典索引
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

const MAX_DICT_SIZE = 4096;

function lzwCompress(input) {
    const dictionary = {};
    for (let i = 0; i < 256; i++) {
        dictionary[String.fromCharCode(i)] = i;
    }
    const compressed = [];
    let current = "";
    let dictSize = 256;
    for (let i = 0; i < input.length; i++) {
        const char = input[i];
        const combined = current + char;
        if (combined in dictionary) {
            current = combined;
        } else {
            compressed.push(dictionary[current]);
            if (dictSize < MAX_DICT_SIZE) {
                dictionary[combined] = dictSize++;
            }
            current = char;
        }
    }
    if (current !== "") {
        compressed.push(dictionary[current]);
    }
    return compressed;
}

function lzwDecompress(compressed) {
    const dictionary = {};
    for (let i = 0; i < 256; i++) {
        dictionary[i] = String.fromCharCode(i);
    }
    let output = "";
    let oldCode = compressed[0];
    let oldString = dictionary[oldCode];
    output += oldString;
    let dictSize = 256;
    for (let i = 1; i < compressed.length; i++) {
        const newCode = compressed[i];
        let stringVal;
        if (!(newCode in dictionary)) {
            stringVal = oldString + oldString[0];
        } else {
            stringVal = dictionary[newCode];
        }
        output += stringVal;
        if (dictSize < MAX_DICT_SIZE) {
            dictionary[dictSize++] = oldString + stringVal[0];
        }
        oldString = stringVal;
    }
    return output;
}

function main() {
    const input = "TOBEORNOTTOBEORTOBEORNOT";
    console.log("=== LZW压缩算法 ===");
    console.log("原始文本: " + input);
    const compressed = lzwCompress(input);
    console.log("压缩后编码: " + compressed);
    const decompressed = lzwDecompress(compressed);
    console.log("解压后文本: " + decompressed);
    console.log("验证: " + (input === decompressed));
}

main();
