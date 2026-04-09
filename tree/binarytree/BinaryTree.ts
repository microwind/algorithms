/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二叉树节点接口
 */
interface TreeNode {
    value: number;
    left?: TreeNode;
    right?: TreeNode;
}

/**
 * 二叉树实现类
 * 
 * 功能特性:
 * - 二叉树的创建和基本操作
 * - 前序、中序、后序遍历（递归）
 * - 层序遍历
 * - 树的高度和节点数计算
 * - 树的平衡性检查
 * 
 * 算法复杂度:
 * - 插入: O(h) - h为树高度
 * - 查找: O(h) - h为树高度
 * - 遍历: O(n) - n为节点数
 * 
 * 应用场景:
 * - 表达式树
 * - 文件系统
 * - 数据库索引
 * - 决策树
 */
class BinaryTree {
    constructor() { }

    /**
     * 前序遍历 - 根-左-右
     * 
     * 应用场景:
     * - 树的复制
     * - 前缀表达式生成
     * - 文件系统遍历
     * 
     * @param tree 二叉树节点
     * @param result 存储遍历结果的数组
     * @returns 遍历结果数组
     */
    preOrderTraverse(tree: TreeNode | undefined, result: Array<number> = []): Array<number> {
        if (tree !== undefined) {
            result.push(tree.value); // 访问根节点
            this.preOrderTraverse(tree.left, result); // 遍历左子树
            this.preOrderTraverse(tree.right, result); // 遍历右子树
        }
        return result;
    }

    /**
     * 中序遍历 - 左-根-右
     * 
     * 应用场景:
     * - BST得到有序序列
     * - 中缀表达式生成
     * - 有序数据处理
     * 
     * @param tree 二叉树节点
     * @param result 存储遍历结果的数组
     * @returns 遍历结果数组
     */
    inOrderTraverse(tree: TreeNode | undefined, result: Array<number> = []): Array<number> {
        if (tree !== undefined) {
            this.inOrderTraverse(tree.left, result); // 遍历左子树
            result.push(tree.value); // 访问根节点
            this.inOrderTraverse(tree.right, result); // 遍历右子树
        }
        return result;
    }

    /**
     * 后序遍历 - 左-右-根
     * 
     * 应用场景:
     * - 树的删除
     * - 目录空间计算
     * - 后缀表达式生成
     * 
     * @param tree 二叉树节点
     * @param result 存储遍历结果的数组
     * @returns 遍历结果数组
     */
    postOrderTraverse(tree: TreeNode | undefined, result: Array<number> = []): Array<number> {
        if (tree !== undefined) {
            this.postOrderTraverse(tree.left, result); // 遍历左子树
            this.postOrderTraverse(tree.right, result); // 遍历右子树
            result.push(tree.value); // 访问根节点
        }
        return result;
    }

    /**
     * 层序遍历 - 广度优先搜索
     * 
     * 应用场景:
     * - 按层级显示树结构
     * - 最短路径问题
     * - 树的层次分析
     * 
     * @param tree 二叉树节点
     * @returns 遍历结果数组
     */
    levelOrderTraverse(tree: TreeNode | undefined): Array<number> {
        if (!tree) return [];
        
        const result: Array<number> = [];
        const queue: Array<TreeNode> = [tree]; // 使用队列进行层序遍历
        
        while (queue.length > 0) {
            const node = queue.shift()!; // 出队节点
            result.push(node.value); // 访问节点
            
            // 子节点入队
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
        
        return result;
    }

    /**
     * 计算树的高度
     * 
     * 递归算法:
     * 1. 计算左子树高度
     * 2. 计算右子树高度
     * 3. 取较大值加1
     * 
     * @param tree 二叉树节点
     * @returns 树的高度
     */
    height(tree: TreeNode | undefined): number {
        if (!tree) return 0;
        
        const leftHeight = this.height(tree.left); // 左子树高度
        const rightHeight = this.height(tree.right); // 右子树高度
        
        return Math.max(leftHeight, rightHeight) + 1;
    }

    /**
     * 计算节点总数
     * 
     * @param tree 二叉树节点
     * @returns 节点总数
     */
    size(tree: TreeNode | undefined): number {
        if (!tree) return 0;
        
        return 1 + this.size(tree.left) + this.size(tree.right);
    }

    /**
     * 查找指定值的节点
     * 
     * @param tree 二叉树节点
     * @param value 要查找的值
     * @returns 找到的节点或null
     */
    search(tree: TreeNode | undefined, value: number): TreeNode | undefined {
        if (!tree || tree.value === value) {
            return tree;
        }
        
        if (value < tree.value) {
            return this.search(tree.left, value); // 向左子树查找
        } else {
            return this.search(tree.right, value); // 向右子树查找
        }
    }

    /**
     * 检查树是否平衡
     * 
     * 平衡树定义: 每个节点的左右子树高度差不超过1
     * 
     * @param tree 二叉树节点
     * @returns 是否平衡
     */
    isBalanced(tree: TreeNode | undefined): boolean {
        if (!tree) return true;
        
        const leftHeight = this.height(tree.left);
        const rightHeight = this.height(tree.right);
        
        // 检查当前节点是否平衡
        if (Math.abs(leftHeight - rightHeight) > 1) {
            return false;
        }
        
        // 递归检查子树
        return this.isBalanced(tree.left) && this.isBalanced(tree.right);
    }

    /**
     * 打印树的结构
     * 
     * @param tree 二叉树节点
     * @param level 当前层级
     */
    printTree(tree: TreeNode | undefined, level: number = 0): void {
        if (!tree) return;
        
        this.printTree(tree.right, level + 1); // 打印右子树
        
        // 打印当前节点
        let indent = '';
        for (let i = 0; i < level; i++) {
            indent += '    ';
        }
        console.log(indent + tree.value);
        
        this.printTree(tree.left, level + 1); // 打印左子树
    }

    /**
     * 创建测试用例的二叉树
     * 
     * @returns 测试二叉树
     */
    createTestTree(): TreeNode {
        // 创建测试树:
        //       50
        //      /  \
        //     30   70
        //    / \   / \
        //   20 40 60 80
        const tree: TreeNode = {
            value: 50,
            left: {
                value: 30,
                left: { value: 20, left: undefined, right: undefined },
                right: { value: 40, left: undefined, right: undefined }
            },
            right: {
                value: 70,
                left: { value: 60, left: undefined, right: undefined },
                right: { value: 80, left: undefined, right: undefined }
            }
        };
        
        return tree;
    }

    /**
     * 测试所有二叉树功能
     */
    test(): void {
        const tree = this.createTestTree();
        
        console.log("=".repeat(60));
        console.log("二叉树算法测试 - TypeScript实现");
        console.log("=".repeat(60));
        console.log();
        
        // 显示树结构
        console.log("树的结构:");
        this.printTree(tree);
        console.log();
        
        // 测试各种遍历
        console.log("前序遍历（根-左-右）:", this.preOrderTraverse(tree));
        console.log("中序遍历（左-根-右）:", this.inOrderTraverse(tree));
        console.log("后序遍历（左-右-根）:", this.postOrderTraverse(tree));
        console.log("层序遍历:", this.levelOrderTraverse(tree));
        console.log();
        
        // 测试基本操作
        console.log("树的高度:", this.height(tree));
        console.log("节点总数:", this.size(tree));
        console.log("树是否平衡:", this.isBalanced(tree));
        
        // 测试查找
        const found = this.search(tree, 40);
        console.log("查找节点40:", found ? "找到" : "未找到");
        
        console.log();
        console.log("=== 算法特性 ===");
        console.log("二叉树:");
        console.log("  - 每个节点最多有两个子节点");
        console.log("  - 左子节点值小于父节点");
        console.log("  - 右子节点值大于父节点");
        console.log("  - 支持高效的查找、插入、删除");
        
        console.log("\n遍历方法:");
        console.log("  - 前序遍历: 根-左-右");
        console.log("  - 中序遍历: 左-根-右（BST得到有序序列）");
        console.log("  - 后序遍历: 左-右-根");
        console.log("  - 层序遍历: 按层级从左到右");
        
        console.log("\n复杂度分析:");
        console.log("  - 平均情况: O(log n) - 平衡树");
        console.log("  - 最坏情况: O(n) - 退化为链表");
        console.log("  - 空间复杂度: O(n) - 存储所有节点");
        
        console.log("\n=== 应用场景 ===");
        console.log("二叉树用于:");
        console.log("  - 数据库索引（B树变种）");
        console.log("  - 文件系统目录结构");
        console.log("  - 编译器语法分析");
        console.log("  - 决策树算法");
        console.log("  - 表达式求值");
    }
}

// 运行测试
if (require.main === module) {
    const binaryTree = new BinaryTree();
    binaryTree.test();
}

export { BinaryTree, TreeNode };
