#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct {
    int size;
    int capacity;
    HuffmanNode** array;
} MinHeap;

HuffmanNode* createNode(char character, int frequency) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (HuffmanNode**)malloc(capacity * sizeof(HuffmanNode*));
    return heap;
}

void swapNodes(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && 
        heap->array[left]->frequency < heap->array[smallest]->frequency)
        smallest = left;

    if (right < heap->size && 
        heap->array[right]->frequency < heap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

HuffmanNode* extractMin(MinHeap* heap) {
    HuffmanNode* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    --heap->size;
    minHeapify(heap, 0);
    return temp;
}

void insertMinHeap(MinHeap* heap, HuffmanNode* node) {
    ++heap->size;
    int i = heap->size - 1;
    
    while (i && node->frequency < heap->array[(i - 1) / 2]->frequency) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    
    heap->array[i] = node;
}

void buildMinHeap(MinHeap* heap) {
    int n = heap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(heap, i);
}

void printCodes(HuffmanNode* root, char* arr, int top) {
    if (root->left) {
        arr[top] = '0';
        printCodes(root->left, arr, top + 1);
    }
    
    if (root->right) {
        arr[top] = '1';
        printCodes(root->right, arr, top + 1);
    }
    
    if (!root->left && !root->right) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; ++i)
            printf("%c", arr[i]);
        printf("\n");
    }
}

void HuffmanCodes(char* data, int* freq, int size) {
    MinHeap* heap = createMinHeap(size);
    
    for (int i = 0; i < size; ++i)
        heap->array[i] = createNode(data[i], freq[i]);
    
    heap->size = size;
    buildMinHeap(heap);
    
    while (heap->size > 1) {
        HuffmanNode* left = extractMin(heap);
        HuffmanNode* right = extractMin(heap);
        
        HuffmanNode* parent = createNode('$', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        insertMinHeap(heap, parent);
    }
    
    char arr[100];
    printCodes(heap->array[0], arr, 0);
}

int main() {
    char* data = "hello world";
    int freq[256] = {0};
    
    // 统计频率
    for (int i = 0; data[i] != '\0'; ++i)
        freq[(unsigned char)data[i]]++;
    
    // 获取唯一字符
    char uniqueChars[256];
    int uniqueFreq[256];
    int uniqueCount = 0;
    
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            uniqueChars[uniqueCount] = (char)i;
            uniqueFreq[uniqueCount] = freq[i];
            uniqueCount++;
        }
    }
    
    printf("Huffman编码:\n");
    HuffmanCodes(uniqueChars, uniqueFreq, uniqueCount);
    
    return 0;
}
