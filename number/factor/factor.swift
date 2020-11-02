import Foundation

/**
 * @desc
 * 质因数分解swift语言示例
 */

// 引用传递
//  func factorize(_ num: inout Int) -> [String] {

// 值传递
 func factorize(num: Int) -> [String] {
  var result = [String]()
  var num = num
  var i = 2
  while (i * i <= num) {
    while (num % i == 0) {
      result.append(String(i))
      num = num / i
    }
    i += 1
  }
  if (num > 1) {
    result.append(String(num))
  }
  return result
}

/* test */
var num = 20
print(num)

func printFactor() {
  // 引用传递
  // let result = factorize(&num)

  // 值传递 
  let result = factorize(num: num)
  let flag = " * "
  print(result.joined(separator: flag))
}
printFactor()

print(num)

/**
  jarry@jarrys-MacBook-Pro algorithms % cd number/factor
  jarry@jarrys-MacBook-Pro factor % swift --version
  Apple Swift version 5.3 (swiftlang-1200.0.29.2 clang-1200.0.30.1)
  Target: x86_64-apple-darwin19.6.0
  jarry@jarrys-MacBook-Pro factor % swift factor.swift 
  20
  2 * 2 * 5
  20
*/

