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
  jarry@jarrys-MacBook-Pro factor % dart factor.dart 
  2 * 2 * 2 * 3 * 5
*/