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

use std::collections::HashMap;

const MAX_DICT_SIZE: usize = 4096;

fn lzw_compress(input: &str) -> Vec<usize> {
    let mut dictionary: HashMap<String, usize> = HashMap::new();

    // 初始化字典（单字符）
    for i in 0..256 {
        dictionary.insert((i as u8 as char).to_string(), i);
    }

    let mut compressed = Vec::new();
    let mut current = String::new();
    let mut dict_size = 256;

    for char in input.chars() {
        let combined = format!("{}{}", current, char);

        if dictionary.contains_key(&combined) {
            current = combined;
        } else {
            // 输出current的编码
            compressed.push(dictionary[&current]);

            // 将combined加入字典
            if dict_size < MAX_DICT_SIZE {
                dictionary.insert(combined, dict_size);
                dict_size += 1;
            }

            // 重置current为char
            current = char.to_string();
        }
    }

    // 输出最后一个编码
    if !current.is_empty() {
        compressed.push(dictionary[&current]);
    }

    compressed
}

fn lzw_decompress(compressed: &[usize]) -> String {
    let mut dictionary: HashMap<usize, String> = HashMap::new();

    // 初始化字典（单字符）
    for i in 0..256 {
        dictionary.insert(i, (i as u8 as char).to_string());
    }

    let mut output = String::new();
    let old_code = compressed[0];
    let old_string = dictionary[&old_code].clone();
    output.push_str(&old_string);

    let mut dict_size = 256;

    for &new_code in &compressed[1..] {
        let string_val = if !dictionary.contains_key(&new_code) {
            // 特殊情况：new_code不在字典中
            format!("{}{}", old_string, old_string.chars().next().unwrap())
        } else {
            dictionary[&new_code].clone()
        };

        output.push_str(&string_val);

        // 将old_string + string[0]加入字典
        if dict_size < MAX_DICT_SIZE {
            let new_entry = format!("{}{}", old_string, string_val.chars().next().unwrap());
            dictionary.insert(dict_size, new_entry);
            dict_size += 1;
        }

        old_string = string_val;
    }

    output
}

fn main() {
    let input = "TOBEORNOTTOBEORTOBEORNOT";
    println!("=== LZW压缩算法 ===");
    println!("原始文本: {}", input);

    let compressed = lzw_compress(input);
    println!("压缩后编码: {:?}", compressed);

    let decompressed = lzw_decompress(&compressed);
    println!("解压后文本: {}", decompressed);

    println!("验证: {}", input == decompressed);
}
