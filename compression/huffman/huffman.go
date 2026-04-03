package main

import (
	"container/heap"
	"fmt"
	"strings"
)

type HuffmanNode struct {
	char     rune
	freq     int
	left     *HuffmanNode
	right    *HuffmanNode
}

type HuffmanHeap []*HuffmanNode

func (h HuffmanHeap) Len() int           { return len(h) }
func (h HuffmanHeap) Less(i, j int) bool { return h[i].freq < h[j].freq }
func (h HuffmanHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *HuffmanHeap) Push(x interface{}) { *h = append(*h, x.(*HuffmanNode)) }
func (h *HuffmanHeap) Pop() interface{} {
	old := *h
	n := len(old)
	item := old[n-1]
	*h = old[0 : n-1]
	return item
}

func HuffmanEncode(text string) map[rune]string {
	// 统计频率
	freqMap := make(map[rune]int)
	for _, char := range text {
		freqMap[char]++
	}
	
	// 构建优先队列
	h := &HuffmanHeap{}
	heap.Init(h)
	for char, freq := range freqMap {
		heap.Push(h, &HuffmanNode{char: char, freq: freq})
	}
	
	// 构建Huffman树
	for h.Len() > 1 {
		left := heap.Pop(h).(*HuffmanNode)
		right := heap.Pop(h).(*HuffmanNode)
		parent := &HuffmanNode{
			freq:  left.freq + right.freq,
			left:  left,
			right: right,
		}
		heap.Push(h, parent)
	}
	
	// 生成编码表
	encodingMap := make(map[rune]string)
	var root *HuffmanNode
	if h.Len() > 0 {
		root = heap.Pop(h).(*HuffmanNode)
	}
	generateCodes(root, "", encodingMap)
	
	return encodingMap
}

func generateCodes(node *HuffmanNode, code string, encodingMap map[rune]string) {
	if node == nil {
		return
	}
	
	if node.left == nil && node.right == nil {
		if code == "" {
			encodingMap[node.char] = "0"
		} else {
			encodingMap[node.char] = code
		}
		return
	}
	
	generateCodes(node.left, code+"0", encodingMap)
	generateCodes(node.right, code+"1", encodingMap)
}

func HuffmanCompress(text string, encodingMap map[rune]string) string {
	var compressed strings.Builder
	for _, char := range text {
		compressed.WriteString(encodingMap[char])
	}
	return compressed.String()
}

func main() {
	text := "hello world"
	fmt.Printf("原始文本: %s\n", text)
	
	encodingMap := HuffmanEncode(text)
	fmt.Printf("编码表: %v\n", encodingMap)
	
	compressed := HuffmanCompress(text, encodingMap)
	fmt.Printf("压缩后: %s\n", compressed)
	
	fmt.Printf("压缩率: %.2f\n", float64(len(compressed))/float64(len(text)*8))
}
