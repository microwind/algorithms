/**
 * @desc
 * 质因数分解c语言示例
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

  int num = 20;
  int len = num / 2;
  int *result = factorize(num, len);
  for  (int i = 0; i < len; i++) {
    if (result[i] <= 0) {
      break;
    }
    if (i != 0) {
      printf(" *");
    }
    printf(" %d", result[i]);
  }
  printf(" = %d", num);
}

/**
  jarry@jarrys-MacBook-Pro factor % gcc --version
  Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/4.2.1
  Apple clang version 12.0.0 (clang-1200.0.32.21)
  Target: x86_64-apple-darwin19.6.0
  Thread model: posix
  InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
  jarry@jarrys-MacBook-Pro factor % gcc factor.c -o factor
  jarry@jarrys-MacBook-Pro factor % ./factor 
  2 * 2 * 5 = 20%   
*/