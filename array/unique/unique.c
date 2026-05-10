/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 2.0
 *
 * 数组去重算法 - C 实现，20 种不同思路
 *
 * 算法原理：扫描数组，保留每个值的首次出现，丢弃后续重复
 *
 * 20 种实现按 5 类组织：
 * - 第1类 基础循环（方法1-5）：纯下标遍历，O(n²)
 * - 第2类 排序后去重（方法6-9）：相同元素相邻后扫描，O(n log n)
 * - 第3类 哈希结构（方法10-14）：键唯一性 O(1) 查询
 * - 第4类 位图与位运算（方法15-17）：极致空间效率
 * - 第5类 泛型与高级技巧（方法18-20）：void* / 字符串 / 结构体按字段
 *
 * C 没有内置 String、HashMap、泛型，所有动态结构都要自己 malloc/free。
 * 这反而让你看清去重算法的"骨架"——同一个问题从 5 个角度切入。
 *
 * 应用场景：数据清洗、统计唯一值、数据库去重
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

/* ==================== 工具函数 ==================== */

/**
 * 打印整型数组（教学用）
 */
static void print_array(const int *arr, int len)
{
  printf("{");
  for (int i = 0; i < len; i++)
  {
    printf(" %d", arr[i]);
    if (i < len - 1) printf(",");
  }
  printf(" }");
}

/**
 * qsort 比较函数：防溢出写法
 * 注意不要写成 `*(int*)a - *(int*)b`——两值符号相反时 int 溢出会出错
 */
static int int_cmp(const void *a, const void *b)
{
  int ia = *(const int *)a;
  int ib = *(const int *)b;
  return (ia > ib) - (ia < ib);
}

/* ==================== 第1类：基础循环（方法1-5） ====================
 *
 * 策略：不依赖任何额外数据结构，纯靠下标、嵌套循环完成判重。
 * 每一步判重都是 O(n)，整体 O(n²)。
 * 适用：教学、嵌入式、内存极度敏感的场景。
 */

/**
 * 方法1：双循环 i == j 索引比较法
 * 核心原理：对每个元素向前查找；若 i == j 表示前面没有相同值，是首次出现
 *
 * 时间复杂度：O(n²)
 * 空间复杂度：O(n) 结果数组
 *
 * @param arr    输入数组（不修改）
 * @param len    数组长度
 * @param result 结果缓冲区（调用者分配，至少 len 长度）
 * @return 去重后的实际长度
 */
int unique1(const int *arr, int len, int *result)
{
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      if (arr[i] == arr[j])
      {
        /* i == j 表示前面没有相同值，是首次出现 */
        if (i == j) result[idx++] = arr[i];
        break;
      }
    }
  }
  return idx;
}

/**
 * 方法2：标记数组 frequent 法
 * 核心原理：给每个元素一个频次标记，frequent[i]==1 表示此前未出现
 *
 * 时间复杂度：O(n²)
 * 空间复杂度：O(n) 频次数组 + 结果数组
 */
int unique2(const int *arr, int len, int *result)
{
  /* malloc 替代 VLA，更稳健（VLA 大数组易爆栈，且 MSVC 支持有限） */
  int *freq = (int *)malloc((size_t)len * sizeof(int));
  if (!freq) return -1;
  freq[0] = 1;
  for (int i = 1; i < len; i++)
  {
    freq[i] = 1;
    // 遍历前面的元素，判断是否重复
    for (int j = 0; j < i; j++)
    {
      if (arr[i] == arr[j]) { freq[i]++; break; }
    }
  }
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    if (freq[i] == 1) result[idx++] = arr[i];
  }
  free(freq);
  return idx;
}

/**
 * 方法3：新建数组 + contains 检查
 * 核心原理：维护结果数组，遍历时线性查找判重
 * 这是最直观的"新手版"
 *
 * 时间复杂度：O(n²) - 每次 contains 是 O(n)
 * 空间复杂度：O(n)
 */
int unique3(const int *arr, int len, int *result)
{
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    int found = 0;
    /* 遍历结果数组，判断是否已存在当前元素 */
    for (int j = 0; j < idx; j++)
    {
      if (result[j] == arr[i]) { found = 1; break; }
    }
    if (!found) result[idx++] = arr[i];
  }
  return idx;
}

/**
 * 方法4：原地从前往后删除（memmove 风格）
 * 核心原理：遇到重复就把后面元素整体前移
 * 注意：会修改原数组，函数返回新长度
 *
 * 时间复杂度：O(n²) - 每次 memmove 是 O(n)
 * 空间复杂度：O(1) - 原地修改
 */
int unique4(int *arr, int len)
{
  for (int i = 0; i < len; i++)
  {
    for (int j = i + 1; j < len; )
    {
      if (arr[i] == arr[j])
      {
        /* 把 [j+1, len) 整体前移一位 */
        memmove(&arr[j], &arr[j + 1], (size_t)(len - j - 1) * sizeof(int));
        len--;
        /* j 不前进，因为新的 arr[j] 是原来的 arr[j+1] */
      }
      else
      {
        j++;
      }
    }
  }
  return len;
}

/**
 * 方法5：原地从后往前删除
 * 核心原理：倒序遍历，与左侧任一相同则删除自身
 * 倒序的好处：删除点之后元素已处理，不影响下标
 *
 * 时间复杂度：O(n²)
 * 空间复杂度：O(1)
 */
int unique5(int *arr, int len)
{
  for (int i = len - 1; i > 0; i--)
  {
    for (int j = 0; j < i; j++)
    {
      if (arr[i] == arr[j])
      {
        memmove(&arr[i], &arr[i + 1], (size_t)(len - i - 1) * sizeof(int));
        len--;
        break;
      }
    }
  }
  return len;
}

/* ==================== 第2类：排序后去重（方法6-9） ====================
 *
 * 策略：先 qsort 让相同元素相邻，再扫一遍删除相邻相同项。
 * 复杂度由排序决定，O(n log n)。
 * 优点：不需要额外哈希结构。
 * 缺点：会破坏原顺序，要求元素可比较。
 */

/**
 * 方法6：qsort + 相邻去重（新数组）
 * 排序后扫描一遍，与前一项不同的才追加到结果
 *
 * 时间复杂度：O(n log n) - 排序主导
 * 空间复杂度：O(n) - 结果数组
 */
int unique6(int *arr, int len, int *result)
{
  if (len == 0) return 0;
  qsort(arr, (size_t)len, sizeof(int), int_cmp);
  int idx = 0;
  result[idx++] = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] != arr[i - 1]) result[idx++] = arr[i];
  }
  return idx;
}

/**
 * 方法7：qsort + 双指针（LeetCode 26 经典解法）
 * 核心原理：原地双指针，slow 指向最后唯一元素，fast 扫描
 * 优势：O(1) 额外空间
 *
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1)
 */
int unique7(int *arr, int len)
{
  if (len == 0) return 0;
  qsort(arr, (size_t)len, sizeof(int), int_cmp);
  int slow = 0;
  for (int fast = 1; fast < len; fast++)
  {
    if (arr[fast] != arr[slow])
    {
      arr[++slow] = arr[fast];
    }
  }
  return slow + 1;
}

/**
 * 方法8：qsort + memmove 原地
 * 排序后从后往前扫，相邻相同就 memmove 删除
 * 与方法7 等价但写法不同，体现 C 中"删除元素 = memmove"的惯用法
 *
 * 时间复杂度：O(n log n + n²) - memmove 累积成 O(n²)
 * 空间复杂度：O(1)
 */
int unique8(int *arr, int len)
{
  if (len == 0) return 0;
  qsort(arr, (size_t)len, sizeof(int), int_cmp);
  for (int i = len - 1; i > 0; i--)
  {
    if (arr[i] == arr[i - 1])
    {
      memmove(&arr[i], &arr[i + 1], (size_t)(len - i - 1) * sizeof(int));
      len--;
    }
  }
  return len;
}

/**
 * 方法9：自实现快排 + 去重（教学用）
 * 不用 qsort，自己写快排展示算法本质
 * 工程上没必要——qsort 是高度优化的 quicksort/mergesort 混合实现
 */
static void quick_sort(int *a, int lo, int hi)
{
  if (lo >= hi) return;
  int pivot = a[(lo + hi) / 2];
  int i = lo, j = hi;
  while (i <= j)
  {
    while (a[i] < pivot) i++;
    while (a[j] > pivot) j--;
    if (i <= j)
    {
      int t = a[i]; a[i] = a[j]; a[j] = t;
      i++; j--;
    }
  }
  quick_sort(a, lo, j);
  quick_sort(a, i, hi);
}

int unique9(int *arr, int len)
{
  if (len == 0) return 0;
  quick_sort(arr, 0, len - 1);
  int slow = 0;
  for (int fast = 1; fast < len; fast++)
  {
    if (arr[fast] != arr[slow]) arr[++slow] = arr[fast];
  }
  return slow + 1;
}

/* ==================== 第3类：哈希结构（方法10-14） ====================
 *
 * 策略：用键唯一性 O(1) 判重。
 * C 没有内置 HashMap，要么自己写、要么用 uthash/GLib 等第三方库。
 * 手写哈希表是 C 程序员必经之路。
 */

/**
 * 方法10：计数数组（仅适合小范围非负整数）
 * 核心原理：把值当下标，count[v] 累加频次
 * 优势：O(n + V) 极快，V 是值域大小
 * 缺点：值域大时浪费空间；负数需偏移
 *
 * 时间复杂度：O(n + V)
 * 空间复杂度：O(V)
 *
 * @param arr     输入数组（非负）
 * @param len     长度
 * @param max_val 已知的最大值
 * @param result  结果数组
 * @return 去重后长度（保序）
 */
int unique10(const int *arr, int len, int max_val, int *result)
{
  /* 假设非负整数；负数需先偏移 */
  char *seen = (char *)calloc((size_t)max_val + 1, sizeof(char));
  if (!seen) return -1;
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    if (arr[i] >= 0 && arr[i] <= max_val && !seen[arr[i]])
    {
      seen[arr[i]] = 1;
      result[idx++] = arr[i];
    }
  }
  free(seen);
  return idx;
}

/* ---- 方法11/14 共用：开链法哈希集合 ---- */

typedef struct HashNode
{
  int key;
  int count;             /* 频次（用于方法14；方法11 不读） */
  struct HashNode *next;
} HashNode;

#define HASH_SIZE 1024

typedef struct
{
  HashNode *buckets[HASH_SIZE];
} HashSet;

/**
 * 简单乘法哈希；工程级请用 wymhash/xxhash
 * 对负数也能工作（unsigned 转换后保留位模式）
 */
static unsigned hash_int(int k)
{
  return (unsigned)((unsigned)k * 2654435761u) % HASH_SIZE;
}

static HashNode *hashset_find(HashSet *s, int key)
{
  unsigned h = hash_int(key);
  for (HashNode *p = s->buckets[h]; p; p = p->next)
  {
    if (p->key == key) return p;
  }
  return NULL;
}

/**
 * 已存在返回 0；新插入返回 1
 */
static int hashset_add(HashSet *s, int key)
{
  if (hashset_find(s, key)) return 0;
  unsigned h = hash_int(key);
  HashNode *node = (HashNode *)malloc(sizeof(HashNode));
  if (!node) return -1;
  node->key = key;
  node->count = 1;
  node->next = s->buckets[h];
  s->buckets[h] = node;
  return 1;
}

static void hashset_free(HashSet *s)
{
  for (int i = 0; i < HASH_SIZE; i++)
  {
    HashNode *p = s->buckets[i];
    while (p) { HashNode *n = p->next; free(p); p = n; }
    s->buckets[i] = NULL;
  }
}

/**
 * 方法11：开链法哈希表（自实现）
 * 核心原理：每个桶是链表头，碰撞时链表追加
 * 是 C 实现哈希表的最经典方式
 *
 * 时间复杂度：O(n) 平均
 * 空间复杂度：O(n)
 */
int unique11(const int *arr, int len, int *result)
{
  HashSet set = {{0}};
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    if (hashset_add(&set, arr[i]) == 1) result[idx++] = arr[i];
  }
  hashset_free(&set);
  return idx;
}

/**
 * 方法12：开放地址法哈希表（线性探测）
 * 核心原理：碰撞时探测下一个槽位，无需链表节点
 * 优势：缓存友好，无 malloc 节点开销
 * 缺点：删除复杂、负载因子敏感（这里只 add 不 remove，简单可用）
 *
 * 时间复杂度：O(n) 平均
 * 空间复杂度：O(n)
 */
typedef struct
{
  int *keys;
  char *used;
  int cap;
} OAHashSet;

/**
 * cap 向上取到 2 的幂（便于线性探测求模等价为按位与，且不易聚集）
 */
static OAHashSet *oahs_new(int cap_hint)
{
  int cap = 16;
  while (cap < cap_hint) cap *= 2;
  OAHashSet *s = (OAHashSet *)malloc(sizeof(*s));
  s->cap = cap;
  s->keys = (int *)malloc((size_t)cap * sizeof(int));
  s->used = (char *)calloc((size_t)cap, sizeof(char));
  return s;
}

static int oahs_add(OAHashSet *s, int key)
{
  unsigned h = (unsigned)((unsigned)key * 2654435761u) % (unsigned)s->cap;
  while (s->used[h])
  {
    if (s->keys[h] == key) return 0;  /* 已存在 */
    h = (h + 1) % (unsigned)s->cap;   /* 线性探测下一个槽 */
  }
  s->keys[h] = key;
  s->used[h] = 1;
  return 1;
}

static void oahs_free(OAHashSet *s)
{
  free(s->keys); free(s->used); free(s);
}

int unique12(const int *arr, int len, int *result)
{
  /* 容量 ≥ 2 × len，保证负载因子 ≤ 0.5 */
  OAHashSet *s = oahs_new(len * 2 > 16 ? len * 2 : 16);
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    if (oahs_add(s, arr[i])) result[idx++] = arr[i];
  }
  oahs_free(s);
  return idx;
}

/**
 * 方法13：开放地址法哈希表（三角数探测）
 * 核心原理：探测序列 h, h+1, h+3, h+6, h+10, ...（增量 1,2,3,4,...）
 * 当 cap 为 2 的幂时，三角数序列能遍历所有槽，避免线性探测的"主聚集"
 * 替代第三方 uthash，避免外部依赖
 *
 * 时间复杂度：O(n) 平均
 * 空间复杂度：O(n)
 */
typedef struct
{
  int *keys;
  char *used;
  int cap;
} TriHashSet;

static TriHashSet *tri_new(int cap_hint)
{
  int cap = 16;
  while (cap < cap_hint) cap *= 2;
  TriHashSet *s = (TriHashSet *)malloc(sizeof(*s));
  s->cap = cap;
  s->keys = (int *)malloc((size_t)cap * sizeof(int));
  s->used = (char *)calloc((size_t)cap, sizeof(char));
  return s;
}

static int tri_add(TriHashSet *s, int key)
{
  unsigned h = (unsigned)((unsigned)key * 2654435761u) % (unsigned)s->cap;
  unsigned step = 0;
  while (s->used[h])
  {
    if (s->keys[h] == key) return 0;
    step++;
    h = (h + step) % (unsigned)s->cap;  /* 三角数：增量 1,2,3,... */
  }
  s->keys[h] = key;
  s->used[h] = 1;
  return 1;
}

static void tri_free(TriHashSet *s)
{
  free(s->keys); free(s->used); free(s);
}

int unique13(const int *arr, int len, int *result)
{
  TriHashSet *s = tri_new(len * 2 > 16 ? len * 2 : 16);
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    if (tri_add(s, arr[i])) result[idx++] = arr[i];
  }
  tri_free(s);
  return idx;
}

/**
 * 方法14：哈希表 + 频次统计
 * 核心原理：去重的同时统计每个值的出现次数
 * 工程里"按 id 去重 + 累计金额"等场景的基础
 *
 * 时间复杂度：O(n) 平均
 * 空间复杂度：O(n)
 *
 * @param arr      输入数组
 * @param len      长度
 * @param result   去重后的元素（保序）
 * @param freq_out 与 result 一一对应的频次
 * @return 去重后长度
 */
int unique14(const int *arr, int len, int *result, int *freq_out)
{
  HashSet set = {{0}};
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    HashNode *node = hashset_find(&set, arr[i]);
    if (node)
    {
      node->count++;            /* 已见过：累加频次 */
    }
    else
    {
      hashset_add(&set, arr[i]); /* 新建（count=1） */
      result[idx++] = arr[i];
    }
  }
  /* 输出每个唯一值对应的频次（顺序与 result 一致） */
  for (int i = 0; i < idx; i++)
  {
    HashNode *node = hashset_find(&set, result[i]);
    freq_out[i] = node ? node->count : 0;
  }
  hashset_free(&set);
  return idx;
}

/* ==================== 第4类：位图与位运算（方法15-17） ====================
 *
 * 策略：用每一位代表一个值是否出现过。
 * 整数集合上的极致空间效率——10 亿个 int 只要 128MB。
 * Linux 内核大量使用（cpumask_t、nodemask_t 等）。
 */

/**
 * 方法15：BitSet 位图（uint64_t 数组）
 * 核心原理：每个非负整数用一位标记
 * 推荐场景：海量非负整数（10亿规模仅约 128MB）
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(max_val / 64)
 */
int unique15(const int *arr, int len, int max_val, int *result)
{
  int n_words = max_val / 64 + 1;
  uint64_t *bits = (uint64_t *)calloc((size_t)n_words, sizeof(uint64_t));
  if (!bits) return -1;
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    int v = arr[i];
    if (v < 0 || v > max_val) continue;
    uint64_t mask = (uint64_t)1 << (v % 64);
    if (!(bits[v / 64] & mask))
    {
      bits[v / 64] |= mask;
      result[idx++] = v;
    }
  }
  free(bits);
  return idx;
}

/**
 * 方法16：字符级位图（256 字节字符集）
 * 核心原理：char 数组的 256 个值，固定 32 字节就能完整覆盖
 * 适合 char 数组去重（如 "banana" -> "ban"）
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1) - 固定 32 字节
 */
int unique16_char(const char *arr, int len, char *result)
{
  uint64_t bits[4] = {0, 0, 0, 0};  /* 256 位 = 4 × 64 */
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    unsigned char v = (unsigned char)arr[i];
    uint64_t mask = (uint64_t)1 << (v % 64);
    if (!(bits[v / 64] & mask))
    {
      bits[v / 64] |= mask;
      result[idx++] = arr[i];
    }
  }
  return idx;
}

/**
 * 方法17：单 uint64_t 整数集合（值域 0~63）
 * 核心原理：所有值都在 [0, 63] 时，一个 uint64_t 就够了
 * 优势：极致紧凑，全部位运算
 * 缺点：值域受限
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
int unique17(const int *arr, int len, int *result)
{
  uint64_t seen = 0;
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    if (arr[i] < 0 || arr[i] > 63) continue;
    uint64_t mask = (uint64_t)1 << arr[i];
    if (!(seen & mask))
    {
      seen |= mask;
      result[idx++] = arr[i];
    }
  }
  return idx;
}

/* ==================== 第5类：泛型与高级技巧（方法18-20） ====================
 *
 * 策略：用 void* + cmp_fn 模拟泛型；自定义 cmp 处理字符串和结构体。
 * 这是 C 中"泛型编程"的标准模式（参考 qsort 的 API 设计）。
 */

/**
 * 方法18：通用泛型去重（void* + cmp_fn）
 * 核心原理：模仿 qsort 的 API 设计，通过 void* 和回调支持任意类型
 *
 * 时间复杂度：O(n log n) - qsort 主导
 * 空间复杂度：O(n) - 临时缓冲
 *
 * @param arr       输入数组（不修改）
 * @param len       元素个数
 * @param elem_size 单元素大小
 * @param cmp       比较函数
 * @param result    结果缓冲区
 * @return 去重后长度
 */
int unique18(const void *arr, int len, size_t elem_size,
             int (*cmp)(const void *, const void *),
             void *result)
{
  if (len == 0) return 0;

  /* 复制一份输入，避免修改原数组 */
  void *tmp = malloc((size_t)len * elem_size);
  if (!tmp) return -1;
  memcpy(tmp, arr, (size_t)len * elem_size);

  qsort(tmp, (size_t)len, elem_size, cmp);

  char *r = (char *)result;
  char *t = (char *)tmp;
  memcpy(r, t, elem_size);
  int idx = 1;
  for (int i = 1; i < len; i++)
  {
    char *cur = t + (size_t)i * elem_size;
    char *prev = t + (size_t)(i - 1) * elem_size;
    if (cmp(cur, prev) != 0)
    {
      memcpy(r + (size_t)idx * elem_size, cur, elem_size);
      idx++;
    }
  }

  free(tmp);
  return idx;
}

/**
 * 方法19：字符串数组去重（char**）
 * 核心原理：与方法18 类似，但 cmp 用 strcmp
 * 注意：char** 元素本身是指针，去重的是"字符串内容相同"
 *
 * 时间复杂度：O(n log n × m) - m 是平均字符串长度
 * 空间复杂度：O(n) - 指针副本
 */
static int str_cmp(const void *a, const void *b)
{
  return strcmp(*(const char **)a, *(const char **)b);
}

int unique19(const char **arr, int len, const char **result)
{
  if (len == 0) return 0;
  /* 排序前先复制指针数组（不复制字符串本身） */
  const char **tmp = (const char **)malloc((size_t)len * sizeof(char *));
  if (!tmp) return -1;
  memcpy(tmp, arr, (size_t)len * sizeof(char *));

  qsort(tmp, (size_t)len, sizeof(char *), str_cmp);

  result[0] = tmp[0];
  int idx = 1;
  for (int i = 1; i < len; i++)
  {
    if (strcmp(tmp[i], tmp[i - 1]) != 0)
    {
      result[idx++] = tmp[i];
    }
  }
  free(tmp);
  return idx;
}

/**
 * 方法20：结构体按字段去重
 * 核心原理：自定义 cmp 函数从结构体提取键
 * 这是工程里最常见的需求："按 user_id 去重"
 *
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1) - 原地排序
 */
typedef struct
{
  int id;
  char name[32];
  double score;
} User;

static int user_id_cmp(const void *a, const void *b)
{
  int ia = ((const User *)a)->id;
  int ib = ((const User *)b)->id;
  return (ia > ib) - (ia < ib);
}

int unique20(User *arr, int len, User *result)
{
  if (len == 0) return 0;
  qsort(arr, (size_t)len, sizeof(User), user_id_cmp);
  result[0] = arr[0];
  int idx = 1;
  for (int i = 1; i < len; i++)
  {
    if (arr[i].id != arr[i - 1].id)
    {
      result[idx++] = arr[i];
    }
  }
  return idx;
}

/* ==================== main 函数 ==================== */

/**
 * 主函数：测试 20 种数组去重方法
 *
 * 测试数据：{1, 3, -1, 1, 2, 2, 4, 2, 2, -1}
 * 包含重复元素：1×2、-1×2、2×4、3×1、4×1
 * 期望保序结果：{1, 3, -1, 2, 4}
 * 期望排序结果：{-1, 1, 2, 3, 4}
 */
int main(void)
{
  int base[] = {1, 3, -1, 1, 2, 2, 4, 2, 2, -1};
  int len = (int)(sizeof(base) / sizeof(base[0]));
  int buf[64];

  printf("base: ");
  print_array(base, len);
  printf("\n\n");

  /* ---- 第1类：基础循环（方法1-5），保序 ---- */
  printf("---- 第1类：基础循环（O(n²)，保序） ----\n");

  int n;
  n = unique1(base, len, buf);
  printf("unique1  (双循环 i==j):       ");
  print_array(buf, n);
  printf("\n");

  n = unique2(base, len, buf);
  printf("unique2  (frequent 标记):     ");
  print_array(buf, n);
  printf("\n");

  n = unique3(base, len, buf);
  printf("unique3  (contains 检查):     ");
  print_array(buf, n);
  printf("\n");

  int tmp4[16];
  memcpy(tmp4, base, sizeof(base));
  n = unique4(tmp4, len);
  printf("unique4  (原地正向删除):      ");
  print_array(tmp4, n);
  printf("\n");

  int tmp5[16];
  memcpy(tmp5, base, sizeof(base));
  n = unique5(tmp5, len);
  printf("unique5  (原地反向删除):      ");
  print_array(tmp5, n);
  printf("\n\n");

  /* ---- 第2类：排序后去重（方法6-9），输出升序 ---- */
  printf("---- 第2类：排序后去重（O(n log n)，输出升序） ----\n");

  int tmp6[16];
  memcpy(tmp6, base, sizeof(base));
  n = unique6(tmp6, len, buf);
  printf("unique6  (qsort+相邻去重):    ");
  print_array(buf, n);
  printf("\n");

  int tmp7[16];
  memcpy(tmp7, base, sizeof(base));
  n = unique7(tmp7, len);
  printf("unique7  (qsort+双指针):      ");
  print_array(tmp7, n);
  printf("\n");

  int tmp8[16];
  memcpy(tmp8, base, sizeof(base));
  n = unique8(tmp8, len);
  printf("unique8  (qsort+memmove):     ");
  print_array(tmp8, n);
  printf("\n");

  int tmp9[16];
  memcpy(tmp9, base, sizeof(base));
  n = unique9(tmp9, len);
  printf("unique9  (自实现快排+双指针): ");
  print_array(tmp9, n);
  printf("\n\n");

  /* ---- 第3类：哈希结构（方法10-14），保序 ---- */
  printf("---- 第3类：哈希结构（O(n)，保序） ----\n");

  /* 方法10/15/17 仅支持非负值，用一组非负数据 */
  int pos_arr[] = {1, 3, 1, 2, 2, 4, 2, 2};
  int pos_len = (int)(sizeof(pos_arr) / sizeof(pos_arr[0]));

  n = unique10(pos_arr, pos_len, 4, buf);
  printf("unique10 (计数数组 V≤4):      ");
  print_array(buf, n);
  printf("  [输入: ");
  print_array(pos_arr, pos_len);
  printf("]\n");

  n = unique11(base, len, buf);
  printf("unique11 (开链哈希表):        ");
  print_array(buf, n);
  printf("\n");

  n = unique12(base, len, buf);
  printf("unique12 (开放地址-线性探测): ");
  print_array(buf, n);
  printf("\n");

  n = unique13(base, len, buf);
  printf("unique13 (开放地址-三角探测): ");
  print_array(buf, n);
  printf("\n");

  int freq_buf[64];
  n = unique14(base, len, buf, freq_buf);
  printf("unique14 (哈希+频次统计):     ");
  print_array(buf, n);
  printf("  freq=");
  print_array(freq_buf, n);
  printf("\n\n");

  /* ---- 第4类：位图与位运算（方法15-17） ---- */
  printf("---- 第4类：位图与位运算（O(n)） ----\n");

  n = unique15(pos_arr, pos_len, 4, buf);
  printf("unique15 (BitSet uint64[]):   ");
  print_array(buf, n);
  printf("  [输入: ");
  print_array(pos_arr, pos_len);
  printf("]\n");

  /* 方法16 用字符数据演示 */
  const char *cstr = "banana";
  char cresult[8];
  n = unique16_char(cstr, (int)strlen(cstr), cresult);
  printf("unique16 (char 位图 256-bit): \"%s\" -> \"", cstr);
  for (int i = 0; i < n; i++) putchar(cresult[i]);
  printf("\"\n");

  n = unique17(pos_arr, pos_len, buf);
  printf("unique17 (单 uint64 [0,63]):  ");
  print_array(buf, n);
  printf("  [输入: ");
  print_array(pos_arr, pos_len);
  printf("]\n\n");

  /* ---- 第5类：泛型与高级技巧（方法18-20） ---- */
  printf("---- 第5类：泛型与高级技巧 ----\n");

  /* 方法18：void*+cmp 通用版（用 int 演示） */
  n = unique18(base, len, sizeof(int), int_cmp, buf);
  printf("unique18 (void*+cmp 泛型):    ");
  print_array(buf, n);
  printf("\n");

  /* 方法19：字符串数组 */
  const char *strs[] = {"apple", "banana", "apple", "cherry", "banana"};
  const char *sresult[5];
  int sn = unique19(strs, 5, sresult);
  printf("unique19 (字符串数组):        { ");
  for (int i = 0; i < sn; i++)
  {
    printf("\"%s\"%s", sresult[i], i < sn - 1 ? ", " : "");
  }
  printf(" }\n");

  /* 方法20：结构体按 id 字段 */
  User users[] = {
    {1, "Alice",   95.0},
    {2, "Bob",     88.5},
    {1, "Alicia",  90.0},
    {3, "Carol",   77.0},
    {2, "Bobby",   85.0}
  };
  User uresult[5];
  int un = unique20(users, 5, uresult);
  printf("unique20 (struct 按 id):      { ");
  for (int i = 0; i < un; i++)
  {
    printf("{id=%d, name=\"%s\"}%s",
           uresult[i].id, uresult[i].name, i < un - 1 ? ", " : "");
  }
  printf(" }\n");

  return 0;
}

/*
 * 编译运行：
 *   gcc unique.c -o /tmp/unique && /tmp/unique
 *
 * 预期输出（已实测）：
 *
 * base: { 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 }
 *
 * ---- 第1类：基础循环（O(n²)，保序） ----
 * unique1  (双循环 i==j):       { 1, 3, -1, 2, 4 }
 * unique2  (frequent 标记):     { 1, 3, -1, 2, 4 }
 * unique3  (contains 检查):     { 1, 3, -1, 2, 4 }
 * unique4  (原地正向删除):      { 1, 3, -1, 2, 4 }
 * unique5  (原地反向删除):      { 1, 3, -1, 2, 4 }
 *
 * ---- 第2类：排序后去重（O(n log n)，输出升序） ----
 * unique6  (qsort+相邻去重):    { -1, 1, 2, 3, 4 }
 * unique7  (qsort+双指针):      { -1, 1, 2, 3, 4 }
 * unique8  (qsort+memmove):     { -1, 1, 2, 3, 4 }
 * unique9  (自实现快排+双指针): { -1, 1, 2, 3, 4 }
 *
 * ---- 第3类：哈希结构（O(n)，保序） ----
 * unique10 (计数数组 V≤4):      { 1, 3, 2, 4 }  [输入: { 1, 3, 1, 2, 2, 4, 2, 2 }]
 * unique11 (开链哈希表):        { 1, 3, -1, 2, 4 }
 * unique12 (开放地址-线性探测): { 1, 3, -1, 2, 4 }
 * unique13 (开放地址-三角探测): { 1, 3, -1, 2, 4 }
 * unique14 (哈希+频次统计):     { 1, 3, -1, 2, 4 }  freq={ 2, 1, 2, 4, 1 }
 *
 * ---- 第4类：位图与位运算（O(n)） ----
 * unique15 (BitSet uint64[]):   { 1, 3, 2, 4 }  [输入: { 1, 3, 1, 2, 2, 4, 2, 2 }]
 * unique16 (char 位图 256-bit): "banana" -> "ban"
 * unique17 (单 uint64 [0,63]):  { 1, 3, 2, 4 }  [输入: { 1, 3, 1, 2, 2, 4, 2, 2 }]
 *
 * ---- 第5类：泛型与高级技巧 ----
 * unique18 (void*+cmp 泛型):    { -1, 1, 2, 3, 4 }
 * unique19 (字符串数组):        { "apple", "banana", "cherry" }
 * unique20 (struct 按 id):      { {id=1, name="Alice"}, {id=2, name="Bob"}, {id=3, name="Carol"} }
 */
