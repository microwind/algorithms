import java.util.*;

public class HuffmanCoding {
    
    static class HuffmanNode implements Comparable<HuffmanNode> {
        char character;
        int frequency;
        HuffmanNode left, right;
        
        HuffmanNode(char character, int frequency) {
            this.character = character;
            this.frequency = frequency;
        }
        
        HuffmanNode(int frequency, HuffmanNode left, HuffmanNode right) {
            this.frequency = frequency;
            this.left = left;
            this.right = right;
        }
        
        @Override
        public int compareTo(HuffmanNode other) {
            return this.frequency - other.frequency;
        }
    }
    
    public static Map<Character, String> huffmanEncode(String text) {
        // 统计频率
        Map<Character, Integer> frequencyMap = new HashMap<>();
        for (char c : text.toCharArray()) {
            frequencyMap.put(c, frequencyMap.getOrDefault(c, 0) + 1);
        }
        
        // 构建优先队列
        PriorityQueue<HuffmanNode> pq = new PriorityQueue<>();
        for (Map.Entry<Character, Integer> entry : frequencyMap.entrySet()) {
            pq.offer(new HuffmanNode(entry.getKey(), entry.getValue()));
        }
        
        // 构建Huffman树
        while (pq.size() > 1) {
            HuffmanNode left = pq.poll();
            HuffmanNode right = pq.poll();
            HuffmanNode parent = new HuffmanNode(
                left.frequency + right.frequency, left, right
            );
            pq.offer(parent);
        }
        
        // 生成编码表
        Map<Character, String> encodingMap = new HashMap<>();
        HuffmanNode root = pq.poll();
        generateCodes(root, "", encodingMap);
        
        return encodingMap;
    }
    
    private static void generateCodes(HuffmanNode node, String code, 
                                   Map<Character, String> encodingMap) {
        if (node == null) return;
        
        if (node.left == null && node.right == null) {
            encodingMap.put(node.character, code.isEmpty() ? "0" : code);
            return;
        }
        
        generateCodes(node.left, code + "0", encodingMap);
        generateCodes(node.right, code + "1", encodingMap);
    }
    
    public static String compress(String text, Map<Character, String> encodingMap) {
        StringBuilder compressed = new StringBuilder();
        for (char c : text.toCharArray()) {
            compressed.append(encodingMap.get(c));
        }
        return compressed.toString();
    }
    
    public static String decompress(String compressed, HuffmanNode root) {
        StringBuilder decompressed = new StringBuilder();
        HuffmanNode current = root;
        
        for (char bit : compressed.toCharArray()) {
            current = bit == '0' ? current.left : current.right;
            
            if (current.left == null && current.right == null) {
                decompressed.append(current.character);
                current = root;
            }
        }
        
        return decompressed.toString();
    }
    
    public static void main(String[] args) {
        String text = "hello world";
        System.out.println("原始文本: " + text);
        
        Map<Character, String> encodingMap = huffmanEncode(text);
        System.out.println("编码表: " + encodingMap);
        
        String compressed = compress(text, encodingMap);
        System.out.println("压缩后: " + compressed);
        
        // 重建树进行解压（实际应用中需要保存树结构）
        System.out.println("压缩率: " + (double)compressed.length() / (text.length() * 8));
    }
}
