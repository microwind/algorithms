package main

import (
  "fmt"
  "hash/fnv"
)

const INITIAL_CAPACITY = 10
const LOAD_FACTOR = 0.75

type Entry struct {
  Key   string
  Value int
  Next  *Entry
}

type HashMap struct {
  Table    []*Entry
  Size     int
  Capacity int
}

func hash(key string, capacity int) int {
  h := fnv.New32a()
  h.Write([]byte(key))
  return int(h.Sum32()) % capacity
}

func initHashMap() *HashMap {
  mapObj := &HashMap{
    Capacity: INITIAL_CAPACITY,
    Table:    make([]*Entry, INITIAL_CAPACITY),
  }
  return mapObj
}

func resizeMap(mapObj *HashMap) {
  newCapacity := mapObj.Capacity * 2
  newTable := make([]*Entry, newCapacity)

  for i := 0; i < mapObj.Capacity; i++ {
    entry := mapObj.Table[i]
    for entry != nil {
      newIndex := hash(entry.Key, newCapacity)
      newEntry := &Entry{
        Key:   entry.Key,
        Value: entry.Value,
        Next:  newTable[newIndex],
      }
      newTable[newIndex] = newEntry
      entry = entry.Next
    }
  }

  mapObj.Table = newTable
  mapObj.Capacity = newCapacity
}

func put(mapObj *HashMap, key string, value int) {
  if float64(mapObj.Size)/float64(mapObj.Capacity) > LOAD_FACTOR {
    resizeMap(mapObj)
  }

  index := hash(key, mapObj.Capacity)
  entry := mapObj.Table[index]

  for entry != nil {
    if entry.Key == key {
      entry.Value = value
      return
    }
    entry = entry.Next
  }

  newEntry := &Entry{
    Key:   key,
    Value: value,
    Next:  mapObj.Table[index],
  }
  mapObj.Table[index] = newEntry
  mapObj.Size++
}

func get(mapObj *HashMap, key string) int {
  index := hash(key, mapObj.Capacity)
  entry := mapObj.Table[index]

  for entry != nil {
    if entry.Key == key {
      return entry.Value
    }
    entry = entry.Next
  }
  return -1
}

func delete(mapObj *HashMap, key string) {
  index := hash(key, mapObj.Capacity)
  entry := mapObj.Table[index]
  var prev *Entry

  for entry != nil {
    if entry.Key == key {
      if prev != nil {
        prev.Next = entry.Next
      } else {
        mapObj.Table[index] = entry.Next
      }
      mapObj.Size--
      return
    }
    prev = entry
    entry = entry.Next
  }
}

func freeHashMap(mapObj *HashMap) {
  for i := 0; i < mapObj.Capacity; i++ {
    entry := mapObj.Table[i]
    for entry != nil {
      next := entry.Next
      entry = next
    }
  }
}

func main() {
  mapObj := initHashMap()

  put(mapObj, "apple", 10)
  put(mapObj, "banana", 20)
  put(mapObj, "orange", 30)

  fmt.Println("apple:", get(mapObj, "apple"))
  fmt.Println("banana:", get(mapObj, "banana"))
  fmt.Println("grape:", get(mapObj, "grape"))

  delete(mapObj, "banana")
  fmt.Println("banana after delete:", get(mapObj, "banana"))

  freeHashMap(mapObj)
}

/*
jarry@MacBook-Pro hash % go run hash_map.go
apple: 10
banana: 20
grape: -1
banana after delete: -1
*/
