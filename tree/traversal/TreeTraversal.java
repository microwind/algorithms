/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树遍历 - 二叉树遍历实现
 * 实现前序、中序、后序遍历（递归和迭代）
 * 以及层序遍历、莫里斯遍历和其他高级遍历方法
 * 包含时间复杂度分析和应用场景
 */

import java.util.*;

public class TreeTraversal {
    
    // 二叉树节点结构
    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        
        public TreeNode(int val) {
            this.val = val;
            this.left = null;
            this.right = null;
        }
    }
    
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
    public static List<Integer> preorderRecursive(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        preorderRecursiveHelper(root, result);
        return result;
    }
    
    private static void preorderRecursiveHelper(TreeNode node, List<Integer> result) {
        if (node == null)
            return;
        result.add(node.val); // 访问根节点
        preorderRecursiveHelper(node.left, result); // 遍历左子树
        preorderRecursiveHelper(node.right, result); // 遍历右子树
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
    public static List<Integer> preorderIterative(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null)
            return result;
        
        Stack<TreeNode> stack = new Stack<>();
        stack.push(root); // 根节点入栈
        
        while (!stack.isEmpty()) {
            TreeNode node = stack.pop(); // 出栈节点
            result.add(node.val); // 访问节点
            
            // 右子节点先入栈，左子节点后入栈
            if (node.right != null)
                stack.push(node.right);
            if (node.left != null)
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
    public static List<Integer> inorderRecursive(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        inorderRecursiveHelper(root, result);
        return result;
    }
    
    private static void inorderRecursiveHelper(TreeNode node, List<Integer> result) {
        if (node == null)
            return;
        inorderRecursiveHelper(node.left, result); // 遍历左子树
        result.add(node.val); // 访问根节点
        inorderRecursiveHelper(node.right, result); // 遍历右子树
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
    public static List<Integer> inorderIterative(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        Stack<TreeNode> stack = new Stack<>();
        TreeNode current = root;
        
        while (current != null || !stack.isEmpty()) {
            // 向左遍历到底
            while (current != null) {
                stack.push(current);
                current = current.left;
            }
            
            // 出栈并访问
            current = stack.pop();
            result.add(current.val);
            
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
    public static List<Integer> postorderRecursive(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        postorderRecursiveHelper(root, result);
        return result;
    }
    
    private static void postorderRecursiveHelper(TreeNode node, List<Integer> result) {
        if (node == null)
            return;
        postorderRecursiveHelper(node.left, result); // 遍历左子树
        postorderRecursiveHelper(node.right, result); // 遍历右子树
        result.add(node.val); // 访问根节点
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
    public static List<Integer> postorderIterative(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null)
            return result;
        
        Stack<TreeNode> stack1 = new Stack<>(); // 遍历栈
        Stack<TreeNode> stack2 = new Stack<>(); // 结果栈
        
        stack1.push(root);
        
        while (!stack1.isEmpty()) {
            TreeNode node = stack1.pop();
            stack2.push(node); // 节点入结果栈
            
            // 左子节点先入栈，保证右子节点先处理
            if (node.left != null)
                stack1.push(node.left);
            if (node.right != null)
                stack1.push(node.right);
        }
        
        // 从结果栈出栈得到后序序列
        while (!stack2.isEmpty()) {
            result.add(stack2.pop().val);
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
    public static List<Integer> levelOrder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null)
            return result;
        
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root); // 根节点入队
        
        while (!queue.isEmpty()) {
            TreeNode node = queue.poll(); // 出队节点
            result.add(node.val); // 访问节点
            
            // 左右子节点入队
            if (node.left != null)
                queue.offer(node.left);
            if (node.right != null)
                queue.offer(node.right);
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
    public static List<Integer> morrisInorder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode current = root;
        TreeNode predecessor = null;
        
        while (current != null) {
            if (current.left == null) {
                // 没有左子节点，访问当前节点
                result.add(current.val);
                current = current.right;
            } else {
                // 找到前驱节点
                predecessor = current.left;
                while (predecessor.right != null && predecessor.right != current) {
                    predecessor = predecessor.right;
                }
                
                if (predecessor.right == null) {
                    // 建立线索
                    predecessor.right = current;
                    current = current.left;
                } else {
                    // 移除线索，访问当前节点
                    predecessor.right = null;
                    result.add(current.val);
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
    public static int treeDepth(TreeNode root) {
        if (root == null)
            return 0;
        
        int leftDepth = treeDepth(root.left);
        int rightDepth = treeDepth(root.right);
        
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
    public static boolean isBalanced(TreeNode root) {
        if (root == null)
            return true;
        
        int leftDepth = treeDepth(root.left);
        int rightDepth = treeDepth(root.right);
        
        // 检查当前节点是否平衡
        if (Math.abs(leftDepth - rightDepth) > 1)
            return false;
        
        // 递归检查子树
        return isBalanced(root.left) && isBalanced(root.right);
    }

    /**
     * 打印遍历结果
     */
    private static void printTraversalResult(String title, List<Integer> result) {
        System.out.println(title + ": " + result.toString());
    }

    /**
     * 测试所有遍历方法
     */
    public static void main(String[] args) {
        // 构建测试树
        //       1
        //      / \
        //     2   3
        //    / \   \
        //   4   5   6
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.right = new TreeNode(6);

        System.out.println("=".repeat(60));
        System.out.println("树遍历算法测试 - Java实现");
        System.out.println("=".repeat(60));
        System.out.println("测试树结构:");
        System.out.println("       1");
        System.out.println("      / \\");
        System.out.println("     2   3");
        System.out.println("    / \\   \\");
        System.out.println("   4   5   6");
        System.out.println();

        // 测试各种遍历方法
        printTraversalResult("前序遍历（递归）", preorderRecursive(root));
        printTraversalResult("前序遍历（迭代）", preorderIterative(root));
        printTraversalResult("中序遍历（递归）", inorderRecursive(root));
        printTraversalResult("中序遍历（迭代）", inorderIterative(root));
        printTraversalResult("后序遍历（递归）", postorderRecursive(root));
        printTraversalResult("后序遍历（迭代）", postorderIterative(root));
        printTraversalResult("层序遍历", levelOrder(root));
        printTraversalResult("莫里斯中序遍历", morrisInorder(root));
        
        System.out.println();
        System.out.println("=== 算法特性 ===");
        System.out.println("前序遍历:");
        System.out.println("  - 根节点最先访问");
        System.out.println("  - 适用于树的复制");
        System.out.println("  - 生成前缀表达式");
        
        System.out.println("\n中序遍历:");
        System.out.println("  - BST中序遍历得到有序序列");
        System.out.println("  - 生成中缀表达式");
        System.out.println("  - 有序数据处理");
        
        System.out.println("\n后序遍历:");
        System.out.println("  - 适用于树的删除");
        System.out.println("  - 从叶子节点开始处理");
        System.out.println("  - 生成后缀表达式");
        
        System.out.println("\n层序遍历:");
        System.out.println("  - 广度优先遍历");
        System.out.println("  - 按层级处理节点");
        System.out.println("  - 适用于最短路径问题");
        
        System.out.println("\n莫里斯遍历:");
        System.out.println("  - O(1)空间复杂度");
        System.out.println("  - 修改树结构但会恢复");
        System.out.println("  - 适合内存受限环境");
        
        System.out.println("\n=== 复杂度分析 ===");
        System.out.println("时间复杂度:");
        System.out.println("  - 所有遍历: O(n) - 每个节点访问一次");
        System.out.println("  - 平衡检查: O(n²) - 朴素算法");
        System.out.println("  - 深度计算: O(n) - 每个节点访问一次");
        
        System.out.println("\n空间复杂度:");
        System.out.println("  - 递归方法: O(h) - h是树高度");
        System.out.println("  - 迭代方法: O(n) - 使用栈或队列");
        System.out.println("  - 莫里斯遍历: O(1) - 常数额外空间");
        
        System.out.println("\n=== 应用场景 ===");
        System.out.println("树遍历算法用于:");
        System.out.println("  - 编译器设计（表达式树）");
        System.out.println("  - 文件系统（目录结构）");
        System.out.println("  - 数据库（B树索引）");
        System.out.println("  - 人工智能（决策树）");
        System.out.println("  - 网络协议（路由树）");
    }
}
