/**
 * @desc
 * 质因数分解c语言示例
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

/* 注释版
int *factorize(int num, int len) {
  int *result = (int *)malloc(len * sizeof(int));
  int i = 2;
  int result_idx = 0;
  // i的平方小于该数字，说明可以继续分解
  while (i * i <= num) {
    // 如果可以被i整除，则说明i是因数，继续以i分解
    while (num % i == 0) {
      result[result_idx] = i;
      // 每分解一次，原分解数就赋值为除以i的结果
      num /= i;
      // 每增加一个因数，数组下标右移，以便追加到结果中
      result_idx++;
    }
    // 当无法被i整除时，i递增继续分解
    i++;
  }
  // 最后的分解数如果大于1说明上一次整除不是自身，即是最后的因素
  if (num > 1) {
    result[result_idx]  = num;
  }
  return result;
}
*/

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