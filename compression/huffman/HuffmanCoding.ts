class HuffmanNode {
    char: string | null;
    freq: number;
    left: HuffmanNode | null;
    right: HuffmanNode | null;

    constructor(char: string | null, freq: number, left: HuffmanNode | null = null, right: HuffmanNode | null = null) {
        this.char = char;
        this.freq = freq;
        this.left = left;
        this.right = right;
    }
}

class HuffmanCoding {
    static huffmanEncode(text: string): Map<string, string> {
        // 统计频率
        const frequency = new Map<string, number>();
        for (const char of text) {
            frequency.set(char, (frequency.get(char) || 0) + 1);
        }
        
        // 构建优先队列
        const queue: HuffmanNode[] = [];
        for (const [char, freq] of frequency.entries()) {
            queue.push(new HuffmanNode(char, freq));
        }
        queue.sort((a, b) => a.freq - b.freq);
        
        // 构建Huffman树
        while (queue.length > 1) {
            const left = queue.shift()!;
            const right = queue.shift()!;
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
        const encodingMap = new Map<string, string>();
        const root = queue[0];
        this.generateCodes(root, "", encodingMap);
        
        return encodingMap;
    }
    
    static generateCodes(node: HuffmanNode | null, code: string, encodingMap: Map<string, string>): void {
        if (!node) return;
        
        if (!node.left && !node.right) {
            encodingMap.set(node.char!, code || "0");
            return;
        }
        
        this.generateCodes(node.left, code + "0", encodingMap);
        this.generateCodes(node.right, code + "1", encodingMap);
    }
    
    static compress(text: string, encodingMap: Map<string, string>): string {
        let compressed = "";
        for (const char of text) {
            compressed += encodingMap.get(char);
        }
        return compressed;
    }
    
    static decompress(compressed: string, root: HuffmanNode): string {
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
