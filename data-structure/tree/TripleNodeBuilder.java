import java.util.LinkedList;
import java.util.Queue;

/**
 * 三叉树节点类
 * 包含父节点、左子节点、右子节点的引用
 * 用于构建具有父子关系的树形结构
 * 
 * @param <T> 节点值的类型
 */
class TripleNode<T> {
    /** 节点存储的值 */
    T value;
    /** 父节点引用 */
    TripleNode<T> parent;
    /** 左子节点引用 */
    TripleNode<T> left;
    /** 右子节点引用 */
    TripleNode<T> right;

    /**
     * 构造函数：创建一个只有父节点引用的节点
     * @param parent 父节点
     */
    TripleNode(TripleNode<T> parent) {
        this.parent = parent;
    }

    /**
     * 构造函数：创建一个包含值和父节点引用的节点
     * @param value 节点值
     * @param parent 父节点
     */
    TripleNode(T value, TripleNode<T> parent) {
        this.value = value;
        this.parent = parent;
    }
}

/**
 * 三叉树构建器
 * 提供构建满二叉树、遍历和验证树结构的功能
 * 使用广度优先搜索算法构建树形结构
 */
public class TripleNodeBuilder {
    
    /**
     * 构建满二叉树
     * 使用广度优先搜索算法，逐层构建树节点
     * 每个节点都有父节点引用，便于向上遍历
     * 
     * @param levels 树的层数
     * @return 返回构建好的满二叉树根节点，如果层数小于等于0则返回null
     */
    public static TripleNode<Integer> buildFullTree(int levels) {
        // 参数验证：层数必须大于0
        if (levels <= 0)
            return null;
            
        // 使用队列进行广度优先遍历
        LinkedList<TripleNode<Integer>> queue = new LinkedList<>();
        // 创建根节点，值为1，父节点为null
        TripleNode<Integer> root = new TripleNode<>(1, null);
        queue.add(root);
        // 从2开始给其他节点赋值
        int nodeValue = 2;

        // 逐层构建树
        for (int i = 1; i < levels; i++) {
            int size = queue.size();
            // 处理当前层的所有节点
            while (size-- > 0) {
                TripleNode<Integer> node = queue.poll();
                // 为当前节点创建左子节点
                node.left = new TripleNode<>(nodeValue++, node);
                // 为当前节点创建右子节点
                node.right = new TripleNode<>(nodeValue++, node);
                // 将子节点加入队列，用于下一层处理
                queue.offer(node.left);
                queue.offer(node.right);
            }
        }
        return root;
    }

    /**
     * 层序遍历并打印树结构
     * 使用广度优先搜索算法，按层打印每个节点的值和其父节点信息
     * 
     * @param root 树的根节点
     */
    public static void printLevelOrder(TripleNode<Integer> root) {
        // 空树检查
        if (root == null) {
            System.out.println("Empty tree");
            return;
        }

        // 使用队列进行层序遍历
        Queue<TripleNode<Integer>> queue = new LinkedList<>();
        queue.offer(root);
        int level = 1;
        
        // 逐层处理节点
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            System.out.printf("Level %d: ", level);
            
            // 处理当前层的所有节点
            for (int i = 0; i < levelSize; i++) {
                TripleNode<Integer> node = queue.poll();
                System.out.printf("%d", node.value);
                
                // 打印父节点信息，便于验证父子关系
                if (node.parent != null) {
                    System.out.printf("(parent:%d) ", node.parent.value);
                } else {
                    System.out.print("(root) ");
                }

                // 将子节点加入队列，用于下一层处理
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            System.out.println();
            level++;
        }
    }

    /**
     * 验证树结构的正确性
     * 检查每个节点的父子关系是否正确
     * 验证满二叉树每层的节点数量是否符合预期
     * 
     * @param root 树的根节点
     */
    public static void validateTree(TripleNode<Integer> root) {
        // 空树检查
        if (root == null) return;
        
        // 使用队列进行层序遍历验证
        Queue<TripleNode<Integer>> queue = new LinkedList<>();
        queue.offer(root);
        int expectedNodes = 1; // 满二叉树每层节点数的期望值
        int level = 1;
        
        // 逐层验证节点
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            // 打印每层的实际节点数与期望节点数
            System.out.printf("Level %d has %d nodes (expected %d)\n", 
                            level, levelSize, expectedNodes);
            
            // 验证当前层的每个节点
            for (int i = 0; i < levelSize; i++) {
                TripleNode<Integer> node = queue.poll();
                
                // 验证左子节点的父子关系
                if (node.left != null) {
                    if (node.left.parent != node) {
                        System.out.println("Invalid parent-child relationship found!");
                    }
                    queue.offer(node.left);
                }
                
                // 验证右子节点的父子关系
                if (node.right != null) {
                    if (node.right.parent != node) {
                        System.out.println("Invalid parent-child relationship found!");
                    }
                    queue.offer(node.right);
                }
            }
            // 满二叉树每层节点数是上一层的2倍
            expectedNodes *= 2;
            level++;
        }
    }

    /**
     * 主方法：测试三叉树构建器的功能
     * 测试不同层数的满二叉树构建、遍历和验证
     */
    public static void main(String[] args) {
        // 测试不同层数的树结构
        int[] testLevels = {1, 2, 3, 4};
        
        // 对每个层数进行测试
        for (int levels : testLevels) {
            System.out.println("\n=== Testing tree with " + levels + " levels ===");
            
            // 构建满二叉树
            TripleNode<Integer> root = buildFullTree(levels);
            
            // 打印树结构（层序遍历）
            System.out.println("Tree structure (level-order traversal):");
            printLevelOrder(root);
            
            // 验证树结构的正确性
            System.out.println("\nValidating tree structure:");
            validateTree(root);
        }
    }
}

/**
jarry@Mac tree % java TripleNodeBuilder.java 

=== Testing tree with 1 levels ===
Tree structure (level-order traversal):
Level 1: 1(root) 

Validating tree structure:
Level 1 has 1 nodes (expected 1)

=== Testing tree with 2 levels ===
Tree structure (level-order traversal):
Level 1: 1(root) 
Level 2: 2(parent:1) 3(parent:1) 

Validating tree structure:
Level 1 has 1 nodes (expected 1)
Level 2 has 2 nodes (expected 2)

=== Testing tree with 3 levels ===
Tree structure (level-order traversal):
Level 1: 1(root) 
Level 2: 2(parent:1) 3(parent:1) 
Level 3: 4(parent:2) 5(parent:2) 6(parent:3) 7(parent:3) 

Validating tree structure:
Level 1 has 1 nodes (expected 1)
Level 2 has 2 nodes (expected 2)
Level 3 has 4 nodes (expected 4)

=== Testing tree with 4 levels ===
Tree structure (level-order traversal):
Level 1: 1(root) 
Level 2: 2(parent:1) 3(parent:1) 
Level 3: 4(parent:2) 5(parent:2) 6(parent:3) 7(parent:3) 
Level 4: 8(parent:4) 9(parent:4) 10(parent:5) 11(parent:5) 12(parent:6) 13(parent:6) 14(parent:7) 15(parent:7) 

Validating tree structure:
Level 1 has 1 nodes (expected 1)
Level 2 has 2 nodes (expected 2)
Level 3 has 4 nodes (expected 4)
Level 4 has 8 nodes (expected 8)
 */