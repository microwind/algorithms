/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树遍历 - 二叉树遍历实现
 * 实现前序、中序、后序遍历（递归和迭代）
 * 以及层序遍历、莫里斯遍历和其他高级遍历方法
 * 包含时间复杂度分析和应用场景
 */

// 二叉树节点
class TreeNode {
    val: number; // 节点值
    left: TreeNode | null; // 左子节点
    right: TreeNode | null; // 右子节点

    constructor(val: number) {
        this.val = val; // 初始化节点值
        this.left = null; // 初始化左子节点为null
        this.right = null; // 初始化右子节点为null
    }
    
    toString(): string {
        return `TreeNode(${this.val})`; // 节点的字符串表示
    }
}

// 树遍历实现
class TreeTraversal {
    /**
     * 前序遍历 - 递归：根-左-右
     *
     * 算法:
     * 1. 访问根节点
     * 2. 递归遍历左子树
     * 3. 递归遍历右子树
     *
     * 时间复杂度: O(n) - 每个节点访问一次
     * 空间复杂度: O(h) - h是树高度，递归栈深度
     *
     * 应用场景:
     * - 树的复制
     * - 从表达式树生成前缀表达式
     * - 文件系统目录结构遍历
     */
    static preorderRecursive(root: TreeNode | null): number[] {
        const result: number[] = [];
        this.preorderRecursiveHelper(root, result);
        return result;
    }
    
    private static preorderRecursiveHelper(node: TreeNode | null, result: number[]): void {
        if (node === null)
            return;
        result.push(node.val); // 访问根节点
        this.preorderRecursiveHelper(node.left, result); // 遍历左子树
        this.preorderRecursiveHelper(node.right, result); // 遍历右子树
    }

    /**
     * 前序遍历 - 迭代：使用栈
     *
     * 算法:
     * 1. 使用栈模拟递归
     * 2. 右子节点先入栈
     * 3. 左子节点后入栈，保证先处理
     *
     * 时间复杂度: O(n) - 每个节点访问一次
     * 空间复杂度: O(n) - 最坏情况栈存储所有节点
     *
     * 优势:
     * - 避免递归栈溢出
     * - 内存使用更可控
     */
    static preorderIterative(root: TreeNode | null): number[] {
        if (root === null)
            return [];
        
        const result: number[] = [];
        const stack: TreeNode[] = [root]; // 初始化栈，根节点入栈
        
        while (stack.length > 0) {
            const node = stack.pop()!; // 出栈节点
            result.push(node.val); // 访问节点
            
            // 右子节点先入栈，左子节点后入栈
            if (node.right !== null)
                stack.push(node.right);
            if (node.left !== null)
                stack.push(node.left);
        }
        
        return result;
    }

    /**
     * 中序遍历 - 递归：左-根-右
     *
     * 算法:
     * 1. 递归遍历左子树
     * 2. 访问根节点
     * 3. 递归遍历右子树
     *
     * 时间复杂度: O(n) - 每个节点访问一次
     * 空间复杂度: O(h) - h是树高度，递归栈深度
     *
     * 应用场景:
     * - 二叉搜索树的中序遍历得到有序序列
     * - 表达式树的中缀表达式生成
     * - 有序数据处理
     */
    static inorderRecursive(root: TreeNode | null): number[] {
        const result: number[] = [];
        this.inorderRecursiveHelper(root, result);
        return result;
    }
    
    private static inorderRecursiveHelper(node: TreeNode | null, result: number[]): void {
        if (node === null)
            return;
        this.inorderRecursiveHelper(node.left, result); // 遍历左子树
        result.push(node.val); // 访问根节点
        this.inorderRecursiveHelper(node.right, result); // 遍历右子树
    }

    /**
     * 中序遍历 - 迭代：使用栈
     *
     * 算法:
     * 1. 向左遍历到底，路径入栈
     * 2. 逐个出栈，访问节点
     * 3. 处理右子树
     *
     * 时间复杂度: O(n) - 每个节点访问一次
     * 空间复杂度: O(n) - 最坏情况栈存储所有节点
     */
    static inorderIterative(root: TreeNode | null): number[] {
        const result: number[] = [];
        const stack: TreeNode[] = [];
        let current: TreeNode | null = root;
        
        while (current !== null || stack.length > 0) {
            // 向左遍历到底
            while (current !== null) {
                stack.push(current);
                current = current.left;
            }
            
            // 出栈并访问
            current = stack.pop()!;
            result.push(current.val);
            
            // 处理右子树
            current = current.right;
        }
        
        return result;
    }

    /**
     * 后序遍历 - 递归：左-右-根
     *
     * 算法:
     * 1. 递归遍历左子树
     * 2. 递归遍历右子树
     * 3. 访问根节点
     *
     * 时间复杂度: O(n) - 每个节点访问一次
     * 空间复杂度: O(h) - h是树高度，递归栈深度
     *
     * 应用场景:
     * - 树的删除（从叶子节点开始）
     * - 目录空间计算
     * - 后缀表达式生成
     */
    static postorderRecursive(root: TreeNode | null): number[] {
        const result: number[] = [];
        this.postorderRecursiveHelper(root, result);
        return result;
    }
    
    private static postorderRecursiveHelper(node: TreeNode | null, result: number[]): void {
        if (node === null)
            return;
        this.postorderRecursiveHelper(node.left, result); // 遍历左子树
        this.postorderRecursiveHelper(node.right, result); // 遍历右子树
        result.push(node.val); // 访问根节点
    }

    /**
     * 后序遍历 - 迭代：使用双栈
     *
     * 算法:
     * 1. 使用第一个栈进行遍历
     * 2. 使用第二个栈存储后序结果
     * 3. 调整入栈顺序保证正确顺序
     *
     * 时间复杂度: O(n) - 每个节点访问一次
     * 空间复杂度: O(n) - 两个栈存储所有节点
     */
    static postorderIterative(root: TreeNode | null): number[] {
        if (root === null)
            return [];
        
        const result: number[] = [];
        const stack1: TreeNode[] = [root]; // 遍历栈
        const stack2: TreeNode[] = []; // 结果栈
        
        while (stack1.length > 0) {
            const node = stack1.pop()!;
            stack2.push(node); // 节点入结果栈
            
            // 左子节点先入栈，保证右子节点先处理
            if (node.left !== null)
                stack1.push(node.left);
            if (node.right !== null)
                stack1.push(node.right);
        }
        
        // 从结果栈出栈得到后序序列
        while (stack2.length > 0) {
            result.push(stack2.pop()!.val);
        }
        
        return result;
    }

    /**
     * 层序遍历 - 广度优先搜索
     *
     * 算法:
     * 1. 使用队列进行层次遍历
     * 2. 每层从左到右访问节点
     * 3. 逐层向下处理
     *
     * 时间复杂度: O(n) - 每个节点访问一次
     * 空间复杂度: O(n) - 队列最多存储一层节点
     *
     * 应用场景:
     * - 树的层次结构显示
     * - 按层级处理节点
     * - 最短路径问题
     */
    static levelOrder(root: TreeNode | null): number[] {
        if (root === null)
            return [];
        
        const result: number[] = [];
        const queue: TreeNode[] = [root]; // 初始化队列，根节点入队
        
        while (queue.length > 0) {
            const node = queue.shift()!; // 出队节点
            result.push(node.val); // 访问节点
            
            // 左右子节点入队
            if (node.left !== null)
                queue.push(node.left);
            if (node.right !== null)
                queue.push(node.right);
        }
        
        return result;
    }

    /**
     * 莫里斯遍历 - 中序遍历的O(1)空间版本
     *
     * 算法:
     * 1. 使用线索连接临时修改树结构
     * 2. 遍历后恢复原始结构
     * 3. 不使用栈或递归
     *
     * 时间复杂度: O(n) - 每个节点访问常数次
     * 空间复杂度: O(1) - 只使用常数额外空间
     *
     * 优势:
     * - 空间复杂度最优
     * - 适合内存受限环境
     * - 可用于树的序列化
     */
    static morrisInorder(root: TreeNode | null): number[] {
        const result: number[] = [];
        let current: TreeNode | null = root;
        let predecessor: TreeNode | null = null;
        
        while (current !== null) {
            if (current.left === null) {
                // 没有左子节点，访问当前节点
                result.push(current.val);
                current = current.right;
            } else {
                // 找到前驱节点
                predecessor = current.left;
                while (predecessor.right !== null && predecessor.right !== current) {
                    predecessor = predecessor.right;
                }
                
                if (predecessor.right === null) {
                    // 建立线索
                    predecessor.right = current;
                    current = current.left;
                } else {
                    // 移除线索，访问当前节点
                    predecessor.right = null;
                    result.push(current.val);
                    current = current.right;
                }
            }
        }
        
        return result;
    }

    /**
     * 计算树的深度
     *
     * 算法:
     * 1. 递归计算左子树深度
     * 2. 递归计算右子树深度
     * 3. 取较大值加1
     *
     * 时间复杂度: O(n) - 每个节点访问一次
     * 空间复杂度: O(h) - h是树高度，递归栈深度
     */
    static treeDepth(root: TreeNode | null): number {
        if (root === null)
            return 0;
        
        const leftDepth = this.treeDepth(root.left);
        const rightDepth = this.treeDepth(root.right);
        
        return Math.max(leftDepth, rightDepth) + 1;
    }

    /**
     * 检查树是否平衡
     *
     * 算法:
     * 1. 计算每个节点的左右子树深度差
     * 2. 检查深度差是否超过1
     * 3. 递归检查所有子树
     *
     * 时间复杂度: O(n²) - 朴素算法
     * 空间复杂度: O(h) - h是树高度，递归栈深度
     */
    static isBalanced(root: TreeNode | null): boolean {
        if (root === null)
            return true;
        
        const leftDepth = this.treeDepth(root.left);
        const rightDepth = this.treeDepth(root.right);
        
        // 检查当前节点是否平衡
        if (Math.abs(leftDepth - rightDepth) > 1)
            return false;
        
        // 递归检查子树
        return this.isBalanced(root.left) && this.isBalanced(root.right);
    }

    /**
     * 打印遍历结果
     */
    static printTraversalResult(title: string, result: number[]): void {
        console.log(`${title}: [${result.join(', ')}]`);
    }

    /**
     * 测试所有遍历方法
     */
    static test(): void {
        // 构建测试树
        //       1
        //      / \
        //     2   3
        //    / \   \
        //   4   5   6
        const root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.right = new TreeNode(6);

        console.log("=".repeat(60));
        console.log("树遍历算法测试 - TypeScript实现");
        console.log("=".repeat(60));
        console.log("测试树结构:");
        console.log("       1");
        console.log("      / \\");
        console.log("     2   3");
        console.log("    / \\   \\");
        console.log("   4   5   6");
        console.log();

        // 测试各种遍历方法
        this.printTraversalResult("前序遍历（递归）", this.preorderRecursive(root));
        this.printTraversalResult("前序遍历（迭代）", this.preorderIterative(root));
        this.printTraversalResult("中序遍历（递归）", this.inorderRecursive(root));
        this.printTraversalResult("中序遍历（迭代）", this.inorderIterative(root));
        this.printTraversalResult("后序遍历（递归）", this.postorderRecursive(root));
        this.printTraversalResult("后序遍历（迭代）", this.postorderIterative(root));
        this.printTraversalResult("层序遍历", this.levelOrder(root));
        this.printTraversalResult("莫里斯中序遍历", this.morrisInorder(root));
        
        console.log();
        console.log("=== 算法特性 ===");
        console.log("前序遍历:");
        console.log("  - 根节点最先访问");
        console.log("  - 适用于树的复制");
        console.log("  - 生成前缀表达式");
        
        console.log("\n中序遍历:");
        console.log("  - BST中序遍历得到有序序列");
        console.log("  - 生成中缀表达式");
        console.log("  - 有序数据处理");
        
        console.log("\n后序遍历:");
        console.log("  - 适用于树的删除");
        console.log("  - 从叶子节点开始处理");
        console.log("  - 生成后缀表达式");
        
        console.log("\n层序遍历:");
        console.log("  - 广度优先遍历");
        console.log("  - 按层级处理节点");
        console.log("  - 适用于最短路径问题");
        
        console.log("\n莫里斯遍历:");
        console.log("  - O(1)空间复杂度");
        console.log("  - 修改树结构但会恢复");
        console.log("  - 适合内存受限环境");
        
        console.log("\n=== 复杂度分析 ===");
        console.log("时间复杂度:");
        console.log("  - 所有遍历: O(n) - 每个节点访问一次");
        console.log("  - 平衡检查: O(n²) - 朴素算法");
        console.log("  - 深度计算: O(n) - 每个节点访问一次");
        
        console.log("\n空间复杂度:");
        console.log("  - 递归方法: O(h) - h是树高度");
        console.log("  - 迭代方法: O(n) - 使用栈或队列");
        console.log("  - 莫里斯遍历: O(1) - 常数额外空间");
        
        console.log("\n=== 应用场景 ===");
        console.log("树遍历算法用于:");
        console.log("  - 编译器设计（表达式树）");
        console.log("  - 文件系统（目录结构）");
        console.log("  - 数据库（B树索引）");
        console.log("  - 人工智能（决策树）");
        console.log("  - 网络协议（路由树）");
    }
}

// 运行测试
TreeTraversal.test();

export { TreeNode, TreeTraversal };
