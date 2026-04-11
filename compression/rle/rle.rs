/*
*
 * 游程编码 (RLE) - 简单的压缩算法
 *
 * 问题：将连续重复的字符压缩为字符+计数的形式
 *
 * 核心思想：
 * - 统计连续相同字符的数量
 * - 用字符+计数表示重复序列
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

/*
*
 * 压缩函数
*/
fn compress(text: &str) -> String {
    if text.is_empty() {
        return text.to_string();
    }

    let mut compressed = String::new();
    let chars: Vec<char> = text.chars().collect();
    let mut current_char = chars[0];
    let mut count = 1;

    for i in 1..chars.len() {
        if chars[i] == current_char {
            count += 1;
        } else {
            compressed.push(current_char);
            if count > 1 {
                compressed.push_str(&count.to_string());
            }
            current_char = chars[i];
            count = 1;
        }
    }

    // 处理最后一个字符
    compressed.push(current_char);
    if count > 1 {
        compressed.push_str(&count.to_string());
    }

    compressed
}

/*
*
 * 解压函数
*/
fn decompress(compressed: &str) -> String {
    if compressed.is_empty() {
        return compressed.to_string();
    }

    let mut decompressed = String::new();
    let chars: Vec<char> = compressed.chars().collect();
    let mut i = 0;

    while i < chars.len() {
        let current_char = chars[i];
        i += 1;
        let mut count_str = String::new();

        // 解析数字
        while i < chars.len() && chars[i].is_digit(10) {
            count_str.push(chars[i]);
            i += 1;
        }

        let count: usize = if count_str.is_empty() {
            1
        } else {
            count_str.parse().unwrap_or(1)
        };

        // 添加字符
        for _ in 0..count {
            decompressed.push(current_char);
        }
    }

    decompressed
}

/*
*
 * 计算压缩比
*/
fn compression_ratio(original: &str, compressed: &str) -> f64 {
    compressed.len() as f64 / original.len() as f64
}

/*
*
 * 主函数
*/
fn main() {
    let text = "AAAABBBCCDAA";
    println!("=== 游程编码 (RLE) ===");
    println!("原始文本: {}", text);

    let compressed = compress(text);
    println!("压缩后: {}", compressed);

    let decompressed = decompress(&compressed);
    println!("解压后: {}", decompressed);

    println!("压缩比: {:.2}", compression_ratio(text, &compressed));
    println!("验证: {}", text == decompressed);

    // 测试用例2
    println!("\n测试用例2:");
    let text2 = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB";
    let compressed2 = compress(text2);
    let decompressed2 = decompress(&compressed2);
    println!("原始文本: {}", text2);
    println!("压缩后: {}", compressed2);
    println!("解压后: {}", decompressed2);
    println!("验证: {}", text2 == decompressed2);
}
