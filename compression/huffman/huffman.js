/**
 * 霍夫曼编码实现 - JavaScript
 * 基于贪心策略构建最优前缀编码树
 */

// 霍夫曼树节点
class HuffmanNode {
    constructor(char, freq, left = null, right = null) {
        this.char = char;    // 字符（叶子节点）
        this.freq = freq;    // 频率
        this.left = left;    // 左子树（编码0）
        this.right = right;  // 右子树（编码1）
    }
}

class HuffmanCoding {
    // 生成霍夫曼编码表
    static huffmanEncode(text) {
        // 统计字符频率
        const frequency = {};
        for (const char of text) {
            frequency[char] = (frequency[char] || 0) + 1;
        }
        
        // 初始化：所有字符节点入队
        const queue = [];
        for (const [char, freq] of Object.entries(frequency)) {
            queue.push(new HuffmanNode(char, freq));
        }
        queue.sort((a, b) => a.freq - b.freq);
        
        // 循环合并最小频率节点，构建霍夫曼树
        while (queue.length > 1) {
            const left = queue.shift();   // 最小
            const right = queue.shift();  // 次小
            const parent = new HuffmanNode(null, left.freq + right.freq, left, right);
            
            // 保持队列有序
            let inserted = false;
            for (let i = 0; i < queue.length; i++) {
                if (queue[i].freq >= parent.freq) {
                    queue.splice(i, 0, parent);
                    inserted = true;
                    break;
                }
            }
            if (!inserted) {
                queue.push(parent);
            }
        }
        
        // 生成编码表
        const encodingMap = {};
        const root = queue[0];
        this.generateCodes(root, "", encodingMap);
        
        return encodingMap;
    }
    
    // 递归生成编码：左0右1
    static generateCodes(node, code, encodingMap) {
        if (!node) return;
        
        // 叶子节点：存储编码
        if (!node.left && !node.right) {
            encodingMap[node.char] = code || '0';
            return;
        }
        
        this.generateCodes(node.left, code + '0', encodingMap);
        this.generateCodes(node.right, code + '1', encodingMap);
    }
    
    static compress(text, encodingMap) {
        let compressed = "";
        for (const char of text) {
            compressed += encodingMap[char];
        }
        return compressed;
    }
    
    static decompress(compressed, root) {
        let decompressed = "";
        let current = root;
        
        for (const bit of compressed) {
            current = bit === '0' ? current.left : current.right;
            
            if (!current.left && !current.right) {
                decompressed += current.char;
                current = root;
            }
        }
        
        return decompressed;
    }
}

// 示例使用
const text = "hello world";
console.log("原始文本:", text);

const encodingMap = HuffmanCoding.huffmanEncode(text);
console.log("编码表:", encodingMap);

const compressed = HuffmanCoding.compress(text, encodingMap);
console.log("压缩后:", compressed);

console.log("压缩率:", compressed.length / (text.length * 8));
