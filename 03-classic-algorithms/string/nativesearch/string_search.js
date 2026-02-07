/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
function find(str, text) {
  var i, textLen = text.length
  var j, strLen = str.length
  // 两个循环，外层是被查找文本，内循环是查找字符串
  for (i = 0; i < textLen; i++) {

    for (j = 0; j < strLen; j++) {
      // 当遇到不有不相等时，跳出从文本下一个字符开始比较
      if (str[j] !== text[i + j]) {
        break
      }

    }
    // 如果查找字符串全部比较完成表示成功匹配
    if (j === strLen) {
      return i
    }

  }

  // 如果文本全部比较完还是没有查找到，则返回-1
  return -1
}


function find2(str, text) {
  const textLen = text.length
  const strLen = str.length
  // 两个循环，外层是被查找文本，内循环是查找字符串
  for (let i = 0, l = textLen - strLen + 1; i < l; i++) {
    let j = 0
    for (; j < strLen; j++) {
      // 循环长度优化+剩余字符优化
      // 如果被查找的长度比要查找的还少，则可以返回-1
      if (textLen - i < strLen - j) {
        // console.log('less length', i, j)
        return -1
      }
      // 当遇到不有不相等时，跳出从文本下一个字符开始比较
      if (str[j] !== text[i + j]) {
        break
      }

    }
    // 如果查找字符串全部比较完成表示成功匹配
    if (j === strLen) {
      return i
    }

  }

  // 如果文本全部比较完还是没有查找到，则返回-1
  return -1
}

console.time('time')
var result = find('ABC', 'AABABC') // 3
console.log("find('ABC', 'AABABC')", result)
result = find('AAB', 'AAAABC') // 2
console.log("find('AAB', 'AAAABC')", result)
result = find('ABC', 'AABAC') // -1
console.log("find('ABC', 'AABAC')", result)
console.timeEnd('time')

console.time('time2')
result = find2('ABC', 'AABABC') // 3
console.log("find2('ABC', 'AABABC')", result)
result = find2('AAB', 'AAAABC') // 2
console.log("find2('AAB', 'AAAABC')", result)
result = find2('ABC', 'AABAC') // -1
console.log("find2('ABC', 'AABAC')", result)
console.timeEnd('time2')

/**
jarry@jarrys-MacBook-Pro nativesearch % node string_search.js
find('ABC', 'AABABC') 3
find('AAB', 'AAAABC') 2
find('ABC', 'AABAC') -1
time: 4.573ms
find2('ABC', 'AABABC') 3
find2('AAB', 'AAAABC') 2
find2('ABC', 'AABAC') -1
time2: 0.512ms
 */