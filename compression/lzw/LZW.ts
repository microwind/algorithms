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

/*
*
 * LZW压缩
*/
function lzwCompress(input: string): number[] {
    const dictionary: { [key: string]: number } = {};

    // 初始化字典（单字符）
    for (let i = 0; i < 256; i++) {
        dictionary[String.fromCharCode(i)] = i;
    }

    const compressed: number[] = [];
    let current = "";
    let dictSize = 256;

    for (let i = 0; i < input.length; i++) {
        const char = input[i];
        const combined = current + char;

        if (combined in dictionary) {
            current = combined;
        } else {
            // 输出current的编码
            compressed.push(dictionary[current]);

            // 将combined加入字典
            if (dictSize < MAX_DICT_SIZE) {
                dictionary[combined] = dictSize++;
            }

            // 重置current为char
            current = char;
        }
    }

    // 输出最后一个编码
    if (current !== "") {
        compressed.push(dictionary[current]);
    }

    return compressed;
}

/*
*
 * LZW解压
*/
function lzwDecompress(compressed: number[]): string {
    const dictionary: { [key: number]: string } = {};

    // 初始化字典（单字符）
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
        let stringVal: string;

        if (!(newCode in dictionary)) {
            // 特殊情况：new_code不在字典中
            stringVal = oldString + oldString[0];
        } else {
            stringVal = dictionary[newCode];
        }

        output += stringVal;

        // 将old_string + string[0]加入字典
        if (dictSize < MAX_DICT_SIZE) {
            dictionary[dictSize++] = oldString + stringVal[0];
        }

        oldString = stringVal;
    }

    return output;
}

/*
*
 * 主函数
*/
function main(): void {
    const input = "TOBEORNOTTOBEORTOBEORNOT";
    console.log("=== LZW压缩算法 ===");
    console.log(`原始文本: ${input}`);

    const compressed = lzwCompress(input);
    console.log(`压缩后编码: ${compressed}`);

    const decompressed = lzwDecompress(compressed);
    console.log(`解压后文本: ${decompressed}`);

    console.log(`验证: ${input === decompressed}`);
}

// 运行测试
main();
