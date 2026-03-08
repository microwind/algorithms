/*
 * B+树 - JavaScript实现
 */

const ORDER = 3;  // B+树阶数

class BPlusNode {
    constructor(isLeaf = true) {
        this.keys = [];
        this.children = [];
        this.next = null;  // 叶节点链表指针
        this.isLeaf = isLeaf;
    }
}

class BPlusTree {
    constructor() {
        this.root = new BPlusNode(true);
    }

    // 查找叶节点
    findLeaf(node, key) {
        if (node.isLeaf) {
            return node;
        }
        
        let i = 0;
        while (i < node.keys.length && key > node.keys[i]) {
            i++;
        }
        
        return this.findLeaf(node.children[i], key);
    }

    // 搜索键值
    search(key) {
        const leaf = this.findLeaf(this.root, key);
        return leaf.keys.includes(key);
    }

    // 分裂子节点
    splitChild(parent, i, child) {
        const newChild = new BPlusNode(child.isLeaf);
        const mid = ORDER - 1;
        
        // 复制后半部分键
        newChild.keys = child.keys.slice(mid + 1);
        
        // 处理子节点或链表指针
        if (!child.isLeaf) {
            newChild.children = child.children.slice(mid + 1);
        } else {
            newChild.next = child.next;
            child.next = newChild;
        }
        
        // 在父节点中插入中间键
        parent.keys.splice(i, 0, child.keys[mid]);
        parent.children.splice(i + 1, 0, newChild);
        
        // 调整原节点的键
        child.keys = child.keys.slice(0, mid);
    }

    // 在非满节点中插入
    insertNonFull(node, key) {
        if (node.isLeaf) {
            // 叶节点直接插入
            let i = node.keys.length - 1;
            while (i >= 0 && key < node.keys[i]) {
                node.keys[i + 1] = node.keys[i];
                i--;
            }
            node.keys[i + 1] = key;
        } else {
            // 内部节点
            let i = node.keys.length - 1;
            while (i >= 0 && key < node.keys[i]) {
                i--;
            }
            i++;
            
            if (node.children[i].keys.length === 2 * ORDER - 1) {
                this.splitChild(node, i, node.children[i]);
                if (key > node.keys[i]) {
                    i++;
                }
            }
            
            this.insertNonFull(node.children[i], key);
        }
    }

    // 插入键值
    insert(key) {
        if (this.root.keys.length === 2 * ORDER - 1) {
            const newRoot = new BPlusNode(false);
            newRoot.children.push(this.root);
            this.splitChild(newRoot, 0, this.root);
            this.root = newRoot;
        }
        this.insertNonFull(this.root, key);
    }

    // 中序遍历
    traverseNode(node, result) {
        if (node.isLeaf) {
            result.push(...node.keys);
        } else {
            for (let i = 0; i < node.keys.length; i++) {
                this.traverseNode(node.children[i], result);
                result.push(node.keys[i]);
            }
            this.traverseNode(node.children[node.keys.length], result);
        }
    }

    traverse() {
        const result = [];
        this.traverseNode(this.root, result);
        return result;
    }
}

// 测试示例
function main() {
    console.log("=".repeat(50));
    console.log("B+树实现 (B+ Tree)");
    console.log("=".repeat(50));
    
    const bpt = new BPlusTree();
    
    const values = [10, 20, 5, 6, 12, 30, 7, 17];
    console.log("\n插入数据:", values.join(" "));
    
    values.forEach(val => bpt.insert(val));
    
    console.log("\n中序遍历结果:", bpt.traverse().join(", "));
    
    console.log("\n搜索测试:");
    const testKeys = [6, 15, 30];
    testKeys.forEach(key => {
        const found = bpt.search(key);
        console.log(`  查找 ${key}: ${found ? "找到" : "未找到"}`);
    });
    
    console.log("\nB+树特点:");
    console.log("  • 所有数据存储在叶节点");
    console.log("  • 叶节点形成有序链表");
    console.log("  • 适合磁盘存储和范围查询");
    console.log("  • 查找、插入、删除: O(log n)");
    console.log("  • 应用于数据库索引、文件系统");
}

main();
