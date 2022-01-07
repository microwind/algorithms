package main

import(
  "fmt"
  "strings"
)

/*
 * @str 查找字符串
 * @text 目标内容
 */
func find(str string, text string) int {
  strLen := len(str)
  textLen := strings.Count(text, "") - 1
  var j int
  for i := 0; i < textLen; i++ {
    for j = 0; j < strLen; j++ {
      fmt.Printf("%d %d %c %c \n", i, j, text[i], str[j])
      if text[i + j] != str[j] {
      	// 将目标字符串里的字符逐个与查找字符串比较
      	// 如果有一个字符串不匹配，则从头开始下一轮比较
      	break
      }
    }
    fmt.Print("i:j", i, j)
    
    if j == strLen {
      fmt.Printf("i=%d j=%d\n", i, j)
      // 如果被查找字符串全部找到了，则返回当前下标
      return i
    }

    fmt.Print("\n")
  }
  return -1
}

func find1(str string, text string) int {
  strLen := len(str)
  textLen := strings.Count(text, "") - 1
  i := 0
  j := 0
  for i < textLen && j < strLen {
  	fmt.Printf("%d %d %c %c \n", i, j, text[i], str[j])
  	if text[i] == str[j] {
  	  // 如果逐个都匹配则加1
  	  i++
  	  j++
    } else {
      // 如果不匹配则查找串从0开始，目标文本则重置上一个字符处开始
      i = i - j + 1
      j = 0
    }
  }
  fmt.Printf("i=%d j=%d\n", i, j)
  // 若查找串全部匹配完成则表示找到
  if j == strLen {
  	return i - j
  }
  return -1
}


func find2(str string, text string) int {
  strLen := len(str)
  textLen := strings.Count(text, "") - 1
  var j int
  var i = 0
  for j = 0; j < strLen; {
  	// fmt.Printf("===No. %d=== \n", j)
    for ; i < textLen; {
      fmt.Printf("%d %d %c %c \n", i, j, text[i], str[j])

      if text[i] != str[j] {
        // 将目标字符串里的字符逐个与查找字符串比较
        // 如果有一个字符串不匹配，则从头开始下一轮比较
        i = i - j + 1
        j = 0
      } else {
        // 将目标文本下标置为上一个比较开始处
        i++
        j++
      }
   	  break
    }
    // 如果剩余字数没有查找字符串长则可以终止
    if textLen - i < strLen - j {
      break
    }
  }
  if j == strLen {
     fmt.Printf("i=%d j=%d\n", i, j)
     // 如果被查找字符串全部找到了，则返回当前下标
     return i - j
  }
  return -1
}



// test
func main() {
  fmt.Println("Hello, search start：")
  var result int
  // find() test
  result = find("ABC", "AABABC")
  fmt.Println("find `ABC` in `AABABC`, the index is 3:", result)  // 3
  result = find("AAB", "AAAABC");
  fmt.Println("find `AAB` in `AAAABC`, the index is 2:", result) // 2
  result = find("ABC", "AABAC");
  fmt.Println("find `ABC` in `AABAC`, the index is -1:", result) // -1

  // find1() test
  result = find1("ABC", "AABABC")
  fmt.Println("find1 `ABC` in `AABABC`, the index is 3:", result)  // 3
  result = find1("AAB", "AAAABC");
  fmt.Println("find1 `AAB` in `AAAABC`, the index is 2:", result) // 2
  result = find1("ABC", "AABAC");
  fmt.Println("find1 `ABC` in `AABAC`, the index is -1:", result) // -1

  // find2() test
  result = find2("ABC", "AABABC")
  fmt.Println("find2 `ABC` in `AABABC`, the index is 3:", result)  // 3
  result = find2("AAB", "AAAABC");
  fmt.Println("find2 `AAB` in `AAAABC`, the index is 2:", result) // 2
  result = find2("ABC", "AABAC");
  fmt.Println("find2 `ABC` in `AABAC`, the index is -1:", result) // -1
  result = find2("ABC", "AABABAABCAA");
  fmt.Println("find2 `ABC` in `AABABAABCAA`, the index is 6:", result) // 6
  result = find2("BAABA", "BAABBABBBAABAABB");
  fmt.Println("find2 `BAABA` in `BAABBABBBAABAABB`, the index is 8:", result) // 8
}

/* Test
jarry@jarrys-MacBook-Pro nativesearch % go version
go version go1.15 darwin/amd64
go run string_search.go
*/