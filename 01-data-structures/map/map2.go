package main

import (
  "fmt"
)

// 定义键值对结构体
type Entry struct {
  key   string
  value int
}

// 定义 HashMap 结构体
type Map struct {
  entries  []Entry
  indexMap map[string]int
  size     int
  capacity int
}

// 初始化 HashMap
func (m *Map) init() {
  m.size = 0
  m.capacity = 10
  m.entries = make([]Entry, m.capacity)
  m.indexMap = make(map[string]int)
}

// 扩容
func (m *Map) resizeMap() {
  m.capacity *= 2
}

// 插入键值对
func (m *Map) put(key string, value int) {
  if _, exists := m.indexMap[key]; exists {
    // 更新值
    index := m.indexMap[key]
    m.entries[index].value = value
  } else {
    // 如果容量已满，扩容
    if m.size >= m.capacity {
      m.resizeMap()
    }

    // 插入新键值对
    m.entries[m.size] = Entry{key, value}
    m.indexMap[key] = m.size
    m.size++
  }
}

// 查找键
func (m *Map) get(key string) int {
  if index, exists := m.indexMap[key]; exists {
    return m.entries[index].value
  }
  return -1 // 未找到
}

// 删除键
func (m *Map) delete(key string) {
  if index, exists := m.indexMap[key]; exists {
    // 从数组中移除
    m.entries = append(m.entries[:index], m.entries[index+1:]...)
    delete(m.indexMap, key)
    // 更新索引
    for i := index; i < m.size-1; i++ {
      m.indexMap[m.entries[i].key] = i
    }
    m.size--
  }
}

// 判断键是否存在
func (m *Map) has(key string) bool {
  _, exists := m.indexMap[key]
  return exists
}

// 获取键值对个数
func (m *Map) getSize() int {
  return m.size
}

// 清空所有数据
func (m *Map) clear() {
  m.entries = nil
  m.indexMap = make(map[string]int)
  m.size = 0
}

// 遍历所有键值对
func (m *Map) forEach(callback func(value int, key string)) {
  for _, entry := range m.entries {
    callback(entry.value, entry.key)
  }
}

func printEntry(value int, key string) {
  fmt.Printf("%s: %d\n", key, value)
}

func main() {
  var mapObj Map
  mapObj.init()

  mapObj.put("apple", 10)
  mapObj.put("banana", 20)
  mapObj.put("orange", 30)

  fmt.Println("apple:", mapObj.get("apple"))
  fmt.Println("banana:", mapObj.get("banana"))
  fmt.Println("grape:", mapObj.get("grape"))

  mapObj.delete("banana")
  fmt.Println("banana after delete:", mapObj.get("banana"))

  mapObj.forEach(printEntry)

  mapObj.clear()
}

/*
jarry@MacBook-Pro map % go run map2.go
apple: 10
banana: 20
grape: -1
banana after delete: -1
apple: 10
orange: 30
: 0
: 0
: 0
: 0
: 0
: 0
: 0
*/
