/**
 * @desc
 * 质因数分解dart语言示例
 */
List factorize(int num) {
  // List<int> result = [];
  var result = [];
  int i  = 2;
  while (i * i <= num) {
    while (num % i == 0) {
      num = num ~/ i;
      result.add(i);
    }
    i++;
  }
  if (num > 1) {
    result.add(num);
  }
  return result;
}

void main() {
  var result = factorize(120);
  print(result.join(' * '));
}

/**
  jarry@jarrys-MacBook-Pro factor % dart --version
  Dart SDK version: 2.10.2 on "macos_x64"
jarry@jarrys-MacBook-Pro bubblesort % dart bubble_sort.dart
bubble sort:
no:0
0 * 0
1 * 0
2 * 0
3 * 0
no:1
0 * 1
1 * 1
2 * 1
no:2
0 * 2
1 * 2
no:3
0 * 3
no:4
[-4, -0.45, 2.5, 3, 10]
bubble sort2:
no:0
4 * 0
3 * 0
2 * 0
1 * 0
no:1
4 * 1
3 * 1
2 * 1
[10, 3, 2.5, -0.45, -4]
*/