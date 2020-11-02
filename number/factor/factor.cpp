/**
 * @desc
 * 质因数分解c++语言示例
 */
#include <iostream>
#include <memory.h>

int *factorize(int num, int len) {
  int *result = (int *)malloc(len * sizeof(int));
  int i = 2;
  int result_idx = 0;
  while (i * i <= num) {
    while (num % i == 0) {
      result[result_idx] = i;
      num /= i;
      result_idx++;
    }
    i++;
  }
  if (num > 1) {
    result[result_idx]  = num;
  }
  return result;
}
int main() {

  int num = 1796;
  int len = num / 2;
  int *result = factorize(num, len);
  std::cout << "the number is " << num << "\n";
  for  (int i = 0; i < len; i++) {
    if (result[i] <= 0) {
      break;
    }
    if (i != 0) {
      printf(" *");
    }
    printf(" %d", result[i]);
  }
  std::cout << " = " << num << std::endl;
}

/* 
  jarry@jarrys-MacBook-Pro factor % g++ --version                      
  Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/4.2.1
  Apple clang version 12.0.0 (clang-1200.0.32.21)
  Target: x86_64-apple-darwin19.6.0
  Thread model: posix
  InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
  jarry@jarrys-MacBook-Pro factor % g++ -std=c++17 factor.cpp -o factor
  jarry@jarrys-MacBook-Pro factor % ./factor
  the number is 1796
  2 * 2 * 449 = 1796
*/