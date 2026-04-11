/*
*
 * Huffman编码 - 无损数据压缩算法
 *
 * 问题：为字符分配变长编码，高频字符用短编码，低频字符用长编码
 *
 * 核心思想：
 * - 统计字符频率
 * - 构建最小堆
 * - 递归构建Huffman树
 * - 生成编码表
 *
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(n)
*/

use std::collections::{BinaryHeap, HashMap};
use std::cmp::Ordering;

/*
*
 * Huffman树节点
*/
#[derive(Debug, Clone)]
struct HuffmanNode {
    character: Option<char>,
    frequency: usize,
    left: Option<Box<HuffmanNode>>,
    right: Option<Box<HuffmanNode>>,
}

impl HuffmanNode {
    fn new(character: Option<char>, frequency: usize) -> Self {
        HuffmanNode {
            character,
            frequency,
            left: None,
            right: None,
        }
    }

    fn is_leaf(&self) -> bool {
        self.left.is_none() && self.right.is_none()
    }
}

/*
*
 * 实现比较 trait 用于最小堆
*/
impl PartialEq for HuffmanNode {
    fn eq(&self, other: &Self) -> bool {
        self.frequency == other.frequency
    }
}

impl Eq for HuffmanNode {}

impl PartialOrd for HuffmanNode {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for HuffmanNode {
    fn cmp(&self, other: &Self) -> Ordering {
        // 反向比较，使 BinaryHeap 成为最小堆
        other.frequency.cmp(&self.frequency)
    }
}

/*
*
 * 构建Huffman树
*/
fn build_huffman_tree(frequency_map: &HashMap<char, usize>) -> Option<HuffmanNode> {
    if frequency_map.is_empty() {
        return None;
    }

    // 创建最小堆
    let mut heap = BinaryHeap::new();

    // 将所有字符节点加入堆
    for (&char, &freq) in frequency_map {
        heap.push(HuffmanNode::new(Some(char), freq));
    }

    // 构建Huffman树
    while heap.len() > 1 {
        let left = heap.pop().unwrap();
        let right = heap.pop().unwrap();

        let parent = HuffmanNode {
            character: None,
            frequency: left.frequency + right.frequency,
            left: Some(Box::new(left)),
            right: Some(Box::new(right)),
        };

        heap.push(parent);
    }

    heap.pop()
}

/*
*
 * 生成编码表
*/
fn generate_codes(node: &HuffmanNode, code: String, codes: &mut HashMap<char, String>) {
    if node.is_leaf() {
        if let Some(char) = node.character {
            codes.insert(char, code);
        }
        return;
    }

    if let Some(ref left) = node.left {
        generate_codes(left, format!("{}0", code), codes);
    }

    if let Some(ref right) = node.right {
        generate_codes(right, format!("{}1", code), codes);
    }
}

/*
*
 * 统计字符频率
*/
fn count_frequencies(text: &str) -> HashMap<char, usize> {
    let mut freq_map = HashMap::new();
    for char in text.chars() {
        *freq_map.entry(char).or_insert(0) += 1;
    }
    freq_map
}

/*
*
 * Huffman编码
*/
fn huffman_encode(text: &str) -> (HashMap<char, String>, String) {
    let freq_map = count_frequencies(text);
    let tree = build_huffman_tree(&freq_map).expect("Failed to build Huffman tree");

    let mut codes = HashMap::new();
    generate_codes(&tree, String::new(), &mut codes);

    // 编码文本
    let encoded: String = text.chars()
        .map(|c| codes.get(&c).unwrap().clone())
        .collect();

    (codes, encoded)
}

/*
*
 * Huffman解码
*/
fn huffman_decode(encoded: &str, codes: &HashMap<char, String>) -> String {
    // 构建反向映射
    let mut code_to_char: HashMap<String, char> = HashMap::new();
    for (char, code) in codes {
        code_to_char.insert(code.clone(), *char);
    }

    let mut result = String::new();
    let mut current_code = String::new();

    for bit in encoded.chars() {
        current_code.push(bit);
        if let Some(&char) = code_to_char.get(&current_code) {
            result.push(char);
            current_code.clear();
        }
    }

    result
}

/*
*
 * 打印编码表
*/
fn print_codes(codes: &HashMap<char, String>) {
    println!("Huffman编码表:");
    let mut sorted_codes: Vec<_> = codes.iter().collect();
    sorted_codes.sort_by_key(|&(_, code)| code.len());

    for (char, code) in sorted_codes {
        println!("  '{}': {}", char, code);
    }
}

/*
*
 * 计算压缩率
*/
fn calculate_compression_ratio(original: &str, encoded: &str) -> f64 {
    let original_bits = original.len() * 8;
    let encoded_bits = encoded.len();
    (1.0 - encoded_bits as f64 / original_bits as f64) * 100.0
}

/*
*
 * 测试函数
*/
fn main() {
    println!("=== Huffman编码 ===\n");

    // 测试用例1：基本用例
    println!("1. 基本用例:");
    let text1 = "hello world";
    let (codes1, encoded1) = huffman_encode(text1);
    print_codes(&codes1);
    println!("  原文: {}", text1);
    println!("  编码: {}", encoded1);
    println!("  压缩率: {:.2}%\n", calculate_compression_ratio(text1, &encoded1));

    // 测试用例2：重复字符
    println!("2. 重复字符:");
    let text2 = "aaaaabbbbbcccccdddddeeeee";
    let (codes2, encoded2) = huffman_encode(text2);
    print_codes(&codes2);
    println!("  原文: {}", text2);
    println!("  编码: {}", encoded2);
    println!("  压缩率: {:.2}%\n", calculate_compression_ratio(text2, &encoded2));

    // 测试用例3：解码测试
    println!("3. 解码测试:");
    let text3 = "this is a test";
    let (codes3, encoded3) = huffman_encode(text3);
    let decoded = huffman_decode(&encoded3, &codes3);
    println!("  原文: {}", text3);
    println!("  编码: {}", encoded3);
    println!("  解码: {}", decoded);
    println!("  解码正确: {}\n", decoded == text3);

    // 测试用例4：空字符串
    println!("4. 边界情况:");
    let text4 = "";
    let (codes4, encoded4) = huffman_encode(text4);
    println!("  空字符串: 编码长度 = {}", encoded4.len());

    let text5 = "a";
    let (codes5, encoded5) = huffman_encode(text5);
    println!("  单字符: 编码长度 = {}", encoded5.len());
}
