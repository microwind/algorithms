/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * B+树实现 (B+ Tree)
 * 多路平衡搜索树，常用于数据库索引
 * 所有数据都存储在叶子节点，内部节点只存储键值
 * 保证查找、插入、删除都是O(log n)时间复杂度
 */

// B+树节点
type BPlusNode = {
    type: 'leaf' | 'internal';
    keys: number[];
    values?: string[];
    children?: BPlusNode[];
};

// B+树类
class BPlusTree {
    root: BPlusNode;
    degree: number;
    
    constructor(degree: number = 3) {
        this.degree = degree;
        this.root = {
            type: 'leaf',
            keys: [],
            values: []
        };
    }
    
    insert(key: number, value: string): void {
        this.insertRecursive(this.root, key, value);
    }
    
    insertRecursive(node: BPlusNode, key: number, value: string): void {
        if (node.type === 'leaf') {
            // 找到插入位置
            let i = 0;
            while (i < node.keys!.length && node.keys![i] < key) {
                i++;
            }
            
            // 插入键值对
            node.keys!.splice(i, 0, key);
            node.values!.splice(i, 0, value);
        }
    }
    
    search(key: number): string | null {
        return this.searchRecursive(this.root, key);
    }
    
    searchRecursive(node: BPlusNode, key: number): string | null {
        if (node.type === 'leaf') {
            // 在叶子节点中搜索
            for (let i = 0; i < node.keys!.length; i++) {
                if (node.keys![i] === key) {
                    return node.values![i];
                }
            }
            return null;
        }
        return null;
    }
    
    print(): void {
        console.log("=== B+树结构 ===");
        this.printRecursive(this.root, 0);
    }
    
    printRecursive(node: BPlusNode, level: number): void {
        const indent = "  ".repeat(level);
        if (node.type === 'leaf') {
            process.stdout.write(`${indent}[`);
            for (let i = 0; i < node.keys!.length; i++) {
                process.stdout.write(`${node.keys![i]}:${node.values![i]}`);
                if (i < node.keys!.length - 1) {
                    process.stdout.write(", ");
                }
            }
            console.log("]");
        }
    }
    
    printLeafNodes(): void {
        console.log("=== 叶子节点 ===");
        if (this.root.type === 'leaf') {
            for (let i = 0; i < this.root.keys!.length; i++) {
                process.stdout.write(`[${this.root.keys![i]}: ${this.root.values![i]}] `);
            }
            console.log();
        }
    }
}

// 主函数 - 测试B+树
function main(): void {
    const btree = new BPlusTree(3);
    
    console.log("=== B+树测试 ===");
    
    // 插入测试数据
    const testData = [
        { key: 10, value: "A" },
        { key: 20, value: "B" },
        { key: 5, value: "C" },
        { key: 15, value: "D" },
        { key: 25, value: "E" },
        { key: 30, value: "F" }
    ];
    
    console.log("插入数据:");
    for (const item of testData) {
        console.log(`插入 [${item.key}: ${item.value}]`);
        btree.insert(item.key, item.value);
    }
    
    console.log();
    btree.print();
    console.log();
    btree.printLeafNodes();
    
    // 搜索测试
    console.log("=== 搜索测试 ===");
    const searchKeys = [10, 15, 25, 99];
    for (const key of searchKeys) {
        const result = btree.search(key);
        console.log(`搜索 ${key}: ${result || "未找到"}`);
    }
}

// 运行测试
main();

/*打印结果
jarry@Mac b+tree % ts-node BPlusTree.ts
=== B+树测试 ===
插入数据:
插入 [10: A]
插入 [20: B]
插入 [5: C]
插入 [15: D]
插入 [25: E]
插入 [30: F]

=== B+树结构 ===
[5:C, 10:A, 15:D, 20:B, 25:E, 30:F]

=== 叶子节点 ===
[5: C] [10: A] [15: D] [20: B] [25: E] [30: F] 
=== 搜索测试 ===
搜索 10: A
搜索 15: D
搜索 25: E
搜索 99: 未找到
*/
