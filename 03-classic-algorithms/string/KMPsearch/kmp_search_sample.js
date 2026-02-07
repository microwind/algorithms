/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 提取模式串的部分匹配值，构建部分匹配表，KMP通过此表来减少比较步骤。
 * @param {string} pattern 模式串
 * @returns {Array} 部分匹配表
 */
function makePMT(pattern) {
  const len = pattern.length
  const pmt = new Array(len).fill(0)
  for (let i = 0; i < len; i++) {
    // 递增取出全部模式字串。子串从第1个字符开始，每次递增1个字符，直到全部完成。
    const subPattern = pattern.slice(0, i + 1)
    let j = 0
    // 共有成员长度，即部分匹配最大值
    // 将当前项与后项逐一比较
    let pmtValue = 0
    const prefixArr = []
    const postfixArr = []
    while (j < i) {
      // 遍历同时得到每一个前后缀，自前往后获得每一个前缀
      let prefix = subPattern.substring(0, j + 1)
      // 自后往前获得当前的后缀
      let postfix = subPattern.substring(i - j, i + 1)
      prefixArr.push(prefix)
      postfixArr.push(postfix)
      // 比较是否有共同项，如果有则更新匹配值，如果遇到更大的则更新最大值
      if (prefix === postfix && prefix.length > pmtValue) {
        pmtValue = prefix.length
      }
      j++
    }
    // 将部分匹配最大值更新到对应位置中
    pmt[i] = pmtValue
    console.log(i, subPattern, ' | ', prefixArr, ' | ', postfixArr, ' | ', pmtValue)
  }
  console.log('makePMT() pmt:', pmt)
  return pmt
}

function makePMT2(pattern) {
  const pmt = new Array(pattern.length).fill(0)
  // 用于记录当前已经匹配的前缀长度
  let pmtValue = 0
  let len = pattern.length
  // 从模式串的第二个字符开始遍历，因为PMT[0]总是0  
  for (let i = 1; i < len; i++) {
    // 当前字符与已匹配前缀的下一个字符不匹配 
    while (pmtValue > 0 && pattern[i] !== pattern[pmtValue]) {
      // 使用PMT中前一个位置的值来回溯，更新pmtValue为更短的前缀长度  
      pmtValue = pmt[pmtValue - 1]
    }

    // 如果当前字符与已匹配的前缀的下一个字符匹配  
    if (pattern[i] === pattern[pmtValue]) {
      // 增加pmtValue的值，表示前缀长度增加  
      pmtValue++
    }

    // 更新PMT数组
    pmt[i] = pmtValue

    // 以下为打印前后缀测试[可选]
    const subPattern = pattern.slice(0, i + 1)
    const prefixArr = []
    const postfixArr = []
    let j = 0
    while (j < i) {
      const prefix = pattern.slice(0, j + 1)
      const postfix = subPattern.slice(i - j, i + 1)
      prefixArr.push(prefix)
      postfixArr.push(postfix)
      j++
    }
    console.log(i, subPattern, ' | ', prefixArr, ' | ', postfixArr, ' | ', pmtValue)
  }

  console.log('makePMT2 pmt:', pmt)
  return pmt
}

/**
 * KMP搜索，是朴素搜索的升级版，通过构建部分匹配表来跳过公共部分，从而减少比较步骤。
 * @param {string} pattern 模式串，要查找的串
 * @param {string} text 目标文本，搜索范围
 */
function kmpSearch(pattern, text) {
  // 输出原始的模式串和文本  
  console.log(' pattern:', pattern, 'text:', text)

  // 用于存储匹配到的模式串在文本中的起始位置  
  const matches = []

  // 生成模式串的部分匹配表
  // const pmtTable = makePMT(pattern)
  const pmtTable = makePMT2(pattern)

  // j 是模式串的当前匹配位置  
  let j = 0

  // 输出生成的部分匹配表  
  console.log('根据模式串获取pmtTable:', pmtTable)

  // 遍历文本  
  for (let i = 0; i < text.length; i++) {
    // 当文本字符与模式串字符不匹配，并且模式串的当前匹配位置不是0时  
    // 回到模式串的部分匹配表的前一个位置继续匹配  
    while (j > 0 && text[i] !== pattern[j]) {
      j = pmtTable[j - 1]
    }

    // 如果文本字符与模式串字符匹配  
    if (text[i] === pattern[j]) {
      // 继续匹配模式串的下一个字符  
      j++
    }

    // 如果模式串的所有字符都已匹配成功  
    if (j === pattern.length) {
      // 将匹配到的模式串在文本中的起始位置添加到结果数组中  
      matches.push(i - j + 1)

      // 根据部分匹配表，调整模式串的当前匹配位置  
      j = pmtTable[j - 1]
    }
  }

  console.log('匹配结果：', matches)

  // 返回匹配结果  
  return matches
}

/** 测试验证 */
;
(function () {
  console.log('KMP搜索测试：')
  const pattern = 'ABCABAB'
  console.log('pattern:', pattern)
  makePMT(pattern)
  makePMT2(pattern)
  // kmpSearch(pattern, 'AAABABCABABCDABABCABAB') // [4, 15]
  // kmpSearch(pattern, 'ABAAABABCABABCDABABCABAB') // [6, 17]
})()