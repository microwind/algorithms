/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 满二叉树三叉节点构建器 - Java实现
 */

import java.util.LinkedList;
import java.util.Queue;

class TripleNode<T> {
    T value;
    TripleNode<T> parent, left, right;

    TripleNode(TripleNode<T> parent) {
        this.parent = parent;
    }

    TripleNode(T value, TripleNode<T> parent) {
        this.value = value;
        this.parent = parent;
    }
}

public class TripleNodeBuilder {
    // 生成满二叉树（广度优先）
    public static TripleNode<Integer> buildFullTree(int levels) {
        if (levels <= 0)
            return null;
            
        LinkedList<TripleNode<Integer>> queue = new LinkedList<>();
        TripleNode<Integer> root = new TripleNode<>(1, null); // 根节点值为1
        queue.add(root);
        int nodeValue = 2; // 从2开始给其他节点赋值

        for (int i = 1; i < levels; i++) {
            int size = queue.size();
            while (size-- > 0) {
                TripleNode<Integer> node = queue.poll();
                node.left = new TripleNode<>(nodeValue++, node);
                node.right = new TripleNode<>(nodeValue++, node);
                queue.offer(node.left);
                queue.offer(node.right);
            }
        }
        return root;
    }

    // 层序遍历打印树
    public static void printLevelOrder(TripleNode<Integer> root) {
        if (root == null) {
            System.out.println("Empty tree");
            return;
        }

        Queue<TripleNode<Integer>> queue = new LinkedList<>();
        queue.offer(root);
        int level = 1;
        
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            System.out.printf("Level %d: ", level);
            
            for (int i = 0; i < levelSize; i++) {
                TripleNode<Integer> node = queue.poll();
                System.out.printf("%d", node.value);
                
                // 打印父节点值（如果存在）
                if (node.parent != null) {
                    System.out.printf("(parent:%d) ", node.parent.value);
                } else {
                    System.out.print("(root) ");
                }

                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            System.out.println();
            level++;
        }
    }

    // 验证树的结构
    public static void validateTree(TripleNode<Integer> root) {
        if (root == null) return;
        
        Queue<TripleNode<Integer>> queue = new LinkedList<>();
        queue.offer(root);
        int expectedNodes = 1;
        int level = 1;
        
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            System.out.printf("Level %d has %d nodes (expected %d)\n", 
                            level, levelSize, expectedNodes);
            
            for (int i = 0; i < levelSize; i++) {
                TripleNode<Integer> node = queue.poll();
                // 验证父子关系
                if (node.left != null) {
                    if (node.left.parent != node) {
                        System.out.println("Invalid parent-child relationship found!");
                    }
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    if (node.right.parent != node) {
                        System.out.println("Invalid parent-child relationship found!");
                    }
                    queue.offer(node.right);
                }
            }
            expectedNodes *= 2;
            level++;
        }
    }

    public static void main(String[] args) {
        // 测试不同层数的树
        int[] testLevels = {1, 2, 3, 4};
        
        for (int levels : testLevels) {
            System.out.println("\n=== Testing tree with " + levels + " levels ===");
            TripleNode<Integer> root = buildFullTree(levels);
            
            System.out.println("Tree structure (level-order traversal):");
            printLevelOrder(root);
            
            System.out.println("\nValidating tree structure:");
            validateTree(root);
        }
    }
}