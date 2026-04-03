/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::fmt;

#[derive(Debug, Clone, Copy)]
struct Token {
    offset: usize,
    length: usize,
    character: Option<char>,
}

impl Token {
    /**
     * 创建LZ77令牌
     * @param offset 偏移量
     * @param length 匹配长度
     * @param character 下一个字符
     */
    fn new(offset: usize, length: usize, character: Option<char>) -> Self {
        Token { offset, length, character }
    }
    
    fn literal(c: char) -> Self {
        Token { offset: 0, length: 0, character: Some(c) }
    }
    
    fn is_literal(&self) -> bool {
        self.length == 0
    }
}

/**
 * LZ77压缩算法
 * @param input_str 输入字符串
 * @return 压缩后的令牌向量
 */
fn lz77_compress(input_str: &str) -> Vec<Token> {
    println!("LZ77压缩开始...");
    let mut tokens = Vec::new();
    let window_size = 256;
    let mut position = 0;
    
    while position < input_str.len() {
        let max_length = window_size.min(position);
        let window = &input_str[position - max_length..position];
        
        let mut best_length = 0;
        let mut best_offset = 0;
        
        // 在窗口中搜索最长匹配
        for (i, _) in window.char_indices() {
            let mut match_length = 0;
            while position + match_length < input_str.len() &&
                  i + match_length < window.len() &&
                  input_str.chars().nth(position + match_length) == window.chars().nth(i + match_length) {
                match_length += 1;
            }
            
            if match_length > best_length {
                best_length = match_length;
                best_offset = window.len() - i;
            }
        }
        
        if best_length >= 3 { // 最小匹配长度
            let next_char = if position + best_length < input_str.len() {
                input_str.chars().nth(position + best_length)
            } else {
                None
            };
            
            tokens.push(Token::new(best_offset, best_length, next_char));
            println!("找到匹配: 偏移={}, 长度={}", best_offset, best_length);
            position += best_length + 1;
        } else {
            tokens.push(Token::literal(input_str.chars().nth(position).unwrap()));
            println!("字面量: {}", input_str.chars().nth(position).unwrap());
            position += 1;
        }
    }
    
    println!("LZ77压缩完成，令牌数: {}", tokens.len());
    tokens
}

/**
 * LZ77解压算法
 * @param tokens 压缩令牌向量
 * @return 解压后的字符串
 */
fn lz77_decompress(tokens: &[Token]) -> String {
    println!("LZ77解压开始...");
    let mut output = String::new();
    
    for (i, token) in tokens.iter().enumerate() {
        println!("处理令牌 {}: {:?}", i, token);
        
        if token.is_literal() {
            output.push(token.character.unwrap());
        } else {
            let start = output.len() - token.offset;
            for j in 0..token.length {
                output.push(output.chars().nth(start + j).unwrap());
            }
            if let Some(c) = token.character {
                output.push(c);
            }
        }
    }
    
    println!("LZ77解压完成，长度: {}", output.len());
    output
}

/**
 * 计算压缩比
 * @param original 原始字符串
 * @param compressed 压缩令牌向量
 * @return 压缩比
 */
fn compression_ratio(original: &str, compressed: &[Token]) -> f64 {
    let original_size = original.len() * 8; // 假设每个字符8位
    let mut compressed_size = 0;
    for token in compressed {
        compressed_size += 16; // 偏移和长度各8位
        if token.length > 0 {
            compressed_size += 8; // 字符8位
        }
    }
    compressed_size as f64 / original_size as f64
}

/**
 * 主函数，演示LZ77压缩和解压
 */
fn main() {
    let input = "ABABABABABAABABABABA";
    println!("=== LZ77算法演示 ===");
    println!("原始文本: {}", input);
    println!("原始长度: {}", input.len());
    
    // 压缩
    let compressed = lz77_compress(input);
    println!("压缩结果: {:?}", compressed);
    
    // 计算压缩比
    let ratio = compression_ratio(input, &compressed);
    println!("压缩比: {:.2}", ratio);
    
    // 解压
    let decompressed = lz77_decompress(&compressed);
    println!("解压结果: {}", decompressed);
    println!("解压长度: {}", decompressed.len());
    
    // 验证
    let is_valid = input == decompressed;
    println!("验证结果: {}", if is_valid { "✓ 成功" } else { "✗ 失败" });
    println!("=== 演示结束 ===");
}
