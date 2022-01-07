
/**
 * @param pattern 查找串
 * @text 目标内容
 */
int find(String pattern, String text) {
  for (int i = 0; i < text.length; i++) {
    int j;
    for (j = 0; j < pattern.length; j++) {
      if (text[i + j] != pattern[j]) {
        break;
      }
    }
    if (j == pattern.length) {
      return i;
    }
  }
  return -1;
}

int find1(String pattern, String text) {
  int i = 0;
  int j = 0;
  while (j < pattern.length && i < text.length) {
    if (pattern[j] != text[i]) {
      i = i - j + 1;
      j = 0;
    } else {
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
  for (; j < pattern.length;) {
    for (; i < text.length;) {
      if (pattern[j] != text[i]) {
        i = i - j + 1;
        j = 0;
      } else {
        i++;
        j++;
      }
      break;
    }
    if (pattern.length - j > text.length - i) {
      break;
    }
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