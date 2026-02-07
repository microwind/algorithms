
/**
 * @param pattern 查找串
 * @text 目标内容
 */
int find(String pattern, String text) {
  for (int i = 0; i < text.length; i++) {
    int j;
    // 外层是要查找的文本内容，内层是查找条目
    for (j = 0; j < pattern.length; j++) {
      // 将外层的项逐个与内层的项比较，如果相等则各移动一位继续比较
      // 如果遇到不相等，则从外层的第2项作为起始项继续循环查找
      if (text[i + j] != pattern[j]) {
        break;
      }
    }
    // 当查找条目全部匹配后直接返回外层的循环下标
    if (j == pattern.length) {
      return i;
    }
  }
  return -1;
}

int find1(String pattern, String text) {
  int i = 0;
  int j = 0;
  // 当查找项和目标内容都没有遍历完成时，循环继续
  while (j < pattern.length && i < text.length) {
    // 当遇到查找项与目标内容不匹配时，目标内容回退至起始+1的位置，查找项则从头开始
    if (pattern[j] != text[i]) {
      i = i - j + 1;
      j = 0;
    } else {
      // 目标内容和查找项逐个对比，如果相同，则继续下一个
      i++;
      j++;
    }
    if (j == pattern.length) {
      return i - j;
    }
  }
  return -1;
}

int find2(String pattern, String text) {
  int i = 0;
  int j = 0;
  print("find2");
  // 以查找项为外循环，目标内容为内循环
  for (; j < pattern.length;) {
    for (; i < text.length;) {
      // 两两逐个对比，当遇到不相同时
      if (pattern[j] != text[i]) {
        // 目标内容回退至上一个位置+1，查找项则从头开始
        i = i - j + 1;
        j = 0;
      } else {
        // 如果比较相同，则继续下一个比较
        i++;
        j++;
      }
      // 每轮只能比一次
      break;
    }
    // 如果查找项剩下的数量比目标内容还长时可以跳出循环
    if (pattern.length - j > text.length - i) {
      break;
    }
    // 如果全部项匹配则返回目标内容当前起始下标
    if (j == pattern.length) {
      return i - j;
    }
  }
  return -1;
}

void main() {
  print("Hello, search start：");
  int result = -1;
  
  // find() test
  result = find("ABC", "AABABC");
  print("find ABC in AABABC. the index is 3: $result");  // 3
  result = find("AABC", "AAAABC");
  print("find `AABC` in `AAAABC` the index is 2: $result"); // 2
  result = find("ABC", "AABAC");
  print("find `ABC` in `AABAC` the index is -1: $result"); // -1

  // find1() test
  result = find1("ABC", "AABABC");
  print("find1 ABC in AABABC. the index is 3: $result");  // 3
  result = find1("AABC", "AAAABC");
  print("find1 `AABC` in `AAAABC` the index is 2: $result"); // 2
  result = find1("ABC", "AABAC");
  print("find1 `ABC` in `AABAC` the index is -1: $result"); // -


  // find2() test
  result = find2("ABC", "AABABC");
  print("find2 ABC in AABABC. the index is 3: $result");  // 3
  result = find2("AABC", "AAAABC");
  print("find2 `AABC` in `AAAABC` the index is 2: $result"); // 2
  result = find2("ABC", "AABAC");
  print("find2 `ABC` in `AABAC` the index is -1: $result"); // -1
  result = find2("ABBCD", "ABBCAABCAABBCDCD");
  print("find2 `ABC` in `AABAC` the index is 9: $result"); // 9
}

/* Test
jarry@jarrys-MacBook-Pro nativesearch % dart --version
Dart SDK version: 2.14.1 (stable) (Wed Sep 8 13:33:08 2021 +0200) on "macos_x64"
jarry@jarrys-MacBook-Pro nativesearch % dart string_search.dart 
*/